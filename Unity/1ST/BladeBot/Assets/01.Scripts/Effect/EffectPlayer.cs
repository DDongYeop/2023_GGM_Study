using System.Collections;
using System.Collections.Generic;
using System.Threading;
using UnityEngine;
using UnityEngine.VFX;

public class EffectPlayer : PoolableMono
{
    [SerializeField] protected List<ParticleSystem> _particle;
    [SerializeField] protected List<VisualEffect> _effects;

    public void StartPlay(float endTime)
    {
        if (_particle != null)
            _particle.ForEach(p => p.Play());
        if (_effects != null)
            _effects.ForEach(e => e.Play());

        StartCoroutine(Timer(endTime));
    }

    protected IEnumerator Timer(float timer)
    {
        yield return new WaitForSeconds(timer);
        PoolManager.Instance.Push(this);
    }
    
    public override void Init()
    {
        if (_particle != null)
            _particle.ForEach(p =>
            {
                p.Simulate(0);
                p.Stop();
            });
        if (_effects != null)
            _effects.ForEach(e => e.Play());
    }
}
