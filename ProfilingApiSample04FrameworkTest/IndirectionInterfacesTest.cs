using System;
using System.Reflection;
using NUnit.Framework;
using ProfilingApiSample04Framework;

namespace ProfilingApiSample04FrameworkTest
{
    [TestFixture]
    public class InstanceGettersTest
    {
        [TestFixtureSetUp]
        public void FixtureSetUp()
        {
            InstanceGetters.Unload();
        }

        [TestFixtureTearDown]
        public void FixtureTearDown()
        {
            InstanceGetters.Unload();
        }

        [Test]
        public void InstanceGettersTest01()
        {
            var assemblyQualifiedName = "System.DateTime, mscorlib, Version=2.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089";
            var curFuncPtr = MethodBase.GetCurrentMethod().MethodHandle.GetFunctionPointer();

            {
                Assert.IsTrue(InstanceGetters.TryAdd(assemblyQualifiedName, curFuncPtr));
            }

            {
                var funcPtr = IntPtr.Zero;
                Assert.IsTrue(InstanceGetters.TryGet(assemblyQualifiedName, out funcPtr));
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
