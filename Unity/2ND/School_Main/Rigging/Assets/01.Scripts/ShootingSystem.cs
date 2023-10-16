using System;
using System.Collections;
using System.Collections.Generic;
using Cinemachine;
using DG.Tweening;
using UnityEngine;
using UnityEngine.Serialization;

public class ShootingSystem : MonoBehaviour
{
    [SerializeField] private InputReader _inputReader;
    [SerializeField] private Transform _paarentTrm;
    [SerializeField] private Transform _gunNozzle;
    [SerializeField] private CinemachineFreeLook _freeLookCam;

    private PlayerMovement _movement;
    private CinemachineImpulseSource _impulseSource;

    private bool _isPressFire = false;

    private void Awake()
    {
        _movement = GetComponent<PlayerMovement>();
        _impulseSource = GetComponent<CinemachineImpulseSource>();
        _inputReader.FireEvent += OnHandFire;
    }

    private void OnDestroy()
    {
        _inputReader.FireEvent -= OnHandFire;
    }

    private void Update()
    {
        Vector3 angle = _paarentTrm.localEulerAngles;
        _movement.blockRotationPlayer = _isPressFire; // 총알 발사모드일떄 멈춤

        if (_isPressFire)
        {
            VisualPolish();
            _movement.RotateToCamera(transform);
        }

        var camYAxis = 0f;
        if (_isPressFire)
        {
            camYAxis = RemapCamera(_freeLookCam.m_YAxis.Value, 0, 1, -25, 25);
        }

        _paarentTrm.localEulerAngles = new Vector3(Mathf.LerpAngle(_paarentTrm.localEulerAngles.x, camYAxis, 0.3f), angle.y, angle.z);
    }

    private void VisualPolish()
    {
        if (!DOTween.IsTweening(_paarentTrm))
        {
            _paarentTrm.DOComplete();
            Vector3 forward = _paarentTrm.forward;
            Vector3 localPos = _paarentTrm.localPosition;

            _paarentTrm.DOLocalMove(localPos - new Vector3(0, 0, 0.2f), 0.03f)
                .OnComplete(() => _paarentTrm.DOLocalMove(localPos, 0.1f).SetEase(Ease.OutSine));
            
            _impulseSource.GenerateImpulse(0.2f);
        }

        if (!DOTween.IsTweening(_gunNozzle))
        {
            _gunNozzle.DOComplete();
            _gunNozzle.DOPunchScale(new Vector3(0, 1, 1) / 1.5f, 0.15f, 10, 1);
        }
    }

    private void OnHandFire(bool value)
    {
        _isPressFire = value;
    }

    private float RemapCamera(float value, float from1, float to1, float from2, float to2)
    {
        return (value - from1) / (to1 - from1) * (to2 - from2) + from2;
    }
}
