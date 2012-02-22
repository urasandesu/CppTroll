using System;

namespace ProfilingApiSample04Framework
{
    class MarshalByRefRunner : MarshalByRefObject
    {
        public Delegate Action { get; set; }
        public void Run(params object[] args)
        {
            if (Action != null)
                Action.DynamicInvoke(args);
        }
    }
}
