// dllmain.h : モジュール クラスの宣言

#pragma once

class CSample01Module : public CAtlDllModuleT< CSample01Module >
{
public :
    DECLARE_LIBID(LIBID_Sample01Lib)
    DECLARE_REGISTRY_APPID_RESOURCEID(IDR_SAMPLE01, "{B180E525-C6D2-4BA6-8728-BEA08F34B795}")
};

extern class CSample01Module _AtlModule;
