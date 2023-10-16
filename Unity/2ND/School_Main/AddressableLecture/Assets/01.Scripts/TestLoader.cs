using System.Threading.Tasks;
using UnityEngine;
using UnityEngine.AddressableAssets;
using UnityEngine.InputSystem;

public class TestLoader : MonoBehaviour
{
    [SerializeField] private AssetReference _levelRef;

    private void Update()
    {
        if (Keyboard.current.qKey.wasPressedThisFrame)
        {
            LoadLevel();
        }
    }

    private async Task LoadLevel()
    {
        if (!_levelRef.IsValid())
        {
            GameObject levelPrefab = await _levelRef.LoadAssetAsync<GameObject>().Task;
            Instantiate(levelPrefab, Vector3.zero, Quaternion.identity);
        }
        else
        {
            Instantiate(_levelRef.Asset, Vector3.zero, Quaternion.identity);
        }
    }
}
