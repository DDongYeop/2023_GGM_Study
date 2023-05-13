using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ActionTest : MonoBehaviour
{
    
    

    void Start()
    {
        Action<float> myFunc =  value => Debug.Log($"Hello {value}"); 
        
        //기능을 전달 
        StartCoroutine(MyCo( myFunc  ));

    }

    

    IEnumerator MyCo(Action<float> abc )
    {
        float randFloat = UnityEngine.Random.Range(1f, 2f);
        yield return new WaitForSeconds(randFloat);
        abc(randFloat);
    }
    
}
