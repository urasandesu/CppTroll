#pragma once
#ifndef INCLUDED_CCOMOBJECTSLIM_H
#define INCLUDED_CCOMOBJECTSLIM_H

namespace My
{
    template<class Base>
    class CComObjectSlim : 
        public CComObjectNoLock<Base>
    {
    public:
	    static HRESULT CreateInstance(CComObjectSlim<Base>** ppObj)
	    {
	        if (ppObj == NULL) return E_POINTER;
	        *ppObj = NULL;

	        HRESULT hr = E_FAIL;
	        auto_ptr<CComObjectSlim<Base>> pObj(new CComObjectSlim<Base>());

	        pObj->SetVoid(NULL);                    // Declared in CComObjectRootBase.
	        pObj->InternalFinalConstructAddRef();   // Declared in user class DECLARE_PROTECT_FINAL_CONSTRUCT.

	        hr = pObj->_AtlInitialConstruct();      // Declared in CComObjectRootEx.
	        if (FAILED(hr)) return hr;

	        hr = pObj->FinalConstruct();            // Declared in user class.
	        if (FAILED(hr)) return hr;

	        hr = pObj->_AtlFinalConstruct();        // Declared in CComObjectRootBase.
	        pObj->InternalFinalConstructRelease();  // Declared in user class DECLARE_PROTECT_FINAL_CONSTRUCT.

	        *ppObj = pObj.release();
	        return S_OK;
	    }
    };
}   // namespace My

#endif  // #ifndef INCLUDED_CCOMOBJECTSLIM_H