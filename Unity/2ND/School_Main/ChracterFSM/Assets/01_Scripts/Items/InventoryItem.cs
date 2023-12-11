using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[Serializable]
public class InventoryItem
{
    public ItemDataSO itemData;
    public int stackSize;

    public InventoryItem(ItemDataSO itemData)
    {
        this.itemData = itemData;
        AddStack();
    }

    public void AddStack()
    {
        ++stackSize;
    }

    public void RemoveStack(int count = 1)
    {
        stackSize -= count;
    }
}
