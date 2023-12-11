using System;
using UnityEngine;

public class PlayerState
{
    protected PlayerStateMachine _stateMachine; // 플레이어 상태 머신
    protected Player _player;
    protected Rigidbody2D _rigidbody; // 편의성을 위해서 참조

    protected int _animBoolHash;
    protected readonly int _yVelocityHash = Animator.StringToHash("y_velocity");

    protected bool _triggerCalled;

    public PlayerState(Player player, PlayerStateMachine stateMachine, string animationBoolTriggerName)
    {
        _player = player;
        _stateMachine = stateMachine;
        _animBoolHash = Animator.StringToHash(animationBoolTriggerName);
        _rigidbody = _player.RigidbodyCompo;
    }

    public virtual void EnterState()
    {
        _triggerCalled = false;
        _player.AnimatorCompo.SetBool(_animBoolHash, true);
    }

    public virtual void UpdateState()
    {
        _player.AnimatorCompo.SetFloat(_yVelocityHash, _rigidbody.velocity.y);    
    }

    public virtual void ExitState()
    {
        _player.AnimatorCompo.SetBool(_animBoolHash, false);
    }

    public void AnimationFinishTrigger()
    {
        _triggerCalled = true;
    }
}
