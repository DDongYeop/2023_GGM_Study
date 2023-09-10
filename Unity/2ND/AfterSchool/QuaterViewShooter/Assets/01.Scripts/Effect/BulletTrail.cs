using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BulletTrail : MonoBehaviour
{
    [SerializeField] private float _lifeTime = 0.2f;

    private TrailRenderer _trailRenderer;

    private void Awake()
    {
        _trailRenderer = GetComponent<TrailRenderer>();
    }

    public void DrawTrail(Vector3 startPos, Vector3 endPos, float lifeTime)
    {
        _trailRenderer.Clear(); //모든 점 제거
        _trailRenderer.AddPosition(startPos);
        transform.position = endPos;
        _trailRenderer.time = lifeTime;
        StartCoroutine(DestroyTimer());
    }

    private IEnumerator DestroyTimer()
    {
        yield return new WaitForSeconds(_lifeTime);
        Destroy(gameObject); //차후 풀메니저 
    }
}
