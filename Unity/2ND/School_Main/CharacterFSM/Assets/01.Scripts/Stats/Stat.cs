using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

//모든 스텟 int, 확률 100
[Serializable]
public class Stat
{
    [SerializeField] private int _baseValue;

    public List<int> modifiers;

    public int GetValue()
    {
        int finalValue = _baseValue;
        for (int i = 0; i < modifiers.Count; ++i)
            finalValue += modifiers[i];
        return finalValue;
    }

    public void AddModifier(int value)
    {
        if (value != 0)
            modifiers.Add(value);
    }

    public void RemoveModifier(int value)
    {
        if (value != 0)
            modifiers.Remove(value);
    }

    public void SetDefaultValue(int value)
    {
        _baseValue = value;
    }

    public void AddDefaultValue(int value)
    {
        _baseValue += value;
    }
}
