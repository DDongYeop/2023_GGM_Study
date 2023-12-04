using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerFallState : PlayerAirState
{
    public PlayerFallState(Player player, PlayerStateMachine stateMachine, string animationBoolName) : base(player, stateMachine, animationBoolName)
    {
    }

    public override void Enter()
    {
        base.Enter();
    }

    public override void UpdateState()
    {
        base.UpdateState();
        //바닥 감지하면 끝
        if (_player.IsGroundDetected())
            _stateMachine.ChangeState(PlayerStateEnum.Idle);
        //벽 감지하면 벽 슬라이드
        //if (_player.IsWallDetected())
        //    _stateMachine.ChangeState(PlayerStateEnum.Idle);
        //좌우 이동도 
    }

    public override void Exit()
    {
        base.Exit();
    }
}
