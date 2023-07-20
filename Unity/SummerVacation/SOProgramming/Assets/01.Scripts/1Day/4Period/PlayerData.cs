using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[CreateAssetMenu (fileName = "PlayerData")]
public class PlayerData : ScriptableObject
{
    [SerializeField] private string _playerName;
    [SerializeField] private int _level;
    [SerializeField] private int _hp;
    [SerializeField] private int _dmg;

    public string PlayerName
    {
        get { return _playerName; }
        set { _playerName = value; }
    }
    
    public int Level
    {
        get { return _level; }
        set { _level = value; }
    }
    
    public int Hp
    {
        get { return _hp; }
        set { _hp = value; }
    }
    
    public int Dmg
    {
        get { return _dmg; }
        set { _dmg = value; }
    }
}
