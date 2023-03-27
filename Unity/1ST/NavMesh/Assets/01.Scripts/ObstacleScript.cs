using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ObstacleScript : MonoBehaviour
{
    [SerializeField] private float _speed, _time;
    private float _direction = 1;
    private float _lateTime = 1;
    private bool isMove = false;

    private void Awake()
    {
        StartCoroutine(ObstacleMove());
    }

    private void Update()
    {   
        if (isMove)
            transform.Translate(new Vector3(_speed * Time.deltaTime * _direction, 0, 0));
    }

    private IEnumerator ObstacleMove()
    {
        while (true)
        {
            isMove = true;
            yield return new WaitForSeconds(_time);
            _direction *= -1;
            isMove = false;
            yield return new WaitForSeconds(_lateTime);
            
        }
    }
}
