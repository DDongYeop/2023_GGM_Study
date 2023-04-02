using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

delegate int MyDelegate(int a, int b);

public class Std
{
    private Func<int, int, int> _action;
    public int Plus(int a, int b)
    {
        return a + b;
    }
    public int Minus(int a, int b)
    {
        return a - b;
    }
}

public class Test2 : MonoBehaviour
{
    private int dummy = 4;
    
    private void Start()
    {
        ABC();
    }

    //대리자 
    public void ABC()
    {
        MyDelegate a = delegate(int a, int b)
        {
            return a + b + dummy;
        };
        int result = a.Invoke(3, 4);
        Debug.Log(result);
    }
}
