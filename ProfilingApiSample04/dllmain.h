// dllmain.h : モジュール クラスの宣言

class CProfilingApiSample04Module : public ATL::CAtlDllModuleT< CProfilingApiSample04Module >
{
public :
	DECLARE_LIBID(LIBID_ProfilingApiSample04Lib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_PROFILINGAPISAMPLE04, "{B24AEBF6-29BC-493B-B464-CDEA4A3CF70D}")
};

extern class CProfilingApiSample04Module _AtlModule;
