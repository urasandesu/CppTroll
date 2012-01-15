using System;
using System.IO;
using System.Prig;
using MyLibrary;
using MyLibraryTest.Helper;
using NUnit.Framework;

namespace MyLibraryTest
{
    [TestFixture]
    public class LifeInfoTest
    {
        [Test]
        public void LunchBreakTest01_NowIsLunchBreak()
        {
            using (new PDateTimeContext.NowGet())
            using (new ConsoleContext())
            using (var sw = new StringWriter())
            {
                Console.SetOut(sw);
                PDateTime.NowGet.Body = () => new DateTime(2011, 12, 13, 12, 00, 00);
                LifeInfo.LunchBreak();
                Assert.AreEqual("時刻: 12\tお昼休みなう！" + sw.NewLine, sw.ToString());
            }
        }

        [Test]
        public void LunchBreakTest02_NowIsNotLunchBreak()
        {
            using (new PDateTimeContext.NowGet())
            using (new ConsoleContext())
            using (var sw = new StringWriter())
            {
                Console.SetOut(sw);
                PDateTime.NowGet.Body = () => new DateTime(2011, 12, 13, 13, 00, 00);
                LifeInfo.LunchBreak();
                Assert.AreEqual("時刻: 13\tお仕事なう・・・" + sw.NewLine, sw.ToString());
            }
        }

        [Test]
        public void LunchBreakTest01_NowIsHoliday()
        {
            using (new PDateTimeContext.NowGet())
            using (new ConsoleContext())
            using (var sw = new StringWriter())
            {
                Console.SetOut(sw);
                PDateTime.NowGet.Body = () => new DateTime(2011, 12, 18, 00, 00, 00);
                LifeInfo.Holiday();
                Assert.AreEqual("曜日: Sunday\t休日なう！" + sw.NewLine, sw.ToString());
            }
        }

        [Test]
        public void LunchBreakTest02_NowIsNotHoliday()
        {
            using (new PDateTimeContext.NowGet())
            using (new ConsoleContext())
            using (var sw = new StringWriter())
            {
                Console.SetOut(sw);
                PDateTime.NowGet.Body = () => new DateTime(2011, 12, 19, 00, 00, 00);
                LifeInfo.Holiday();
                Assert.AreEqual("曜日: Monday\tお仕事なう・・・" + sw.NewLine, sw.ToString());
            }
        }
    }
}

namespace MyLibraryTest.Helper
{
    public class ConsoleContext : IDisposable
    {
        bool m_disposed;
        TextWriter m_lastOut;

        public ConsoleContext()
        {
            m_lastOut = Console.Out;
        }

        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        protected virtual void Dispose(bool disposing)
        {
            if (!m_disposed)
            {
                if (disposing)
                {
                    Console.SetOut(m_lastOut);
                }
            }
            m_disposed = true;
        }

        ~ConsoleContext()
        {
            Dispose(false);
        }
    }
}
