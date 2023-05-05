using System;
using System.Collections;
using System.Collections.Generic;
using TMPro;
using UnityEngine;
using UnityEngine.UI;

public class UIManager : MonoBehaviour
{
    public static UIManager Instance;

    private Image _gaugeFillImage;
    private TextMeshProUGUI _powerTrmText;

    public void Init()
    {
        Transform gaugeTrm = transform.Find("BottomInfoBox/GaugeBox");
        _gaugeFillImage = gaugeTrm.Find("Mask/Fill").GetComponent<Image>();
        _powerTrmText = gaugeTrm.Find("PowerText").GetComponent<TextMeshProUGUI>();
    }
    
    public void AddEvent(Cannon playerCannon)
    {
        playerCannon.OnPowerChanged += OnChangeGauge;
        playerCannon.OnAngleChanged += OnChangeGaugeHandle;
    }

    private void OnChangeGaugeHandle(float angle)
    {
        
    }

    private void OnChangeGauge(float currentPower, float maxPower)
    {
        _gaugeFillImage.fillAmount = currentPower / maxPower;
        _powerTrmText.SetText(Mathf.CeilToInt(currentPower).ToString());
    }
}
