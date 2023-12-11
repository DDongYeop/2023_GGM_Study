using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerJumpState : PlayerAirState
{
    public PlayerJumpState(Player player, PlayerStateMachine stateMachine, string animationBoolTriggerName) : base(player, stateMachine, animationBoolTriggerName)
    {
    }

    public override void EnterState()
    {
        base.EnterState();
        _player.SetVelocity(_rigidbody.velocity.x, _player.jumpForce, true);
    }

    public override void UpdateState()
    {
        base.UpdateState();

        // 점프 중에 좌우로 움직이길 원한다면 여기다 뭔가 코딩해야해

        if(_rigidbody.velocity.y < 0)
        {
            _stateMachine.ChangeState(PlayerStateEnum.Fall);
        }
    }

    public override void ExitState()
    {
        base.ExitState();
    }
}
