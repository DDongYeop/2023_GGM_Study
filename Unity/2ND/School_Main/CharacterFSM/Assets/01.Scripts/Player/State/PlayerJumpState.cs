using System.Collections;
using System.Collections.Generic;
using Unity.VisualScripting.FullSerializer;
using UnityEngine;

public class PlayerJumpState : PlayerAirState
{
    public PlayerJumpState(Player player, PlayerStateMachine stateMachine, string animationBoolName) : base(player, stateMachine, animationBoolName)
    {
    }

    public override void Enter()
    {
        base.Enter();
        _player.SetVelocity(_rigidbody.velocity.x, _player.jumpForce, true);
    }

    public override void UpdateState()
    {
        base.UpdateState();
        
        //점프 중에 좌우로 움직이길 원하면 코딩 ㄱㅅㄱ 
        
        if (_rigidbody.velocity.y < 0)
            _stateMachine.ChangeState(PlayerStateEnum.Fall);
    }

    public override void Exit()
    {
        base.Exit();
    }
}
