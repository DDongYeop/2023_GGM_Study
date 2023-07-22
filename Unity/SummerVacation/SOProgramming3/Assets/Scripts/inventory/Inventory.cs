using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

[Serializable]
public class Inventory
{ 
    public InvenSlot[] InvenSlots = new InvenSlot[24];
     
    public void Clear()
    {
        foreach (InvenSlot invenSlot in InvenSlots)
        {
            invenSlot.destoryItem();
        }
    }
     
    public bool getFlagHave(ItemObj itemObj)
    { 
        return getFlagHave(itemObj.itemData.item_id);
    }
     
    public bool getFlagHave(int id)
    { 
        return InvenSlots.FirstOrDefault(i => i.item.item_id == id) != null;
    } 
}
 
