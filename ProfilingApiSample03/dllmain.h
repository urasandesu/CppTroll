// dllmain.h : モジュール クラスの宣言

class CProfilingApiSample03Module : public CAtlDllModuleT< CProfilingApiSample03Module >
{
public :
	DECLARE_LIBID(LIBID_ProfilingApiSample03Lib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_PROFILINGAPISAMPLE03, "{AE4C4557-84C1-4BB9-94F5-FE3BC0A05BA2}")
};

extern class CProfilingApiSample03Module _AtlModule;
