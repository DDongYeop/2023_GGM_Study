using System.Collections;
using System.Collections.Generic;
using Core;
using UnityEngine;

public class AttackState : CommonState
{
    [SerializeField] private float _keyDelay = 0.5f;
    
    private int _currentCombo = 1; //현재 콤보가 몇인지
    private bool _canAttack = true; //선입력 막기위해 다음 공격 가능 상태인가
    private float _keyTimer = 0; //다음공곡이 이뤄지기까지 기다리는 시간
    // 이시간내로 입력 안 하면 Idle로 돌아감
    
    public override void OnEnterState()
    {
        _agentInput.OnAttackKeyPress += OnAttackHandle;
        _animator.OnAnimationEndTrigger += OnAnimaionEnd;
        _currentCombo = 0;
        _canAttack = true;
        _animator.SetAttackState(true);
        OnAttackHandle(); //처음 1타 들어가도록 
    }

    public override void OnExitState()
    {
        _agentInput.OnAttackKeyPress -= OnAttackHandle;
        _animator.OnAnimationEndTrigger -= OnAnimaionEnd;
        _animator.SetAttackState(false);
        _animator.SetAttackTrigger(false);
    }

    private void OnAnimaionEnd()
    {
        _canAttack = true;
        _keyTimer = _keyDelay; //0.5초 기다리기 시작
    }

    public void OnAttackHandle()
    {
        if (_canAttack && _currentCombo < 3)
        {
            _canAttack = false;
            _currentCombo++;
            _animator.SetAttackTrigger(true);
        }
    }

    public override void UpdateState()
    {
        if (_canAttack && _keyTimer > 0)
        {
            _keyTimer -= Time.deltaTime;
            if (_keyTimer <= 0)
                _agentController.ChangeState(StateType.Normal);
        }
    }
}
