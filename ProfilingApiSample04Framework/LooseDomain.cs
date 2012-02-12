using System;
using System.Reflection;
using System.Reflection.Emit;
using System.Threading;

namespace ProfilingApiSample04Framework
{
    public static class LooseDomain
    {
        public static void Register<T>(Func<T> instanceGetter) where T : class
        {
            LooseDomain<T>.Register(instanceGetter);
        }

        public static void Unload<T>() where T : class
        {
            LooseDomain<T>.Unload();
        }

        public static T Get<T>() where T : class
        {
            return LooseDomain<T>.Instance;
        }

        public static T GetOrRegister<T>(Func<T> instanceGetter) where T : class
        {
            var instance = default(T);
            if ((instance = LooseDomain<T>.InstanceOrDefault) == null)
            {
                LooseDomain<T>.Register(instanceGetter);
                instance = LooseDomain<T>.Instance;
            }
            return instance;
        }

        public static bool TryGet<T>(out T instance) where T : class
        {
            instance = LooseDomain<T>.InstanceOrDefault;
            return instance != null;
        }
    }

    public sealed class LooseDomain<T> where T : class
    {
        static readonly object ms_lockObj = new object();
        static T ms_instance = null;
        static bool ms_ready = false;

        LooseDomain() { }

        public static void Register(Func<T> instanceGetter)
        {
            Register(instanceGetter.Method);
        }

        public static void Register(MethodInfo method)
        {
            if (!method.IsStatic)
                throw new ArgumentException("The parameter must be the reference of a " +
                                            "static method.");

            var funcPtr = method.MethodHandle.GetFunctionPointer();
            InstanceGetters.TryAdd(typeof(T).AssemblyQualifiedName, funcPtr);
        }

        static T GetInstance()
        {
            var funcPtr = default(IntPtr);
            if (!InstanceGetters.TryGet(typeof(T).AssemblyQualifiedName, out funcPtr))
                throw new InvalidOperationException("The instance getter of T has not been " +
                            "registered yet. Please call the method Register and give a " +
                            "instance getter to it.");

            return GetInstanceCore(funcPtr);
        }

        static bool TryGetInstance(out T instance)
        {
            var funcPtr = default(IntPtr);
            if (!InstanceGetters.TryGet(typeof(T).AssemblyQualifiedName, out funcPtr))
            {
                instance = null;
                return false;
            }
            else
            {
                instance = GetInstanceCore(funcPtr);
                return true;
            }
        }

        static T GetInstanceCore(IntPtr funcPtr)
        {
            var instanceGetter = new DynamicMethod("Instantiator", typeof(T), null, typeof(T).Module);
            var gen = instanceGetter.GetILGenerator();
            if (IntPtr.Size == 4)
            {
                gen.Emit(OpCodes.Ldc_I4, funcPtr.ToInt32());
            }
            else if (IntPtr.Size == 8)
            {
                gen.Emit(OpCodes.Ldc_I8, funcPtr.ToInt64());
            }
            else
            {
                throw new NotSupportedException();
            }
            gen.EmitCalli(OpCodes.Calli, CallingConventions.Standard, typeof(T), null, null);
            gen.Emit(OpCodes.Ret);
            return ((Func<T>)instanceGetter.CreateDelegate(typeof(Func<T>)))();
        }

        public static T Instance
        {
            get
            {
                if (!ms_ready)
                {
                    lock (ms_lockObj)
                    {
                        if (!ms_ready)
                        {
                            ms_instance = GetInstance();
                            Thread.MemoryBarrier();
                            ms_ready = true;
                        }
                    }
                }
                // !! Type is not checked by CLR if a opcode castclass does not exist !!
                return ms_instance;
            }
        }

        public static T InstanceOrDefault
        {
            get
            {
                if (!ms_ready)
                {
                    lock (ms_lockObj)
                    {
                        if (!ms_ready)
                        {
                            var instance = default(T);
                            if (TryGetInstance(out instance))
                            {
                                ms_instance = instance;
                                Thread.MemoryBarrier();
                                ms_ready = true;
                            }
                        }
                    }
                }
                return ms_instance;
            }
        }

        public static void Unload()
        {
            if (ms_ready)
            {
                lock (ms_lockObj)
                {
                    if (ms_ready)
                    {
                        InstanceGetters.Unload();
                        ms_instance = null;
                        Thread.MemoryBarrier();
                        ms_ready = false;
                    }
                }
            }
        }
    }
}
