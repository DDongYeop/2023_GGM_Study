using System.Collections.Generic;
using System.Threading.Tasks;
using UnityEngine;
using UnityEngine.AddressableAssets;
using UnityEngine.InputSystem;

public class TestLoader : MonoBehaviour
{
    [SerializeField] private AssetReference _levelRef;
    private List<GameObject> _list = new();

    private void Update()
    {
        if (Keyboard.current.qKey.wasPressedThisFrame)
        {
            LoadLevel();
        }
        if (Keyboard.current.wKey.wasPressedThisFrame)
        {
            DestroyAsset();
        }
    }

    private void DestroyAsset()
    {
        foreach (var level in _list)
        {
            Destroy(level);
            //_levelRef.ReleaseInstance(level);
        }
        _levelRef.ReleaseAsset();
        _list.Clear();
    }

    private async Task LoadLevel()
    {
        if (!_levelRef.IsValid())
            await _levelRef.LoadAssetAsync<GameObject>().Task;
        
        var obj = Instantiate(_levelRef.Asset, Vector3.zero, Quaternion.identity) as GameObject;
        _list.Add(obj);
    }
}
