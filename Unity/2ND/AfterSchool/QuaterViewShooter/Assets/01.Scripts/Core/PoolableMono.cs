using UnityEngine;
using UnityEngine.AddressableAssets;

public abstract class PoolableMono : MonoBehaviour
{
    public AssetReference assetRef;
    public abstract void Init();
}
