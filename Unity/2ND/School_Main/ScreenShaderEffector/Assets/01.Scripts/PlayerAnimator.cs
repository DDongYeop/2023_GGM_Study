using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.U2D.Animation;

public class PlayerAnimator : MonoBehaviour
{
    [SerializeField] private SpriteLibraryAsset[] _spriteAssets;
    private SpriteRenderer _renderer; 

    private SpriteLibrary _spriteLibrary;

    private int _currentSpriteIndex = 0;

    [Header("ShockWave")] 
    [SerializeField] private float _duration;
    private float _currentTime;
    private float _startDistance = -.1f;
    private float _endDistance = 1;
    private readonly int _hashWaveDistance = Shader.PropertyToID("_WaveDistance");
    
    private void Awake()
    {
        _spriteLibrary = GetComponent<SpriteLibrary>();
        _renderer = GameObject.Find("ShockwaveScreen").GetComponent<SpriteRenderer>();
    }

    private void SetNextSprite()
    {
        _currentSpriteIndex = (_currentSpriteIndex + 1) % _spriteAssets.Length;
        _spriteLibrary.spriteLibraryAsset = _spriteAssets[_currentSpriteIndex];
    }

    private void Update()
    {
        if (Input.GetKeyDown(KeyCode.Space))
        {
            SetNextSprite();
            StartCoroutine(ShockWaveCo());
        }
    }

    private IEnumerator ShockWaveCo()
    {
        _currentTime = 0;
        
        while (_currentTime <= _duration)
        {
            yield return null;
            _currentTime += Time.deltaTime;
            float time = _currentTime / _duration;
            _renderer.material.SetFloat(_hashWaveDistance, Mathf.Lerp(_startDistance, _endDistance, time));
        }
        _renderer.material.SetFloat(_hashWaveDistance, _endDistance);
    }
}
