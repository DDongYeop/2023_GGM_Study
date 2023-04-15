using System;
using System.Collections;
using System.Collections.Generic;
using Cinemachine;
using UnityEngine;
using DG.Tweening;

public class CameraManager : MonoBehaviour
{
    [SerializeField] private CinemachineVirtualCamera _followCam;
    public static CameraManager Instance;

    public Camera _mainCam;

    public Camera MainCam
    {
        get
        {
            if (_mainCam == null)
                _mainCam = Camera.main;
            return _mainCam;
        }
    }

    public float CamWidth
    {
        get
        {
            float width = MainCam.aspect * MainCam.orthographicSize;
            return width;
        }
    }

    public bool CheckIsCamY(float y) // 내가 넣은 y값이 카메라의 안쪽에 있는지
    {
        return y > transform.position.y - MainCam.orthographicSize && y < transform.position.y + MainCam.orthographicSize; 
    }

    public Vector2 CamWidthBound() //카메라 너비의 외곽을 반환하는거 
    {
        float x = transform.position.x;
        Vector2 bound = new Vector2( x - CamWidth,  x + CamWidth );
        return bound;
    }

    private void Awake()
    {
        if (Instance != null)
            Debug.LogError("Multiple CameraManager Running");
        Instance = this;
    }

    public void Zoom(float value, float time = 0.3f)
    {
        DOTween.To( 
            () => _followCam.m_Lens.OrthographicSize,
            x => _followCam.m_Lens.OrthographicSize = x,
            value,
            time
            );
        
        _followCam.m_Lens.OrthographicSize = value;
    }
}
