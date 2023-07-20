using UnityEngine;

[CreateAssetMenu]
public class ObjectSO : ScriptableObject
{
    public string monsterName;
    public float monsterAtk;
    public double monsterHP;
    public int monsterMoveSpd;
}

// 클래스는 자료형이다. 
// JSON은 직열화 구조이다 [시리얼라이즈]

/*
 * 데이터 컨테이너
 * -------------
 * 데이터 필드 1 => 필드마다 특정 데이터 저장, 다양한 유형의 데이터 저장
 * 데이터 필드 2
 * 데이터 필드 3
 * --------------
 * 데이터 조작 함수 => 데이터를 CRUD 및 접근 가능 
 */
