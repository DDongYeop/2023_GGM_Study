using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[RequireComponent(typeof(AudioSource))]
public class Resource : PoolableMono
{
    [SerializeField] private ResourceDataSO _resourceData;
    public ResourceDataSO ResourceData => _resourceData;
    private AudioSource _audioSource;
    private Collider _collider;

    private void Awake()
    {
        _audioSource = GetComponent<AudioSource>();
        _audioSource.clip = _resourceData.UseSound; //사용 사운드 넣기
        _collider = GetComponent<Collider>();
    }

    public void PickUpResource()
    {
        StartCoroutine(DestroyCoroutine());
    }

    private IEnumerator DestroyCoroutine()
    {
        if (_audioSource.clip != null)
        {
            _audioSource.Play();
            yield return new WaitForSeconds(_audioSource.clip.length + 0.3f);
        }
        else
        {
            yield return null;
        }
        
        PoolManager.Instance.Push(this);
    }

    public override void Init()
    {
        gameObject.layer = LayerMask.NameToLayer("Resource");
        _collider.enabled = true;
    }

    private void OnDisable()
    {
        StopAllCoroutines();
    }
}
