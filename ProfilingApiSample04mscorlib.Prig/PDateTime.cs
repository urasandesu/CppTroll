using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ProfilingApiSample04Framework;

namespace System.Prig
{
    public class PDateTime
    {
        public static class NowGet
        {
            public static Func<DateTime> Body
            {
                set
                {
                    var t = typeof(DateTime);
                    var info = new IndirectionInfo();
                    info.m_assemblyName = t.Assembly.FullName;
                    info.m_typeFullName = t.FullName;
                    info.m_methodName = "get_Now";
                    if (value == null)
                    {
                        Indirection.SetFunctionPointer(ref info, IntPtr.Zero);
                    }
                    else
                    {
                        Indirection.SetFunctionPointer(ref info, value.Method.MethodHandle.GetFunctionPointer());
                    }
                }
            }
        }
    }

    public class PDateTimeContext : IDisposable
    {
        bool m_disposed;

        public PDateTimeContext()
        {
        }

        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        protected virtual void Dispose(bool disposing)
        {
            if (!m_disposed)
            {
                if (disposing)
                {
                }
            }
            m_disposed = true;
        }

        ~PDateTimeContext()
        {
            Dispose(false);
        }

        public class NowGet : IDisposable
        {
            bool m_disposed;

            public NowGet()
            {
            }

            public void Dispose()
            {
                Dispose(true);
                GC.SuppressFinalize(this);
            }

            protected virtual void Dispose(bool disposing)
            {
                if (!m_disposed)
                {
                    if (disposing)
                    {
                        PDateTime.NowGet.Body = null;
                    }
                }
                m_disposed = true;
            }

            ~NowGet()
            {
                Dispose(false);
            }
        }
    }
}
