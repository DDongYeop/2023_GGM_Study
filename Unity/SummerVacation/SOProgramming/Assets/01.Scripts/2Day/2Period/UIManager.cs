using System;
using System.Collections;
using System.Collections.Generic;
using TMPro;
using UnityEngine;

public class UIManager : MonoBehaviour
{
    private TextMeshProUGUI _textMeshProUGUI;

    private void Start()
    {
        _textMeshProUGUI = GetComponent<TextMeshProUGUI>();
    }

    private void Update()
    {
        //_textMeshProUGUI.text = "EXP : " + GlobalData.Instance.playerExperience;
    }
}
