using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public abstract class PlayerAirState : PlayerState
{
    public PlayerAirState(Player player, PlayerStateMachine stateMachine, string animationBoolTriggerName) : base(player, stateMachine, animationBoolTriggerName)
    {
    }

    public override void EnterState()
    {
        base.EnterState();
    }

    public override void UpdateState()
    {
        base.UpdateState();
        float xInput = _player.PlayerInput.XInput;
        if (Mathf.Abs(xInput) >= 0.05f)
        {
            _player.SetVelocity(xInput * _player.moveSpeed * 0.8f, _rigidbody.velocity.y);
        }

        if (_player.IsWallDected())
        {
            _stateMachine.ChangeState(PlayerStateEnum.WallSlide);
        }
    }

    public override void ExitState()
    {
        base.ExitState();
    }
}
