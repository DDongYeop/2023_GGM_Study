using System.Collections;
using System.Collections.Generic;
using System.Threading.Tasks;
using UnityEngine;
using UnityEngine.AddressableAssets;

public class Pool<T> where T : PoolableMono
{
    private Stack<T> _pool = new Stack<T>();
    private AssetReference _assetRef;
    private Transform _parent;
    private int _count;

    public Pool(AssetReference assetRef, Transform parent, int count = 10)
    {
        _assetRef = assetRef;
        _parent = parent;
        _count = count;
    }

    public async Task MakeObjects()
    {
        for (int i = 0; i < _count; i++)
        {
            GameObject obj = await MakeObject();
            T poolIntance = obj.GetComponent<T>();
            poolIntance.assetRef = _assetRef;
            obj.SetActive(false);
            _pool.Push(poolIntance);
        }
    }

    private async Task<GameObject> MakeObject()
    {
        return await _assetRef.InstantiateAsync(_parent).Task;
    }

    public void Clear(bool unloadPrefab = false)
    {
        while(_pool.Count > 0)
        {
            var item = _pool.Pop();
            GameObject.Destroy(item.gameObject);
        }

        if(unloadPrefab)
        {
            _assetRef.ReleaseAsset();
        }
    }

    public async Task<T> Pop()
    {
        T obj = null;

        if(_pool.Count <= 0)
        {
            GameObject objInstance = await MakeObject();
            obj = objInstance.GetComponent<T>();
            obj.assetRef = _assetRef;
        }
        else
        {
            obj = _pool.Pop();
            obj.gameObject.SetActive(true);
        }

        return obj;
    }

    public void Push(T obj)
    {
        obj.gameObject.SetActive(false);
        _pool.Push(obj);
    }

}
