using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class IdleAction : AIAction
{
    private SpriteRenderer _spriteRenderer;

    private readonly int _normalState = Shader.PropertyToID("_NormalState");

    public override void SetUp(AIBrain brain)
    {
        base.SetUp(brain);
        _spriteRenderer = brain.GetComponent<SpriteRenderer>();
    }
    
    public override void TakeAction()
    {
        _brain.NavAgentCompo.StopImmediately();
        /*Material mat = _spriteRenderer.material;
        mat.SetInt(_normalState, 1);*/
    }
}
