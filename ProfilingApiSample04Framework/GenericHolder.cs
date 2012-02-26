namespace ProfilingApiSample04Framework
{
    public class GenericHolder<T> : InstanceHolder<GenericHolder<T>>
    {
        GenericHolder() { }
        public T Source { get; set; }
    }
}
