using System;
using System.Collections;
using UnityEngine;

public class PlayerAttack : MonoBehaviour
{
    [SerializeField] private InputReader _inputReader;
    [SerializeField] private UziGun _gun;
    [SerializeField] private float _armingDelay = 0.15f;
    private PlayerAnimation _animation;
    private bool _isArmed = false;
    private bool _canReadyToFire; //팔을 들어올리는 동작
    private Coroutine _armingCoroutine;
    
    private void Awake()
    {
        _animation = transform.Find("Visual").GetComponent<PlayerAnimation>();
        _inputReader.ArmedEvent += OnHandleArm;
        _inputReader.FireEvent += OnFireHand;
    }

    private void OnDestroy()
    {
        _inputReader.ArmedEvent -= OnHandleArm;
        _inputReader.FireEvent -= OnFireHand;
    }

    private void OnFireHand(bool value)
    {
        if (_isArmed && _canReadyToFire)
        {
            _gun.OnFireHandle(value);
        }
    }

    private void OnHandleArm(bool value)
    {
        _isArmed = value;
        _animation.SetArmed(value);
        if (_isArmed)
        {
            _armingCoroutine = StartCoroutine(ArmDelay());
        }
        else
        {
            StopCoroutine(_armingCoroutine);
            _canReadyToFire = value;
        }
    }
    
    IEnumerator ArmDelay()
    {
        yield return new WaitForSeconds(_armingDelay);
        _canReadyToFire = true;
    }
}