using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using UnityEngine;

public class Inventory : MonoSingleton<Inventory>
{
    public List<InventoryItem> stash; //???????
    public Dictionary<ItemDataSO, InventoryItem> stashDictionary;

    public List<InventoryItem> inven; //??? ???
    public Dictionary<ItemDataSO, InventoryItem> invenDictionary;

    public List<InventoryItem> equipments;
    public Dictionary<ItemDataEquipmentSO, InventoryItem> equipmentDictionary;

    [Header("Inventory UI")]
    [SerializeField] private Transform _stashSlotParent;
    [SerializeField] private Transform _invenSlotParent;
    [SerializeField] private Transform _equipmentSLotParent;

    private ItemSlotUI[] _stashItemSlots;
    private ItemSlotUI[] _invenItemSlots;
    private EquipmentSlotUI[] _equipmentSlots;


    private void Awake()
    {
        stash = new List<InventoryItem>();
        stashDictionary = new Dictionary<ItemDataSO, InventoryItem>();
        _stashItemSlots = _stashSlotParent.GetComponentsInChildren<ItemSlotUI>();

        inven = new List<InventoryItem>();
        invenDictionary = new Dictionary<ItemDataSO, InventoryItem>();
        _invenItemSlots = _invenSlotParent.GetComponentsInChildren<ItemSlotUI>();

        equipments = new List<InventoryItem>();
        equipmentDictionary = new Dictionary<ItemDataEquipmentSO, InventoryItem>();
        _equipmentSlots = _equipmentSLotParent.GetComponentsInChildren<EquipmentSlotUI>();
    }

    private void Start()
    {
        UpdateSlotUI();
    }

    public void UpdateSlotUI()
    {
        #region equipment window cleanup

        for (int i = 0; i < _equipmentSlots.Length; ++i)
        {
            EquipmentSlotUI currentSlot = _equipmentSlots[i];
            //해당슬록에 장착할 장비를 내가 List에 넣어 뒀는지
            ItemDataEquipmentSO slotEquipment = equipmentDictionary.Keys.ToList().Find(x => x.equipmentType == currentSlot.slotType);

            if (slotEquipment != null)
            {
                currentSlot.UpdateSlot(equipmentDictionary[slotEquipment]);
            }
            else
            {
                currentSlot.CleanUpSlot();
            }
        }

        #endregion
        
        #region clean up slots
        
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
        if(item.itemType == ItemType.Equipment)
        {
            AddToInventory(item);
        }else if(item.itemType == ItemType.Material)
        {
            AddToStash(item);
        }

        UpdateSlotUI();
    }

    
    public void RemoveItem(ItemDataSO item, int count = 1)
    {
        //??????? ??? item?? ????????? ?????? 
        if(stashDictionary.TryGetValue(item, out InventoryItem stashItem))
        {
            if(stashItem.stackSize <= count)
            {
                stash.Remove(stashItem);
                stashDictionary.Remove(item);
            }
            else
            {
                stashItem.RemoveStack(count);
            }
        }
        else if(invenDictionary.TryGetValue(item, out InventoryItem inventoryItem))
        {
            if(inventoryItem.stackSize <= count)
            {
                inven.Remove(inventoryItem);
                invenDictionary.Remove(item);
            }
            else
            {
                inventoryItem.RemoveStack(count);
            }
        }

        UpdateSlotUI(); 
    }

    private void AddToInventory(ItemDataSO item)
    {
        //??? ??? ???????? ?κ????? ???? ????? ?ø??? ????? ???? ???? ??????
        if (invenDictionary.TryGetValue(item, out InventoryItem inventoryItem))
        {
            inventoryItem.AddStack(); //???? ??? ????
        }
        else
        {
            InventoryItem newInventoryItem = new InventoryItem(item);
            inven.Add(newInventoryItem);
            invenDictionary.Add(item, newInventoryItem);
        }
    }


    private void AddToStash(ItemDataSO item)
    {
        //??? ??? ???????? ?κ????? ???? ????? ?ø??? ????? ???? ???? ??????
        if(stashDictionary.TryGetValue(item, out InventoryItem inventoryItem))
        {
            inventoryItem.AddStack(); //???? ??? ????
        }
        else
        {
            InventoryItem newInventoryItem = new InventoryItem(item);
            stash.Add(newInventoryItem);
            stashDictionary.Add(item, newInventoryItem);
        }
    }

    public void EquipItem(ItemDataSO item)
    {
        ItemDataEquipmentSO newEquipItem = item as ItemDataEquipmentSO;

        if (newEquipItem == null)
        {
            Debug.Log("can not equip!");
            return;
        }

        InventoryItem newItem = new InventoryItem(newEquipItem);
        
        ItemDataEquipmentSO oldEquipment = GetEquipmentByType(newEquipItem.equipmentType);

        if (oldEquipment != null)
            UnEquipItem(oldEquipment);
        
        equipments.Add(newItem);
        equipmentDictionary.Add(newEquipItem, newItem);
        newEquipItem.AddModifiers();
        
        RemoveItem(item);
        UpdateSlotUI();
    }

    public ItemDataEquipmentSO GetEquipmentByType(EquipmentType type)
    {
        ItemDataEquipmentSO equipItem = null;

        foreach (var pair in equipmentDictionary)
        {
            if (pair.Key.equipmentType == type)
            {
                equipItem = pair.Key;
                break;
            }
        }
        
        return equipItem;
    }

    public void UnEquipItem(ItemDataEquipmentSO oldEquipment)
    {
        //널체크
        if (oldEquipment == null) return;

        //equiDic에서 존재 확인
        if (equipmentDictionary.TryGetValue(oldEquipment, out InventoryItem invenItem))
        {
            //존재하면 equipment에서 작세, 딕셔너리 삭제
            equipments.Remove(invenItem);
            equipmentDictionary.Remove(oldEquipment);
            
            //removemodifiers
            oldEquipment.RemoveModifiers();
            
            //additem 
            AddItem(oldEquipment);
        }
    }
}
