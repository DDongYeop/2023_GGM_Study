using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class IdleAction : AIAction
{
    private MeshRenderer _renderer;
    protected override void Awake()
    {
        base.Awake();
        _renderer = _brain.GetComponent<MeshRenderer>();
    }
    
    public override void TakeAction()
    {
        // do nothing;
        _renderer.material.color = new Color(0, 0, 1); //파란색 컬러로 셋
        _brain.SetDestination(_brain.transform.position);
    }
}
