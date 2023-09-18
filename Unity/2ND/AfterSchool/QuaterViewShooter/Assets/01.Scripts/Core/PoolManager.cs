using System.Collections.Generic;
using System.Threading.Tasks;
using UnityEngine;
using UnityEngine.AddressableAssets;

public class PoolManager
{
    public static PoolManager Instance;

    private Dictionary<string, Pool<PoolableMono>> _pools = new Dictionary<string, Pool<PoolableMono>>();

    private Transform _parentTrm;

    public PoolManager(Transform parentTrm)
    {
        _parentTrm = parentTrm;
    }
    //풀에 있는거 싹다 날리는거
    public void ClearPool(bool unloadPrefab = false)
    {
        foreach(var pool in _pools)
        {
            pool.Value.Clear(unloadPrefab);
        }

        _pools.Clear();
    }

    public async Task CreatePool(AssetReference assetRef, int count = 10)
    {
        Pool<PoolableMono> pool = new Pool<PoolableMono>(assetRef, _parentTrm, count);
        await pool.MakeObjects();
        _pools.Add(assetRef.AssetGUID, pool);
    }

    public async Task<PoolableMono> Pop(AssetReference assetRef)
    {
        if(!_pools.ContainsKey(assetRef.AssetGUID))
        {
            Debug.LogError("Prefab doesn't exist on pool");
            return null;
        }

        PoolableMono item = await _pools[assetRef.AssetGUID].Pop();
        item.Init();
        return item;
    }

    public void Push(PoolableMono obj)
    {
        _pools[obj.assetRef.AssetGUID].Push(obj);
    }
}
