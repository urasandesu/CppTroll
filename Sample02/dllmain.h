// dllmain.h : モジュール クラスの宣言

#pragma once

class CSample02Module : public CAtlDllModuleT< CSample02Module >
{
public :
	DECLARE_LIBID(LIBID_Sample02Lib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_SAMPLE02, "{DFAEFFB0-C529-4682-BE90-5FFF9FF06435}")
};

extern class CSample02Module _AtlModule;
