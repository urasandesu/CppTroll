// AppDomainGen.cpp : CAppDomainGen ‚ÌŽÀ‘•

#include "stdafx.h"
#include "AppDomainGen.h"


// CAppDomainGen

STDMETHODIMP CAppDomainGen::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IAppDomainGen
	};

	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}
