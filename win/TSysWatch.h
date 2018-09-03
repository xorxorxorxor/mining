// TSysWatch.h: interface for the CTSysWatch class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TSYSWATCH_H__6BA6A002_1447_44D9_A401_69C507908B09__INCLUDED_)
#define AFX_TSYSWATCH_H__6BA6A002_1447_44D9_A401_69C507908B09__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <windows.h>
#include "Iphlpapi.h"

//Net interface adapter
typedef struct _NETINTERFACE_INFO
{
	DWORD dwIndex; 
	/*
	#define MIB_IF_TYPE_OTHER               1
	#define MIB_IF_TYPE_ETHERNET            6
	#define MIB_IF_TYPE_TOKENRING           9
	#define MIB_IF_TYPE_FDDI                15
	#define MIB_IF_TYPE_PPP                 23
	#define MIB_IF_TYPE_LOOPBACK            24
	#define MIB_IF_TYPE_SLIP                28
	*/
	DWORD dwType;
	BYTE bDescr[MAXLEN_IFDESCR];
}NETINTERFACE_INFO, * LPNETINTERFACE_INFO;

typedef struct _NETADAPTER_FLUX
{
	float fInCurrentFlux;
	float fInAverageFlux;
	float fInMaxFlux;

	float fOutCurrentFlux;
	float fOutAverageFlux;
	float fOutMaxFlux;
}NETADAPTER_FLUX, * LPNETADAPTER_FLUX;

typedef struct _ADAPTER_TABLE
{
	DWORD dwOldInOctets;
	float fInAverageFlux;
	float fInMaxFlux;
	
	DWORD dwOldOutOctets;
	float fOutAverageFlux;
	float fOutMaxFlux;
	
	DWORD dwTimes;
}ADAPTER_TABLE, * PADAPTER_TABLE;
//System memory
typedef struct _MEM_STATUS 
{
    DWORD dwMemoryLoad;    // percent of memory in use 
    DWORD dwTotalPhys;     // bytes of physical memory 
    DWORD dwAvailPhys;     // free physical memory bytes 
    DWORD dwTotalPageFile; // bytes of paging file 
    DWORD dwAvailPageFile; // free bytes of paging file 
    DWORD dwTotalVirtual;  // user bytes of address space 
    DWORD dwAvailVirtual;  // free user bytes 
}MEM_STATUS, * LPMEM_STATUS;


//System processor
typedef struct _PROCESSOR_INFO
{
	  DWORD dwNumberOfProcessors;  
	  /*
	  #define PROCESSOR_INTEL_386     386
	  #define PROCESSOR_INTEL_486     486
	  #define PROCESSOR_INTEL_PENTIUM 586
	  #define PROCESSOR_INTEL_IA64    2200
	  #define PROCESSOR_AMD_X8664     8664*/
	  DWORD dwProcessorType;
}PROCESSOR_INFO, * LPPROCESSOR_INFO;


typedef struct _PROCESSOR_USAGE
{
	double dbProcessorUsage;
	double dbKernelUsage;
}PROCESSOR_USAGE, * LPPROCESSOR_USAGE;

//Computer processor usage
#define SystemBasicInformation       0
#define SystemPerformanceInformation 2
#define SystemTimeInformation        3
#define SystemProcessorPerformanceInformation   8

#define Li2Double(x) ((double)((x).HighPart) * 4.294967296E9 + (double)((x).LowPart))

typedef struct
{
    DWORD dwUnknown1;
    ULONG uKeMaximumIncrement;
    ULONG uPageSize;
    ULONG uMmNumberOfPhysicalPages;
    ULONG uMmLowestPhysicalPage;
    ULONG uMmHighestPhysicalPage;
    ULONG uAllocationGranularity;
    PVOID pLowestUserAddress;
    PVOID pMmHighestUserAddress;
    ULONG uKeActiveProcessors;
    BYTE bKeNumberProcessors;
    BYTE bUnknown2;
    WORD wUnknown3;
} SYSTEM_BASIC_INFORMATION;

typedef struct
{
    LARGE_INTEGER liIdleTime;
    DWORD dwSpare[76];
} SYSTEM_PERFORMANCE_INFORMATION;

typedef struct
_SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION 
{
    LARGE_INTEGER IdleTime;
    LARGE_INTEGER KernelTime;
    LARGE_INTEGER UserTime;
    LARGE_INTEGER Reserved1[2];
    ULONG Reserved2;
}SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION, * PSYSTEM_PROCESSOR_PERFORMANCE_INFORMATION;

typedef struct
{
    LARGE_INTEGER liKeBootTime;
    LARGE_INTEGER liKeSystemTime;
    LARGE_INTEGER liExpTimeZoneBias;
    ULONG uCurrentTimeZoneId;
    DWORD dwReserved;
} SYSTEM_TIME_INFORMATION;

typedef LONG (WINAPI *PROCNTQSI)(UINT,PVOID,ULONG,PULONG);

#define NANO 1000000000 //power(10,9)

typedef struct _PROCESSORTIME_INFO
{
    LARGE_INTEGER liOldIdleTime;
	LARGE_INTEGER liOldUserTime;
    LARGE_INTEGER liOldSystemTime;
}PROCESSORTIME_INFO, * PPROCESSORTIME_INFO;

class CTSysWatch  
{
public:
	CTSysWatch();
	virtual ~CTSysWatch();
	//获取cpu信息(个数、类型)
	BOOL GetProcessorInfo(LPPROCESSOR_INFO lpProcessorInfo);
	/*
	获取cpu利用率
	lpUsage: [out] cpu 利用率
	nIndex:  [in]  cpu 索引*/
	BOOL GetProcessorUsage(LPPROCESSOR_USAGE lpUsage,int nIndex = 0); //ntquerysysteminformation

	//获取内存信息
	BOOL GetMemStatus(LPMEM_STATUS lpStatus);//GlobalMemoryStatusEx

	/*
	 获取网络接口信息(标示、类型、描述)
	 pIfInfo: [out] 接口信息
	 pdwCount: [in out] 网络接口个数
	 return : 0 success,1 没有提供足够的buffer pdwCount返回实际接口个数
	          -1 失败
	 */
	int GetNetAdapterInfo(LPNETINTERFACE_INFO pIfInfo,PDWORD pdwCount);

	/*
	 获取网络流量
	 pAdapterFlux:[out] 流量统计结果
	 nIndex:[in] 网络接口唯一标示,从网络接口信息得到
	 */
	BOOL GetNetAdapterFlux(LPNETADAPTER_FLUX pAdapterFlux,int nIndex = 0); //GetIfTable

	//获取上行流量
	bool GetBandOut(DWORD &dwBandoutBytes);
private:
	PADAPTER_TABLE m_parrAdapterTable;
	PMIB_IFTABLE m_ifTable;
	DWORD m_dwTableSize;
	
	PROCESSOR_INFO m_ProcessBaseInfo;
	PPROCESSORTIME_INFO m_pProcessorOldTime;
	PSYSTEM_PROCESSOR_PERFORMANCE_INFORMATION m_pSysProcessorInfo;

	DWORD m_dwStartMiSeconds;
	BOOL bFirst;
};

#endif // !defined(AFX_TSYSWATCH_H__6BA6A002_1447_44D9_A401_69C507908B09__INCLUDED_)

