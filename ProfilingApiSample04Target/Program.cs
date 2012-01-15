using System;
using MyLibrary;
using ThirdPartyLibrary;

namespace ProfilingApiSample04Target
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
            Console.WriteLine("時刻: " + now.Hour + "\t" +
                (12 <= now.Hour && now.Hour < 13 ? "お昼休みなう！" : "お仕事なう・・・"));
        }

        public static void Holiday()
        {
            var dayOfWeek = ConfigurationManager.GetProperty("Holiday", DayOfWeek.Sunday);
            var now = DateTime.Now;
            Console.WriteLine("曜日: " + now.DayOfWeek + "\t" +
                (now.DayOfWeek == dayOfWeek ? "休日なう！" : "お仕事なう・・・"));
        }
    }
}

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
