// AssemblyGen.cpp : CAssemblyGen ‚ÌŽÀ‘•

#include "stdafx.h"
#include "AssemblyGen.h"


// CAssemblyGen

STDMETHODIMP CAssemblyGen::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IAssemblyGen
	};

	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}
