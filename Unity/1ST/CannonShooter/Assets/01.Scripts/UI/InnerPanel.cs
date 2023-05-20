using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public enum ResultCategory
{
    Ball = 1,
    Box = 2,
    Time = 3
}

public class InnerPanel : MonoBehaviour
{
    private Dictionary<ResultCategory, ResultText> _textDictionary;

    private void Awake()
    {
        _textDictionary = new Dictionary<ResultCategory, ResultText>();
        foreach (ResultCategory cat in Enum.GetValues(typeof(ResultCategory)))
        {
            ResultText rt = transform.Find($"Left/Result{cat.ToString()}").GetComponent<ResultText>();
            _textDictionary.Add(cat, rt);
        }
    }

    public void SetText(ResultCategory cat, string value)
    {
        if (_textDictionary.TryGetValue(cat, out ResultText rt))
        {
            rt.SetText(value);
        }
    }
}
