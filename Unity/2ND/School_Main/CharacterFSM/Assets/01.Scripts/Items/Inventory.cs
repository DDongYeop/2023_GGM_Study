using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Inventory : MonoSingleton<Inventory>
{
    public List<InventoryItem> stash; //잡템 창고
    public Dictionary<ItemDataSO, InventoryItem> stashDictory;
    
    public List<InventoryItem> inven; //장비 창고
    public Dictionary<ItemDataSO, InventoryItem> invenDictory;

    [Header("Inventory UI")] 
    [SerializeField] private Transform _stashSlotParent;
    [SerializeField] private Transform _invenSlotParent;

    private ItemSlotUI[] _stashItemSlots;
    private ItemSlotUI[] _invenItemSlots;

    private void Awake()
    {
        stash = new List<InventoryItem>();
        stashDictory = new Dictionary<ItemDataSO, InventoryItem>();
        _stashItemSlots = _stashSlotParent.GetComponentsInChildren<ItemSlotUI>();
        
        inven = new List<InventoryItem>();
        invenDictory = new Dictionary<ItemDataSO, InventoryItem>();
        _invenItemSlots = _stashSlotParent.GetComponentsInChildren<ItemSlotUI>();
        
    }

    private void Start()
    {
        UpdateSlotUI();
    }

    public void UpdateSlotUI()
    {
        #region Clean up slots

        for (int i = 0; i < _stashItemSlots.Length; ++i)
        {
            _stashItemSlots[i].CleanUpSlot();
        }
        
        for (int i = 0; i < _invenItemSlots.Length; ++i)
        {
            _invenItemSlots[i].CleanUpSlot();
        }

        #endregion

        #region redraw slots

        for (int i = 0; i < stash.Count; ++i)
        {
            _stashItemSlots[i].UpdateSlot(stash[i]);
        }
        
        for (int i = 0; i < inven.Count; ++i)
        {
            _invenItemSlots[i].UpdateSlot(inven[i]);
        }

        #endregion
    }

    public void AddItem(ItemDataSO item)
    {
        if (item.itemType == ItemType.Equipment)
        {
            AddToInventory(item);
        }
        else if (item.itemType == ItemType.Material)
        {
            AddToStash(item);
        }
        
        UpdateSlotUI();
    }

    public void RemoveItem(ItemDataSO item, int count = 1)
    {
        if (stashDictory.TryGetValue(item, out InventoryItem inventoryItem))
        {
            if (stashDictory[item].stackSize <= count)
                stashDictory.Remove(item);
            else
                stashDictory[item].RemoveStack();
        }
        
        UpdateSlotUI();
    }

    private void AddToInventory(ItemDataSO item)
    {
        //이미 해당 아이템이 인벤토리상에 ㅇ;ㅣㅆ다면 수치를 올리고 그렇지 않다면 새로 등록하고
        if (invenDictory.TryGetValue(item, out InventoryItem inventoryItem))
        {
            inventoryItem.AddStack();
        }
        else
        {
            InventoryItem newInventoryItem = new InventoryItem(item);
            inven.Add(newInventoryItem);
            invenDictory.Add(item, newInventoryItem); 
        }
    }

    private void AddToStash(ItemDataSO item)
    {
        //이미 해당 아이템이 인벤토리상에 ㅇ;ㅣㅆ다면 수치를 올리고 그렇지 않다면 새로 등록하고
        if (stashDictory.TryGetValue(item, out InventoryItem inventoryItem))
        {
            inventoryItem.AddStack();
        }
        else
        {
            InventoryItem newInventoryItem = new InventoryItem(item);
            stash.Add(newInventoryItem);
            stashDictory.Add(item, newInventoryItem); 
        }
    }
}
