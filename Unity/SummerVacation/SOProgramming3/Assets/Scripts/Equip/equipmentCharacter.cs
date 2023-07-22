using System;
using System.Data;
using Unity.VisualScripting;
using UnityEngine;
 
public class equipmentCharacter : MonoBehaviour
{ 
    public InventoryObj inventoryObj; 
    private equipItemMerge equipMergeitem; 
    private boneItemManager[] boneItemManagers = new boneItemManager[4];
     
    public ItemObj[] defaultItemObjs = new ItemObj[4];
     
    void Awake()
    { 
        equipMergeitem = new equipItemMerge(gameObject);

        for (int i = 0; i < inventoryObj.invenSlots.Length; ++i)
        {
            inventoryObj.invenSlots[i].OnPreUpload  += OnUnEquipItem;
            inventoryObj.invenSlots[i].OnPostUpload += OnEquipItem;
        }
    }


    private void Start()
    { 
        foreach ( InvenSlot slot in inventoryObj.invenSlots)
        {
            OnEquipItem(slot);
        }
    }
     
    private void OnEquipItem(InvenSlot slot)
    { 
        ItemObj itemObj = slot.ItemObject;
        if (itemObj == null)
        { 
            equipItemDefault(slot.itemTypes[0]);
            return;
        }
         
        int rowBoneItem = (int)slot.itemTypes[0];
         
        switch (slot.itemTypes[0])
        {
            case ItemType.Hair:
            case ItemType.Head:
            case ItemType.Body:
            case ItemType.Pants:
                boneItemManagers[rowBoneItem] = equipItemSkinned(itemObj);
                break;

            case ItemType.Pauldrons:
            case ItemType.LeftWeapon:
            case ItemType.RightWeapon:
                boneItemManagers[rowBoneItem] = equipItemMesh(itemObj);
                break;
        }
         
    }
     
    private boneItemManager equipItemSkinned(ItemObj itemObj)
    { 
        if (itemObj == null)
        {
            return null;
        }
         
        Transform itemInfo = equipMergeitem.setBoneItem(itemObj.objModelPrefab, itemObj.boneNameLists);
 
        boneItemManager boneItem = itemInfo.gameObject.AddComponent<boneItemManager>();
        if (boneItem != null)
        {
            boneItem.itemLists.Add(itemInfo);
        }

        return boneItem;
    }
     
    private boneItemManager equipItemMesh(ItemObj itemObj)
    { 
        if (itemObj == null)
        {
            return null;
        } 
        Transform[] itemInfos = equipMergeitem.setMeshItem(itemObj.objModelPrefab); 
        if (itemInfos.Length > 0)
        {   
            boneItemManager boneItem = new GameObject().AddComponent<boneItemManager>();
            foreach (Transform t in itemInfos)
            {
                boneItem.itemLists.Add(t);
            }

            boneItem.transform.parent = transform;

            return boneItem;
        }

        return null;
    }

    private void OnUnEquipItem(InvenSlot invenSlot)
    { 
        ItemObj itemObj = invenSlot.ItemObject; 
        if (itemObj == null)
        { 
            destroyItem(invenSlot.itemTypes[0]);
            return;
        }
         
        if (invenSlot.ItemObject.objModelPrefab != null)
        { 
            destroyItem(invenSlot.itemTypes[0]);
        }
    }
     
    private void destroyItem(ItemType type)
    {
        int itemRow = (int)type; 
        if (boneItemManagers[itemRow] != null)
        {
            Destroy(boneItemManagers[itemRow].gameObject);
            boneItemManagers[itemRow] = null;
        }
    }
     
    private void equipItemDefault(ItemType type)
    {
        int itemRow = (int)type;

        ItemObj itemObject = defaultItemObjs[itemRow];
        switch (type)
        {
            case ItemType.Hair:
            case ItemType.Head:
            case ItemType.Body:
            case ItemType.Pants: 
                boneItemManagers[itemRow] = equipItemSkinned(itemObject);
                break;

            case ItemType.Pauldrons:
            case ItemType.LeftWeapon:
            case ItemType.RightWeapon:
                boneItemManagers[itemRow] = equipItemMesh(itemObject);
                break;
        }
    }
      
} 