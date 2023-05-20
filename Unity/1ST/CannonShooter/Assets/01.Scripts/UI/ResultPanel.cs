using System;
using System.Collections;
using System.Collections.Generic;
using DG.Tweening;
using UnityEngine;
using Screen = UnityEngine.Device.Screen;

public class ResultPanel : MonoBehaviour
{
    private RectTransform _backRectTrm;
    private RectTransform _innerRectTrm;
    private InnerPanel _innerPanel;

    private CanvasGroup _canvasGroup;
    
    private void Awake()
    {
        _backRectTrm = GetComponent<RectTransform>();
        _innerRectTrm = transform.Find("InnerPanel").GetComponent<RectTransform>();
        _innerRectTrm.anchoredPosition = new Vector2(0, Screen.height);
        _innerPanel = _innerRectTrm.GetComponent<InnerPanel>();
        _canvasGroup = GetComponent<CanvasGroup>();
        SetCanvasGroup(false);
    }

    private void SetCanvasGroup(bool active)
    {
        _canvasGroup.alpha = active ? 1 : 0;
        _canvasGroup.interactable = active;
        _canvasGroup.blocksRaycasts = active;
    }

    public void OpenPopup(int ballCount, int destroyBoxCnt, int sec, int starCnt)
    {
        _innerPanel.SetText(ResultCategory.Ball, ballCount.ToString());
        _innerPanel.SetText(ResultCategory.Box, destroyBoxCnt.ToString());
        _innerPanel.SetText(ResultCategory.Time, sec.ToString());
        
        SetCanvasGroup(true);
        Sequence seq = DOTween.Sequence();
        seq.AppendInterval(.3f);
        seq.Append(_innerRectTrm.DOAnchorPosY(0, .6f).SetEase(Ease.InBounce));
    }

    public void ClosePopup()
    {
        SetCanvasGroup(true);
        Sequence seq = DOTween.Sequence();
        seq.Append(_innerRectTrm.DOAnchorPosY(Screen.height, .6f).SetEase(Ease.InBounce));
        seq.AppendInterval(.3f);
        seq.AppendCallback(() =>
        {
            SetCanvasGroup(false);
        });
    }

    private void Update()
    {
        if (Input.GetKeyDown(KeyCode.P))
            OpenPopup(3, 20, 320, 3);
        if (Input.GetKeyDown(KeyCode.O))
            ClosePopup();
    }
}
