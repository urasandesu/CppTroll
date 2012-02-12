using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;

namespace ProfilingApiSample04Framework
{
    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode)]
    public struct IndirectionInfo
    {
        public string m_assemblyName;
        public string m_typeFullName;
        public string m_methodName;
    }

    public static class Indirection
    {
        [DllImport("ProfilingApiSample04.dll", EntryPoint = "IndirectionGetFunctionPointer")]
        [return: MarshalAs(UnmanagedType.Bool)]
        public static extern bool GetFunctionPointer(ref IndirectionInfo pInfo, ref IntPtr ppFuncPtr);

        [DllImport("ProfilingApiSample04.dll", EntryPoint = "IndirectionSetFunctionPointer")]
        [return: MarshalAs(UnmanagedType.Bool)]
        public static extern bool SetFunctionPointer(ref IndirectionInfo pInfo, IntPtr pFuncPtr);

        //[DllImport("ProfilingApiSample04.dll", EntryPoint = "IndirectionTryAdd")]
        //[return: MarshalAs(UnmanagedType.Bool)]
        //public static extern bool TryAdd(string key, IntPtr pFuncPtr);

        //[DllImport("ProfilingApiSample04.dll", EntryPoint = "IndirectionTryGet")]
        //[return: MarshalAs(UnmanagedType.Bool)]
        //public static extern bool TryGet(string key, out IntPtr ppFuncPtr);

        //[DllImport("ProfilingApiSample04.dll", EntryPoint = "IndirectionUnload")]
        //public static extern void Unload();
    }

    public static class InstanceGetters
    {
        [DllImport("ProfilingApiSample04.dll", EntryPoint = "InstanceGettersTryAdd")]
        [return: MarshalAs(UnmanagedType.Bool)]
        public static extern bool TryAdd([MarshalAs(UnmanagedType.LPWStr)] string key, IntPtr pFuncPtr);

        [DllImport("ProfilingApiSample04.dll", EntryPoint = "InstanceGettersTryGet")]
        [return: MarshalAs(UnmanagedType.Bool)]
        public static extern bool TryGet([MarshalAs(UnmanagedType.LPWStr)] string key, out IntPtr ppFuncPtr);

        [DllImport("ProfilingApiSample04.dll", EntryPoint = "InstanceGettersUnload")]
        public static extern void Unload();
    }
}
