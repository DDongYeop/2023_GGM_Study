using System;
using System.Collections;
using System.Collections.Generic;
using System.Net.NetworkInformation;
using UnityEngine;
using UnityEngine.UIElements;

public class AimPlug : BaseBehavior
{
    public Texture2D crossHair;
    public float aimTurnSmoothing = .15f;
    public Vector3 aimPivotOffset = new Vector3(.5f, 1.2f, .0f);
    public Vector3 aimCamOffset = new Vector3(.0f, .4f, -.7f);

    private int aimBool;
    private bool aim;
    private int cornerBool;
    private bool peekCorner;
    private Vector3 initialRootRotation;
    private Vector3 initialHipRotation;
    private Vector3 initialSpineRotation;

    private void Start()
    {
        aimBool = Animator.StringToHash(AnimatorVarKey.Aim);
        cornerBool = Animator.StringToHash(AnimatorVarKey.Corner);

        Transform hips = behaviourController.GetAnimator.GetBoneTransform(HumanBodyBones.Hips);

        initialRootRotation = (hips.parent == transform) ? Vector3.zero : hips.parent.localEulerAngles;

        initialHipRotation = hips.localEulerAngles;

        initialSpineRotation = behaviourController.GetAnimator.GetBoneTransform(HumanBodyBones.Spine).localEulerAngles;
    }

    private void Rotating()
    {
        Vector3 forward = behaviourController.playerCamera.TransformDirection(Vector3.forward);
        forward.y = 0;
        forward = forward.normalized;

        Quaternion targetRotation = Quaternion.Euler(0f, behaviourController.GetCamScript.GetHorizontal, .0f);
        float minspeed = Quaternion.Angle(transform.rotation, targetRotation) * aimTurnSmoothing;

        if (peekCorner)
        {
            transform.rotation = Quaternion.LookRotation(-behaviourController.GetLastDirection());
            targetRotation *= Quaternion.Euler(initialRootRotation);
            targetRotation *= Quaternion.Euler(initialHipRotation);
            targetRotation *= Quaternion.Euler(initialSpineRotation);

            Transform spine = behaviourController.GetAnimator.GetBoneTransform(HumanBodyBones.Spine);
            spine.rotation = targetRotation;
        }
        else
        {
            behaviourController.SetLastDirection(forward);
            transform.rotation = Quaternion.Slerp(transform.rotation, targetRotation, minspeed * Time.deltaTime);
        }
    }

    private void AimManagement()
    {
        Rotating();
    }

    private IEnumerator ToggleAimOn()
    {
        yield return new WaitForSeconds(0.05f);
        if (behaviourController.GetTempLockStatus(GetBehaviourCode) || behaviourController.IsOverriding(this))
            yield return false;
        else
        {
            aim = true;
            int signal = 1;

            if (peekCorner)
            {
                signal = (int)Mathf.Sign(behaviourController.GetH);
            }

            aimCamOffset.x = Mathf.Abs(aimCamOffset.x) * signal;
            aimPivotOffset.x = Mathf.Abs(aimPivotOffset.x) * signal;
            yield return new WaitForSeconds(.1f);
            behaviourController.GetAnimator.SetFloat(speedFloat, .0f);
            behaviourController.OverrideWithBehaviour(this);
        }
    }

    private IEnumerator ToggleAimOff()
    {
        aim = false;
        yield return new WaitForSeconds(.3f);
        behaviourController.GetCamScript.ResetTargetOffsets();
        behaviourController.GetCamScript.ResetMaxVerticalAngle();
        yield return new WaitForSeconds(.1f);
        behaviourController.RevokeOverridingBehaviour(this);
    }

    public override void LocalFixedUpdate()
    {
        if (aim)
        {
            behaviourController.GetCamScript.SetTargetOffset(aimPivotOffset, aimCamOffset);
        }
    }

    public override void LocalLateUpdate()
    {
        AimManagement();
    }

    private void OnGUI()
    {
        if (crossHair != null)
        {
            float length = behaviourController.GetCamScript.GetNowPivotMagnitude(aimPivotOffset);
            if (length < .05f)
            {
                GUI.DrawTexture(new Rect(Screen.width * .5f - (crossHair.width * .5f), Screen.height * .5f -(crossHair.height * .5f), crossHair.width, crossHair.height), crossHair);
            }
        }
    }

    private void Update()
    {
        peekCorner = behaviourController.GetAnimator.GetBool(cornerBool);

        if (Input.GetAxisRaw(BtnName.Aim) != 0 && !aim)
        {
            StartCoroutine(ToggleAimOn());
        }
        else if (aim && Input.GetAxisRaw(BtnName.Aim) == 0)
        {
            StartCoroutine(ToggleAimOff());
        }

        //canSprint = !aim;
        if (aim && Input.GetButtonDown(BtnName.Shoulder) && peekCorner)
        {
            aimCamOffset.x = aimCamOffset.x * -1;
            aimPivotOffset.x = aimPivotOffset.x * -1;
        }
        behaviourController.GetAnimator.SetBool(aimBool, aim);
    }
}
