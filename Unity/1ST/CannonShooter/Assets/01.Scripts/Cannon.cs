using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Cannon : MonoBehaviour
{
    [SerializeField] private float _rotateSpeed = 90f;
    [SerializeField] private float _currentRotation;
    private Transform _barrelTrm;

    private void Awake()
    {
        _barrelTrm = transform.Find("CannonBarrel");
    }

    private void Update()
    {
        CheckRotate();
    }

    private void CheckRotate()
    {
        float y = Input.GetAxisRaw("Vertical");
        _currentRotation += y * _rotateSpeed * Time.deltaTime;
        _currentRotation = Mathf.Clamp(_currentRotation, 0, 90f);
        _barrelTrm.rotation = Quaternion.Euler(0, 0, _currentRotation);
    }
}
