#pragma once
#include <atlbase.h>
#include <atlcom.h>

namespace My
{
    template <class Base, class T, class Copy, class RangeType, class ThreadModel = CComObjectThreadModel>
    class ATL_NO_VTABLE CComEnumOnRange :
	    public IEnumOnSTLImpl<Base, &__uuidof(Base), T, Copy, RangeType>,
	    public CComObjectRootEx<ThreadModel>
    {
    public:
	    typedef CComEnumOnSTL<Base, &__uuidof(Base), T, Copy, RangeType, ThreadModel> _CComEnum;
	    typedef IEnumOnSTLImpl<Base, &__uuidof(Base), T, Copy, RangeType> _CComEnumBase;
	    BEGIN_COM_MAP(_CComEnum)
		    COM_INTERFACE_ENTRY_IID(__uuidof(Base), _CComEnumBase)
	    END_COM_MAP()
    };
}   // namespace My
