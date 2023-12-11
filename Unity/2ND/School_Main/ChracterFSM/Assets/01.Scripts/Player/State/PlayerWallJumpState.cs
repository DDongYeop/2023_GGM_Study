using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerWallJumpState : PlayerState
{
    public PlayerWallJumpState(Player player, PlayerStateMachine stateMachine, string animationBoolTriggerName) : base(player, stateMachine, animationBoolTriggerName)
    {
    }

    public override void EnterState()
    {
        base.EnterState();
        _player.SetVelocity(5 * - _player.FacingDirection, _player.jumpForce);
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

    public override void ExitState()
    {
        base.ExitState();
    }
}
