using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Sample03Lib;

namespace Sample03Test
{
    class Program
    {
        static void Main(string[] args)
        {
            var mg = new MyEnumerableGenerator();
            var m = mg.CreateInstance();
            foreach (var item in m)
            {
                Console.WriteLine("Item: {0}", item);
            }

            Console.ReadLine();
        }
    }
}
