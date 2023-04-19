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

    [SerializeField] private bool _isDead = false;

    public int MaxHP;
    private int _currentHP;

    public void SetMaxHP(int value)
    {
        _currentHP = MaxHP = value;
        _isDead = false;
    }
    
    private void Awake()
    {
        _aiActionData = transform.Find("AI").GetComponent<AIActionData>();
    }

    public void OnDamage(int damage, Vector3 point, Vector3 normal)
    {
        if (_isDead)
            return;
        
        _aiActionData.HitPoint = point;
        _aiActionData.HitNormal = normal;
        OnHitTriggered?.Invoke();

        _currentHP -= damage;
        if (_currentHP <= 0)
        {
            _isDead = true;
            OnDeadTriggered?.Invoke();
        }
        
        OnHealthCchanged?.Invoke(_currentHP, MaxHP);
    }
}
