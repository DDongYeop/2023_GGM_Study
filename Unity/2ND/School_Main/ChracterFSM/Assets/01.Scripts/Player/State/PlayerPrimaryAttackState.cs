using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerPrimaryAttackState : PlayerState
{
    private int _comboCounter; //현재 콤보 수치 
    private float _lastAttackTime; //마지막으로 공격했던 시간
    private float _comboWindow = 0.8f; //콤보 윈도우 
    private readonly int _comboCounterHash = Animator.StringToHash("ComboCounter");

    public PlayerPrimaryAttackState(Player player, PlayerStateMachine stateMachine, string animationBoolTriggerName) : base(player, stateMachine, animationBoolTriggerName)
    {
    }

    public override void EnterState()
    {
        base.EnterState();
        if(_comboCounter > 2 || Time.time >= _lastAttackTime + _comboWindow)
        {
            _comboCounter = 0; //콤보 초기화 조건에 따라 콤보 초기화
        }
        _player.AnimatorCompo.SetInteger(_comboCounterHash, _comboCounter);
        _player.AnimatorCompo.speed = _player.attackSpeed;

        //공격방향을 알아내라. 아무키도 안눌렸다면 FacingDirection
        //만약 키가 눌리고 있다면 해당방향으로 공격을 정하고
        float attackDirection = _player.FacingDirection;
        float xInput = _player.PlayerInput.XInput;
        if(Mathf.Abs(xInput) > 0.05f)
        {
            attackDirection = Mathf.Sign( xInput);
        }

        //플레이어를 약간 전진하게 만들어주자.
        // 전진이 끝나면(0.1초가량) StopImmediately 호출)
        Vector2 move = _player.attackMovement[_comboCounter];
        _player.SetVelocity(move.x * attackDirection, move.y);

        _player.StartDelayCall(0.1f, () => _player.StopImmediately(false));
    }

    public override void UpdateState()
    {
        base.UpdateState();

        if (_triggerCalled)
        {
            _stateMachine.ChangeState(PlayerStateEnum.Idle);
        }
    }

    public override void ExitState()
    {
        ++_comboCounter;
        _lastAttackTime = Time.time;
        _player.AnimatorCompo.speed = 1;
        base.ExitState();
    }

}
