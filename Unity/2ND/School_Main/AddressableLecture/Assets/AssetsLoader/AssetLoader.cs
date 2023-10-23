using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

using UnityEngine;

public class AssetLoader : MonoBehaviour
{
    [SerializeField] private AssetLoaderSO _assetList;

    public AssetLoaderSO Assets => _assetList;
    public delegate void InvokeMessage(string msg);
    public delegate void Motify();

    public static event InvokeMessage OnCategoryMessage;
    public static event InvokeMessage OnDescMessage;
    public static event Motify OnLoadComplete;

    public static AssetLoader Instance;
    
    private void Awake()
    {
        DontDestroyOnLoad(gameObject);
        Instance = this;
    }

    private async void Start()
    {
        var totalCount = _assetList.TotalCount;
        OnCategoryMessage?.Invoke($"Loading {totalCount} Assets");
        await LoadAssets();
        
        PoolManager.Instance = new PoolManager(transform);
        OnLoadComplete?.Invoke(); //로딩 완료 인보크
    }

    private async Task LoadAssets()
    {
        //await Task.WhenAll(_assetList.loadingList.Select(x => x.LoadAssetAsync<GameObject>().Task));
        
        foreach (var r in _assetList.loadingList)
        {
            var asset = await r.LoadAssetAsync<GameObject>().Task;
            OnDescMessage?.Invoke($"Loading.. {asset.name}");
            _assetList.LoadingComplete(r, asset.name);
        }
        
        foreach (var r in _assetList.poolingList)
        {
            var asset = await r.assetRef.LoadAssetAsync<GameObject>().Task;
            OnDescMessage?.Invoke($"Loading.. {asset.name}");
            _assetList.LoadingComplete(r.assetRef, asset.name);
        }
    }

    public async Task MakePooling()
    {
        foreach (var r in _assetList.poolingList)
        {
            var prefab = (r.assetRef.Asset as GameObject).GetComponent<PoolableMono>();
            if (prefab == null)
            {
                Debug.LogWarning($"{r.assetRef.Asset.name} has not PoolableMono component");
                continue;
            }
            
            OnDescMessage?.Invoke($"loading... {r.assetRef.Asset.name}");
            await Task.Delay(1);//UI반영시간고려
            PoolManager.Instance.CreatePool(r.assetRef.AssetGUID, prefab, r.count);
        }
    }
}
