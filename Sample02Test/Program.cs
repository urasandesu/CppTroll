using System;
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
            myCache.set_Item(keys[3], new DateTime(2011, 5, 19, 23, 56, 41));
            myCache.set_Item(keys[4], 10d);

            Console.WriteLine("MyCache.Count: {0}", myCache.Count);
            for (int i = 0; i < keys.Length; i++)
            {
                Console.WriteLine("MyCache[{0}]: {1}", keys[i], myCache.get_Item(keys[i]));
            }
            // Messages will display as below: 
            // MyCache[a]: 1
            // MyCache[i]: mogeta
            // MyCache[u]: Sample02Test.A
            // MyCache[e]: 2011/05/19 23:56:41
            // MyCache[o]: 10
            // 
            Console.WriteLine();
            Console.WriteLine("--------------------------------------------------");
            Console.WriteLine();

            foreach (PairBStrVariant item in myCache)
            {
                Console.WriteLine("MyCache[{0}]: {1}", item.First, item.Second);
            }
            // Messages will display as below: 
            // MyCache[i]: mogeta
            // MyCache[u]: Sample02Test.A
            // MyCache[a]: 1
            // MyCache[o]: 10
            // MyCache[e]: 2011/05/19 23:56:41
            // 
            Console.WriteLine();
            Console.WriteLine("--------------------------------------------------");
            Console.WriteLine();

            myCache.set_Item("f", new NotImplemented());
            var printer = new MyCachePrinter();
            try
            {
                printer.Print();
                // Messages will display as below: 
                // MyCache[i]:  mogeta
                // MyCache[u]:  Sample02Test.A
                // MyCache[a]:   1
                // MyCache[o]:  10
                // MyCache[e]:  2011/05/19 23:56:42
            }
            catch (NotImplementedException e)
            {
                Console.WriteLine(e.Message);   // Message will display as "Error, World !!".
            }

            Console.ReadLine();
        }
    }

    class A
    {
        public int Key { get; set; }
        public string Value { get; set; }
    }

    class NotImplemented
    {
        public override string ToString()
        {
            // This exception's message will be overwritten by MyCachePrinter.
            throw new NotImplementedException();
        }
    }
}
