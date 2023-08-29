using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Serialization;

public class PlayerMove : MonoBehaviour
{
    private float moveSpeed = 100.0f;
    private Rigidbody playerRigidbody;
    private bool isMoving = false;

    private void Awake()
    {
        playerRigidbody = GetComponent<Rigidbody>();
    }

    private void Update()
    {
        Movement();
    }

    private void Movement()
    {
        float x = Input.GetAxisRaw("Horizontal");
        float y = Input.GetAxisRaw("Vertical");
        Vector3 pos = new Vector3(x, 0, y) * (moveSpeed * Time.deltaTime);
        playerRigidbody.MovePosition(transform.position + pos);

        if (pos == Vector3.zero)
            isMoving = false;
        else
            isMoving = true;
    }

    public bool IsMoving()
    {
        return isMoving;
    }
}
