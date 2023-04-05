using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ChaseAction : AIAction
{
    private MeshRenderer _renderer;
    
    protected override void Awake()
    {
        base.Awake();
        _renderer = _brain.GetComponent<MeshRenderer>();
    }
    
    public override void TakeAction()
    {
        _brain.SetDestination(_brain.TargetTrm.position);
        _renderer.material.color = new Color(1, 0, 0); //파란색 컬러로 셋
    }
}
