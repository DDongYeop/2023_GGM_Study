using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Bullet : MonoBehaviour
{
    private Rigidbody _rigidbody;

    private void Awake()
    {
        _rigidbody = GetComponent<Rigidbody>();
    }

    public void Fire(Vector3 dir)
    {
        _rigidbody.AddForce(dir, ForceMode.Impulse);
        Destroy(gameObject, 2f);
    }
}
