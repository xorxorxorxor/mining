// TSysWatch.cpp: implementation of the CTSysWatch class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TSysWatch.h"

// #ifdef _DEBUG
// #undef THIS_FILE
// static char THIS_FILE[]=__FILE__;
// #define DEBUG_NEW new(THIS_FILE, __LINE__) 
// #define new DEBUG_NEW
// #endif

#pragma comment(lib,"Iphlpapi.lib")

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTSysWatch::CTSysWatch()
{
	m_parrAdapterTable = NULL;
	m_ifTable = NULL;
	m_dwTableSize = 0;
	m_pProcessorOldTime = NULL;
	m_pSysProcessorInfo = NULL;
	bFirst = TRUE;
	m_dwStartMiSeconds = 0;
	memset(&m_ProcessBaseInfo,0,sizeof(m_ProcessBaseInfo));
}

CTSysWatch::~CTSysWatch()
{
	if(m_parrAdapterTable != NULL)
		delete [] m_parrAdapterTable; m_parrAdapterTable = NULL;
	if(m_ifTable != NULL)
		free(m_ifTable); m_ifTable = NULL;
	if(m_pProcessorOldTime != NULL)
		delete [] m_pProcessorOldTime; m_pProcessorOldTime = NULL;
	if(m_pSysProcessorInfo != NULL)
		delete [] m_pSysProcessorInfo; m_pSysProcessorInfo = NULL;
}

BOOL CTSysWatch::GetMemStatus(LPMEM_STATUS lpStatus)
{
	MEMORYSTATUS state;
	state.dwLength = sizeof(state);
	GlobalMemoryStatus(&state);	

	memcpy(lpStatus,&(state.dwMemoryLoad),sizeof(MEM_STATUS));
	return TRUE;		
}


BOOL CTSysWatch::GetProcessorInfo(LPPROCESSOR_INFO lpProcessorInfo)
{
	SYSTEM_INFO SystemInfo;
	GetSystemInfo(&SystemInfo);
	m_ProcessBaseInfo.dwNumberOfProcessors = SystemInfo.dwNumberOfProcessors;
	m_ProcessBaseInfo.dwProcessorType = SystemInfo.dwProcessorType;

	if(m_pProcessorOldTime == NULL)
	{
		m_pProcessorOldTime = new PROCESSORTIME_INFO[m_ProcessBaseInfo.dwNumberOfProcessors];
		memset(m_pProcessorOldTime,0,sizeof(PROCESSORTIME_INFO) * m_ProcessBaseInfo.dwNumberOfProcessors);
	}

	memcpy(lpProcessorInfo,&m_ProcessBaseInfo,sizeof(m_ProcessBaseInfo));
	return TRUE;
}

PROCNTQSI NtQuerySystemInformation = NULL;

BOOL CTSysWatch::GetProcessorUsage(LPPROCESSOR_USAGE lpUsage,int nIndex /* = 0 */)
{
    //SYSTEM_PERFORMANCE_INFORMATION SysPerfInfo;
    SYSTEM_TIME_INFORMATION SysTimeInfo;
    SYSTEM_BASIC_INFORMATION SysBaseInfo;
    double dbIdleTime;
	double dbUserTime;
    double dbSystemTime;
    LONG status = 0;

	if(NtQuerySystemInformation == NULL)
	{
		//从动态链节库中调用函数
		NtQuerySystemInformation = (PROCNTQSI)GetProcAddress(GetModuleHandle("ntdll"),"NtQuerySystemInformation");
		
		if (!NtQuerySystemInformation)  
			return FALSE;
	}
	
	// 获得系统中当前的处理器个数
	status = NtQuerySystemInformation(SystemBasicInformation,&SysBaseInfo,sizeof(SysBaseInfo),NULL);
	if (status != NO_ERROR)  
		return FALSE;
	
	if(nIndex >= (int)SysBaseInfo.bKeNumberProcessors)
		return FALSE;
	
	if(m_pProcessorOldTime == NULL)
	{
		m_pProcessorOldTime = new PROCESSORTIME_INFO[SysBaseInfo.bKeNumberProcessors];
		memset(m_pProcessorOldTime,0,sizeof(PROCESSORTIME_INFO) * SysBaseInfo.bKeNumberProcessors);
	}

	if(m_pSysProcessorInfo == NULL)
	{
		m_pSysProcessorInfo = new SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION[SysBaseInfo.bKeNumberProcessors];
		memset(m_pSysProcessorInfo,0,sizeof(SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION) * SysBaseInfo.bKeNumberProcessors);
	}
	// 获得新的cpu的空闲时间(idle time)
	status = NtQuerySystemInformation(SystemProcessorPerformanceInformation,m_pSysProcessorInfo,SysBaseInfo.bKeNumberProcessors * sizeof(SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION),NULL);
	if (status != NO_ERROR)  
		return FALSE;
	
    // 获得新的系统时间
    status = NtQuerySystemInformation(SystemTimeInformation,&SysTimeInfo,sizeof(SysTimeInfo),0);
    if (status!=NO_ERROR)   
		return FALSE;
	
	/*
    // 获得新的系统的空闲时间(idle time)
    status = NtQuerySystemInformation(SystemPerformanceInformation,&SysPerfInfo,sizeof(SysPerfInfo),NULL);
    if (status != NO_ERROR)  
		return FALSE;*/
	
    // if it's a first call - skip it
    if (m_pProcessorOldTime[nIndex].liOldIdleTime.QuadPart != 0)
    {
        // CurrentValue = NewValue - OldValue
        dbIdleTime = Li2Double(m_pSysProcessorInfo[nIndex].IdleTime) - Li2Double(m_pProcessorOldTime[nIndex].liOldIdleTime);
		dbUserTime = Li2Double(m_pSysProcessorInfo[nIndex].UserTime) - Li2Double(m_pProcessorOldTime[nIndex].liOldUserTime);
        dbSystemTime = Li2Double(SysTimeInfo.liKeSystemTime) - Li2Double(m_pProcessorOldTime[nIndex].liOldSystemTime);
		
        // CurrentCpuIdle = IdleTime / SystemTime
        dbIdleTime = dbIdleTime / dbSystemTime;
        
        // (CPU利用率的计算公式)CurrentCpuUsage% = 100 - (CurrentCpuIdle * 100) / NumberOfProcessors
        lpUsage->dbProcessorUsage = 100.0 - dbIdleTime * 100.0;
		dbUserTime = dbUserTime / dbSystemTime;
		dbUserTime = dbUserTime * 100.0;
		lpUsage->dbKernelUsage = lpUsage->dbProcessorUsage - dbUserTime;
    }
	
    // store new CPU's idle and system time
    m_pProcessorOldTime[nIndex].liOldIdleTime = m_pSysProcessorInfo[nIndex].IdleTime;
	m_pProcessorOldTime[nIndex].liOldUserTime = m_pSysProcessorInfo[nIndex].UserTime;
    m_pProcessorOldTime[nIndex].liOldSystemTime = SysTimeInfo.liKeSystemTime;	
	return TRUE;
}

BOOL CTSysWatch::GetNetAdapterFlux(LPNETADAPTER_FLUX pAdapterFlux, int nIndex /* = 0 */)
{
	// Declare and initialize variables
	DWORD dwRetVal = 0;
	
	// Make an initial call to GetIfTable to get the
	// necessary size into the dwSize variable
	if(m_ifTable == NULL)
	{
		if (GetIfTable(m_ifTable, &m_dwTableSize, 0) == ERROR_INSUFFICIENT_BUFFER) 
		{
			m_ifTable = (MIB_IFTABLE *) malloc (m_dwTableSize);
		}
	}
	
	// Make a second call to GetIfTable to get the 
	// actual data we want
	if ((dwRetVal = GetIfTable(m_ifTable, &m_dwTableSize, 0)) != NO_ERROR) 
	{
		return FALSE;
	}

	int nPos = 0;
	for(int i = 0; i < (int)m_ifTable->dwNumEntries; i++)
	{
		if(m_ifTable->table[i].dwIndex == (DWORD)nIndex)
		{
			nPos = i;
			break;
		}
	}
	if(nPos == (int)m_ifTable->dwNumEntries)
		return FALSE;

	if(m_parrAdapterTable == NULL)
	{
		m_parrAdapterTable = new ADAPTER_TABLE[m_ifTable->dwNumEntries];
		memset(m_parrAdapterTable,0,m_ifTable->dwNumEntries * sizeof(ADAPTER_TABLE));
		m_parrAdapterTable[nPos].dwOldInOctets = m_ifTable->table[nPos].dwInOctets;
		m_parrAdapterTable[nPos].dwOldOutOctets = m_ifTable->table[nPos].dwOutOctets;
		return TRUE;
	}
	
	//in
	pAdapterFlux->fInCurrentFlux = (float)((m_ifTable->table[nPos].dwInOctets - m_parrAdapterTable[nPos].dwOldInOctets) * 8.0/1000.0);
	m_parrAdapterTable[nPos].dwOldInOctets = m_ifTable->table[nPos].dwInOctets;

	if(pAdapterFlux->fInCurrentFlux > m_parrAdapterTable[nPos].fInMaxFlux) 
		m_parrAdapterTable[nPos].fInMaxFlux = pAdapterFlux->fInCurrentFlux;
	pAdapterFlux->fInMaxFlux = m_parrAdapterTable[nPos].fInMaxFlux;

	m_parrAdapterTable[nPos].fInAverageFlux = (float)(m_parrAdapterTable[nPos].fInAverageFlux + (pAdapterFlux->fInCurrentFlux - m_parrAdapterTable[nPos].fInAverageFlux) / (m_parrAdapterTable[nPos].dwTimes + 1.0));
	pAdapterFlux->fInAverageFlux = m_parrAdapterTable[nPos].fInAverageFlux;
	
	//out
	pAdapterFlux->fOutCurrentFlux = (float)((m_ifTable->table[nPos].dwOutOctets - m_parrAdapterTable[nPos].dwOldOutOctets) * 8.0/1000.0);
	m_parrAdapterTable[nPos].dwOldOutOctets = m_ifTable->table[nPos].dwOutOctets;
	
	if(pAdapterFlux->fOutCurrentFlux > m_parrAdapterTable[nPos].fOutMaxFlux) 
		m_parrAdapterTable[nPos].fOutMaxFlux = pAdapterFlux->fOutCurrentFlux;
	pAdapterFlux->fOutMaxFlux = m_parrAdapterTable[nPos].fOutMaxFlux;
	
	m_parrAdapterTable[nPos].fOutAverageFlux = (float)(m_parrAdapterTable[nPos].fOutAverageFlux + (pAdapterFlux->fOutCurrentFlux - m_parrAdapterTable[nPos].fOutAverageFlux) / (m_parrAdapterTable[nPos].dwTimes + 1.0));
	pAdapterFlux->fOutAverageFlux = m_parrAdapterTable[nPos].fOutAverageFlux;

	m_parrAdapterTable[nPos].dwTimes++;
	return TRUE;
}

//return 0 success
//return 1 ERROR_INSUFFICIENT_BUFFER
//return -1 failed
BOOL CTSysWatch::GetNetAdapterInfo(LPNETINTERFACE_INFO pIfInfo,PDWORD pdwCount)
{
	// Declare and initialize variables
	DWORD dwRetVal = 0;
	
	// Make an initial call to GetIfTable to get the
	// necessary size into the dwSize variable
	if(m_ifTable == NULL)
	{
		if (GetIfTable(m_ifTable, &m_dwTableSize, 0) == ERROR_INSUFFICIENT_BUFFER) 
		{
			m_ifTable = (MIB_IFTABLE *) malloc (m_dwTableSize);
		}
	}
	
	// Make a second call to GetIfTable to get the 
	// actual data we want
	if ((dwRetVal = GetIfTable(m_ifTable, &m_dwTableSize, 0)) != NO_ERROR) 
	{
		return -1;
	}	

	if(*pdwCount < m_ifTable->dwNumEntries)
	{
		*pdwCount = m_ifTable->dwNumEntries;
		return 1;
	}

	for(int i = 0; i < (int)m_ifTable->dwNumEntries; i++)
	{
		pIfInfo[i].dwIndex = m_ifTable->table[i].dwIndex;
		pIfInfo[i].dwType = m_ifTable->table[i].dwType;
		memcpy(pIfInfo[i].bDescr,m_ifTable->table[i].bDescr,MAXLEN_IFDESCR);
	}
	return 0;
}


DWORD dwLastIn  = 0;   
DWORD dwLastOut = 0;   
DWORD dwBandIn  = 0;   
DWORD dwBandOut = 0;   
DWORD dwLastIn1[5]  = {0, 0};
DWORD dwLastOut1[5] = {0, 0};
bool CTSysWatch::GetBandOut(DWORD &dwBandoutBytes)
{
	//获取网络适配器数量
	PMIB_IFTABLE pTable = NULL;   
	DWORD dwAdapters = 0;   
	ULONG uRetCode = GetIfTable(pTable, &dwAdapters, TRUE);   
	if (ERROR_NOT_SUPPORTED == uRetCode)   
	{
		return false;   
	}   
	else if (ERROR_INSUFFICIENT_BUFFER == uRetCode)   
	{   
		pTable = (PMIB_IFTABLE)new BYTE[dwAdapters];   
	}   
	
	//获取适配器数据
	DWORD dwRet = GetIfTable(pTable, &dwAdapters, TRUE);
	if (NO_ERROR != dwRet)
	{
		return false;
	}
	
	//解析适配器数据，获取流量信息
	DWORD dwInOctets = 0;   
	DWORD dwOutOctets = 0;   
	for (UINT i = 0; i < pTable->dwNumEntries; i++)   
	{//分别统计每个网卡数据   
		MIB_IFROW Row = pTable->table[i];   
		
		//获取下载数据
		DWORD dwBandIn1 = 0;
		if (dwLastIn1[i] <= 0)
			dwBandIn1 = 0;
		else
			dwBandIn1 = (Row.dwInOctets - dwLastIn1[i]);
		
		//获取上传数据
		DWORD dwBandOut1 = 0;
		if (dwLastOut1[i] <= 0)
			dwBandOut1 = 0;
		else
			dwBandOut1 = Row.dwOutOctets - dwLastOut1[i];
		
		dwLastIn1[i] = Row.dwInOctets;
		dwLastOut1[i] = Row.dwOutOctets;
		
		//统计总的数据
		dwInOctets += Row.dwInOctets;   
		dwOutOctets += Row.dwOutOctets;   
	}   
	
	dwBandIn = dwInOctets - dwLastIn;   
	dwBandOut = dwOutOctets - dwLastOut;   
	if (dwLastIn <= 0)   
	{   
		dwBandIn = 0;   
	}   
	else   
	{   
		dwBandIn = dwBandIn;   
	}   
	
	if (dwLastOut <= 0)   
	{   
		dwBandOut = 0;   
	}   
	else   
	{   
		dwBandOut = dwBandOut;   
	}   
	
	dwLastIn = dwInOctets;   
	dwLastOut = dwOutOctets;   
	
	dwBandoutBytes = dwBandOut;

	if(bFirst)
	{
		bFirst = FALSE;
	}
	else
	{
		DWORD dwMiSeconds = GetTickCount() - m_dwStartMiSeconds;
		dwMiSeconds = dwMiSeconds < 0 ? 1000 : dwMiSeconds;
		dwBandoutBytes = dwBandoutBytes * 1000 / dwMiSeconds;
	}

	m_dwStartMiSeconds = GetTickCount();
	delete  []pTable;   
	
	return true;
}
