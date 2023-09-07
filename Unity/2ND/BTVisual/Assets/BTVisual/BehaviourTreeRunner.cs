using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace BTVisual
{
    public class BehaviourTreeRunner : MonoBehaviour
    {
        private BehaviourTree _tree;

        private void Start()
        {
            _tree = ScriptableObject.CreateInstance<BehaviourTree>();

            var wait1 = ScriptableObject.CreateInstance<WaitNode>();
            wait1.duration = 1;
            var debug1 = ScriptableObject.CreateInstance<DebugNode>();
            debug1.message = "Hello GGM1";
            
            var wait2 = ScriptableObject.CreateInstance<WaitNode>();
            wait2.duration = 2;
            var debug2 = ScriptableObject.CreateInstance<DebugNode>();
            debug2.message = "Hello GGM2";

            var seq = ScriptableObject.CreateInstance<SequenceNode>();
            seq.children.Add(wait1);
            seq.children.Add(debug1);
            seq.children.Add(wait2);
            seq.children.Add(debug2);

            var repeatNode = ScriptableObject.CreateInstance<RepeatNode>();
            repeatNode.child = seq;

            _tree.rootNode = repeatNode;

        }


        private void Update()
        {
            _tree.Update();
        }
    }
}
