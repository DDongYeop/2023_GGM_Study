using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ParticleEffect : PoolableMono
{
    [SerializeField] private ParticleSystem _particle;
    [SerializeField] private float _effectTime;

    public void PlayParticle(Vector3 position, Quaternion dir)
    {
        transform.position = position;
        transform.rotation = dir;
        _particle.Play();

        StartCoroutine(DissapearParticle());
    }

    private IEnumerator DissapearParticle()
    {
        yield return new WaitForSeconds(_effectTime);
        PoolManager.Instance.Push(this);
    }

    public override void Init()
    {
        _particle.Stop();
        _particle.Simulate(0);
    }
}
