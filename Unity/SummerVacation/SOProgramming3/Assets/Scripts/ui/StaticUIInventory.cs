using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using UnityEngine;
using UnityEngine.EventSystems;
 
public class StaticUIInventory : UIInventory
{
    public GameObject[] staticSlots = null;

    public override void createUISlots()
    { 
        uiSlotLists = new Dictionary<GameObject, InvenSlot>();
        for (int i = 0; i < inventoryObj.invenSlots.Length; i++)
        {
            GameObject gameObj = staticSlots[i];

            AddEventAction(gameObj, EventTriggerType.PointerEnter, delegate { OnEnterSlots(gameObj); });
            AddEventAction(gameObj, EventTriggerType.PointerExit, delegate { OnExitSlots(gameObj); });
            AddEventAction(gameObj, EventTriggerType.BeginDrag, delegate { OnStartDrag(gameObj); });
            AddEventAction(gameObj, EventTriggerType.EndDrag, delegate { OnEndDrag(gameObj); });
            AddEventAction(gameObj, EventTriggerType.Drag, delegate { OnMovingDrag(gameObj); });

            inventoryObj.invenSlots[i].slotUI = gameObj;
            uiSlotLists.Add(gameObj, inventoryObj.invenSlots[i]);
        }
    }
} 