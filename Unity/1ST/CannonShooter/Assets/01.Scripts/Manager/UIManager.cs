using System;
using System.Collections;
using System.Collections.Generic;
using TMPro;
using UnityEngine;
using UnityEngine.UI;
using DG.Tweening;

public class UIManager : MonoBehaviour
{
    public static UIManager Instance;

    private Image _gaugeFillImage;
    private TextMeshProUGUI _powerTmpText;
    private Color _fullColor;

    private bool _isShowMsgPopup = false;
    public Action OnCloseMessagePopup = null;
    private TextMeshProUGUI _msgTmpText;

    public void Init()
    {
        Transform gaugeTrm = transform.Find("BottomInfoBox/GaugeBox");
        _gaugeFillImage = gaugeTrm.Find("Mask/Fill").GetComponent<Image>();
        _powerTmpText = gaugeTrm.Find("PowerText").GetComponent<TextMeshProUGUI>();
        _msgTmpText = transform.Find("BottomInfoBox/MsgBox").GetComponent<TextMeshProUGUI>();
        _msgTmpText.SetText("");
    }

    public void AddEvent(Cannon playerCannon)
    {
        playerCannon.OnPowerChanged += OnChangeGaugeHandle;
        playerCannon.OnAngleChanged += OnChangeAngleHandle;
    }

    private void OnChangeAngleHandle(float angle)
    {
        //�� ���!
    }

    private void OnChangeGaugeHandle(float currentPower, float maxPower)
    {
        _gaugeFillImage.fillAmount = currentPower / maxPower;
        _powerTmpText.SetText( Mathf.CeilToInt(currentPower).ToString());
    }


    public void ShowMessagePopup(string msg)
    {
        //���� ����� ���⼭ �޽����� ����� �ϴ��� �׳� �ƹ��͵� ����.
        _msgTmpText.DOFade(.4f, 0.5f).SetLoops(-1, LoopType.Yoyo);
        _msgTmpText.SetText(msg);
        _isShowMsgPopup = true;
    }


    private void Update()
    {
        if(_isShowMsgPopup && Input.GetButtonDown("Jump"))
        {
            _isShowMsgPopup = false;

            _msgTmpText.SetText("");
            _msgTmpText.DOKill();
            _msgTmpText.alpha = 1; //이걸 복귀시켜야한다
            OnCloseMessagePopup?.Invoke();
        }
    }
}
