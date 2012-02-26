using ProfilingApiSample04Framework.Mixin.System;

namespace ProfilingApiSample04Framework
{
    public abstract class InstanceHolder<T> where T : InstanceHolder<T>
    {
        protected InstanceHolder() { }
        static T ms_instance = TypeMixin.ForciblyNew<T>();
        public static T Instance { get { return ms_instance; } }
    }
}
