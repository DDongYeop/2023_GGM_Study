using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Inventory : MonoBehaviour
{
    public GameItemSO[] items;

    private void Start()
    {
        items = new GameItemSO[3];

        items[0] = Resources.Load<GameItemSO>("ItemData");
        items[1] = Resources.Load<GameItemSO>("ArmorData");
        items[2] = Resources.Load<GameItemSO>("ConsumableData");

        foreach (var item in items)
        {
            Debug.Log($"인벤토리 아이템 : " + item.name);
        }
    }
}
