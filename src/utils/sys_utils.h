/**
 * 死人
 * siren186@163.com
 * Date: 2014-05-06
 */

#ifndef __SYS_UTILS__
#define __SYS_UTILS__

#include <windows.h>

namespace sr
{
    enum SystemMode
    {
        SM_Error,
        SM_NormalMode,
        SM_SafeMode,
        SM_SafeWithNetworkMode,
    };

    SystemMode GetSysMode()
    {
        int nMode = ::GetSystemMetrics(SM_CLEANBOOT);
        switch (nMode)
        {
        case 0: return SM_NormalMode;
        case 1: return SM_SafeMode;
        case 2: return SM_SafeWithNetworkMode;
        }
        return SM_Error;
    }

    enum OsVersion
    {
        OS_Error,
        OS_Win9X,
        OS_WinMe,
        OS_Win2000,
        OS_WinNT,
        OS_Win2003,
        OS_WinXp,
        OS_Vista,
        OS_Win7,
        OS_Win2008,
        OS_Win8,
    };

    OsVersion GetOsVer()
    {
        OsVersion emOsVer = OS_Error;

        OSVERSIONINFOEX osvi;
        ZeroMemory(&osvi, sizeof(OSVERSIONINFOEX));
        osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
        BOOL bRet = ::GetVersionEx((OSVERSIONINFO*)&osvi);

        if (bRet)
        {
            switch (osvi.dwPlatformId)
            {
            case VER_PLATFORM_WIN32_NT:
                if (6 == osvi.dwMajorVersion && 1 == osvi.dwMinorVersion)
                {
                    emOsVer = (osvi.wProductType == VER_NT_WORKSTATION) ? OS_Win7 : OS_Win2008;
                }
                else if (5 == osvi.dwMajorVersion && 1 == osvi.dwMinorVersion)
                {
                    emOsVer = OS_WinXp;
                }
                else if (6 == osvi.dwMajorVersion && 2 == osvi.dwMinorVersion)
                {
                    emOsVer = OS_Win8;
                }
                else if (6 == osvi.dwMajorVersion && 3 == osvi.dwMinorVersion)
                {
                    emOsVer = OS_Win8;
                }
                else if (6 == osvi.dwMajorVersion && 0 == osvi.dwMinorVersion)
                {
                    emOsVer = (osvi.wProductType == VER_NT_WORKSTATION) ? OS_Vista : OS_Win2008;
                }
                else if (osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 2)
                {
                    emOsVer = OS_Win2003;
                }
                else if (osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 0)
                {
                    emOsVer = OS_Win2000;
                }
                break;
            case VER_PLATFORM_WIN32_WINDOWS:
                if (((osvi.dwBuildNumber >> 16) & 0x0000FFFF) < 0x045A)
                {
                    emOsVer = OS_Win9X;
                }
                else
                {
                    emOsVer = OS_WinMe;
                }
                break;
            }
        }

        return emOsVer;
    }

    VOID SafeGetNativeSystemInfo(__out LPSYSTEM_INFO lpSystemInfo)
    {
        if (NULL == lpSystemInfo)
            return;

        typedef VOID (WINAPI *LPFN_GetNativeSystemInfo)(LPSYSTEM_INFO lpSysInfo);
        LPFN_GetNativeSystemInfo fnGetNativeSystemInfo = (LPFN_GetNativeSystemInfo)GetProcAddress(GetModuleHandleW(L"kernel32"), "GetNativeSystemInfo");;
        if (NULL != fnGetNativeSystemInfo)
        {
            fnGetNativeSystemInfo(lpSystemInfo);
        }
        else
        {
            GetSystemInfo(lpSystemInfo);
        }
    }

    int GetOsBits()
    {
        SYSTEM_INFO si;
        SafeGetNativeSystemInfo(&si);
        if (PROCESSOR_ARCHITECTURE_IA64     == si.wProcessorArchitecture ||
            PROCESSOR_ARCHITECTURE_AMD64    == si.wProcessorArchitecture ||
            PROCESSOR_ARCHITECTURE_ALPHA64  == si.wProcessorArchitecture)
        {
            return 64;
        }
        return 32;
    }

    BOOL Is64BitOs()
    {
        return (64 == GetOsBits());
    }

} ///> end of namespace sr

#endif ///> __SYS_UTILS__