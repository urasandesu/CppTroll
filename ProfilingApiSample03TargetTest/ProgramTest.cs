//#define SECOND_IDEA
//#define FIRST_IDEA
//#define DOES_NOT_WORK
#define ORIGINAL

#if _

#elif SECOND_IDEA
using System;
using System.IO;
using System.Prig;
using MyLibrary;
using MyLibraryTest.Helper;
using MyLibraryTest.Helper.System.Prig;
using Xunit;

namespace MyLibraryTest
{
    public class LifeInfoTest
    {
        [Fact]
        public void LunchBreakTest01_NowIsLunchBreak()
        {
            using (new PDateTimeContext.NowGet())
            using (new ConsoleContext())
            using (var sw = new StringWriter())
            {
                Console.SetOut(sw);
                PDateTime.NowGet.Body = () => new DateTime(2011, 12, 13, 12, 00, 00);
                LifeInfo.LunchBreak();
                Assert.Equal("時刻: 12\tお昼休みなう！" + sw.NewLine, sw.ToString());
            }
        }

        [Fact]
        public void LunchBreakTest02_NowIsNotLunchBreak()
        {
            using (new PDateTimeContext.NowGet())
            using (new ConsoleContext())
            using (var sw = new StringWriter())
            {
                Console.SetOut(sw);
                PDateTime.NowGet.Body = () => new DateTime(2011, 12, 13, 13, 00, 00);
                LifeInfo.LunchBreak();
                Assert.Equal("時刻: 13\tお仕事なう・・・" + sw.NewLine, sw.ToString());
            }
        }

        [Fact]
        public void LunchBreakTest01_NowIsHoliday()
        {
            using (new PDateTimeContext.NowGet())
            using (new ConsoleContext())
            using (var sw = new StringWriter())
            {
                Console.SetOut(sw);
                PDateTime.NowGet.Body = () => new DateTime(2011, 12, 18, 00, 00, 00);
                LifeInfo.Holiday();
                Assert.Equal("曜日: Sunday\t休日なう！" + sw.NewLine, sw.ToString());
            }
        }

        [Fact]
        public void LunchBreakTest02_NowIsNotHoliday()
        {
            using (new PDateTimeContext.NowGet())
            using (new ConsoleContext())
            using (var sw = new StringWriter())
            {
                Console.SetOut(sw);
                PDateTime.NowGet.Body = () => new DateTime(2011, 12, 19, 00, 00, 00);
                LifeInfo.Holiday();
                Assert.Equal("曜日: Monday\tお仕事なう・・・" + sw.NewLine, sw.ToString());
            }
        }
    }
}

namespace MyLibraryTest.Helper.System.Prig
{
    public class PDateTimeContext : IDisposable
    {
        bool m_disposed;

        public PDateTimeContext()
        {
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
                }
            }
            m_disposed = true;
        }

        ~PDateTimeContext()
        {
            Dispose(false);
        }

        public class NowGet : IDisposable
        {
            bool m_disposed;
            Func<DateTime> m_lastBody;

            public NowGet()
            {
                m_lastBody = PDateTime.NowGet.Body;
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
                        PDateTime.NowGet.Body = m_lastBody;
                    }
                }
                m_disposed = true;
            }

            ~NowGet()
            {
                Dispose(false);
            }
        }
    }
}
#elif FIRST_IDEA
using System;
using System.IO;
using System.Wedge;
using MyLibrary;
using MyLibraryTest.Helper;
using MyLibraryTest.Helper.System.Wedge;
using Xunit;

namespace MyLibraryTest
{
    public class LifeInfoTest
    {
        [Fact]
        public void LunchBreakTest01_NowIsLunchBreak()
        {
            using (new WDateTimeContext.NowGet())
            using (new ConsoleContext())
            using (var sw = new StringWriter())
            {
                Console.SetOut(sw);
                WDateTime.NowGet.Body = () => new DateTime(2011, 12, 13, 12, 00, 00);
                LifeInfo.LunchBreak();
                Assert.Equal("時刻: 12\tお昼休みなう！" + sw.NewLine, sw.ToString());
            }
        }

        [Fact]
        public void LunchBreakTest02_NowIsNotLunchBreak()
        {
            using (new WDateTimeContext.NowGet())
            using (new ConsoleContext())
            using (var sw = new StringWriter())
            {
                Console.SetOut(sw);
                WDateTime.NowGet.Body = () => new DateTime(2011, 12, 13, 13, 00, 00);
                LifeInfo.LunchBreak();
                Assert.Equal("時刻: 13\tお仕事なう・・・" + sw.NewLine, sw.ToString());
            }
        }

        [Fact]
        public void LunchBreakTest01_NowIsHoliday()
        {
            using (new WDateTimeContext.NowGet())
            using (new ConsoleContext())
            using (var sw = new StringWriter())
            {
                Console.SetOut(sw);
                WDateTime.NowGet.Body = () => new DateTime(2011, 12, 18, 00, 00, 00);
                LifeInfo.Holiday();
                Assert.Equal("曜日: Sunday\t休日なう！" + sw.NewLine, sw.ToString());
            }
        }

        [Fact]
        public void LunchBreakTest02_NowIsNotHoliday()
        {
            using (new WDateTimeContext.NowGet())
            using (new ConsoleContext())
            using (var sw = new StringWriter())
            {
                Console.SetOut(sw);
                WDateTime.NowGet.Body = () => new DateTime(2011, 12, 19, 00, 00, 00);
                LifeInfo.Holiday();
                Assert.Equal("曜日: Monday\tお仕事なう・・・" + sw.NewLine, sw.ToString());
            }
        }
    }
}

namespace MyLibraryTest.Helper.System.Wedge
{
    public class WDateTimeContext : IDisposable
    {
        bool m_disposed;

        public WDateTimeContext()
        {
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
                }
            }
            m_disposed = true;
        }

        ~WDateTimeContext()
        {
            Dispose(false);
        }

        public class NowGet : IDisposable
        {
            bool m_disposed;
            Func<DateTime> m_lastBody;

            public NowGet()
            {
                m_lastBody = WDateTime.NowGet.Body;
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
                        WDateTime.NowGet.Body = m_lastBody;
                    }
                }
                m_disposed = true;
            }

            ~NowGet()
            {
                Dispose(false);
            }
        }
    }
}
#elif DOES_NOT_WORK
using System;
using System.IO;
using MyLibrary;
using MyLibraryTest.Helper;
using Xunit;

namespace MyLibraryTest
{
    public class LifeInfoTest
    {
        [Fact]
        public void LunchBreakTest01_NowIsLunchBreak()
        {
            using (new ConsoleContext())
            using (var sw = new StringWriter())
            {
                Console.SetOut(sw);
                DateTime.Now = () => new DateTime(2011, 12, 13, 12, 00, 00);
                LifeInfo.LunchBreak();
                Assert.Equal("時刻: 12\tお昼休みなう！" + sw.NewLine, sw.ToString());
            }
        }

        [Fact]
        public void LunchBreakTest02_NowIsNotLunchBreak()
        {
            using (new ConsoleContext())
            using (var sw = new StringWriter())
            {
                Console.SetOut(sw);
                DateTime.Now = () => new DateTime(2011, 12, 13, 13, 00, 00);
                LifeInfo.LunchBreak();
                Assert.Equal("時刻: 13\tお仕事なう・・・" + sw.NewLine, sw.ToString());
            }
        }

        [Fact]
        public void LunchBreakTest01_NowIsHoliday()
        {
            using (new ConsoleContext())
            using (var sw = new StringWriter())
            {
                Console.SetOut(sw);
                DateTime.Now = () => new DateTime(2011, 12, 18, 00, 00, 00);
                LifeInfo.Holiday();
                Assert.Equal("曜日: Sunday\t休日なう！" + sw.NewLine, sw.ToString());
            }
        }

        [Fact]
        public void LunchBreakTest02_NowIsNotHoliday()
        {
            using (new ConsoleContext())
            using (var sw = new StringWriter())
            {
                Console.SetOut(sw);
                DateTime.Now = () => new DateTime(2011, 12, 19, 00, 00, 00);
                LifeInfo.Holiday();
                Assert.Equal("曜日: Monday\tお仕事なう・・・" + sw.NewLine, sw.ToString());
            }
        }
    }
}
#elif ORIGINAL
using System;
using System.IO;
using MyLibrary;
using MyLibraryTest.Helper;
using Xunit;

namespace MyLibraryTest
{
    public class LifeInfoTest
    {
        [Fact]
        public void LunchBreakTest01_NowIsLunchBreak()
        {
            using (new ConsoleContext())
            using (var sw = new StringWriter())
            {
                Console.SetOut(sw);
                LifeInfo.LunchBreak();
                Assert.Equal("時刻: 12\tお昼休みなう！" + sw.NewLine, sw.ToString());
            }
        }

        [Fact]
        public void LunchBreakTest02_NowIsNotLunchBreak()
        {
            using (new ConsoleContext())
            using (var sw = new StringWriter())
            {
                Console.SetOut(sw);
                LifeInfo.LunchBreak();
                Assert.Equal("時刻: 13\tお仕事なう・・・" + sw.NewLine, sw.ToString());
            }
        }

        [Fact]
        public void LunchBreakTest01_NowIsHoliday()
        {
            using (new ConsoleContext())
            using (var sw = new StringWriter())
            {
                Console.SetOut(sw);
                LifeInfo.Holiday();
                Assert.Equal("曜日: Sunday\t休日なう！" + sw.NewLine, sw.ToString());
            }
        }

        [Fact]
        public void LunchBreakTest02_NowIsNotHoliday()
        {
            using (new ConsoleContext())
            using (var sw = new StringWriter())
            {
                Console.SetOut(sw);
                LifeInfo.Holiday();
                Assert.Equal("曜日: Monday\tお仕事なう・・・" + sw.NewLine, sw.ToString());
            }
        }
    }
}
#endif

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
