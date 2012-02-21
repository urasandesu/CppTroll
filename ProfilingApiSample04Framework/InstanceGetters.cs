using System;
using System.Runtime.InteropServices;

namespace ProfilingApiSample04Framework
{
    public static class InstanceGetters
    {
        [DllImport("ProfilingApiSample04.dll", EntryPoint = "InstanceGettersTryAdd")]
        [return: MarshalAs(UnmanagedType.Bool)]
        public static extern bool TryAdd([MarshalAs(UnmanagedType.LPWStr)] string key, IntPtr pFuncPtr);

        [DllImport("ProfilingApiSample04.dll", EntryPoint = "InstanceGettersTryGet")]
        [return: MarshalAs(UnmanagedType.Bool)]
        public static extern bool TryGet([MarshalAs(UnmanagedType.LPWStr)] string key, out IntPtr ppFuncPtr);

        [DllImport("ProfilingApiSample04.dll", EntryPoint = "InstanceGettersTryRemove")]
        [return: MarshalAs(UnmanagedType.Bool)]
        public static extern bool TryRemove([MarshalAs(UnmanagedType.LPWStr)] string key, out IntPtr ppFuncPtr);

        [DllImport("ProfilingApiSample04.dll", EntryPoint = "InstanceGettersClear")]
        public static extern void Clear();
    }
}
