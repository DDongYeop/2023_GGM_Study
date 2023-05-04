using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TimeController : MonoBehaviour
{
    public static TimeController Instance = null;

    private void Awake()
    {
        if (Instance != null)
            Debug.LogError("Multiple TimeController Running ");
        Instance = this;
    }

    public void SetTimeScale(float value)
    {
        Time.timeScale = value;
    }
}
