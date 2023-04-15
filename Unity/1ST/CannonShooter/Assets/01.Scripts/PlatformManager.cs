using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Random = UnityEngine.Random;

public class PlatformManager : MonoBehaviour
{
    [SerializeField] private Platform _platformPrefab;

    [SerializeField] private Vector2 _randomYDelta; //min max

    private List<Platform> _platformList = new List<Platform>();
    
    private void Start()
    {
        float lastY = 0;
        
        for (int i = 0; i < 8; ++i)
        {
            Platform p = Instantiate(_platformPrefab, transform) as Platform;
            p.ResetPlatform(lastY);
            lastY += Random.Range(_randomYDelta.x, _randomYDelta.y);
        }
    }
}
