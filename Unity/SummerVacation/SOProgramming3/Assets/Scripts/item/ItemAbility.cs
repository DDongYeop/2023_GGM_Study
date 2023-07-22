using System;
using System.Collections;
using System.Collections.Generic; 
using UnityEngine;
 
public enum CharacterStack
{ 
    Int, Hp, Str
}
 
[Serializable]  
public class ItemAbility 
{ 
    public CharacterStack characterStack; 
    public int valStack;
     
    [SerializeField]
    private int min;

    [SerializeField]
    private int max;
      
    public int Min => min;
    public int Max => max;
     
    public ItemAbility(int min, int max)
    { 
        this.min = min;
        this.max = max; 
        getStackVal();
    }
     
    public void getStackVal()
    { 
        valStack = UnityEngine.Random.Range(min, max);
    }
     
    public void addStackVal(ref int v)
    {
        v += valStack;
    } 
} 
