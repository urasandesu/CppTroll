//#define SECOND_IDEA
//#define FIRST_IDEA
//#define DOES_NOT_WORK
#define ORIGINAL


#if _

#elif SECOND_IDEA
using System;
using MyLibrary;
using ThirdPartyLibrary;

namespace ProfilingApiSample03Target
{
    class Program
    {
        static void Main(string[] args)
        {
            LifeInfo.LunchBreak();
            LifeInfo.Holiday();
        }
    }
}

namespace MyLibrary
{
    public static class LifeInfo
    {
        public static void LunchBreak()
        {
            var now = DateTime.Now;
            Console.WriteLine("時刻: " + now.Hour + "\t" + (12 <= now.Hour && now.Hour < 13 ? "お昼休みなう！" : "お仕事なう・・・"));
        }

        public static void Holiday()
        {
            var dayOfWeek = ConfigurationManager.GetProperty("Holiday", DayOfWeek.Sunday);
            var now = DateTime.Now;
            Console.WriteLine("曜日: " + now.DayOfWeek + "\t" + (now.DayOfWeek == dayOfWeek ? "休日なう！" : "お仕事なう・・・"));
        }
    }
}
#elif FIRST_IDEA
using System;
using MyLibrary;
using ThirdPartyLibrary;
using System.Wedge;
using System.Runtime.CompilerServices;

[assembly: InternalsVisibleTo("ProfilingApiSample03TargetTest")]

namespace ProfilingApiSample03Target
{
    class Program
    {
        static void Main(string[] args)
        {
            LifeInfo.LunchBreak();
            LifeInfo.Holiday();
        }
    }
}

namespace MyLibrary
{
    public static class LifeInfo
    {
        public static void LunchBreak()
        {
            var now = WDateTime.NowGet.Body();
            Console.WriteLine("時刻: " + now.Hour + "\t" + (12 <= now.Hour && now.Hour < 13 ? "お昼休みなう！" : "お仕事なう・・・"));
        }

        public static void Holiday()
        {
            var dayOfWeek = ConfigurationManager.GetProperty("Holiday", DayOfWeek.Sunday);
            var now = WDateTime.NowGet.Body();
            Console.WriteLine("曜日: " + now.DayOfWeek + "\t" + (now.DayOfWeek == dayOfWeek ? "休日なう！" : "お仕事なう・・・"));
        }
    }
}

namespace System.Wedge
{
    struct WDateTime
    {
        public static class NowGet
        {
            static Func<DateTime> m_body = () => DateTime.Now;
            public static Func<DateTime> Body { get { return m_body; } set { m_body = value; } }
        }
    }
}
#elif DOES_NOT_WORK

#elif ORIGINAL
using System;
using MyLibrary;
using ThirdPartyLibrary;

namespace ProfilingApiSample03Target
{
    class Program
    {
        static void Main(string[] args)
        {
            LifeInfo.LunchBreak();
            LifeInfo.Holiday();
        }
    }
}

namespace MyLibrary
{
    public static class LifeInfo
    {
        public static void LunchBreak()
        {
            var now = DateTime.Now;
            Console.WriteLine("時刻: " + now.Hour + "\t" + (12 <= now.Hour && now.Hour < 13 ? "お昼休みなう！" : "お仕事なう・・・"));
        }

        public static void Holiday()
        {
            var dayOfWeek = ConfigurationManager.GetProperty("Holiday", DayOfWeek.Sunday);
            var now = DateTime.Now;
            Console.WriteLine("曜日: " + now.DayOfWeek + "\t" + (now.DayOfWeek == dayOfWeek ? "休日なう！" : "お仕事なう・・・"));
        }
    }
}
#endif

namespace ThirdPartyLibrary
{
    public static class ConfigurationManager
    {
        public static T GetProperty<T>(string key, T defaultValue)
        {
            // Returns the value which is linked by key.
            // If any errors are occurred, returns defaultValue.
            // ...
            return default(T);
        }
    }
}
