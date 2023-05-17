using System;
using System.Collections;
using System.Collections.Generic;
using Cinemachine;
using UnityEngine;

public class CameraManager : MonoBehaviour
{
    public static CameraManager Instance;
    
    private CinemachineVirtualCamera _followCam;
    private CinemachineBasicMultiChannelPerlin _camPerlin;

    private float _initPower;
    private float _initTime;
    private float _currentShakeTime;

    public void Init(Transform cameraTrm)
    {
        _followCam = cameraTrm.GetComponent<CinemachineVirtualCamera>();
        _camPerlin = _followCam.GetCinemachineComponent<CinemachineBasicMultiChannelPerlin>();
    }

    public void AddShake(float power, float time)
    {
        _camPerlin.m_AmplitudeGain = _initPower = power;
        _currentShakeTime = _initTime = time;
    }

    private void Update()
    {
        if (_currentShakeTime > 0)
        {
            _currentShakeTime -= Time.deltaTime;

            float ampGain = Mathf.Lerp(_initPower, 0, _currentShakeTime / _initTime);
            _camPerlin.m_AmplitudeGain = ampGain;

            if (_currentShakeTime <= 0)
            {
                _currentShakeTime = 0;
                _camPerlin.m_AmplitudeGain = 0;
            }
        }
    }
}
