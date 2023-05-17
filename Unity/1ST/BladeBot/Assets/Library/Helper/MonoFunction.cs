using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MonoFunction : MonoBehaviour
{
    public static MonoFunction Instance;

    private void Awake()
    {
        if(Instance != null)
        {
            Debug.LogError("Multiple Mono function is running");
        }
        Instance = this;
    }

    public void AddCoroutine(Action Callback, float delayTime)
    {
        StartCoroutine(DelayCoroutine(Callback, delayTime));
    }

    private IEnumerator DelayCoroutine(Action Callback, float delayTime)
    {
        yield return new WaitForSeconds(delayTime);
        Callback?.Invoke();
    }

}
