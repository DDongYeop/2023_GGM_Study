using System;
using System.Collections;
using System.Collections.Generic;
using System.Reflection;
using System.Text;
using Unity.VisualScripting;
using UnityEngine;

public enum EquipmentType
{
    Weapon,
    Armor,
    Amulet,
    Flask
}

[CreateAssetMenu(menuName = "SO/Item/Equipment")]
public class ItemDataEquipmentSO : ScriptableObject
{
    public EquipmentType equipmentType;

    [TextArea] public string itemEffectDescription;

    public ItemType itemType;
    public string itemName;
    public Sprite itemIcon;

    protected StringBuilder _stringBuilder = new StringBuilder();

    #region 스텟 선언부

    [Header("Major stat")]
    public int strength; // 1포인트당 데미지 증가, 크증뎀 1%
    public int agility; // 1포인트당 회피 1%, 크리티컬 1%
    public int intelligence; // 1포인트당 마법데미지 1증가, 마법저항 3증가, 도트 데미지에 지능의 10% 증뎀(지능10당 도트뎀 10퍼 증가)
    public int vitality; // 1포인트당 체력 5증가.

    [Header("Defensive stats")]
    public int maxHealth; //체력
    public int armor; //방어도
    public int evasion; //회피도
    public int magicResistance; //마법방어

    [Header("Offensive stats")]
    public int damage;
    public int criticalChance;
    public int criticalDamage;

    [Header("Magic stats")] 
    public int fireDamage;
    public int ignitePercent;
    public int iceDamage;
    public int chillPercent;
    public int thunderDamage;
    public int shockPercent;    

    #endregion

    protected Dictionary<StatType, FieldInfo> _fieldInfoDictionary;

    private void OnEnable()
    {
        _fieldInfoDictionary = new Dictionary<StatType, FieldInfo>();

        Type itemType = typeof(ItemDataEquipmentSO);

        foreach (StatType statType in Enum.GetValues(typeof(StatType)))
        {
            FieldInfo itemStatField = itemType.GetField(statType.ToString());
            
            if (itemStatField == null)
                UnityEngine.Debug.LogError($"There is no stat field in {statType.ToString()}-{name}");
            else
                _fieldInfoDictionary.Add(statType, itemStatField);
        }
    }

    public void AddModifiers()
    {
        PlayerStat playerStat = GameManager.Instance.Player.Stat;
        
        if (playerStat == null)
            return;

        foreach (var pair in _fieldInfoDictionary)
        {
            Stat stat = playerStat.GetStatByType(pair.Key);
            int modifyValue = (int)pair.Value.GetValue(this);
            stat.AddModifier(modifyValue);
        }
    }

    public void RemoveModifiers()
    {
        //모디파이어 제거 
    }
}
