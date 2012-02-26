//#define SOLUTION
#define ISSUE

#if _
#elif SOLUTION
using System;
using System.Diagnostics;
using System.IO;
using NUnit.Framework;
using ProfilingApiSample04Framework.Mixin.System;
using LooseStopwatch = 
    ProfilingApiSample04Framework.LooseCrossDomainAccessor<
        ProfilingApiSample04Framework.GenericHolder<System.Diagnostics.Stopwatch>>;

namespace ProfilingApiSample04FrameworkTest
{
    [TestFixture]
    public class StopwatchTest
    {
        [TestFixtureSetUp]
        public void FixtureSetUp()
        {
            LooseStopwatch.Unload();
            LooseStopwatch.Register();
            LooseStopwatch.Holder.Source = new Stopwatch();
        }

        [TestFixtureTearDown]
        public void FixtureTearDown()
        {
            LooseStopwatch.Holder.Source = null;
            LooseStopwatch.Unload();
        }

        [Test]
        public void Test()
        {
            using (var sw = new StringWriter())
            {
                LooseStopwatch.Holder.Source.Restart();

                sw.WriteLine("Elapsed: {0} ms", LooseStopwatch.Holder.Source.ElapsedMilliseconds);

                AppDomain.CurrentDomain.RunAtIsolatedDomain<StringWriter>(sw_ =>
                {
                    sw_.WriteLine("Elapsed: {0} ms", LooseStopwatch.Holder.Source.ElapsedMilliseconds);
                }, sw);

                sw.WriteLine("Elapsed: {0} ms", LooseStopwatch.Holder.Source.ElapsedMilliseconds);

                Console.WriteLine(sw.ToString());
            }
        }
    }
}
#elif ISSUE
using System;
using System.Diagnostics;
using System.IO;
using NUnit.Framework;
using ProfilingApiSample04Framework.Mixin.System;

namespace ProfilingApiSample04FrameworkTest
{
    [TestFixture]
    public class StopwatchTest
    {
        [Test]
        public void Test()
        {
            using (var sw = new StringWriter())
            {
                var stopwatch = new Stopwatch();
                stopwatch.Restart();

                sw.WriteLine("Elapsed: {0} ms", stopwatch.ElapsedMilliseconds);

                AppDomain.CurrentDomain.RunAtIsolatedDomain<StringWriter, Stopwatch>((sw_, stopwatch_) =>
                {
                    sw_.WriteLine("Elapsed: {0} ms", stopwatch_.ElapsedMilliseconds);
                }, sw, stopwatch);

                sw.WriteLine("Elapsed: {0} ms", stopwatch.ElapsedMilliseconds);

                Console.WriteLine(sw.ToString());
            }
        }
    }
}
#endif

namespace ProfilingApiSample04FrameworkTest
{
    public static class StopwatchMixin
    {
        public static void Restart(this Stopwatch s)
        {
            s.Reset();
            s.Start();
        }
    }
}
