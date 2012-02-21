using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

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
