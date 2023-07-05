using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public static class MonoExtensions
{
    public static CoroutineHandle RunCoroutine(this MonoBehaviour owner, IEnumerator coroutine)
    {
        return new CoroutineHandle(owner, coroutine);
    }
}
