using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerWallJumpState : PlayerState
{
    public PlayerWallJumpState(Player player, PlayerStateMachine stateMachine, string animationBoolName) : base(player, stateMachine, animationBoolName)
    {
    }

    public override void Enter()
    {
        base.Enter();
        _player.SetVelocity(5 * -_player.FacingDirection, _player.jumpForce);
        _player.StartCoroutine(DelayToAir());
    }

    private IEnumerator DelayToAir()
    {
        yield return new WaitForSeconds(0.3f);
        _stateMachine.ChangeState(PlayerStateEnum.Fall);
    }

    public override void UpdateState()
    {
        base.UpdateState();
    }

    public override void Exit()
    {
        base.Exit();
    }
}
