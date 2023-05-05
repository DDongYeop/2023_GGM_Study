using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CannonBall : MonoBehaviour
{
    private Rigidbody2D _rigidbody2D;

    private void Awake()
    {
        _rigidbody2D = GetComponent<Rigidbody2D>();
    }

    public void Fire(Vector2 dir, float power)
    {
        _rigidbody2D.AddForce(dir * power, ForceMode2D.Impulse);
    }
}
