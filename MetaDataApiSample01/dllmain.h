// dllmain.h : ���W���[�� �N���X�̐錾
#pragma once

class CMetaDataApiSample01Module : public CAtlDllModuleT< CMetaDataApiSample01Module >
{
public :
	DECLARE_LIBID(LIBID_MetaDataApiSample01Lib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_METADATAAPISAMPLE01, "{4B5714CD-BED9-456B-BCE8-D38D55455050}")
};

extern class CMetaDataApiSample01Module _AtlModule;
