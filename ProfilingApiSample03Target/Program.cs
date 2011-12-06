using System;
using System.Prig;

namespace ProfilingApiSample03Target
{
    class Program
    {
        static void Main(string[] args)
        {
            PDateTime.NowGet.Body = () => new DateTime(2011, 11, 11, 11, 11, 11);
            Console.WriteLine(DateTime.Now + "なう！");
        }
    }
}
