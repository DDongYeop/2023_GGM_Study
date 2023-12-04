using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerPrimaryAttackState : PlayerState
{
    private int _comboCounter; //현재 콤보 수치
    private float _lastAttackTime; //마지막 공격 시간
    private float _comboWindow = 0.8f; //콤보 이어나갈 시간 
    private readonly int _comboCounterHash = Animator.StringToHash("ComboCounter");
    
    public PlayerPrimaryAttackState(Player player, PlayerStateMachine stateMachine, string animationBoolName) : base(player, stateMachine, animationBoolName)
    {
    }

    public override void Enter()
    {
        base.Enter();
        if (_comboCounter > 2 || Time.time >= _lastAttackTime + _comboWindow)
            _comboCounter = 0;
        
        _player.AnimatorCompo.SetInteger(_comboCounterHash, _comboCounter);
        
        _player.AnimatorCompo.speed = _player.attackSpeed;

        //공격 방향을 알아내고
        //아무키도 안 눌리면 FacingDirection
        //키 눌리고 있으면 행당방향 공격 정하고
        float direction = _player.FacingDirection;
        float xInput = _player.PlayerInput.XInput;
        if (Mathf.Abs(xInput) > 0.05f)
            direction = Mathf.Sign(xInput);
        
        //플레이어 약간 전진하도록 
        //전진이 끝나면 (0.1초 가량이 흐르면) StopImmediately 호출
        Vector2 move = _player.attackMovement[_comboCounter];
        _player.SetVelocity(move.x * direction, move.y);

        _player.StartDelayCall(0.1f, () => _player.StopImmediately(false));
    }

    public override void UpdateState()
    {
        base.UpdateState();
        if (_triggerCalled)
            _stateMachine.ChangeState(PlayerStateEnum.Idle);
    }

    public override void Exit()
    {
        ++_comboCounter;
        _lastAttackTime = Time.time;
        _player.AnimatorCompo.speed = 1;
        base.Exit();
    }
}
