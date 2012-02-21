using System;
using System.IO;
using ProfilingApiSample04FrameworkTest;
using ProfilingApiSample04Framework;

namespace ProfilingApiSample04FrameworkTest
{
    class Holder<T>
    {
        static Holder<T> ms_instance = new Holder<T>();
        public static Holder<T> Instance { get { return ms_instance; } }
        public T Source { get; set; }
    }
}
