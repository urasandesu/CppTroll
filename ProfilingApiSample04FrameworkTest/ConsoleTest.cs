using System;
using NUnit.Framework;
using ProfilingApiSample04Framework;
using ConsoleHolder = ProfilingApiSample04Framework.SingletonHolder<System.Func<System.IO.TextWriter>>;
using LooseConsole = ProfilingApiSample04Framework.LooseDomain<ProfilingApiSample04Framework.SingletonHolder<System.Func<System.IO.TextWriter>>>;

namespace ProfilingApiSample04FrameworkTest
{
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
