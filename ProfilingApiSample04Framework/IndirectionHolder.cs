using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ProfilingApiSample04Framework
{
    public class IndirectionHolder<TDelegate>
    {
        IndirectionHolder() { }
        static IndirectionHolder<TDelegate> ms_instance = new IndirectionHolder<TDelegate>();
        public static IndirectionHolder<TDelegate> Instance { get { return ms_instance; } }

        public bool TryGet(IndirectionInfo2 info, out TDelegate method)
        {
            throw new NotImplementedException();
        }

        public bool TryRemove(IndirectionInfo2 info, out TDelegate method)
        {
            throw new NotImplementedException();
        }

        public TDelegate AddOrUpdate(IndirectionInfo2 info, TDelegate method)
        {
            throw new NotImplementedException();
        }
    }

    public struct IndirectionInfo2
    {
        public string AssemblyName { get; set; }
        public string TypeFullName { get; set; }
        public string MethodName { get; set; }
    }
}
