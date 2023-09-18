using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ObjectPools : MonoBehaviour
{
    private static ObjectPools _instance;
    public static ObjectPools Instance => _instance;
    
    private void Awake()
    {
        if(_instance != null)
        {
            Destroy(_instance.gameObject);
        }
        _instance = this;

        PoolManager.Instance = new PoolManager(transform);
        DontDestroyOnLoad(gameObject); //현재 오브젝트를 부수지 않도록 함.
    }

    public void DestroyAll()
    {
        PoolManager.Instance.ClearPool();
    }
}
