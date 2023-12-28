using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using Unity.VisualScripting;
using UnityEngine;

public class Inventory : MonoSingleton<Inventory>, ISaveManager
{
    [SerializeField] private ItemDatabaseSO _itemDB;
    public List<InventoryItem> stash; //잡템창고
    public Dictionary<ItemDataSO, InventoryItem> stashDictionary;

    public List<InventoryItem> inven; //장비 창고
    public Dictionary<ItemDataSO, InventoryItem> invenDictionary;

    public List<InventoryItem> equipments;
    public Dictionary<ItemDataEquipmentSO, InventoryItem> equipmentDictionary;


    [Header("Inventory UI")]
    [SerializeField] private Transform _stashSlotParent;
    [SerializeField] private Transform _invenSlotParent;
    [SerializeField] private Transform _equipmentSlotParent;

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
        _equipmentSlots = _equipmentSlotParent.GetComponentsInChildren<EquipmentSlotUI>();
    }

    private void Start()
    {
        UpdateSlotUI();
    }

    public void UpdateSlotUI()
    {
        #region equipment window cleanup
        for(int i = 0; i < _equipmentSlots.Length; ++i)
        {
            EquipmentSlotUI currentSlot = _equipmentSlots[i];
            //해당 슬롯에 장착할 장비를 내가 List에 보유하고 있는지를 찾는건데
            ItemDataEquipmentSO slotEquipment = equipmentDictionary.Keys.ToList().Find(
                                            x => x.equipmentType == currentSlot.slotType);
            if(slotEquipment != null)
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
        //장비창고에 해당 item이 존재하는지 검사해서 
        if (invenDictionary.TryGetValue(item, out InventoryItem inventoryItem))
        {
            if (inventoryItem.stackSize <= count)
            {
                inven.Remove(inventoryItem);
                invenDictionary.Remove(item);
            }
            else
            {
                inventoryItem.RemoveStack(count);
            }
        }
        
        if (stashDictionary.TryGetValue(item, out InventoryItem stashItem))
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

        UpdateSlotUI(); 
    }

    private void AddToInventory(ItemDataSO item)
    {
        //이미 해당 아이템이 인벤토리상에 있다면 수치를 올리고 그렇지 않다면 새로 등록하고
        if (invenDictionary.TryGetValue(item, out InventoryItem inventoryItem))
        {
            inventoryItem.AddStack(); //스택 하나 증가
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
        //이미 해당 아이템이 인벤토리상에 있다면 수치를 올리고 그렇지 않다면 새로 등록하고
        if(stashDictionary.TryGetValue(item, out InventoryItem inventoryItem))
        {
            inventoryItem.AddStack(); //스택 하나 증가
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

        if(newEquipItem == null)
        {
            Debug.Log("can not equip!");
            return;
        }

        InventoryItem newItem = new InventoryItem(newEquipItem);

        //해당 칸에 다른장비가 장착되어 있는지를 체크해야하고 
        ItemDataEquipmentSO oldEquipment = GetEquipmentByType(newEquipItem.equipmentType);
        //여기다가 그 로직 작성하고

        if(oldEquipment != null)
        {
            UnEquipItem(oldEquipment);
        }

        equipments.Add(newItem);
        equipmentDictionary.Add(newEquipItem, newItem);
        newEquipItem.AddModifiers(); //해당 장비의 능력치를 플레이어 스텟에 반영

        RemoveItem(item);
        UpdateSlotUI();
    }

    public ItemDataEquipmentSO GetEquipmentByType(EquipmentType type)
    {
        ItemDataEquipmentSO equipItem = null;

        foreach(var pair in equipmentDictionary)
        {
            if(pair.Key.equipmentType == type)
            {
                equipItem = pair.Key;
                break;
            }
        }

        return equipItem;
    }

    public void UnEquipItem(ItemDataEquipmentSO oldEquipment)
    {
        if (oldEquipment == null) return;
        // equipmentDictionary에서 그녀석이 존재하는지 체크하고
        if(equipmentDictionary.TryGetValue(oldEquipment, out InventoryItem invenItem))
        {
            equipments.Remove(invenItem);
            equipmentDictionary.Remove(oldEquipment);
            oldEquipment.RemoveModifiers();

            AddItem(oldEquipment);
        }
    }

    public void LoadData(GameData data)
    {
        List<ItemDataSO> itemDB = _itemDB.itemList;

        foreach (var pair in data.inventory)
        {
            ItemDataSO item = itemDB.Find(x => x.itemID == pair.Key);
            if (item != null)
            {
                for (int i = 0; i < pair.Value; i++)
                    AddItem(item);
            }
        }
    }

    public void SaveData(ref GameData data)
    {
        data.inventory.Clear();
        foreach (var pair in stashDictionary)
        {
            data.inventory.Add(pair.Key.itemID, pair.Value.stackSize);
        }
        foreach (var pair in invenDictionary)
        {
            data.inventory.Add(pair.Key.itemID, pair.Value.stackSize);
        }
    }
}
