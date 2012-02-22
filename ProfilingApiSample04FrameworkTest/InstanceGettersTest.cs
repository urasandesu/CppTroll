using System;
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
            InstanceGetters.Clear();
        }

        [TestFixtureTearDown]
        public void FixtureTearDown()
        {
            InstanceGetters.Clear();
        }

        [Test]
        public void InstanceGettersTest01()
        {
            var assemblyQualifiedName = "System.DateTime, mscorlib, Version=2.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089";
            var get_NowPtr = typeof(DateTime).GetProperty("Now").GetGetMethod().MethodHandle.GetFunctionPointer();

            {
                Assert.IsTrue(InstanceGetters.TryAdd(assemblyQualifiedName, get_NowPtr));
            }

            {
                var funcPtr = IntPtr.Zero;
                Assert.IsTrue(InstanceGetters.TryGet(assemblyQualifiedName, out funcPtr));
                Assert.AreEqual(get_NowPtr, funcPtr);
            }
        }
    }
}
