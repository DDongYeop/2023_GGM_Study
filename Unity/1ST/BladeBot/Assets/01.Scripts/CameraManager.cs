using System.Collections;
using System.Collections.Generic;
using Cinemachine;
using UnityEngine;

public class CameraManager : MonoBehaviour
{
    public static CameraManager Instance;

    [SerializeField] private CinemachineVirtualCamera _cmVcam;
    [SerializeField] private float _amplitude;
    [SerializeField] private float _duration;

    private CinemachineBasicMultiChannelPerlin _noise = null;

    private void Awake() 
    {
        if (Instance != null)
            Debug.LogError("Multiple CameraManager is running");
        Instance = this;
            
        _noise = _cmVcam.GetCinemachineComponent<CinemachineBasicMultiChannelPerlin>(); 
    } 
    
    public void CameraShake()
    {
        StartCoroutine(ShakeCoroutine());
    }

    IEnumerator ShakeCoroutine()
    {
        float time = _duration;
        while (time > 0)
        {
            _noise.m_AmplitudeGain = Mathf.Lerp(0, _amplitude, time / _duration);

            yield return null;
            time -= Time.deltaTime;
        }
        _noise.m_AmplitudeGain = 0;
    }
}
