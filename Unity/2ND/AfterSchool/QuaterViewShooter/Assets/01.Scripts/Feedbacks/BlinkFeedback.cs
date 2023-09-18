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
        _meshRenderer.GetPropertyBlock(_matPropBlock); //해당 렌더러에 붙어있는 매티리얼의 프로퍼티 블록
    }

    public override void CompletePrevFeedback()
    {
        
    }

    public override void CreateFeedback()
    {
        //맞으면 
    }
}
