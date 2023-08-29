using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GotoTarget : Node
{
    private Func<NodeState> action;

    public GotoTarget(Func<NodeState> action)
    {
        this.action = action;
    }

    public override NodeState Evaluate()
    {
        return action.Invoke();
    }
}
