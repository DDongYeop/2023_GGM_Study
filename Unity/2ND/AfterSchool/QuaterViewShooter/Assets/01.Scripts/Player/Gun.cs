using System.Collections;
using System.Collections.Generic;
using Cinemachine;
using UnityEngine;

public class Gun : MonoBehaviour
{
    [Header("참조 값들")]
    [SerializeField] private LineRenderer _lineRenderer;
    [SerializeField] private ParticleSystem _particleSystem;
    [SerializeField] private ParticleSystem _impactPrefab;
    [SerializeField] private CinemachineImpulseSource _impulseSource;

    [Header("셋팅 값들")] 
    [SerializeField] private float _coolTime = 0.3f;

    private float _lastFireTime = 0;
    
    public void TryToFire()
    {
        if (Time.time < _coolTime + _lastFireTime)
            return;
        Fire();
        _lastFireTime = Time.time;
    }
    
    public void Fire()
    {
        _particleSystem.Play();
        _impulseSource.GenerateImpulse(.2f);
        Vector3 destination = transform.forward * 20f + transform.position;
        
        if(Physics.Raycast(transform.position, transform.forward, out var hit, 20f))
        {
            destination = hit.point;
            var impact = Instantiate(_impactPrefab, hit.point, Quaternion.LookRotation(hit.normal));
            impact.Play();
            Destroy(impact.gameObject, 2f);
        }

        StartCoroutine(MuzzleCoroutine(destination));
    }

    private IEnumerator MuzzleCoroutine(Vector3 destination)
    {
        Vector3 start = transform.position;
        _lineRenderer.positionCount = 2;
        _lineRenderer.SetPosition(0, start);
        _lineRenderer.SetPosition(1, destination);
        _lineRenderer.enabled = true;
        
        yield return new WaitForSeconds(0.1f);
        _lineRenderer.enabled = false;
    }
}
