using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Events;

public class Health : MonoBehaviour, IDamageable
{
    [SerializeField] private int _maxHP;
    private int _currentHP;

    public UnityEvent<int, int> OnChangeHealth;
    public UnityEvent OnHit;
    public UnityEvent OnDie;
    
    public Vector3 HitPoint { get; private set; }
    public Vector3 HitNormal { get; private set; }
    
    public void OnDamage(int damage, Vector3 point, Vector3 normal)
    {
        HitPoint = point;
        HitNormal = normal;

        _currentHP = Mathf.Clamp(_currentHP - damage, 0, _maxHP);
        
        OnChangeHealth?.Invoke(_currentHP, _maxHP);
        OnHit?.Invoke();
        if (_currentHP == 0)
            OnDie?.Invoke();
    }
}
