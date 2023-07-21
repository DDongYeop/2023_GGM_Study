using System;
using UnityEngine;

public enum CharacterStack
{
    Int = 0, Hp = 1, Str = 2
}

[Serializable]
public class ItemAbility
{
    public CharacterStack CharacterStack;
    public int valStack;

    [SerializeField] private int _min;
    [SerializeField] private int _max;

    public int Min => _min;
    public int Max => _max;

    public ItemAbility(int min, int max)
    {
        this._min = min;
        this._max = max;
    }

    public void GetStackVal()
    {
        valStack = UnityEngine.Random.Range(_min, _max);
    }

    public void AddStackVal(ref int v)
    {
        v += valStack;
    }
}
