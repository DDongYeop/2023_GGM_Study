using System;
using System.ComponentModel;
using System.IO;
using System.Linq;
using System.Runtime.Serialization;
using System.Runtime.Serialization.Formatters.Binary;
using UnityEngine;
 
public enum InterfaceType
{
    Inventory,  
    Equipment,  
    QuickSlot,  
    Box  
}
 
[CreateAssetMenu(fileName = "New InvnetoryObject", menuName = "Inventory/InvnetoryObject")]
public class InventoryObj : ScriptableObject
{ 
    public ItemDBObj itemDBObj;
     
    public InterfaceType type;
     
    [SerializeField]
    private Inventory inventory = new Inventory();
     
    public InvenSlot[] invenSlots => inventory.InvenSlots;
     
    public int getEmptySlotCnt
    {
        get
        { 
            int cnt = 0; 
            foreach (InvenSlot slot in invenSlots)
            {  
                if (slot.item.item_id <= -1)
                { 
                    cnt++;
                }
            }

            return cnt;
        }
    }

    public Action<ItemObj> OnUseItemObj;
     
    public bool AddItem(Item item, int amount)
    { 
        InvenSlot invenSlot = seachItemInInven(item); 
        if (!itemDBObj.itemObjs[item.item_id].getFlagStackable || invenSlot == null)
        { 
            if (getEmptySlotCnt <= 0)
            {
                return false;
            }
      
            getEmptySlot().uploadSlot(item, amount);
        }
        else
        {  
            invenSlot.addCnt(amount);
        }

        return true;
    }
     
    public InvenSlot seachItemInInven(Item item)
    { 
        return invenSlots.FirstOrDefault(i => i.item.item_id == item.item_id);
    }
     
    public InvenSlot getEmptySlot()
    {
        return invenSlots.FirstOrDefault(i => i.item.item_id <= -1);
    }
     
    public bool IsContainItem(ItemObj itemObject)
    { 
        return invenSlots.FirstOrDefault(i => i.item.item_id == itemObject.itemData.item_id) != null;
    }
     
    public void SwapItems(InvenSlot itemA, InvenSlot itemB)
    { 
        if (itemA == itemB)
        {
            return;
        }
         
        if (itemB.getFlagEquipSlot(itemA.ItemObject) && itemA.getFlagEquipSlot(itemB.ItemObject))
        { 
            InvenSlot temp = new InvenSlot(itemB.item, itemB.itemCnt); 
            itemB.uploadSlot(itemA.item, itemA.itemCnt); 
            itemA.uploadSlot(temp.item, temp.itemCnt);
        }
    }

    public void Clear()
    {
        inventory.Clear();
    }
} 