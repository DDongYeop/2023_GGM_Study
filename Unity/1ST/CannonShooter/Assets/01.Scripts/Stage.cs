using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Stage : MonoBehaviour
{
    [SerializeField] private int _ballCount = 4;
    public int BallCount => _ballCount;

    private int _boxCount;
    public int BoxCount => _boxCount;
    
    public Vector3 StartPos => _startTrm.position;
    public Vector3 EndPos => _endTrm.position;
    public Vector3 PlayerPosition => _playerPositionTrm.position;

    private Transform _startTrm;
    private Transform _endTrm;
    private Transform _playerPositionTrm;

    private void Awake()
    {
        _startTrm = transform.Find("BoundTrm/StartTrm");
        _endTrm = transform.Find("BoundTrm/EndTrm");
        _playerPositionTrm = transform.Find("PlayerStartTrm");

        _boxCount = transform.Find("Crates").childCount; //전체 박스의 개수
    }
}
