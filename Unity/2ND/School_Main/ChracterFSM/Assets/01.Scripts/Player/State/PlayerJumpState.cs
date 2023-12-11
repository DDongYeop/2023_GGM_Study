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

        // ���� �߿� �¿�� �����̱� ���Ѵٸ� ����� ���� �ڵ��ؾ���

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
