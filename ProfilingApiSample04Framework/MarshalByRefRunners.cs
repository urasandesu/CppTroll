using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ProfilingApiSample04Framework
{
    //public class MarshalByRefRunner : AbstractMarshalByRefRunner
    //{
    //    public new Action Action { get { return (Action)base.Action; } set { base.Action = value; } }
    //}

    //public class MarshalByRefRunner<T> : AbstractMarshalByRefRunner
    //{
    //    public new Action<T> Action { get { return (Action<T>)base.Action; } set { base.Action = value; } }
    //}
    
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
