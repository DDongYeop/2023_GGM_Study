using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AddressableAssets;

public class AddressableTest : MonoBehaviour
{
    private void Update()
    {
        if (Input.GetKeyDown(KeyCode.A))
            LoadPopupText();
    }
    
    private void LoadPopupText()
    {
        Addressables.LoadAssetAsync<GameObject>($"PopupText").Completed += obj =>
        {
            Debug.Log(obj);
            Debug.Log(obj.Result);
        };
    }
}
