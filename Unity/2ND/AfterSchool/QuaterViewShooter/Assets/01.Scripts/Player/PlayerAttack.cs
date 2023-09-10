using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Events;

public class PlayerAttack : MonoBehaviour
{
    [SerializeField] private InputReader _inputReader;
    [SerializeField] private Transform _firePos;
    [SerializeField] private PlayerAnimator _playerAnimator;

    [SerializeField] private float _shootRange = 10f;
    [SerializeField] private float _cooltime = 0.2f;
    [SerializeField] private float _armDelay = 0.15f;
    [SerializeField] private int _damage = 10;
    [SerializeField] private int _maxAmmo = 60;
    [SerializeField] private float _reloadTime = 1f;

    private bool _isReloading = false;
    private int _currentAmmo = 0;
    
    public Vector3 HitPoint { get; private set; }

    public UnityEvent OnFire;
    public UnityEvent CannotShoot;
    public UnityEvent<bool> OnRelaod;

    private float _lastFireTime;
    private bool _isArmed;
    private bool _canReadyToFire;
    private bool _isFire;
    private Coroutine _armingCoroutine;
    
    private void Awake()
    {
        _inputReader.ArmedEvent += OnHandleArm;
        _inputReader.ReloadEvent += OnHandleReload;
        _inputReader.FireEvent += OnHandleFire;
    }

    private void OnDestroy()
    {
        _inputReader.ArmedEvent -= OnHandleArm;
        _inputReader.ReloadEvent -= OnHandleReload;
        _inputReader.FireEvent -= OnHandleFire;
    }

    private void OnHandleFire(bool value)
    {
        _isFire = value;
    }

    private void Start()
    {
        _currentAmmo = _maxAmmo - 20;
    }

    private void OnHandleReload()
    {
        if (_currentAmmo == _maxAmmo || _isReloading)
            return;

        StartCoroutine(ReloadCoroutine());
    }

    private IEnumerator ReloadCoroutine()
    {
        _isReloading = true;
        OnRelaod?.Invoke(_isReloading);
        _playerAnimator.SetReload(_isReloading);
        yield return new WaitForSeconds(_reloadTime);

        _currentAmmo = _maxAmmo; //리로드 완료되면 채워지기
        _isReloading = false;
        OnRelaod?.Invoke(_isReloading);
        _playerAnimator.SetReload(_isReloading);
    }

    private void OnHandleArm(bool value)
    {
        if(_isReloading)
            return;

        _isArmed = value;
        _playerAnimator.SetArmed(value);
        
        if (_isArmed)
        {
            _armingCoroutine = StartCoroutine(ArmingDelay());
        }
        else
        {
            StopCoroutine(_armingCoroutine);
            _canReadyToFire = false;
        }
    }

    private IEnumerator ArmingDelay()
    {
        yield return new WaitForSeconds(_armDelay);
        _canReadyToFire = true;
    }

    private void Update()
    {
        bool canFire = !_isReloading && _canReadyToFire && _isFire && _lastFireTime + _cooltime < Time.time;

        if (canFire)
        {
            if (_currentAmmo <= 0)
            {
                CannotShoot?.Invoke();
                _isFire = false;
                return;
            }

            if (Physics.Raycast(_firePos.position, _firePos.forward, out var hit, _shootRange))
            {
                HitPoint = hit.point;
                //데미지 주기
            }
            else
            {
                HitPoint = _firePos.position + _firePos.forward * _shootRange;
            }
            
            OnFire?.Invoke();
            _currentAmmo--;
            _lastFireTime = Time.time;
        }
    }
}
