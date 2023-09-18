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
        _meshRenderer.GetPropertyBlock(_matPropBlock); //�ش� �������� �پ��ִ� ��Ƽ������ ������Ƽ ���
    }

    public override void CompletePrevFeedback()
    {
        
    }

    public override void CreateFeedback()
    {
        //������ 
    }
}
