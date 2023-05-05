using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public enum CannonState : short
{
    IDLE = 0,
    MOVING = 1,
    CHARGING = 2,
    FIRE = 3
}

public class Cannon : MonoBehaviour
{
    [SerializeField] private float _rotateSpeed = 90f;
    private float _currentRotation;
    private Transform _barrelTrm;

    [SerializeField] private CannonBall _ballPrefab;
    private Transform _firePosition;

    [SerializeField] private float _chargingSpeed, _maxPower = 90f;
    public float _currentPower;

    [SerializeField] private CannonState _currentState;
    
    private void Awake()
    {
        _barrelTrm = transform.Find("CannonBarrel");
        _firePosition = transform.Find("CannonBarrel/FirePos");
        _currentState = CannonState.IDLE;
    }

    private void Update()
    {
        if ((short)_currentState < 2)
            CheckRotate();
        
        CheckFire();
    }

    private void CheckFire()
    {
        if (Input.GetButtonDown("Jump") && (short)_currentState < 2)
        {
            _currentPower = 0;
            _currentState = CannonState.CHARGING;
        }
        else if (Input.GetButton("Jump") && _currentState == CannonState.CHARGING)
        {
            _currentPower += _maxPower * Time.deltaTime;
            _currentPower = Mathf.Clamp(_currentPower, 0, _maxPower);
        }
        else if (Input.GetButtonUp("Jump") && _currentState == CannonState.CHARGING)
        {
            _currentState = CannonState.FIRE;
            CannonBall ball = Instantiate(_ballPrefab, _firePosition.position, Quaternion.identity);
            ball.Fire(_firePosition.right, _currentPower);
        }
    }

    private void CheckRotate()
    {
        float y = Input.GetAxisRaw("Vertical");
        _currentRotation += y * _rotateSpeed * Time.deltaTime;
        _currentRotation = Mathf.Clamp(_currentRotation, 0, 90f);

        if (Mathf.Abs(y) > 0)
        {
            _currentState = CannonState.MOVING;
        }
        else
        {
            _currentState = CannonState.IDLE;
        }
        
        _barrelTrm.rotation = Quaternion.Euler(0, 0, _currentRotation);
    }
}
