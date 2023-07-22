using System;
using System.Collections.Generic;
using System.Diagnostics.Tracing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using UnityEngine;
 
[Serializable]
public class InvenSlot
{  
    public ItemType[] itemTypes = new ItemType[0];
     
    [NonSerialized]
    public InventoryObj inventoryObj;
     
    [NonSerialized]
    public GameObject slotUI;
     
    [NonSerialized]
    public Action<InvenSlot> OnPreUpload; 
    [NonSerialized]
    public Action<InvenSlot> OnPostUpload;
     
    public Item item; 
    public int itemCnt;
     
    public ItemObj ItemObject
    {
        get
        { 
            return item.item_id >= 0 ? inventoryObj.itemDBObj.itemObjs[item.item_id] : null;
        }
    }
     
    public InvenSlot() => uploadSlot(new Item(), 0); 
    public InvenSlot(Item item, int cnt) => uploadSlot(item, cnt);

     
    public void destoryItem() => uploadSlot(new Item(), 0);
     
    public void addCnt(int value) => uploadSlot(item, itemCnt += value);
     
    public void uploadSlot(Item item, int cnt)
    { 
        if (cnt <= 0)
        {
            item = new Item();
        }
 
        OnPreUpload?.Invoke(this); 
        this.item = item;
        this.itemCnt = cnt; 
        OnPostUpload?.Invoke(this);
    }
       
    public bool getFlagEquipSlot(ItemObj itemObj)
    { 
        if (itemTypes.Length <= 0 || itemObj == null || itemObj.itemData.item_id < 0)
        { 
            return true;
        }
         
        foreach (ItemType itemType in itemTypes)
        { 
            if (itemObj.itemType == itemType)
            {
                return true;
            }
        }
         
        return false;
    } 
}  