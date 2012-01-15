using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using NUnit.Framework;
using ProfilingApiSample04Framework;
using System.Reflection;
using ProfilingApiSample04FrameworkTest;

namespace ProfilingApiSample04FrameworkTest
{
    [TestFixture]
    public class IndiretionInterfacesTest
    {
        [Test]
        public void IndiretionTest01()
        {
            var info = new IndiretionInfo();
            info.m_assemblyName = "mscorlib, Version=2.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089, processorArchitecture=x86";
            info.m_typeFullName = "System.DateTime";
            info.m_methodName = "get_Now";
            var curFuncPtr = MethodBase.GetCurrentMethod().MethodHandle.GetFunctionPointer();

            {
                Assert.IsTrue(Indiretion.SetFunctionPointer(ref info, curFuncPtr));
            }

            {
                var funcPtr = IntPtr.Zero;
                Assert.IsTrue(Indiretion.GetFunctionPointer(ref info, ref funcPtr));
                Assert.AreEqual(curFuncPtr, funcPtr);
            }
        }
    }

    public static class IntPtrMixin
    {
#if _WIN32
        public static Int32 ToValue(this IntPtr p)
#elif _WIN64
        public static Int64 ToValue(this IntPtr p)
#else
#error This assembly must build in x86 or x64.
#endif
        {
#if _WIN32
            return p.ToInt32();
#elif _WIN64
            return p.ToInt64();
#else
#error This assembly must build in x86 or x64.
#endif
        }
    }
}
