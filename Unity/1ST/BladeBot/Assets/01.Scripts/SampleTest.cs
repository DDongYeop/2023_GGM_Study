using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MyGGM : IEnumerable // IEnumerable상속 받으면 foreach돌릴 수 있음 
{
    private int[] _arr = { 1, 2, 3 };
    private int _index = 0;
    
    public IEnumerator GetEnumerator()
    {
        yield return _arr[0];
        yield return _arr[1];
        yield return _arr[2];
    }
    /*
        foreach (var ggm in _ggm)
        {
            Debug.Log(ggm);
        }
     */
}

public class CoroutineHandle : IEnumerator
{
    public bool IsDone { get; private set; }
    public object Current { get; }
    
    public bool MoveNext()
    {
        return !IsDone;
    }

    public void Reset()
    {
        
    }

    public CoroutineHandle(MonoBehaviour owner, IEnumerator coroutine)
    {
        Current = owner.StartCoroutine(Wrap(coroutine));
    }

    private IEnumerator Wrap(IEnumerator corutine)
    {
        yield return corutine;
        IsDone = true;
    }
}

public class SampleTest : MonoBehaviour
{
    private IEnumerator Start()
    {
        // yield return CoA(); //yield return에 IEnumerator 박을 수 있다.
        // yield return CoB();

        //var task1 = StartCoroutine(CoA());
        //var task2 = StartCoroutine(CoB());
        //yield return task1;
        //yield return task2;

        var task1 = this.RunCoroutine(CoA());
        var task2 = this.RunCoroutine(CoB());

        while (!task1.IsDone || !task2.IsDone)
        {
            yield return null;
        }
        
        Debug.Log("Job Complete");
    }

    private IEnumerator CoA()
    {
        yield return new WaitForSeconds(1f);
        Debug.Log("Co A Complete");
    }
    
    private IEnumerator CoB()
    {
        yield return new WaitForSeconds(1f);
        Debug.Log("Co B Complete");
    }
}
