// dllmain.h : モジュール クラスの宣言

class CMetaDataApiSample01Module : public CAtlDllModuleT< CMetaDataApiSample01Module >
{
public :
	DECLARE_LIBID(LIBID_MetaDataApiSample01Lib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_METADATAAPISAMPLE01, "{9C68C84B-183A-450F-9BA0-1123C1E19566}")
};

extern class CMetaDataApiSample01Module _AtlModule;
