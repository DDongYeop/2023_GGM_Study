using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TestItems : MonoBehaviour
{
    public InventoryObj equipmentObject;
    public InventoryObj inventoryObject;
    public ItemDBObj databaseObject;

    public void AddNewItem()
    {
        if (databaseObject.itemObjs.Length > 0)
        {
            ItemObj newItemObject = databaseObject.itemObjs[Random.Range(0, databaseObject.itemObjs.Length )]; 
            Item newItem = new Item(newItemObject);
             
            inventoryObject.AddItem(newItem, 1);
        }
    }

    public void ClearInventory()
    { 
         inventoryObject.Clear();
    }
}
