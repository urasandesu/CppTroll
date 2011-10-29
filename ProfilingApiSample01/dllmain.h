// dllmain.h : モジュール クラスの宣言

class CProfilingApiSample01Module : public CAtlDllModuleT< CProfilingApiSample01Module >
{
public :
    DECLARE_LIBID(LIBID_ProfilingApiSample01Lib)
    DECLARE_REGISTRY_APPID_RESOURCEID(IDR_PROFILINGAPISAMPLE01, "{95F45898-588E-4B15-8FD1-D96847890F67}")
};

extern class CProfilingApiSample01Module _AtlModule;
