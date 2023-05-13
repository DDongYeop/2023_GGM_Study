using System;
using System.Collections;
using System.Collections.Generic;
using TMPro;
using UnityEngine;

public class CountBox : MonoBehaviour
{
    private TextMeshProUGUI _txtText;

    public string Text
    {
        set
        {
            _txtText.text = value;
        }
    }

    private void Awake()
    {
        _txtText = transform.Find("Text").GetComponent<TextMeshProUGUI>();
    }
}
