using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using BTVisual;

public class InRangeNode : ActionNode
{
    public float range;

    protected override void OnStart()
    {
    }

    protected override void OnStop()
    {
    }

    protected override State OnUpdate()
    {
        Collider[] targets = new Collider[1];
        int cnt = Physics.OverlapSphereNonAlloc(brain.transform.position, range, targets, blackboard.whatIsEnemy);

        if (cnt >= 1)
        {
            blackboard.enemySpotPosition = targets[0].transform.position;
            return State.SUCCESS;
        }
        return State.FAILURE;
    }
}