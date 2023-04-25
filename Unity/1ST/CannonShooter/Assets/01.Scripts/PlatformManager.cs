using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Random = UnityEngine.Random;

public class PlatformManager : MonoBehaviour
{
    [SerializeField] private Platform _platformPrefab;
    [SerializeField] private Vector2 _randomYDelta; //min max

    private float _lastY = 0;
    
    private void Start()
    {
        for (int i = 0; i < 8; ++i)
        {
            Platform p = Instantiate(_platformPrefab, transform) as Platform;
            p.ResetPlatform(_lastY);
            _lastY += Random.Range(_randomYDelta.x, _randomYDelta.y);
            p.PlatformManager = this;
        }
    }

    public void PlatformReset(Platform p)
    {
        p.ResetPlatform(_lastY);
        _lastY += Random.Range(_randomYDelta.x, _randomYDelta.y);
    }
}