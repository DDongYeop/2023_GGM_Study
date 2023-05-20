using System;
using System.Collections;
using System.Collections.Generic;
using DG.Tweening;
using UnityEngine;
using UnityEngine.UI;
using Screen = UnityEngine.Device.Screen;

public class LoadingScreen : MonoBehaviour
{
    private RectTransform _rectTrm;
    private Image _image;

    private Vector2 _screenSize;
    
    private void Awake()
    {
        _rectTrm = GetComponent<RectTransform>();
        _image = GetComponent<Image>();

        _screenSize = new Vector2(Screen.width, Screen.height);

        _rectTrm.sizeDelta = _screenSize;
        _rectTrm.anchoredPosition = Vector2.zero;
    }

    public void ScreenOff()
    {
        Sequence sequence = DOTween.Sequence();
        sequence.Append(_rectTrm.DOAnchorPosX(_screenSize.x, .5f).SetEase(Ease.InCubic));
        sequence.Join(_image.DOFade(0, 0.5f).SetEase(Ease.InCubic));
    }
    
    public void ScreenOn()
    {
        Sequence sequence = DOTween.Sequence();
        sequence.Append(_rectTrm.DOAnchorPosX(0, .5f).SetEase(Ease.InCubic));
        sequence.Join(_image.DOFade(1, 0.5f).SetEase(Ease.InCubic));
    }
}
