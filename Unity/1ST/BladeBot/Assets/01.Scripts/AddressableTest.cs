using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AddressableAssets;
using UnityEngine.ResourceManagement.AsyncOperations;

public class AddressableTest : MonoBehaviour
{
    [SerializeField] private AssetReference _ref;
    
    private void Update()
    {
        if (Input.GetKeyDown(KeyCode.A))
            LoadPopupText();
        if (Input.GetKeyDown(KeyCode.D))
            UnloadPopupText();
    }

    private AsyncOperationHandle<GameObject> _handle;
    private GameObject _popupText;
    
    private void LoadPopupText()
    {
        _ref.InstantiateAsync(Vector3.zero, Quaternion.identity).Completed += (obj) =>
        {
            _handle = obj;
            _popupText = obj.Result;
        };
    }

    private void UnloadPopupText()
    { 
        _ref.ReleaseInstance(_popupText);
    }
}
