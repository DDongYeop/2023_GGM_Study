using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[CreateAssetMenu (fileName = "DBContainer", menuName = "Game/Player DB")]
public class DataContainer : ScriptableObject // 클래스 == 데이터 컨테이너 // 클래스와 SO차이는 MonoBehaviour 상속 받냐 안 받냐 
{
    // 데이터 필드
    [SerializeField] private string _playerName;
    
    public string PlayerName => _playerName;
    [SerializeField] private int playerLv;
    [SerializeField] private float playerHealth;

    // 데이터 조작 함수 
    public void SetPlayerName(string name) //접근제한자 반환타입 함수이름
    {
        _playerName = name;
    }
}
