// MetaDataApiSample01Test.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"

//#define BOOST_TEST_NO_LIB
#include <boost/test/unit_test.hpp>

namespace {

    BOOST_AUTO_TEST_SUITE(MetaDataApiSample01TestSuite)

    // ildasm /out=hello.dasm /all /metadata=SCHEMA /metadata=HEAPS /metadata=CSV /source hello.exe
    // MetaDataApiSample01Test --log_level=test_suite --run_test=MetaDataApiSample01TestSuite/MetaDataApiSample01Test01
    BOOST_AUTO_TEST_CASE(MetaDataApiSample01Test01)
    {
        // 【テスト その 1】
        // ・一番単純な EXE を作成→実行まで。
        // ・標準出力に出力された文字列を検証する。
        // 
        IExeCreatorPtr pExeCreator;
        HRESULT hr = pExeCreator.CreateInstance(__uuidof(ExeCreator));
        BOOST_REQUIRE(SUCCEEDED(hr));

        try
        {
            hr = pExeCreator->Create(L"hello.exe");
            BOOST_REQUIRE(SUCCEEDED(hr));
        }
        catch (_com_error& e)
        {
            // 基本的にクライアントでは _com_error 例外が投げられるので hr 確認するの無駄っぽい・・・(/_;)
            BOOST_FAIL(e.Description());
        }
    }

    BOOST_AUTO_TEST_CASE(MetaDataApiSample01Test)
    {
        // 【テスト その 1】
        // ・一番単純な EXE を作成→実行まで。
        // ・標準出力に出力された文字列を検証する。
        // 
        HRESULT hr = E_FAIL;

        using std::cout;
        using std::endl;

#ifndef _MAC
#include <pshpack2.h>
#endif

        struct HINT_NAME_TABLE
        {
            WORD Hint;
            CHAR Name[MAX_PATH];
        };
        
#ifndef _MAC
#include <poppack.h>
#endif

#define RESERVED 0
        static const CHAR* const COR_EXE_MAIN = "_CorExeMain";
        cout << strnlen(COR_EXE_MAIN, MAX_PATH) << endl;
        

//size_t strnlen(
//   const char *str,
//   size_t numberOfElements 
//);

//void *_malloca( 
//   size_t size 
//);

//errno_t memcpy_s(
//   void *dest,
//   size_t numberOfElements,
//   const void *src,
//   size_t count 
//);
    //BOOST_SCOPE_EXIT((hFile))
    //{
    //    ::CloseHandle(hFile);
    //}
    //BOOST_SCOPE_EXIT_END
        
        HINT_NAME_TABLE corExeMain = {
            0,                                      // Hint
            "_CorExeMain"                           // Name
        };
        
        
        
        VOID* pCorExeMain = &corExeMain;
        VOID* pCorExeMainName = corExeMain.Name;
        cout << pCorExeMain << endl;
        cout << pCorExeMainName << endl;
        cout << "Size of HINT_NAME_TABLE: " << sizeof(corExeMain) << endl;
        cout << "Actual writing size: " << sizeof(corExeMain.Hint) + strnlen(corExeMain.Name, MAX_PATH) + 1 << endl;

        WORD fixupBlocks[] = { (IMAGE_REL_BASED_HIGHLOW << 12) + 0x330, 0 };
        cout << "Size of Fixup Blocks: " << sizeof(fixupBlocks) << endl;
        
        WCHAR buffer[MAX_PATH] = { 0 };
        DWORD length = 0;
        hr = ::GetCORSystemDirectory(buffer, MAX_PATH, &length);
        BOOST_REQUIRE(SUCCEEDED(hr));
        
        using std::wcout;
        wcout << L"CLR install directory: " << buffer << endl;
        cout << "Path size: " << length << endl;
        
//HRESULT GetCORSystemDirectory ( 
//        [out] LPWSTR  pbuffer,   
//        [in]  DWORD   cchBuffer, 
//        [out] DWORD*  dwlength
//); 

        using boost::filesystem::path;
        //using boost::filesystem::directory_iterator;
        //path mscorlibPath(buffer);
        //for (directory_iterator i(mscorlibPath), i_end; i != i_end; ++i)
        //{
        //    cout << *i << endl;
        //}
        
        path mscorlibPath(buffer);
        mscorlibPath /= L"mscorlib.dll";
        cout << mscorlibPath << endl;

        // 読み取りテスト
        { 
            CComPtr<IMetaDataDispenserEx> pDispenser;
            hr = ::CoCreateInstance(CLSID_CorMetaDataDispenser, NULL, CLSCTX_INPROC_SERVER, IID_IMetaDataDispenserEx, (void**)&pDispenser);
            BOOST_REQUIRE(SUCCEEDED(hr));

            CComPtr<IMetaDataImport2> pImport2;
            hr = pDispenser->OpenScope(mscorlibPath.wstring().c_str(), ofRead, IID_IMetaDataImport2, (IUnknown**)&pImport2);
            BOOST_REQUIRE(SUCCEEDED(hr));

            CComPtr<IMetaDataAssemblyImport> pAssemblyImport;
            hr = pImport2->QueryInterface(IID_IMetaDataAssemblyImport, (void**)&pAssemblyImport);
            BOOST_REQUIRE(SUCCEEDED(hr));


#define STRING_BUFFER_LEN 1024

            mdAssembly mda = mdAssemblyNil;
            const void *pbPublicKey = NULL;
            ULONG cbPublicKey = 0;
            ULONG ulHashAlgId = 0;
            WCHAR szName[STRING_BUFFER_LEN] = { 0 };
            ASSEMBLYMETADATA metaData;
            DWORD dwFlags = 0;

            hr = pAssemblyImport->GetAssemblyFromScope(&mda);
            BOOST_REQUIRE(SUCCEEDED(hr));

            ::ZeroMemory(&metaData, sizeof(ASSEMBLYMETADATA));
            hr = pAssemblyImport->GetAssemblyProps(mda, NULL, NULL, NULL, NULL, 0, NULL, &metaData, NULL);
            BOOST_REQUIRE(SUCCEEDED(hr));

            if (metaData.cbLocale)
                metaData.szLocale = (WCHAR*)_malloca(sizeof(WCHAR) * metaData.cbLocale);
            if (metaData.ulProcessor)
                metaData.rProcessor = (DWORD*)_malloca(sizeof(DWORD) * metaData.ulProcessor);
            if (metaData.ulOS)
                metaData.rOS = (OSINFO*)_malloca(sizeof(OSINFO) * metaData.ulOS);

        //STDMETHOD(GetAssemblyProps)(            // S_OK or error.
        //    mdAssembly  mda,                    // [IN] The Assembly for which to get the properties.
        //    const void  **ppbPublicKey,         // [OUT] Pointer to the public key.
        //    ULONG       *pcbPublicKey,          // [OUT] Count of bytes in the public key.
        //    ULONG       *pulHashAlgId,          // [OUT] Hash Algorithm.
        //    __out_ecount_part_opt(cchName, *pchName) LPWSTR  szName, // [OUT] Buffer to fill with assembly's simply name.
        //    ULONG       cchName,                // [IN] Size of buffer in wide chars.
        //    ULONG       *pchName,               // [OUT] Actual # of wide chars in name.
        //    ASSEMBLYMETADATA *pMetaData,        // [OUT] Assembly MetaData.
        //    DWORD       *pdwAssemblyFlags) PURE;    // [OUT] Flags.
            hr = pAssemblyImport->GetAssemblyProps(mda, &pbPublicKey, &cbPublicKey, &ulHashAlgId, szName, STRING_BUFFER_LEN, NULL, &metaData, &dwFlags);
            BOOST_REQUIRE(SUCCEEDED(hr));

            wcout << L"mscorlib name: " << szName << endl;
            
    //STDMETHOD(FindTypeDefByName)(           // S_OK or error.
    //    LPCWSTR     szTypeDef,              // [IN] Name of the Type.
    //    mdToken     tkEnclosingClass,       // [IN] TypeDef/TypeRef for Enclosing class.
    //    mdTypeDef   *ptd) PURE;             // [OUT] Put the TypeDef token here.
            {
                mdTypeDef mdtd = mdTypeDefNil;
                hr = pImport2->FindTypeDefByName(L"System.Runtime.CompilerServices.CompilationRelaxationsAttribute", NULL, &mdtd);
                BOOST_REQUIRE(SUCCEEDED(hr));
                cout << std::resetiosflags(cout.flags());
                cout << "CompilationRelaxationsAttribute token: 0x" << std::hex << mdtd << endl;
                
                
    //STDMETHOD(FindMethod)(  
    //    mdTypeDef   td,                     // [IN] given typedef   
    //    LPCWSTR     szName,                 // [IN] member name 
    //    PCCOR_SIGNATURE pvSigBlob,          // [IN] point to a blob value of CLR signature 
    //    ULONG       cbSigBlob,              // [IN] count of bytes in the signature blob    
    //    mdMethodDef *pmb) PURE;             // [OUT] matching memberdef 
                COR_SIGNATURE pvSigBlob[] = { IMAGE_CEE_CS_CALLCONV_HASTHIS, 1, ELEMENT_TYPE_VOID, 8 };
                ULONG cbSigBlob = sizeof(pvSigBlob) / sizeof(COR_SIGNATURE);
                mdMethodDef mmd = mdMethodDefNil;
                hr = pImport2->FindMethod(mdtd, L".ctor", pvSigBlob, cbSigBlob, &mmd);
                BOOST_REQUIRE(SUCCEEDED(hr));
                cout << "CompilationRelaxationsAttribute..ctor token: 0x" << std::hex << mmd << endl;
                
                cout << std::resetiosflags(cout.flags());
            }
        }   // 読み取りテスト
        
        // 書き込みテスト
        {
            CComPtr<IMetaDataDispenserEx> pDispenser;
            hr = ::CoCreateInstance(CLSID_CorMetaDataDispenser, NULL, CLSCTX_INPROC_SERVER, IID_IMetaDataDispenserEx, (void**)&pDispenser);
            BOOST_REQUIRE(SUCCEEDED(hr));
            
    //STDMETHOD(DefineScope)(                 // Return code.
    //    REFCLSID    rclsid,                 // [in] What version to create.
    //    DWORD       dwCreateFlags,          // [in] Flags on the create.
    //    REFIID      riid,                   // [in] The interface desired.
    //    IUnknown    **ppIUnk) PURE;         // [out] Return interface on success.
            CComPtr<IMetaDataEmit2> pEmit2;
            hr = pDispenser->DefineScope(CLSID_CorMetaDataRuntime, 0, IID_IMetaDataEmit2, (IUnknown**)&pEmit2);
            BOOST_REQUIRE(SUCCEEDED(hr));

    //STDMETHOD(DefineUserString)(            // Return code.
    //    LPCWSTR szString,                   // [IN] User literal string.
    //    ULONG       cchString,              // [IN] Length of string.
    //    mdString    *pstk) PURE;            // [OUT] String token.
            std::wstring s(L"Hello World!");
            mdString mds = mdStringNil;
            cout << "Size of s: " << s.size() << endl;
            hr = pEmit2->DefineUserString(s.c_str(), s.size(), &mds);
            BOOST_REQUIRE(SUCCEEDED(hr));

    //STDMETHOD(GetSaveSize)(                 // S_OK or error.
    //    CorSaveSize fSave,                  // [IN] cssAccurate or cssQuick.
    //    DWORD       *pdwSaveSize) PURE;     // [OUT] Put the size here.
            DWORD dwSaveSize = 0;
            hr = pEmit2->GetSaveSize(cssAccurate, &dwSaveSize);
            BOOST_REQUIRE(SUCCEEDED(hr));
            cout << "Save size: " << dwSaveSize << endl;
            
    //STDMETHOD(SaveToMemory)(                // S_OK or error.
    //    void        *pbData,                // [OUT] Location to write data.
    //    ULONG       cbData) PURE;           // [IN] Max size of data buffer.
            std::auto_ptr<BYTE> pData(new BYTE[dwSaveSize]);
            hr = pEmit2->SaveToMemory(pData.get(), dwSaveSize);
            BOOST_REQUIRE(SUCCEEDED(hr));

#if 0
            INT count = 0;
            cout << std::resetiosflags(cout.flags());
            cout << std::uppercase << std::hex;            
            for (const BYTE *i = pData.get(), *i_end = pData.get() + dwSaveSize; i != i_end; ++i)
            {
                cout << std::setfill('0') << std::setw(2) << static_cast<DWORD>(*i) << " ";
                if (++count % 8 == 0)
                    cout << endl;
            }
            cout << endl;
#endif            
        }   // 書き込みテスト

        // 書き込みテスト 2
        {
            path mscorpePath(buffer);
            mscorpePath /= L"mscorpe.dll";
            cout << mscorpePath << endl;
            
            HMODULE hmodCorPE = ::LoadLibraryW(mscorpePath.wstring().c_str());
            BOOST_REQUIRE(hmodCorPE);
            BOOST_SCOPE_EXIT((hmodCorPE))
            {
                ::FreeLibrary(hmodCorPE);
            }
            BOOST_SCOPE_EXIT_END
            
            {
                HRESULT (__stdcall *pfnCreateCeeFileGen)(ICeeFileGen **ceeFileGen) = NULL;
                HRESULT (__stdcall *pfnDestroyCeeFileGen)(ICeeFileGen **ceeFileGen) = NULL;

                pfnCreateCeeFileGen = reinterpret_cast<HRESULT (__stdcall *)(ICeeFileGen **ceeFileGen)>(::GetProcAddress(hmodCorPE, "CreateICeeFileGen"));
                BOOST_REQUIRE(pfnCreateCeeFileGen);
                pfnDestroyCeeFileGen = reinterpret_cast<HRESULT (__stdcall *)(ICeeFileGen **ceeFileGen)>(::GetProcAddress(hmodCorPE, "DestroyICeeFileGen"));
                BOOST_REQUIRE(pfnDestroyCeeFileGen);
                
                ICeeFileGen* pCeeFileGen = NULL;
                hr = pfnCreateCeeFileGen(&pCeeFileGen);
                BOOST_REQUIRE(SUCCEEDED(hr));
                BOOST_SCOPE_EXIT((pCeeFileGen)(pfnDestroyCeeFileGen))
                {
                    pfnDestroyCeeFileGen(&pCeeFileGen);
                }
                BOOST_SCOPE_EXIT_END
                
    //virtual HRESULT CreateCeeFileEx(HCEEFILE *ceeFile, ULONG createFlags);
                HCEEFILE ceeFile = NULL;
                hr = pCeeFileGen->CreateCeeFileEx(&ceeFile, ICEE_CREATE_FILE_PURE_IL);
                BOOST_REQUIRE(SUCCEEDED(hr));
                BOOST_SCOPE_EXIT((ceeFile)(pCeeFileGen))
                {
    //virtual HRESULT DestroyCeeFile(HCEEFILE *ceeFile); // call this to delete a file handle
                    pCeeFileGen->DestroyCeeFile(&ceeFile);
                }
                BOOST_SCOPE_EXIT_END
                
    //virtual HRESULT SetOutputFileName (HCEEFILE ceeFile, __in LPWSTR outputFileName);
                hr = pCeeFileGen->SetOutputFileName(ceeFile, L"hello.exe");
                BOOST_REQUIRE(SUCCEEDED(hr));
                
    //virtual HRESULT SetComImageFlags (HCEEFILE ceeFile, DWORD mask);
                hr = pCeeFileGen->SetComImageFlags(ceeFile, COMIMAGE_FLAGS_ILONLY);
                BOOST_REQUIRE(SUCCEEDED(hr));
                
    //virtual HRESULT SetSubsystem(HCEEFILE ceeFile, DWORD subsystem, DWORD major, DWORD minor);
                hr = pCeeFileGen->SetSubsystem(ceeFile, IMAGE_SUBSYSTEM_WINDOWS_CUI, 4, 0);
                BOOST_REQUIRE(SUCCEEDED(hr));
                
    //virtual HRESULT EmitMetaDataEx (HCEEFILE ceeFile, IMetaDataEmit *emitter); 
                //pCeeFileGen->EmitMetaDataEx(
                // ここでメタデータ生成
                
    //virtual HRESULT GenerateCeeFile (HCEEFILE ceeFile);
                hr = pCeeFileGen->GenerateCeeFile(ceeFile);
                BOOST_REQUIRE(SUCCEEDED(hr));
            }
        }   // 書き込みテスト 2

#if 0        
        IExeCreatorPtr pExeCreator;
        hr = pExeCreator.CreateInstance(__uuidof(ExeCreator));
        BOOST_REQUIRE(SUCCEEDED(hr));

        try
        {
            hr = pExeCreator->Create(L"hello.exe");
            BOOST_REQUIRE(SUCCEEDED(hr));
        }
        catch (_com_error& e)
        {
            // 基本的にクライアントでは _com_error 例外が投げられるので hr 確認するの無駄っぽい・・・(/_;)
            BOOST_FAIL(e.Description());
        }
        
#endif
        
        // 【テスト その 2】
        // ・一番単純な DLL を作成。
        // ・現在の AppDomain に読み込み。
        // ・リフレクションを使ってオブジェクトをインスタンス化。メソッド呼び出し。
        // ・呼び出し結果を検証する。
        BOOST_REQUIRE(true);
    }

    BOOST_AUTO_TEST_SUITE_END()
}
