using System.Collections;
using System.Collections.Generic;
using UnityEditor;
using UnityEngine;

public enum ItemType : int  
{
    Hair,
    Head,
    Body, 
    Pants,

    Pauldrons,
    LeftWeapon,
    RightWeapon,
    Food
}
 
[CreateAssetMenu(fileName ="New Item", menuName = "Inventory System/Items/New Item")]
public class ItemObj : ScriptableObject
{ 
    public ItemType itemType; 
    public bool getFlagStackable;
     
    public Sprite itemIcon; 
    public GameObject objModelPrefab;
     
    public Item itemData = new Item();
     
    public List<string> boneNameLists = new List<string>();
     
    [TextArea(15, 20)]
    public string itemSummery;
     
    private void OnValidate()
    {
        boneNameLists.Clear();
        if (objModelPrefab == null || objModelPrefab.GetComponentInChildren<SkinnedMeshRenderer>() == null)
        {
            return;
        }
        SkinnedMeshRenderer renderer = objModelPrefab.GetComponentInChildren<SkinnedMeshRenderer>();
        var bones = renderer.bones;
        foreach (var t in bones)
        { 
            boneNameLists.Add(t.name);
        }
    }
     
    public Item createItemObj()
    { 
        Item new_Item = new Item(this);
        return new_Item;
    } 
} 