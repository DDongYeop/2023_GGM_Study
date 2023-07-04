using System;
using System.Collections;
using System.Collections.Generic;
using DG.Tweening;
using UnityEngine;
using UnityEngine.Rendering.Universal;
using UnityEngine.Serialization;

public class DropDecal : PoolableMono
{
    private DecalProjector _decalProjecter;
    [FormerlySerializedAs("_defaltSize")] [SerializeField] private float _defaultSize = 3f;

    private readonly int _alphaHash = Shader.PropertyToID("_Alpha");
    private readonly int _sizeHash = Shader.PropertyToID("_Size");
    
    public override void Init()
    {
        _decalProjecter.material.SetFloat(_alphaHash, 1); //풀에서 꺼내면 초기화
    }

    private void Awake()
    {
        _decalProjecter = GetComponent<DecalProjector>();
        _decalProjecter.material = new Material(_decalProjecter.material);
    }

    public void StartSeq(Action EndCallback)
    {
        Material targetMat = _decalProjecter.material;
        targetMat.SetFloat(_sizeHash, 0);

        DOTween.To(
            getter: () => targetMat.GetFloat(_sizeHash),
            setter: value => targetMat.SetFloat(_sizeHash, value),
            endValue: 1,
            duration: 1f).SetEase(Ease.InOutSine)
            .OnComplete(() => EndCallback());
    }

    public void FadeOut(float time)
    {
        Material targetMat = _decalProjecter.material;
        DOTween.To(
            getter: () => targetMat.GetFloat(_alphaHash),
            setter: value => targetMat.SetFloat(_alphaHash, value),
            endValue: 0,
            duration: time).OnComplete(GotoPool);
    }

    public void GotoPool()
    {
        PoolManager.Instance.Push(this);
    }

    public void SetUpSize(Vector3 size)
    {
        _decalProjecter.size = size; //x,y == width, height | z == 깊이
        _defaultSize = size.x;
    }

#if UNITY_EDITOR

    private void OnDrawGizmos()
    {
        Gizmos.color = Color.red;
        Gizmos.DrawWireSphere(transform.position, _defaultSize * 0.5f);
        Gizmos.color = Color.white;
    }

#endif
}
