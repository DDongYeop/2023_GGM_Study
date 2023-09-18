using System;
using System.Collections;
using System.Collections.Generic;
using System.Net.NetworkInformation;
using UnityEngine;

public class MovePlug : BaseBehavior
{
    public float spdDampTIme = .04f;
    public float spd;

    private void Start()
    {
        behaviourController.SubscribeBehaviour(this);
        behaviourController.RegisterDefaultBehaviour(GetBehaviourCode);
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
        
        behaviourController.GetAnimator.SetFloat("speedFloat", spd, spdDampTIme, Time.deltaTime);
    }

    public override void LocalFixedUpdate()
    {
        SetMove(behaviourController.GetH, behaviourController.GetV);
    }
}
