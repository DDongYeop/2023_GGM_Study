using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MuzzleFlashFeedback : Feedback
{
    [SerializeField] private Light _flashLight;
    [SerializeField] private bool _lightDefaultState = false;
    [SerializeField] private ParticleSystem _muzzleParticle;
    [SerializeField] private float _feedbackTime = 0.05f;

    public override void CompletePreFeedback()
    {
        StopAllCoroutines();
        _muzzleParticle.Stop();
        _muzzleParticle.Simulate(0);
        _flashLight.enabled = _lightDefaultState;
    }
    
    public override void CreateFeedback()
    {
        _muzzleParticle.Play();
        _flashLight.enabled = !_lightDefaultState;
        StartCoroutine(MuzzleFlash());
    }

    private IEnumerator MuzzleFlash()
    {
        yield return new WaitForSeconds(_feedbackTime);
        _muzzleParticle.Stop();
        _muzzleParticle.Simulate(0);
        _flashLight.enabled = _lightDefaultState;
    }
}
