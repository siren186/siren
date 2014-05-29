/**
 * À¿»À
 * siren186@163.com
 * Date: 2014-05-06
 */

#ifndef __FILE_UTILS_H__
#define __FILE_UTILS_H__

#include <atlstr.h>
#include <atlconv.h> 
#include <shobjidl.h>
#include <shlguid.h>
#include <atlcomcli.h>
#include <Shlwapi.h>

namespace sr
{
    BOOL CreateLnkFile(
        LPCTSTR lpLnkFilePath,
        LPCTSTR lpDstFilePath,
        LPCTSTR lpArgs = NULL,
        LPCTSTR lpDescription = NULL,
        WORD    wVirtualKeyCode = 0,
        LPCTSTR lpIconPath = NULL,
        int     nIcon = 1,
        int     nShowCmd = -1
        )
    {
        if (!lpLnkFilePath || !lpDstFilePath)
            return FALSE;

        BOOL bReturn = FALSE;
        ::CoInitialize(NULL);

        CComPtr<IShellLink> pShellLink;
        HRESULT hr = ::CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLink, (LPVOID *)&pShellLink);
        if (SUCCEEDED(hr))
        {
            pShellLink->SetPath(lpDstFilePath);

            WCHAR szWorkDir[MAX_PATH + 1] = {0};
            wcsncpy_s(szWorkDir, MAX_PATH, lpDstFilePath, MAX_PATH);
            if (!::PathRemoveFileSpec(szWorkDir))
            {
                pShellLink->SetWorkingDirectory(szWorkDir); 
            }

            if (lpArgs)          pShellLink->SetArguments(lpArgs);
            if (lpDescription)   pShellLink->SetDescription(lpDescription);
            if (0 != wVirtualKeyCode) pShellLink->SetHotkey(wVirtualKeyCode);
            if (lpIconPath)      pShellLink->SetIconLocation(lpIconPath, nIcon);
            if (-1 != nShowCmd)  pShellLink->SetShowCmd(nShowCmd);

            CComPtr<IPersistFile> pPersistFile;
            hr = pShellLink->QueryInterface(IID_IPersistFile, (LPVOID *)&pPersistFile );
            if (SUCCEEDED(hr))
            {
                pPersistFile->Save(lpLnkFilePath, TRUE);
                bReturn = TRUE;
            }
        }

        ::CoUninitialize(); 
        return bReturn;
    }

    BOOL GetPathFromLnkFile( LPCTSTR lpLnkFilePath, LPTSTR lpDstPath, int cchDstPath )
    {
        bool bReturn = FALSE;

        ::CoInitialize(NULL);

        CComPtr<IPersistFile> pPersistFile;
        HRESULT hr = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IPersistFile, (void**)(&pPersistFile));
        if(SUCCEEDED(hr))
        {
            CComPtr<IShellLink> pShellLink;
            hr = pPersistFile->QueryInterface(IID_IShellLink, (void**)(&pShellLink));
            if(SUCCEEDED(hr))
            {
                hr = pPersistFile->Load(lpLnkFilePath, STGM_READ);
                if(SUCCEEDED(hr))
                {
                    hr = pShellLink->GetPath(lpDstPath, cchDstPath, NULL, 0);
                    if(SUCCEEDED(hr))
                    {
                        bReturn = TRUE;
                    }
                }
            }
        }

        CoUninitialize();
        return bReturn;
    }

    BOOL DeleteFolder(LPCTSTR lpFolder)
    {
        if (!::PathFileExists(lpFolder))
            return FALSE;

        CString sFolder = lpFolder;
        sFolder.AppendChar(L'\0');

        SHFILEOPSTRUCT FileOp; 
        ZeroMemory((void*)&FileOp,sizeof(SHFILEOPSTRUCT));

        FileOp.fFlags = FOF_NOCONFIRMATION; 
        FileOp.hNameMappings = NULL; 
        FileOp.hwnd = NULL; 
        FileOp.lpszProgressTitle = NULL; 
        FileOp.pFrom = sFolder; 
        FileOp.pTo = NULL; 
        FileOp.wFunc = FO_DELETE; 

        return SHFileOperation(&FileOp) == 0;
    }

    BOOL CopyFolder(LPCTSTR lpSrcFolder, LPCTSTR lpDstFolder)
    {
        if (!lpSrcFolder || !lpDstFolder)
            return FALSE;

        CString sSrcFolder = lpSrcFolder;
        sSrcFolder.AppendChar(L'\0');
        CString sDstFolder = lpDstFolder;
        sDstFolder.AppendChar(L'\0');

        SHFILEOPSTRUCT FileOp; 
        ZeroMemory((void*)&FileOp,sizeof(SHFILEOPSTRUCT));

        FileOp.fFlags = FOF_NOCONFIRMATION ; 
        FileOp.hNameMappings = NULL; 
        FileOp.hwnd = NULL; 
        FileOp.lpszProgressTitle = NULL; 
        FileOp.pFrom = sSrcFolder; 
        FileOp.pTo = sDstFolder; 
        FileOp.wFunc = FO_COPY; 

        return SHFileOperation(&FileOp) == 0;
    }

} ///> end of namespace sr

#endif ///> __FILE_UTILS_H__