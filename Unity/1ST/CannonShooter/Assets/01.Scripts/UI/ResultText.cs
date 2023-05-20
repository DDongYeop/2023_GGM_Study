using System;
using System.Collections;
using System.Collections.Generic;
using TMPro;
using UnityEngine;

public class ResultText : MonoBehaviour
{
    private TextMeshProUGUI _text;

    private void Awake()
    {
        _text = transform.Find("CountText").GetComponent<TextMeshProUGUI>();
    }

    public void SetText(string text)
    {
        _text.SetText(text);
    }
}
