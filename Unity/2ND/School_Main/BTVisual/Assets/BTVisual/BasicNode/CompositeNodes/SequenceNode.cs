using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace BTVisual
{
    public class SequenceNode : CompositeNode
    {
        private int _current = 0;
        
        protected override void OnStart()
        {
            _current = 0;
        }

        protected override void OnStop()
        {
        }

        protected override State OnUpdate()
        {
            // 지금 실행할 차일드를 골라와서 실행을하고
            // 그 결과에 따라서 작동을 다음과 같이 해야한다 
            // Running => Running
            // Failure => Failure
            // Success => 다음 친구로 ㄱㄱ
            
            // 현재 자식 넘버가 전체 자식넘버 
            // Success
            // 그게 아니면 
            // Running

            switch (children[_current].Update())
            {
                case State.SUCCESS:
                    _current++;
                    break;
                case State.RUNNING:
                    return State.RUNNING;
                case State.FAILURE:
                    return State.FAILURE;
            }

            return _current == children.Count ? State.SUCCESS : State.RUNNING;
        }
    }
}
