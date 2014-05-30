#ifndef __MSGBOX_H__
#define __MSGBOX_H__

#include <WtsApi32.h>

namespace sr
{
    ///> windows�����е���.�����ڵ��Է���.
    void SvcMsgBox()
    {
        DWORD physicalConsoleSession = WTSGetActiveConsoleSessionId();

        if (0xFFFFFFFF != physicalConsoleSession)
        {
            LPWSTR title = L"hehe";
            DWORD titleLength = static_cast<DWORD>(wcslen(title) * sizeof(*title));
            LPWSTR message = L"hehehe";
            DWORD messageLength = static_cast<DWORD>(wcslen(message) * sizeof(*message));
            DWORD response;
            WTSSendMessage(WTS_CURRENT_SERVER_HANDLE,
                physicalConsoleSession,
                title, titleLength,
                message, messageLength,
                MB_OK | MB_ICONINFORMATION,
                0,
                & response,
                TRUE);
        }
    }
}
#endif ///> __MSGBOX_H__