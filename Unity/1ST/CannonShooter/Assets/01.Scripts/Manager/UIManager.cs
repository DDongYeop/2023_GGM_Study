using System;
using System.Collections;
using System.Collections.Generic;
using TMPro;
using UnityEngine;
using UnityEngine.UI;
using DG.Tweening;
using UnityEngine.SceneManagement;

public class UIManager : MonoBehaviour
{
    public static UIManager Instance;

    private Image _gaugeFillImage;
    private TextMeshProUGUI _powerTmpText;
    private Color _fullColor;

    private bool _isShowMsgPopup = false;
    public Action OnCloseMessagePopup = null;
    private TextMeshProUGUI _msgTmpText;

    private Transform _playerTrm;
    private Transform _mainCamTrm;
    private RectTransform _cannonThumbnail;
    private bool _isIconShow;

    private LoadingScreen _loadingScreen;
    
    private CountBox _boxCount, _ballCount;

    private ResultPanel _resultPanel;

    public string BoxCount
    {
        set
        {
            _boxCount.Text = value;
        }
    }
    
    public string BallCount
    {
        set
        {
            _ballCount.Text = value;
        }
    }
    
    public void Init()
    {
        Transform gaugeTrm = transform.Find("BottomInfoBox/GaugeBox");
        _gaugeFillImage = gaugeTrm.Find("Mask/Fill").GetComponent<Image>();
        _powerTmpText = gaugeTrm.Find("PowerText").GetComponent<TextMeshProUGUI>();
        _msgTmpText = transform.Find("BottomInfoBox/MsgBox").GetComponent<TextMeshProUGUI>();
        _msgTmpText.SetText("");
        _playerTrm = GameManager.Instance.Player.transform;
        _mainCamTrm = GameObject.Find("Main Camera").GetComponent<Transform>();
        _cannonThumbnail = GameObject.Find("CannonThumbnail").GetComponent<RectTransform>();

        _boxCount = transform.Find("TopRightBox/BoxCountBox").GetComponent<CountBox>();
        _ballCount = transform.Find("TopRightBox/BallCountBox").GetComponent<CountBox>();

        _resultPanel = transform.Find("ResultPanel").GetComponent<ResultPanel>();

        _loadingScreen = transform.Find("LoadingScreen").GetComponent<LoadingScreen>();
        GameManager.Instance.OnStageLoadCompleted += _loadingScreen.ScreenOff;
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

        CameraPlayerCheck();
    }

    private void CameraPlayerCheck()
    {
        float value = Mathf.Abs(_mainCamTrm.position.x - _playerTrm.position.x);

        if (value < 13 && _isIconShow == false) 
        {
            _isIconShow = !_isIconShow;
            _cannonThumbnail.DOKill();
            _cannonThumbnail.DOAnchorPosX(-200, .5f);
        }
        else if (value > 13 && _isIconShow)
        {
            _isIconShow = !_isIconShow;
            _cannonThumbnail.DOKill();
            _cannonThumbnail.DOAnchorPosX(0, .5f);
        }
    }

    public void ShowResultPanel(int ballCount, int destroyBoxCnt, int sec, int starCnt)
    {
        _resultPanel.OpenPopup(ballCount, destroyBoxCnt, sec, starCnt);
    }
}
