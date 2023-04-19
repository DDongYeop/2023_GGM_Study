using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Events;

public class DissolveFeedback : Feedback
{
    [SerializeField] private SkinnedMeshRenderer _skinnedMeshRenderer;

    private MaterialPropertyBlock _materialProp;

    public UnityEvent OfAfterDissolve = null; //디졸브 끝나고 할 일

    private readonly int _dissolveHeightHash = Shader.PropertyToID("_DissolveHeight");
    private readonly int _isDissolveHash = Shader.PropertyToID("_IsDissolve");
    
    private void Awake()
    {
        _materialProp = new MaterialPropertyBlock();
        _skinnedMeshRenderer.GetPropertyBlock(_materialProp);
    }

    public override void CreateFeedback()
    {
        StartCoroutine(MaterialDissolve());
    }

    private IEnumerator MaterialDissolve()
    {
        float dissolveTime = 2f;
        float current = 0;
        float dissolveHeightStart = 5f;
        float dissolveHeightTarget = -5f;
        float dissolveHeight = 0;
        
        _materialProp.SetFloat(_isDissolveHash, 1); //true
        _skinnedMeshRenderer.SetPropertyBlock(_materialProp);

        while (current < dissolveTime)
        {
            current += Time.deltaTime;
            dissolveHeight = Mathf.Lerp(dissolveHeightStart, dissolveHeightTarget, current / dissolveTime);
            _materialProp.SetFloat(_dissolveHeightHash, dissolveHeight);
            _skinnedMeshRenderer.SetPropertyBlock(_materialProp);
            yield return null;
        }
        {
            
        }
    }

    public override void FinishFeedback()
    {
        StopAllCoroutines();
        _materialProp.SetFloat(_isDissolveHash, 0); //true는 1, false는 0 넣으면 된다. 
        _materialProp.SetFloat(_dissolveHeightHash, 5f); //5는 초기화
        _skinnedMeshRenderer.SetPropertyBlock(_materialProp);
    }
}
