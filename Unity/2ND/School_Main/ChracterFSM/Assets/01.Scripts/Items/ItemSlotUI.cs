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

            if (_itemAmountText == null) return;
            
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
        
        if (_itemAmountText == null) return;
        _itemAmountText.text = string.Empty;
    }

    //?????? ??????? ?? 
    public virtual void OnPointerDown(PointerEventData eventData)
    {
        if (item == null) return;

        if (!Keyboard.current.ctrlKey.isPressed)
        {
            return;
        }

        if (item.itemData.itemType == ItemType.Equipment)
        {
            //장비 장착 or 해제 
            Inventory.Instance.EquipItem(item.itemData as ItemDataEquipmentSO);
            return;
        }

        Inventory.Instance.RemoveItem(item.itemData);
    }

}
