using System;
using System.Diagnostics;
using System.IO;
using NUnit.Framework;
using ProfilingApiSample04Framework;
using LooseStopwatch = ProfilingApiSample04Framework.LooseDomain<ProfilingApiSample04Framework.SingletonHolder<System.Func<System.Diagnostics.Stopwatch>>>;
using StopwatchHolder = ProfilingApiSample04Framework.SingletonHolder<System.Func<System.Diagnostics.Stopwatch>>;

namespace ProfilingApiSample04FrameworkTest
{
    [TestFixture]
    public class StopwatchTest
    {
        [TestFixtureSetUp]
        public void FixtureSetUp()
        {
            LooseStopwatch.Unload();
            LooseStopwatch.Register(() => StopwatchHolder.Instance);
            var s = new Stopwatch();
            LooseStopwatch.Instance.Source = () => s;
        }

        [TestFixtureTearDown]
        public void FixtureTearDown()
        {
            LooseStopwatch.Instance.Source = null;
            LooseStopwatch.Unload();
        }

        [Test]
        public void Test()
        {
            using (var sw = new StringWriter())
            {
                LooseStopwatch.Instance.Source().Restart();

                sw.WriteLine("Elapsed: {0} ms", LooseStopwatch.Instance.Source().ElapsedMilliseconds);

                AppDomain.CurrentDomain.RunAtIsolatedDomain<StringWriter>(sw_ =>
                {
                    sw_.WriteLine("Elapsed: {0} ms", LooseStopwatch.Instance.Source().ElapsedMilliseconds);
                }, sw);

                sw.WriteLine("Elapsed: {0} ms", LooseStopwatch.Instance.Source().ElapsedMilliseconds);

                Console.WriteLine(sw.ToString());
            }
        }
    }

    public static class StopwatchMixin
    {
        public static void Restart(this Stopwatch s)
        {
            s.Reset();
            s.Start();
        }
    }
}
