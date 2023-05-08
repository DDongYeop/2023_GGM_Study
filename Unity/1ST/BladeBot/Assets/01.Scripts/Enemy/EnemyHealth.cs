using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Events;

public class EnemyHealth : MonoBehaviour, IDamageable
{
    public UnityEvent OnDeadTriggered = null; //사망 트리거
    public UnityEvent OnHitTriggered = null;
    private AIActionData _aiActionData;

    public Action<int, int> OnHealthCchanged; //나중에 UI랑 연결 될거다. 

    public int MaxHP;
    private int _currentHP;

    private EnemyController _contoller;
    
    public void SetMaxHP(int value)
    {
        _currentHP = MaxHP = value;
    }
    
    private void Awake()
    {
        _aiActionData = transform.Find("AI").GetComponent<AIActionData>();
    }

    public void SetInit(EnemyController controller)
    {
        _contoller = controller;
    }

    public void OnDamage(int damage, Vector3 point, Vector3 normal)
    {
        if (_contoller.IsDead)
            return;
        
        _aiActionData.HitPoint = point;
        _aiActionData.HitNormal = normal;
        OnHitTriggered?.Invoke();

        _currentHP -= damage;
        _currentHP = Mathf.Clamp(_currentHP, 0, MaxHP);
        if (_currentHP <= 0)
        {
            OnDeadTriggered?.Invoke();
        }
        
        UIManager.Instance.Subscribe(this);
        
        OnHealthCchanged?.Invoke(_currentHP, MaxHP);
    }
}
