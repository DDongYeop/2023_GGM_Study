using System;
using System.Collections.Generic;
using System.Linq;
using System.Security.Cryptography;
using System.Text;
using System.Threading.Tasks;
using UnityEngine;
using UnityEngine.EventSystems;

 
public class DynamicUIInventory : UIInventory
{ 
    [SerializeField]
    protected GameObject prefabSlot;

    [SerializeField]
    protected Vector2 start;

    [SerializeField]
    protected Vector2 size;

    [SerializeField]
    protected Vector2 space;

    [SerializeField]
    protected int numCols = 4; 

    public override void createUISlots()
    {
        uiSlotLists = new Dictionary<GameObject, InvenSlot>();

        for (int i = 0; i < inventoryObj.invenSlots.Length; ++i)
        {
            GameObject gameObj = Instantiate(prefabSlot, Vector3.zero, Quaternion.identity, transform);
            gameObj.GetComponent<RectTransform>().anchoredPosition = CalculatePosition(i);

            AddEventAction(gameObj, EventTriggerType.PointerEnter, delegate {  OnEnterSlots(gameObj); });
            AddEventAction(gameObj, EventTriggerType.PointerExit, delegate { OnExitSlots(gameObj); });
            AddEventAction(gameObj, EventTriggerType.BeginDrag, delegate { OnStartDrag(gameObj); });
            AddEventAction(gameObj, EventTriggerType.EndDrag, delegate { OnEndDrag(gameObj); });
            AddEventAction(gameObj, EventTriggerType.Drag, delegate { OnMovingDrag(gameObj); });
            AddEventAction(gameObj, EventTriggerType.PointerClick, (data) => { OnClick(gameObj, (PointerEventData)data); });

            inventoryObj.invenSlots[i].slotUI = gameObj;
            uiSlotLists.Add(gameObj, inventoryObj.invenSlots[i]);
            gameObj.name += ": " + i;
        }
    }

    public Vector3 CalculatePosition(int i)
    {
        float x = start.x + ((space.x + size.x) * (i % numCols));
        float y = start.y + (-(space.y + size.y) * (i / numCols));

        return new Vector3(x, y, 0f);
    } 
} 