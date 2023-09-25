using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using BTVisual;

public class InRangeNode : ActionNode
{
    public float range;
    public bool isChase;

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
        else
        {
            if (isChase)
            {
                brain.NavAgent.isStopped = true;
                blackboard.enemySpotPosition = brain.transform.position;
                brain.NavAgent.destination = blackboard.enemySpotPosition;
            }
        }
        return State.FAILURE;
    }
}