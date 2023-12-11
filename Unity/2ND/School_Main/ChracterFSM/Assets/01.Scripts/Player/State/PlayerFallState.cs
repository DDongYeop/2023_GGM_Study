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
        // 땅바닥을 감지해야 끝남.
        if(_player.IsGroundDected())
        {
            _stateMachine.ChangeState(PlayerStateEnum.Idle);
        }
        // 벽을 감지하면 벽슬라이드모드

        // 여기다가도 xInput입력시 좌우 움직이는 기능
    }

    public override void ExitState()
    {
        base.ExitState();
    }
}
