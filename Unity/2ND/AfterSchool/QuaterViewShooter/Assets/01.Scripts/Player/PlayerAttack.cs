using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerAttack : MonoBehaviour
{
    [Header("참조 값들")]
    [SerializeField] private InputReader _inputReader;
    [SerializeField] private Gun _gun;
    
    private bool _isFire;

    private void OnEnable()
    {
        _inputReader.FireEvent += SetFireValue;
    }

    private void OnDisable()
    {
        _inputReader.FireEvent -= SetFireValue;
    }

    private void SetFireValue(bool value)
    {
        _isFire = value;
    }

    private void Update()
    {
        if (_isFire)
            _gun.TryToFire();
    }
}
