using UnityEngine;
using UnityEngine.VFX;

public class PlayerVFXManager : MonoBehaviour
{
    [SerializeField]
    private ParticleSystem[] _blades;

    [SerializeField]
    private VisualEffect _footStep;

    [SerializeField]
    private VisualEffect _healEffect;
    private AttackState _atkState;

    private void Awake()
    {
        _atkState = transform.Find("States").GetComponent<AttackState>();
        _atkState.OnAttackStart += PlayBlade;
        _atkState.OnAttackEnd += StopBlade;
    }

    public void UpdateFootStep(bool state)
    {
        if(state)
        {
            _footStep.Play();
        }else
        {
            _footStep.Stop();
        }
    }

    private void StopBlade()
    {
        foreach (ParticleSystem p in _blades)
        {
            p.Simulate(0); //초기상태로 돌리고
            p.Stop();
        }
    }

    private void PlayBlade(int combo)
    {
        _blades[combo - 1].Play();
    }

    public void PlayHealEffect()
    {
        _healEffect.Play();
    }
}
