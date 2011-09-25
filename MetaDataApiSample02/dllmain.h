// dllmain.h : モジュール クラスの宣言

class CMetaDataApiSample02Module : public CAtlDllModuleT< CMetaDataApiSample02Module >
{
public :
	DECLARE_LIBID(LIBID_MetaDataApiSample02Lib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_METADATAAPISAMPLE02, "{9C314975-7846-4D10-8852-BED380D5157C}")
};

extern class CMetaDataApiSample02Module _AtlModule;
