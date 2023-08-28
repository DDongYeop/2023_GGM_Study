using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Selector : Composite
{
    public Selector(BehaviorTree t, BT_Node[] nodes) : base(t, nodes) { }

    public override Result Execute()
    {
        foreach (var child in children)
        {
            Result result = child.Execute();

            if (result == Result.Success)
                return Result.Success;
            else if (result == Result.Running)
                return Result.Running;
        }

        return Result.Fail;
    }
}
