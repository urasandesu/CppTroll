// AssemblyGenCollection.cpp : CAssemblyGenCollection ‚ÌŽÀ‘•

#include "stdafx.h"
#include "AssemblyGenCollection.h"


// CAssemblyGenCollection

STDMETHODIMP CAssemblyGenCollection::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IAssemblyGenCollection
	};

	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}
