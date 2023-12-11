using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerFallState : PlayerAirState
{
    public PlayerFallState(Player player, PlayerStateMachine stateMachine, string animationBoolTriggerName) : base(player, stateMachine, animationBoolTriggerName)
    {
    }

    public override void EnterState()
    {
        base.EnterState();
    }

    public override void UpdateState()
    {
        base.UpdateState();
        // ���ٴ��� �����ؾ� ����.
        if(_player.IsGroundDected())
        {
            _stateMachine.ChangeState(PlayerStateEnum.Idle);
        }
        // ���� �����ϸ� �������̵���

        // ����ٰ��� xInput�Է½� �¿� �����̴� ���
    }

    public override void ExitState()
    {
        base.ExitState();
    }
}
