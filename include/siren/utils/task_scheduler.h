/**
 * 死人
 * siren186@163.com
 * Date: 2014-05-06
 */
 
#ifndef __TASK_SCHEDULER_H__
#define __TASK_SCHEDULER_H__

#include <initguid.h>
#include <mstask.h>

namespace sr
{
    void _InitLogonTaskTrigger( TASK_TRIGGER &stTrigger )
    {
        ZeroMemory(&stTrigger, sizeof(TASK_TRIGGER));
        stTrigger.wBeginYear    = 1999;
        stTrigger.wBeginMonth   = 1;
        stTrigger.wBeginDay     = 1;
        stTrigger.cbTriggerSize = sizeof(TASK_TRIGGER); 
        stTrigger.wStartHour    = 13;
        stTrigger.TriggerType   = TASK_EVENT_TRIGGER_AT_LOGON; ///> TASK_EVENT_TRIGGER_AT_SYSTEMSTART;
        stTrigger.Type.Daily.DaysInterval = 1;
    }

    BOOL CreateTaskScheduler(
        LPCTSTR         lpTaskName,
        LPCTSTR         lpAppFilePath,
        DWORD           dwTaskFlag,
        TASK_TRIGGER    &stTrigger,
        LPCTSTR         lpAccountName,
        LPCTSTR         lpPassword)
    {
        BOOL bReturn = FALSE;
        ::CoInitialize(NULL);

        if (!lpTaskName || !lpAppFilePath || !lpAccountName)
            goto Exit0;

        {
            CComPtr<ITaskScheduler> pITS;
            CComPtr<ITask>          pITask;
            CComPtr<ITaskTrigger>   pITaskTrigger;
            CComPtr<IPersistFile>   pIPersistFile;

            HRESULT hr = ::CoCreateInstance(CLSID_CTaskScheduler, NULL, CLSCTX_INPROC_SERVER, IID_ITaskScheduler, (void **) &pITS);
            if (FAILED(hr))
                goto Exit0;

            hr = pITS->NewWorkItem(lpTaskName, CLSID_CTask, IID_ITask, (IUnknown**)&pITask);
            if (FAILED(hr))
                goto Exit0;

            hr = pITask->SetApplicationName(lpAppFilePath);
            if (FAILED(hr))
                goto Exit0;

            hr = pITask->SetFlags(dwTaskFlag);
            if (FAILED(hr))
                goto Exit0;

            hr = pITask->SetAccountInformation(lpAccountName, lpPassword);
            if (FAILED(hr))
                goto Exit0;

            WORD nNewTrigger;
            hr = pITask->CreateTrigger(&nNewTrigger, &pITaskTrigger);
            if (FAILED(hr))
                goto Exit0;

            hr = pITaskTrigger->SetTrigger(&stTrigger);
            if (FAILED(hr))
                goto Exit0;

            hr = pITask->QueryInterface(IID_IPersistFile, (void **)&pIPersistFile);
            if (FAILED(hr))
                goto Exit0;

            hr = pIPersistFile->Save(NULL, TRUE);
            if (FAILED(hr))
                goto Exit0;
        }

        bReturn = TRUE;

Exit0:
        ::CoUninitialize();
        return bReturn;
    }

    BOOL DeleteTaskScheduler( LPCTSTR lpTaskName )
    {
        BOOL bReturn = FALSE;
        ::CoInitialize(NULL);

        if (!lpTaskName)
            goto Exit0;

        {
            CComPtr<ITaskScheduler> pITS;
            HRESULT hr = ::CoCreateInstance(CLSID_CTaskScheduler, NULL, CLSCTX_INPROC_SERVER, IID_ITaskScheduler, (void **) &pITS);
            if (FAILED(hr))
                goto Exit0;

            hr = pITS->Delete(lpTaskName);
            if (FAILED(hr))
                goto Exit0;
        }

        bReturn = TRUE;

Exit0:
        ::CoUninitialize();
        return bReturn;
    }

    BOOL CreateSimpleLogonTaskScheduler( LPCTSTR lpTaskName, LPCTSTR lpAppFilePath )
    {
        if (!lpTaskName || !lpAppFilePath)
            return FALSE;

        TASK_TRIGGER stTrigger;
        _InitLogonTaskTrigger(stTrigger);

        return CreateTaskScheduler(lpTaskName, lpAppFilePath, TASK_FLAG_RUN_ONLY_IF_LOGGED_ON, stTrigger, L"", NULL);
    }

} ///> end of namespace sr

#endif ///> __TASK_SCHEDULER_H__