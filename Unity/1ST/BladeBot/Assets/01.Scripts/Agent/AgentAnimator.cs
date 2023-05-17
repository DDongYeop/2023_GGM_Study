using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class AgentAnimator : MonoBehaviour
{
    private readonly int _speedHash = Animator.StringToHash("speed");
    private readonly int _isAirboneHash = Animator.StringToHash("is_airbone");
    private readonly int _attackHash = Animator.StringToHash("attack");
    private readonly int _isAttackHash = Animator.StringToHash("is_attack");
    private readonly int _isRollingHash = Animator.StringToHash("is_rolling");  //1

    private readonly int _isDeadHash = Animator.StringToHash("is_dead");
    private readonly int _deadTriggerHash = Animator.StringToHash("dead");

    private readonly int _hurtTriggerHash = Animator.StringToHash("hurt");

    public event Action OnAnimationEndTrigger = null;
    public event Action OnAnimationEventTrigger = null;
    public event Action OnPreAnimationEventTrigger = null; //프리챠징 이벤트

    private Animator _animator;
    public Animator Animator => _animator;
    //이미지 메이킹
    private void Awake()
    {
        _animator = GetComponent<Animator>();
    }

    public void OnAnimationEvent()
    {
        OnAnimationEventTrigger?.Invoke();
    }

    public void SetRollingState(bool value) //2
    {
        _animator.SetBool(_isRollingHash, value);
    }

    public void SetSpeed(float value)
    {
        _animator.SetFloat(_speedHash, value);
    }

    public void SetAirbone(bool value)
    {
        _animator.SetBool(_isAirboneHash, value);
    }

    public void SetAttackState(bool value)
    {
        _animator.SetBool(_isAttackHash, value);
    }

    public void SetAttackTrigger(bool value)
    {
        if(value)
        {
            _animator.SetTrigger(_attackHash);
        }else
        {
            _animator.ResetTrigger(_attackHash);
        }
    }
    
    public void SetHurtTrigger(bool value)
    { 
        if(value )
        {
            _animator.SetTrigger(_hurtTriggerHash);
        }else
        {
            _animator.ResetTrigger(_hurtTriggerHash);
        }
    }


    public void OnAnimationEnd()
    {
        OnAnimationEndTrigger?.Invoke();
    }

    public void OnPreAnimationEvent()
    {
        OnPreAnimationEventTrigger?.Invoke();
    }

    public void StopAnimation(bool value)
    {
        _animator.speed = value ? 0 : 1; //true일 때 0으로 만들어서 정지, 
        //아닐때 1로 만들어서 다시 재생
    }

    public void SetDead()
    {
        _animator.SetBool(_isDeadHash, true);
        _animator.SetTrigger(_deadTriggerHash);
    }
}
