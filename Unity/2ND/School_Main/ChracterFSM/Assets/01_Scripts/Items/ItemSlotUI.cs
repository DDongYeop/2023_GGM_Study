using System.Collections;
using System.Collections.Generic;
using TMPro;
using UnityEngine;
using UnityEngine.EventSystems;
using UnityEngine.InputSystem;
using UnityEngine.UI;

public class ItemSlotUI : MonoBehaviour, IPointerDownHandler
{
    [SerializeField] private Image _itemImage;
    [SerializeField] private TextMeshProUGUI _itemAmountText;

    [SerializeField] private Sprite _emptySprite;
    public InventoryItem item;

    public void UpdateSlot(InventoryItem newItem)
    {
        item = newItem;
        
        if(item != null)
        {
            _itemImage.sprite = item.itemData.itemIcon;

            if(item.stackSize > 1)
            {
                _itemAmountText.text = item.stackSize.ToString();
            }
            else
            {
                _itemAmountText.text = string.Empty;
            }
        }
    }

    public void CleanUpSlot()
    {
        item = null;
        _itemImage.sprite = _emptySprite;
        _itemAmountText.text = string.Empty;
    }

    //여기다가 클릭했을 때 
    public void OnPointerDown(PointerEventData eventData)
    {
        if (item == null) return;

        if (!Keyboard.current.ctrlKey.isPressed)
        {
            return;
        }

        if (item.itemData.itemType == ItemType.Equipment)
        {
            //장비해제 또는 장착 쪽으로 갈꺼고
        }

        Inventory.Instance.RemoveItem(item.itemData);
    }

}
