using Core;
using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class AttackState : CommonState
{
    public event Action<int> OnAttackStart = null;
    public event Action OnAttackEnd = null;

    [SerializeField]
    private float _keyDelay = 0.5f;

    private int _currentCombo = 1; //현재 콤보가 몇인지 
    private bool _canAttack = true; // 선입력 막기 위해서 다음 공격가능상태인가
    private float _keyTimer = 0; //다음공격이 이뤄지기까지 기다리는 시간
    //이 시간내로 입력 안하면 idle로 돌아간다.

    private float _attackStartTime; //공격이 시작된 시간을 기록하고
    [SerializeField]
    private float _attackSlideDuration = 0.2f, _attackSlideSpeed = 0.1f;
    //이거는 슬라이드되는 시간과 슬라이드 되는 스피드를 나타낸다.

    private DamageCaster _damageCaster;

    public override void SetUp(Transform agentRoot)
    {
        base.SetUp(agentRoot);
        _damageCaster = agentRoot.Find("DamageCaster").GetComponent<DamageCaster>();
    }

    public override void OnEnterState()
    {
        _agentInput.OnAttackKeyPress += OnAttackHandle;
        _animator.OnAnimationEndTrigger += OnAnimationEnd;
        _agentInput.OnRollingKeyPress += OnRollingHandle;
        _animator.OnAnimationEventTrigger += OnDamageCastHandle;

        _currentCombo = 0;
        _canAttack = true;
        _animator.SetAttackState(true);

        _agentMovement.IsActiveMove = false;  //키보드 이동을 잠그고
        Vector3 pos = _agentInput.GetMouseWorldPosition();
        _agentMovement.SetRotation(pos);
        OnAttackHandle(); //처음 1타 들어가도록
    }

    public override void OnExitState() 
    {
        _agentInput.OnAttackKeyPress -= OnAttackHandle;
        _animator.OnAnimationEndTrigger -= OnAnimationEnd;
        _agentInput.OnRollingKeyPress -= OnRollingHandle;
        _animator.OnAnimationEventTrigger -= OnDamageCastHandle;

        _animator.SetAttackState(false);
        _animator.SetAttackTrigger(false);

        _agentMovement.IsActiveMove = true; //키보드 이동을 풀어주고

        OnAttackEnd?.Invoke();
    }

    private void OnDamageCastHandle()
    {
        _damageCaster.CastDamage();
    }

    private void OnRollingHandle()
    {
        _agentController.ChangeState(StateType.Rolling);
    }

    private void OnAnimationEnd()
    {
        _canAttack = true;
        _keyTimer = _keyDelay; //0.5초 기다리기 시작
    }


    public void OnAttackHandle()
    {
        if(_canAttack && _currentCombo < 3)
        {
            _attackStartTime = Time.time;
            _canAttack = false;
            _currentCombo++;
            //애니메이션 트리거 해주고
            _animator.SetAttackTrigger(true);
            OnAttackStart?.Invoke(_currentCombo); //현재 콤보수치를 발행해준다.
        }
    }

    public override bool UpdateState()
    {
        if(Time.time < _attackStartTime + _attackSlideDuration) //슬라이드가 되고 있어야 하는 시간
        {
            float timePassed = Time.time - _attackStartTime; //현재 흘러간 시간이 나오고
            float lerpTime = timePassed / _attackSlideDuration; //0~1값으로 맵핑하고

            Vector3 targetSpeed = Vector3.Lerp(_agentController.transform.forward * _attackSlideSpeed, 
                                                Vector3.zero, 
                                                lerpTime);
            _agentMovement.SetMovementVelocity(targetSpeed);
        }

        if(_canAttack && _keyTimer > 0)
        {
            _keyTimer -= Time.deltaTime;
            if(_keyTimer <= 0)
            {
                _agentController.ChangeState(StateType.Normal);
            }
        }

        return true;
    }
}
