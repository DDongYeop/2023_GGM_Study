using System.Collections;
using System.Collections.Generic;
using BTVisual;
using UnityEngine;

public class ReloadingNode : ActionNode
{
    public float CoolTime;
    private float _reloadingTime;
    
    protected override void OnStart()
    {
        _reloadingTime = Time.time;
    }

    protected override void OnStop()
    {
    }

    protected override State OnUpdate()
    {
        if (_reloadingTime + CoolTime >= Time.time)
            return State.RUNNING;

        brain.CurrentMagazine = brain.MaxMagazine;
        return State.SUCCESS;
    }
}
