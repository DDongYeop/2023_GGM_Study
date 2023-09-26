using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MovingPlug : BaseBehavior
{
    public float spdDampTime = .5f;
    public float spd;
    public float spdMin = .15f;
    public float spdMax = 1.0f;
    public float sprint = 2.0f;

    public float spdSeeker;

    public float jumpHeight = 1.5f;
    public float JumpForwardForce = 10f;
    private int jumpBool;
    private int groundBool;
    private bool isJumpping;
    private bool isCollid;
    private CapsuleCollider capsuleCollider;

    private void Start()
    {
        capsuleCollider = GetComponent<CapsuleCollider>();
        jumpBool = Animator.StringToHash(AnimatorVarKey.Jump);
        groundBool = Animator.StringToHash(AnimatorVarKey.Grounded);
        
        behaviourController.SubscribeBehaviour(this);
        behaviourController.RegisterDefaultBehaviour(GetBehaviourCode);

        spdSeeker = spdMin;
    }

    private void RemoveVerticalVelocity()
    {
        Vector3 horizontalVelocity = behaviourController.GetRigidbody.velocity;
        horizontalVelocity.y = .0f;
        behaviourController.GetRigidbody.velocity = horizontalVelocity;
    }

    private void SetJump()
    {
        if (isJumpping && !behaviourController.GetAnimator.GetBool(jumpBool) && behaviourController.IsGrounded())
        {
            behaviourController.LockTempBehaviour(GetBehaviourCode);
            behaviourController.GetAnimator.SetBool(jumpBool, true);

            if (behaviourController.GetAnimator.GetFloat(speedFloat) > .1f)
            {
                capsuleCollider.material.dynamicFriction = .0f;
                capsuleCollider.material.staticFriction = .0f;
                
                RemoveVerticalVelocity();

                float velocity = 2.0f * Mathf.Abs(Physics.gravity.y) * jumpHeight;
                velocity = Mathf.Sqrt(velocity);
                
                behaviourController.GetRigidbody.AddForce(Vector3.up * velocity, ForceMode.VelocityChange);
            }
        }
        else if (behaviourController.GetAnimator.GetBool(jumpBool))
        {
            if (!behaviourController.IsGrounded() && !isCollid && behaviourController.GetTempLockStatus())
            {
                behaviourController.GetRigidbody.AddForce(transform.forward * JumpForwardForce * Physics.gravity.magnitude * spdSeeker, ForceMode.Acceleration);
            }

            if (behaviourController.GetRigidbody.velocity.y < .0f && behaviourController.IsGrounded())
            {
                behaviourController.GetAnimator.SetBool(groundBool, true);
                capsuleCollider.material.dynamicFriction = .6f;
                capsuleCollider.material.staticFriction = .6f;
                isJumpping = false;
                behaviourController.GetAnimator.SetBool(jumpBool, false);
                behaviourController.UnLockTempBehaviour(GetBehaviourCode);
            }
        }
    }

    private Vector3 CharacterRotate(float horizontal, float vertical)
    {
        Vector3 dirForward = behaviourController.playerCamera.TransformDirection(Vector3.forward);

        dirForward.y = .0f;
        dirForward = dirForward.normalized;
        Vector3 dirRight = new Vector3(dirForward.z, .0f, -dirForward.x);
        Vector3 dirTarget;
        dirTarget = dirForward * vertical + dirRight * horizontal;

        if (behaviourController.IsMoving() && dirTarget != Vector3.zero)
        {
            Quaternion rotateTargetOri = Quaternion.LookRotation(dirTarget);
            Quaternion rotateTargetNew = Quaternion.Slerp(behaviourController.GetRigidbody.rotation, rotateTargetOri, behaviourController.turnSmoothing);

            behaviourController.GetRigidbody.MoveRotation(rotateTargetNew);
            behaviourController.SetLastDirection(dirTarget);
        }

        if (!(Mathf.Abs(horizontal) > .9f || Mathf.Abs(vertical) > .9f))
            behaviourController.Repositioning();

        return dirTarget;
    }


    private void SetMove(float horizontal, float vertical)
    {
        CharacterRotate(horizontal, vertical);
        Vector2 dir = new Vector2(horizontal, vertical);
        spd = dir.normalized.magnitude;

        spdSeeker += Input.GetAxis("Mouse ScrollWheel");
        spdSeeker = Mathf.Clamp(spdSeeker, spdMin, spdMax);
        spd *= spdSeeker;

        if (behaviourController.IsSprinting())
        {
            spd = sprint;
        }

        behaviourController.GetAnimator.SetFloat(speedFloat, spd, spdDampTime, Time.deltaTime);
    }

    public override void LocalFixedUpdate()
    {
        SetMove(behaviourController.GetH, behaviourController.GetV);
        SetJump();
    }

    private void Update()
    {
        if (!isJumpping && Input.GetButtonDown(BtnName.Jump) && behaviourController.IsCurrentBehaviour(GetBehaviourCode) && !behaviourController.IsOverriding())
            isJumpping = true;
    }
}
