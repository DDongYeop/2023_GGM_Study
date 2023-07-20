using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerManager : MonoBehaviour
{
    public PlayerData _playerData;

    private void Start()
    {
        _playerData = Resources.Load<PlayerData>("PlayerData");
        Debug.Log($"플레이어 이름 { _playerData.PlayerName }");

        _playerData.name = "Lee";
    }
}
