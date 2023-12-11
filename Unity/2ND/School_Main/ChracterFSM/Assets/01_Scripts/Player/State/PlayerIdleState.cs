using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerIdleState : PlayerGroundState
{
    public PlayerIdleState(Player player, PlayerStateMachine stateMachine, string animationBoolTriggerName) : base(player, stateMachine, animationBoolTriggerName)
    {

    }

    public override void EnterState()
    {
        base.EnterState();
        _player.StopImmediately(false);
    }

    public override void UpdateState()
    {
        base.UpdateState();
        float xInput = _player.PlayerInput.XInput;

        if(Mathf.Abs(xInput) >= 0.05f)
        {
            _stateMachine.ChangeState(PlayerStateEnum.Move);
        }
    }

    public override void ExitState()
    {
        base.ExitState();
    }
}
