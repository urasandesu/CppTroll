using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Sample02Lib;

namespace Sample02Test
{
    class Program
    {
        static void Main(string[] args)
        {
            var keys = new string[] { "a", "i", "u", "e", "o" };
            var myCache = new MyCache();
            myCache.set_Item(keys[0], 1);
            myCache.set_Item(keys[1], "mogeta");
            myCache.set_Item(keys[2], new A() { Key = 10, Value = "hoge" });
            myCache.set_Item(keys[3], DateTime.Now);
            myCache.set_Item(keys[4], 10d);

            Console.WriteLine("MyCache.Count: {0}", myCache.Count);
            for (int i = 0; i < keys.Length; i++)
            {
                Console.WriteLine("MyCache[{0}]: {1}", keys[i], myCache.get_Item(keys[i]));
            }
            Console.WriteLine();
            Console.WriteLine("--------------------------------------------------");
            Console.WriteLine();
            foreach (PairBStrVariant item in myCache)
            {
                Console.WriteLine("MyCache[{0}]: {1}", item.First, item.Second);
            }
            Console.WriteLine();
            Console.WriteLine("--------------------------------------------------");
            Console.WriteLine();
            var printer = new MyCachePrinter();
            printer.Print();

            Console.ReadLine();
        }
    }

    class A
    {
        public int Key { get; set; }
        public string Value { get; set; }
    }
}
