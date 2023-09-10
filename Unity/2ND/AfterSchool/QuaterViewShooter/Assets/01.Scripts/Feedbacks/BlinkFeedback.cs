using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BlinkFeedback : Feedback
{
    [SerializeField] private SkinnedMeshRenderer _meshRenderer;
    [SerializeField] private float _blinkTime = 0.2f;

    private MaterialPropertyBlock _matPropBlock;
    private int _blinkHash = Shader.PropertyToID("_Blink");

    private void Awake()
    {
        _matPropBlock = new MaterialPropertyBlock();
        _meshRenderer.GetPropertyBlock(_matPropBlock);
    }

    public override void CompletePreFeedback()
    {
        
    }
    
    public override void CreateFeedback()
    {
        //빤딱빤딱과제 
        // 0.2초 후에 다시 돌아오기 
    }
}
