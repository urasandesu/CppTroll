using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;

namespace ProfilingApiSample04Framework
{
    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode)]
    public struct IndiretionInfo
    {
        public string m_assemblyName;
        public string m_typeFullName;
        public string m_methodName;
    }

    public static class Indiretion
    {
        [DllImport("ProfilingApiSample04.dll", EntryPoint = "IndiretionGetFunctionPointer")]
        [return: MarshalAs(UnmanagedType.Bool)]
        public static extern bool GetFunctionPointer(ref IndiretionInfo pInfo, ref int pFuncPtr);

        [DllImport("ProfilingApiSample04.dll", EntryPoint = "IndiretionSetFunctionPointer")]
        [return: MarshalAs(UnmanagedType.Bool)]
        public static extern bool SetFunctionPointer(ref IndiretionInfo pInfo, int funcPtr);
    }
}
