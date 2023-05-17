using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BlinkFeedback : Feedback
{
    [SerializeField]
    private SkinnedMeshRenderer _meshRenderer;
    [SerializeField]
    private float _blinkTime = 0.2f;

    private MaterialPropertyBlock _matPropBlock;

    private readonly int _blinkHash = Shader.PropertyToID("_Blink");

    private void Awake()
    {
        _matPropBlock = new MaterialPropertyBlock();
        _meshRenderer.GetPropertyBlock(_matPropBlock); //여기에 해당 메티리얼에 있는 프로퍼티를 가져와준다.
    }

    public override void CreateFeedback()
    {
        StartCoroutine(MaterialBlink());
    }

    IEnumerator MaterialBlink()
    {
        _matPropBlock.SetFloat(_blinkHash, 0.5f);
        _meshRenderer.SetPropertyBlock(_matPropBlock);

        yield return new WaitForSeconds(_blinkTime);

        _matPropBlock.SetFloat(_blinkHash, 0);
        _meshRenderer.SetPropertyBlock(_matPropBlock);
    }

    public override void FinishFeedback()
    {
        StopAllCoroutines(); //이 비해비어에서 관리하는 모든 코루틴 종료
        _matPropBlock.SetFloat(_blinkHash, 0);
        _meshRenderer.SetPropertyBlock(_matPropBlock);

    }
}
