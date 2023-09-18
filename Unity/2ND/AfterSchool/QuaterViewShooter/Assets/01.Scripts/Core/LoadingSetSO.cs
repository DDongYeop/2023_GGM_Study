using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AddressableAssets;

[System.Serializable]
public struct PoolingItem
{
    public AssetReference reference;
    public int count;
}

[System.Serializable]
public struct LoadingItem
{
    public AssetReference reference;
}

[CreateAssetMenu(menuName = "SO/LoadingAsset")]
public class LoadingSetSO : ScriptableObject
{
    public List<PoolingItem> poolingList;
    public List<LoadingItem> loadingList;

    public int GetTotalCount()
    {
        return poolingList.Count + loadingList.Count;
    }
}
