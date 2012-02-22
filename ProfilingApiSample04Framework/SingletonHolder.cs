
namespace ProfilingApiSample04Framework
{
    public class SingletonHolder<T>
    {
        static SingletonHolder<T> ms_instance = new SingletonHolder<T>();
        public static SingletonHolder<T> Instance { get { return ms_instance; } }
        public T Source { get; set; }
    }
}
