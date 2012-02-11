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

        Dictionary<string, TDelegate> m_dict = new Dictionary<string, TDelegate>();

        public bool TryGet(IndirectionInfo2 info, out TDelegate method)
        {
            var key = info.AssemblyName + ", " + info.TypeFullName + ", " + info.MethodName;
            if (m_dict.ContainsKey(key))
            {
                method = m_dict[key];
                return true;
            }
            else
            {
                method = default(TDelegate);
                return false;
            }
        }

        public bool TryRemove(IndirectionInfo2 info, out TDelegate method)
        {
            var key = info.AssemblyName + ", " + info.TypeFullName + ", " + info.MethodName;
            if (m_dict.ContainsKey(key))
            {
                method = m_dict[key];
                m_dict.Remove(key);
                return true;
            }
            else
            {
                method = default(TDelegate);
                return false;
            }
        }

        public TDelegate AddOrUpdate(IndirectionInfo2 info, TDelegate method)
        {
            var key = info.AssemblyName + ", " + info.TypeFullName + ", " + info.MethodName;
            if (m_dict.ContainsKey(key))
            {
                m_dict.Add(key, method);
            }
            else
            {
                m_dict[key] = method;
            }
            return method;
        }
    }

    public struct IndirectionInfo2
    {
        public string AssemblyName { get; set; }
        public string TypeFullName { get; set; }
        public string MethodName { get; set; }
    }
}
