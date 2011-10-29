// dllmain.h : モジュール クラスの宣言

class CProfilingApiSample02Module : public CAtlDllModuleT< CProfilingApiSample02Module >
{
public :
    DECLARE_LIBID(LIBID_ProfilingApiSample02Lib)
    DECLARE_REGISTRY_APPID_RESOURCEID(IDR_PROFILINGAPISAMPLE02, "{A275343C-4474-4C6E-B370-61F76995B8F6}")
};

extern class CProfilingApiSample02Module _AtlModule;
