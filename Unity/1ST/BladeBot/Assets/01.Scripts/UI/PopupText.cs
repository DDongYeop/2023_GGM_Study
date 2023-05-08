using System;
using System.Collections;
using System.Collections.Generic;
using Core;
using TMPro;
using UnityEditor;
using UnityEngine;

public class PopupText : PoolableMono
{
    private TextMeshPro _tmpText;

    private void Awake()
    {
        _tmpText = GetComponent<TextMeshPro>();
    }

    public void StartPopup(string text, Vector3 pos, int fontSize, Color color, float time = 1f, float yDelta = 2f)
    {
        _tmpText.SetText(text);
        _tmpText.color = color;
        _tmpText.fontSize = fontSize;
        transform.position = pos;
        StartCoroutine(ShowRoutine(time, yDelta));
    }
    
    private float EaseOutElastic(float x) 
    {
        float c4 = (2f * Mathf.PI) / 3f;

        return x == 0 ? 0 : x == 1 ? 1 : Mathf.Pow(2f, -10f * x) * Mathf.Sin((x * 10f - 0.75f) * c4) + 1;
    }

    private IEnumerator ShowRoutine(float time, float yDelta)
    {
        float percent = 0;
        Vector3 firstPos = transform.position;
        float currentTime = 0;
        
        while (percent < 1)
        {
            //올라가면서 투명도 내려서 투명하게 만들기
            currentTime += Time.deltaTime; //나중에 지우기
            percent = currentTime / time;
            //float nextY = Mathf.Lerp(0, yDelta, percent);
            float nextOpacity = Mathf.Lerp(1, 0, percent);

            float value = EaseOutElastic(percent);
            
            transform.position = firstPos + new Vector3(0, yDelta * value, 0);
            _tmpText.alpha = nextOpacity;
            
            Vector3 camDirection = (transform.position - Define.MainCam.transform.position).normalized;
            transform.rotation = Quaternion.LookRotation(camDirection);
            yield return null;
        }
        PoolManager.Instance.Push(this);
    }

    public override void Init()
    {
        _tmpText.alpha = 1;
    }
}
