using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

#if NULL
namespace Anonym.System
{
    public static class ADateTime
    {
        public static DateTime Now
        {
            get
            {
                return new DateTime(2011, 11, 11, 11, 11, 11);
            }
        }
    }
}

namespace ProfilingApiSample03Patch
{
    public class Hoge<T>
    {
        
    }
}
#endif

namespace System.Prig
{
    public static class PDateTime
    {
        public static class NowGet
        {
            static Func<DateTime> m_body;

            public static Func<DateTime> Body
            {
                get
                {
                    return m_body;
                }
                set
                {
                    m_body = value;
                }
            }
        }
    }
}
