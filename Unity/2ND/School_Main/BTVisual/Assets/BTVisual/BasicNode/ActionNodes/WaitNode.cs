using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace BTVisual
{
    public class WaitNode : ActionNode
    {
        public float duration = 1f;

        private float _startTime;
        
        protected override void OnStart()
        {
            //시작할때 _startTime 저장
            _startTime = Time.time;
        }

        protected override void OnStop()
        {
            
        }

        protected override State OnUpdate()
        {
            //duration만큼 지났다면 Success
            //아니라면 Running
            if (_startTime + duration > Time.time)
                return State.RUNNING;
            return State.SUCCESS;
        }
    }
}
