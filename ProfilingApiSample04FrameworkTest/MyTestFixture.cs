using System;
using NUnit.Framework;
using ProfilingApiSample04FrameworkTest;
using ProfilingApiSample04Framework;
using System.IO;
using ConsoleHolder = ProfilingApiSample04FrameworkTest.Holder<System.Func<System.IO.TextWriter>>;
using LooseConsole = ProfilingApiSample04Framework.LooseDomain<ProfilingApiSample04FrameworkTest.Holder<System.Func<System.IO.TextWriter>>>;
using StopwatchHolder = ProfilingApiSample04FrameworkTest.Holder<System.Func<System.Diagnostics.Stopwatch>>;
using LooseStopwatch = ProfilingApiSample04Framework.LooseDomain<ProfilingApiSample04FrameworkTest.Holder<System.Func<System.Diagnostics.Stopwatch>>>;
using System.Diagnostics;

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

                AppDomain.CurrentDomain.RunAtIsolatedDomain<StringWriter, Stopwatch>((sw_, s) =>
                {
                    sw_.WriteLine("Elapsed: {0} ms", s.ElapsedMilliseconds);
                }, sw, new Stopwatch());

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
    
    [TestFixture]
    public class ConsoleTest
    {
        [TestFixtureSetUp]
        public void FixtureSetUp()
        {
            // 境界があいまいな Domain アクセッサに、持ち運ぶ情報を登録。
            LooseConsole.Unload();
            LooseConsole.Register(() => ConsoleHolder.Instance);
            var @out = Console.Out;
            LooseConsole.Instance.Source = () => @out;

            // NUnit GUI が管理するイベントループは書き込み処理毎に別スレッドで回る。
            // こちら側の AppDomain で登録した処理が AppDomain を越えてから 
            // JIT されないようにするための事前呼び出し。
            Console.Write(string.Empty);
            Console.Out.Flush();
        }

        [TestFixtureTearDown]
        public void FixtureTearDown()
        {
            // 境界があいまいな Domain アクセッサから持ち運ぶ情報削除。
            LooseConsole.Instance.Source = null;
            LooseConsole.Unload();
        }

        [Test]
        public void Test()
        {
            LooseConsole.Instance.Source().WriteLine("AppDomain: {0}", AppDomain.CurrentDomain.FriendlyName);

            AppDomain.CurrentDomain.RunAtIsolatedDomain(() =>
            {
                LooseConsole.Instance.Source().WriteLine("AppDomain: {0}", AppDomain.CurrentDomain.FriendlyName);
            });

            LooseConsole.Instance.Source().WriteLine("AppDomain: {0}", AppDomain.CurrentDomain.FriendlyName);
        }
    }
}
