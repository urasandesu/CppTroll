// dllmain.h : モジュール クラスの宣言

class CSample03Module : public CAtlDllModuleT< CSample03Module >
{
public :
    DECLARE_LIBID(LIBID_Sample03Lib)
    DECLARE_REGISTRY_APPID_RESOURCEID(IDR_SAMPLE03, "{8E6093ED-678F-4F33-BF3D-9E7E4E366DD7}")
};

extern class CSample03Module _AtlModule;
