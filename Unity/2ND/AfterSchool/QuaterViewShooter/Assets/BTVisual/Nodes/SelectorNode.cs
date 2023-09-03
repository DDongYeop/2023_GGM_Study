using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace BTVisual
{
    public class SelectorNode : CompositeNode
    {
        protected int _current;
        
        protected override void OnStart()
        {
            _current = 0;
        }

        protected override void OnStop()
        {
            
        }

        protected override State OnUpdate()
        {
            for (int i = _current; i < children.Count; ++i)
            {
                _current = i;
                var child = children[_current];
                switch (child.Update())
                {
                    case State.RUNNING:
                        return State.RUNNING;
                        break;
                    case State.FAILURE:
                        //실패하면 아무것도 안함. 다음노드로 바로 넘어간다.
                        break;
                    case State.SUCCESS:
                        return State.SUCCESS;
                }
            }
            
            return State.FAILURE; //다 돌아도 실패면 실패
        }
    }
}