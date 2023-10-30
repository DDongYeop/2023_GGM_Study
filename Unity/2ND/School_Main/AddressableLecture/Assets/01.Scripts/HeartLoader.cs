using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AddressableAssets;

public class HeartLoader : MonoBehaviour
{
    [SerializeField] private AssetReference _assetRef;

    private void Awake()
    {
        GameObject prefab = AssetLoader.Instance.Assets.GetAssetByGUID(_assetRef.AssetGUID) as GameObject;
        Instantiate(prefab, transform);
    }
}
