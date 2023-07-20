using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ItemManager : MonoBehaviour
{
    public ItemData ItemData;

    private void Start()
    {
        print(Resources.Load<Sprite>("HealthPotion"));
        CreateNewItem("Health Potion", Resources.Load<Sprite>("HealthPotion"), 10);
        CreateNewItem("Mana Potion", Resources.Load<Sprite>("ManaPotion"), 10);
        CreateNewItem("Atk Potion", Resources.Load<Sprite>("AtkPotion"), 10);
    }

    private void CreateNewItem(string name, Sprite icon, int price)
    {
        //ItemData newItem = new ItemData(); // 인스턴스 생성
        ItemData newItem = ScriptableObject.CreateInstance<ItemData>(); 
        
        newItem.itemName = name;
        newItem.itemIcon = icon;
        newItem.itemPrice = price;

        string assetsPath = "Assets/" + name + ".asset";
        UnityEditor.AssetDatabase.CreateAsset(newItem, assetsPath);
        UnityEditor.AssetDatabase.SaveAssets();

        Debug.Log("SO에셋으로 저장 되었습니다.");
    }
}
