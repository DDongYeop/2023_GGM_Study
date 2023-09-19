using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerController : MonoBehaviour
{
    public Animator animator;
    public Transform targetTransform;

    private void Update()
    {
        if (Input.GetButtonDown("Jump"))
        {
            animator.SetBool("Jump", true);
        }
        else
        {
            animator.SetBool("Jump", false);
        }
    }

    private void OnAnimatorIK(int layerIndex)
    {
        animator.SetIKPositionWeight(AvatarIKGoal.LeftHand, 1.0f);
        animator.SetIKRotationWeight(AvatarIKGoal.LeftHand, 1.0f);
        
        animator.SetIKPosition(AvatarIKGoal.LeftHand, targetTransform.position);
        animator.SetIKRotation(AvatarIKGoal.LeftHand, targetTransform.rotation);

        animator.SetLookAtWeight(1.0f);
        animator.SetLookAtPosition(targetTransform.position);
    }
}
