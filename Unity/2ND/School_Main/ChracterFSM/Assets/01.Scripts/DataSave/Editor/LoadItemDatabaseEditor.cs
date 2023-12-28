using System;
using System.Collections.Generic;
using UnityEditor;
using UnityEngine;

[CustomEditor(typeof(SaveManager))]
public class LoadItemDatabaseEditor : Editor
{
    private SaveManager _saveManager;
    private string _soFilename = "ItemDB";

    private void OnEnable()
    {
        _saveManager = (SaveManager)target;
    }

    public override void OnInspectorGUI()
    {
        base.OnInspectorGUI();

        if (GUILayout.Button("Generate item DB"))
        {
            CreateItemDBAsset();
            AssetDatabase.SaveAssets();
            AssetDatabase.Refresh();
        }
    }

    private void CreateItemDBAsset()
    {
        List<ItemDataSO> loadedList = new List<ItemDataSO>();
        string[] assetIDArray = AssetDatabase.FindAssets("", new[] { "Assets/08.SO/Items" });

        foreach (var assetID in assetIDArray)
        {
            string assetPath = AssetDatabase.GUIDToAssetPath(assetID);
            ItemDataSO item = AssetDatabase.LoadAssetAtPath<ItemDataSO>(assetPath);

            if (item != null)
            {
                loadedList.Add(item);
            }
        }

        string dbPath = $"Assets/08.SO/{_soFilename}.asset";
        ItemDatabaseSO itemDB = AssetDatabase.LoadAssetAtPath<ItemDatabaseSO>(dbPath);
        
        if (itemDB == null)
        {
            //새로운거 만들기 
            itemDB = ScriptableObject.CreateInstance<ItemDatabaseSO>(); //메모리에만
            itemDB.itemList = loadedList;
            string realPath = AssetDatabase.GenerateUniqueAssetPath(dbPath);
            AssetDatabase.CreateAsset(itemDB, realPath);
            Debug.Log($"item db created at {dbPath}");
        }
        else
        {
            //여기는 데이터만 고치고
            itemDB.itemList = loadedList;
            EditorUtility.SetDirty(itemDB); //너 더러워
        }
    }
}
