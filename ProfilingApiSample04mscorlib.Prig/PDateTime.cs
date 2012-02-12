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
                    info.AssemblyName = t.Assembly.FullName;
                    info.TypeFullName = t.FullName;
                    info.MethodName = "get_Now";
                    if (value == null)
                    {
                        var holder = default(IndirectionHolder<Func<DateTime>>);
                        if (LooseDomain.TryGet(out holder))
                        {
                            var method = default(Func<DateTime>);
                            holder.TryRemove(info, out method);
                        }
                    }
                    else
                    {
                        var holder = LooseDomain.GetOrRegister(() => IndirectionHolder<Func<DateTime>>.Instance);
                        holder.AddOrUpdate(info, value);
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
