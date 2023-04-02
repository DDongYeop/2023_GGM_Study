using System.Collections;
using UnityEngine;

public class CoroutineHandle : IEnumerator
{
    public object Current { get; }
    public bool IsDone { get; private set; }
    
    public bool MoveNext()
    {
        return !IsDone;
    }

    public void Reset()
    {
        
    }

    public CoroutineHandle(MonoBehaviour owner, IEnumerator coroutine)
    {
        Current = owner.StartCoroutine(Warp(coroutine));
    }

    private IEnumerator Warp(IEnumerator coroutine)
    {
        yield return coroutine;
        IsDone = true;
    }
}
