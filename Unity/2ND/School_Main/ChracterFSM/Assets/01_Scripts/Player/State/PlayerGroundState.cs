using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public abstract class PlayerGroundState : PlayerState
{
    public PlayerGroundState(Player player, PlayerStateMachine stateMachine, string animationBoolTriggerName) : base(player, stateMachine, animationBoolTriggerName)
    {

    }

    public override void EnterState()
    {
        base.EnterState();
        _player.PlayerInput.JumpEvent += HandleJumpInput;
        _player.PlayerInput.AttackEvent += HandleAttackInput;
    }

    public override void UpdateState()
    {
        base.UpdateState();
    }

    public override void ExitState()
    {
        base.ExitState();
        _player.PlayerInput.JumpEvent -= HandleJumpInput;
        _player.PlayerInput.AttackEvent -= HandleAttackInput;
    }

    
    #region 입력처리 핸들러

    private void HandleJumpInput()
    {
        if(_player.IsGroundDected())
        {
            _stateMachine.ChangeState(PlayerStateEnum.Jump);
        }
    }

    private void HandleAttackInput()
    {
        if (_player.IsGroundDected())
        {
            _stateMachine.ChangeState(PlayerStateEnum.PrimaryAttack);
        }
    }


    #endregion
}
