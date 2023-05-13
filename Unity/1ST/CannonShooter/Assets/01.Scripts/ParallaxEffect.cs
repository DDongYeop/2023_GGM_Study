using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ParallaxEffect : MonoBehaviour
{
    [SerializeField] private Vector2 _parallaxRatio;

    private Transform _mainCamTrm;
    private Vector3 _lastCamPosition;
    private float _textureUnitSizeX; //텍스터의 유닛이로 변환한 크기의 너비

    private void Start()
    {
        _mainCamTrm = Camera.main.transform;

        _lastCamPosition = _mainCamTrm.position;

        SpriteRenderer sr = GetComponent<SpriteRenderer>();
        Sprite sprite = sr.sprite;
        Texture2D texture = sprite.texture;

        _textureUnitSizeX = texture.width / sprite.pixelsPerUnit; //텍스쳐 너비가 몇 유닛인지 정확하게 알아내야함
    }

    private void LateUpdate()
    {
        Vector3 deltaMove = _mainCamTrm.position - _lastCamPosition;
        transform.position += new Vector3(deltaMove.x * _parallaxRatio.x, deltaMove.y * _parallaxRatio.y);
        _lastCamPosition = _mainCamTrm.position;
        
        //무한 스크롤 안 만듦

        if (Mathf.Abs(_mainCamTrm.position.x - transform.position.x) >= _textureUnitSizeX)
        {
            float offsetPositionX = (_mainCamTrm.position.x - transform.position.x) % _textureUnitSizeX;
            transform.position = new Vector3(_mainCamTrm.position.x + offsetPositionX, transform.position.y);
        }
    }
}
