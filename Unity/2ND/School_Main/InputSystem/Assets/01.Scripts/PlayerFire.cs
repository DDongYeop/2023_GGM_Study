using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerFire : MonoBehaviour
{
    [SerializeField] private Ball _ballPrefab;
    [SerializeField] private Transform _firePos;

    private PlayerInput _inputReader;

    private void Awake()
    {
        _inputReader = GetComponent<PlayerInput>();
        _inputReader.OnFire += FireHandle;
    }

    private void FireHandle()
    {
        Ball ball = Instantiate(_ballPrefab, _firePos.position, Quaternion.identity);
        ball.Fire(_firePos.forward * 20f);
    }
}