using System;
using System.Collections;
using System.Collections.Generic;
using Core;
using UnityEngine;

public class AttackState : CommonState
{
    public event Action<int> OnAttackStart = null;
    public event Action OnAttackEnd = null;
    [SerializeField] private float _keyDelay = 0.5f;
    
    private int _currentCombo = 1; //현재 콤보가 몇인지
    private bool _canAttack = true; //선입력 막기위해 다음 공격 가능 상태인가
    private float _keyTimer = 0; //다음공곡이 이뤄지기까지 기다리는 시간
    // 이시간내로 입력 안 하면 Idle로 돌아감

    private float _attackStartTime; //공격이 시작된 시간 기록
    [SerializeField] private float _attackSlideDuration = .2f, _attackSlideSpeed = .1f; //슬라이드 되는 시간과 슬라이드 되는 스피드 나타냄 
    
    public override void OnEnterState()
    {
        _agentInput.OnAttackKeyPress += OnAttackHandle;
        _animator.OnAnimationEndTrigger += OnAnimaionEnd;
        _agentInput.OnRollingKeyPress += OnRollingHandle;
        _currentCombo = 0;
        _canAttack = true;
        print(2);
        _animator.SetAttackState(true);

        _agentMovement.IsActiveMove = false; // 키보드 입력을 잡그고

        Vector3 pos = _agentInput.GetMouseWorldPosition();
        _agentMovement.SetRotation(pos);
        OnAttackHandle(); //처음 1타 들어가도록 
    }

    public override void OnExitState()
    {
        _agentInput.OnAttackKeyPress -= OnAttackHandle;
        _animator.OnAnimationEndTrigger -= OnAnimaionEnd;
        _agentInput.OnRollingKeyPress -= OnRollingHandle;
        _animator.SetAttackState(false);
        _animator.SetAttackTrigger(false);
        
        _agentMovement.IsActiveMove = true; //키보드 이동을 풀어주고 
        
        OnAttackEnd?.Invoke();
    }

    private void OnRollingHandle()
    {
        _agentController.ChangeState(StateType.Rolling);
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
            _attackStartTime = Time.time;
            _canAttack = false;
            _currentCombo++;
            _animator.SetAttackTrigger(true);
            OnAttackStart?.Invoke(_currentCombo); //현재 콤보 수치 발행
        }
    }

    public override void UpdateState()
    {
        if (Time.time < _attackStartTime + _attackSlideDuration) //슬라이드가 되고 있어야하는 시간
        {
            float timePassed = Time.time - _attackStartTime; //현재 흘러간 시간이 나오고
            float lerpTime = timePassed / _attackSlideDuration; // 0~1값으로 맵핑

            Vector3 targetSpeed = Vector3.Lerp(_agentController.transform.forward * _attackSlideSpeed, Vector3.zero, lerpTime);
            _agentMovement.SetMovementVelocity(targetSpeed);
        }
        
        if (_canAttack && _keyTimer > 0)
        {
            _keyTimer -= Time.deltaTime;
            if (_keyTimer <= 0)
                _agentController.ChangeState(StateType.Normal);
        }
    }
}
