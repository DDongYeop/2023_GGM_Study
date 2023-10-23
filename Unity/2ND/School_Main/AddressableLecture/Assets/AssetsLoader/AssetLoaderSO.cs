using System;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AddressableAssets;
using Object = UnityEngine.Object;

public enum AssetName
{
    LineTrail = 0,
    AudioEffect = 1,
}

[Serializable]
public struct PoolingItem
{
    public AssetReference assetRef;
    public ushort count; //몇개 만들거냐
}

[CreateAssetMenu (menuName = "SO/AddressableAssets")]
public class AssetLoaderSO : ScriptableObject
{
    public int TotalCount => loadingList.Count + poolingList.Count;
    public List<AssetReference> loadingList; //로딩만 할 애들 
    public List<PoolingItem> poolingList; //풀링 필요한 애들

    private Dictionary<string, AssetReference> _nameDictionary; //이름으로 부르기
    private Dictionary<string, AssetReference> _guidDictionary; //guid로 부르기

    private void OnEnable()
    {
        _nameDictionary = new();
        _guidDictionary = new();
    }

    //로딩이 완료되면 언제든 쓸수 있게 딕셔너리로 
    public void LoadingComplete(AssetReference reference, string name)
    {
        _guidDictionary.Add(reference.AssetGUID, reference);
        _nameDictionary.Add(name, reference);
    }

    public Object GetAssetByGUID(string guid)
    {
        if (_guidDictionary.TryGetValue(guid, out AssetReference value))
        {
            return value.Asset;
        }

        return null;
    }


    public Object GetAssetByName(string guid)
    {
        if (_nameDictionary.TryGetValue(name, out AssetReference value))
        {
            return value.Asset;
        }

        return null;
    }
}
