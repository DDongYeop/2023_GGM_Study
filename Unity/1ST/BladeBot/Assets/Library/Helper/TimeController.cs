using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TimeController : MonoBehaviour
{
    public static TimeController Instance;

    public void ResetTimeScale()
    {
        StopAllCoroutines();
        Time.timeScale = 1f;
    }

    public void ModifyTimeScale(float endTimeValue, float timeToWait, Action OnComplete = null )
    {
        StartCoroutine(TimeScaleCoroutine(endTimeValue, timeToWait, OnComplete));
    }

    private IEnumerator TimeScaleCoroutine(float endTimeValue, float timeToWait, Action OnComplete)
    {
        yield return new WaitForSecondsRealtime(timeToWait);
        Time.timeScale = endTimeValue;
        OnComplete?.Invoke();
    }
}
