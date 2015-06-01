#include "stdafx.h"
#include <string>
#include <set>

int KDemoLog( lua_State* L )
{
    CString sMsg = CA2W(lua_tostring(L, 1), CP_UTF8);
    OutputDebugString(sMsg + "\n");
    return 0;
}

int __stdcall KDemoGetTime( lua_State* L )
{
    lua_pushinteger(L, 2014);
    lua_pushinteger(L, 6);
    lua_pushinteger(L, 19);

    return 3;   
}

struct luaL_Reg KDemoApi[] = {
    {"Log",     KDemoLog},
    {"GetTime", KDemoGetTime},
    {NULL, NULL}
};

void OpenDemoLibs( lua_State* L )
{
    luaL_openlib(L, "KDemo", KDemoApi, 0);
}

class KLuaDemo
{
public:
    KLuaDemo() : m_luaL(NULL)
    {}

    BOOL Init()
    {
        if (!m_luaL)
        {
            m_luaL = luaL_newstate();   ///> 创建新的Lua虚拟机
            if (m_luaL)
            {
                luaL_openlibs(m_luaL);           ///> 打开Lua本身的库
                OpenDemoLibs(m_luaL);            ///> 打开我们的自定义库
            }
        }

        return NULL != m_luaL;
    }

    void UnInit()
    {
        if (m_luaL)
        {
            lua_close(m_luaL);
            m_luaL = NULL;
        }
    }

    int Play(const char* pLuaFile)
    {
        if (!pLuaFile || !m_luaL)
            goto Exit0;

        if (LUA_OK != luaL_loadfile(m_luaL, pLuaFile)) ///> 编译Lua文件, 在栈上形成一个匿名函数
            goto Exit0;

        lua_pcall(m_luaL, 0, 0, 0);     ///> 执行栈上的函数调用
        lua_getglobal(m_luaL, "main");  ///> 将一个全局变量放至栈顶(取一个变量的值)
        lua_pcall(m_luaL, 0, 0, 0);
Exit0:
        return 0;
    }

    int DoString(const char* buff, int sz)
    {
        int nRet = luaL_loadbuffer(m_luaL, buff, sz, NULL);
        if (nRet != 0)
        {
            return -1;
        }
        nRet = lua_pcall(m_luaL, 0, LUA_MULTRET, 0);
        if (nRet != 0)
        {
            const char* pszErrorMsg = lua_tostring(m_luaL, -1);
            return -2;
        }
        return 0;
    }

private:
    lua_State* m_luaL;
};

struct MyT
{
    std::string s;
    std::string s2;
    int n;

     bool operator < (const MyT &rhs) const
     {
         if ((s + s2) < (rhs.s + rhs.s2))
             return true;
         return false;
     }
};


int _cdecl main(int argc, char **argv)
{
    KLuaDemo lua;
    if (lua.Init())
    {
        lua.Play("c:\\test.lua");
        //lua.DoString(test_lua.c_str(), test_lua.size());
        lua.UnInit();
    }

    return 0;
}
