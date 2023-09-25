using System.Collections;
using System.Collections.Generic;
using BTVisual;
using UnityEngine;

public class FOVNode : ActionNode
{
    public float range;
    public LayerMask obstacle;
    
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

        if (cnt <= 0)
        {
            brain.NavAgent.isStopped = true;
            blackboard.enemySpotPosition = brain.transform.position;
            brain.NavAgent.destination = blackboard.enemySpotPosition;
            return State.FAILURE;
        }    
        
        float distance = Vector3.Distance(brain.transform.position, targets[0].transform.position);
        if (Physics.Raycast(brain.transform.position, (targets[0].transform.position - brain.transform.position).normalized, distance, obstacle))
        {
            brain.NavAgent.isStopped = true;
            blackboard.enemySpotPosition = brain.transform.position;
            brain.NavAgent.destination = blackboard.enemySpotPosition;
            return State.RUNNING;
        }

        return State.SUCCESS;
    }
}
