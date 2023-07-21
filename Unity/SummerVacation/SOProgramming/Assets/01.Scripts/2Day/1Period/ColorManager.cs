using System;
using System.Collections;
using System.Collections.Generic;
using TMPro;
using UnityEngine;

public class ColorManager : MonoBehaviour
{
    public ColorSetSO colorSet;

    private void Start()
    {
        // SO로드 
        colorSet = Resources.Load<ColorSetSO>("ColorDB");
        
        // 색상 설정
    }

    private void SetColor(ColorSetSO colorSetSO)
    {
        //SO 데이터 가지고 오고 적용하는 로직 만든다 
        //배경색 변경 폰트를 변경 배경 이미지도 바꿔본다 
        Camera.main.backgroundColor = colorSetSO.BackgroundColor;
        
        //UI text color 변경
        TextMeshProUGUI[] textMesh = FindObjectsOfType<TextMeshProUGUI>();
        foreach (var txt in textMesh)
        {
            txt.color = colorSet.TextColor;
        }
        
        //배경 이미지
        GameObject backgroundImageObj = GameObject.FindGameObjectWithTag("BackgroundImage");
        if (backgroundImageObj != null)
        {
            SpriteRenderer backgroundImageRenderer = backgroundImageObj.GetComponent<SpriteRenderer>();
            backgroundImageRenderer.sprite = colorSetSO.BackgroundImage;
        }
        else
        {
            Debug.LogWarning("BackgroundImage를 찾을 수 없음.");
        }
    }
}
