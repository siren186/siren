/**
 * @file
 * @brief 文件操作相关函数集合
 * @version
 * @remarks
 * @date 2014-05-06
 * @bug
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
    /**
     * @brief 创建快捷方式
     * @param[in] lpLnkFilePath 快捷方式生成路径
     * @param[in] lpDstFilePath 指向的目标文件路径
     * @param[in] lpArgs 命令行参数
     * @param[in] lpDescription 描述
     * @param[in] wVirtualKeyCode 快捷键
     * @param[in] lpIconPath 图标路径
     * @param[in] nIcon 指定使用第几个图标
     * @param[in] nShowCmd 窗口显示方式
     * @return 成功返回TRUE, 失败返回FALSE
     * @see GetPathFromLnkFile
     */
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

    /**
     * @brief 获取快捷方式指向的目标文件路径
     * @param[in] lpLnkFilePath 快捷方式路径
     * @param[out] lpDstPath 用于存储目标路径的缓冲区
     * @param[in] cchDstPath 缓冲区长度
     * @return 成功返回TRUE, 失败返回FALSE
     * @see CreateLnkFile
     */
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

    /**
     * @brief 删除文件夹
     * @param[in] lpFolder 要删除的文件夹全路径
     * @return 成功返回TRUE, 失败返回FALSE
     * @see CopyFolder
     */
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

    /**
     * @brief 复制文件夹
     * @param[in] lpSrcFolder 源文件夹
     * @param[in] lpDstFolder 目标文件夹
     * @return 成功返回TRUE,失败返回FALSE
     * @see DeleteFolder
     */
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