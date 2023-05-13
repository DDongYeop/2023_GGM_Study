using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BrokenEffect : MonoBehaviour
{
    private ParticleSystem _boxParticle;
    private ParticleSystem _trailParticle;


    private void Awake()
    {
        _boxParticle = GetComponent<ParticleSystem>();
        _trailParticle = transform.Find("TrailEffect").GetComponent<ParticleSystem>();
    }

    public void PlayEffect(Vector2 dir)
    {
        var boxVModule = _boxParticle.velocityOverLifetime;
        boxVModule.x = dir.x;
        boxVModule.y = dir.y;


        var trailVModuel = _trailParticle.velocityOverLifetime;
        trailVModuel.x = dir.x;
        trailVModuel.y = dir.y;

        _boxParticle.Play();
        _trailParticle.Play();

        Destroy(gameObject, 2f);
    }
}
