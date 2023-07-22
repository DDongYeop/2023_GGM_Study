using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
 
[Serializable]
public class Item
{ 
    public int item_id = -1; 
    public string item_name;
 
    public Item()
    {
        item_id = -1;
        item_name = "";
    }
     
    public ItemAbility[] ability;
     
    public Item(ItemObj itemObj)
    {
        item_name = itemObj.name;
        item_id = itemObj.itemData.item_id;
         
        ability = new ItemAbility[itemObj.itemData.ability.Length];
         
        for (int i = 0; i < ability.Length; i++)
        { 
            ability[i] = new ItemAbility(itemObj.itemData.ability[i].Min, itemObj.itemData.ability[i].Max)
            { 
                characterStack = itemObj.itemData.ability[i].characterStack
            };
        }
    }
} 