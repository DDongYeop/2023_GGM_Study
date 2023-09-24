using System.Collections;
using System.Collections.Generic;
using BTVisual;
using UnityEngine;

public class MagazineEmptyNode : ActionNode
{
    protected override void OnStart()
    {
    }

    protected override void OnStop()
    {
    }

    protected override State OnUpdate()
    {
        if (brain.CurrentMagazine <= 0)
        {
            return State.SUCCESS;
        }

        return State.FAILURE;
    }
}
