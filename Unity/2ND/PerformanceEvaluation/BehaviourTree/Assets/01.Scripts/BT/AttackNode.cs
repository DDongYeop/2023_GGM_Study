using System.Collections;
using System.Collections.Generic;
using BTVisual;
using UnityEngine;

public class AttackNode : ActionNode
{
    public float coolTime;

    private float _lastAttackTime;
    
    protected override void OnStart()
    {
        brain.NavAgent.isStopped = true;
    }

    protected override void OnStop()
    {
    }

    protected override State OnUpdate()
    {
        if (Time.time < coolTime + _lastAttackTime)
            return State.RUNNING;

        brain.transform.rotation = Quaternion.LookRotation(brain.targetTrm.position - brain.transform.position);
        
        brain.Attack();
        _lastAttackTime = Time.time;
        return State.SUCCESS;
    }
}