using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public enum ItemType
{
    Weapon, Armor, Consumable
}

[CreateAssetMenu (menuName = "SO/GameItem", fileName = "GameItem")]
public class GameItemSO : ScriptableObject
{
    public string name;
    public string type;
    public int price;
    public Sprite icon;
}
