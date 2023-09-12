using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Serialization;

[RequireComponent(typeof(Camera))]
public class ShoulderViewCamera : MonoBehaviour
{
    public Vector3 pivotOffset = new Vector3(0, 1, 0);
    public Vector3 directOffset = new Vector3(.4f, .5f, -2);

    public float smooth = 10f;
    public float horizontalAimingSpd = 6f;
    public float verticalAimingSpd = 6f;
    
    public float verticalAngleMax = 30f;
    public float verticalAngleMin = -60f;
    public float recoilAngleBounce = 5f;
    
    private float horizontalAngle = 0f;
    public float GetHorizontal => horizontalAngle;
    private float verticalAngle = 0f;
    public float GetVertical => verticalAngle;

    public Transform playerTransform;
    private Transform cameraTransform;
    private Camera myCamera;

    private Vector3 realCameraPosition;
    private float realCameraPositionMag;

    private Vector3 smoothPivotOffset;
    private Vector3 smoothCameraOffset;

    private Vector3 targetPivotOffset;
    private Vector3 targetDirectOffset;

    private float defaultFOV;
    private float targetFOV;

    private float targetMaxVerticleAngle;
    private float recoilAngle = 0f;

    private void Awake()
    {
        cameraTransform = transform;
        myCamera = cameraTransform.GetComponent<Camera>();
        cameraTransform.position = playerTransform.position + Quaternion.identity * pivotOffset + Quaternion.identity * directOffset;
        cameraTransform.rotation = Quaternion.identity;

        realCameraPosition = cameraTransform.position - playerTransform.position;
        realCameraPositionMag = realCameraPosition.magnitude - .5f;

        smoothPivotOffset = pivotOffset;
        smoothCameraOffset = directOffset;
        defaultFOV = myCamera.fieldOfView;
        horizontalAngle = playerTransform.eulerAngles.y;
        
        ResetTargetOffsets();
        ResetFOV();
        ResetMaxVerticalAngle();
    }

    public void ResetTargetOffsets()
    {
        targetPivotOffset = pivotOffset;
        targetDirectOffset = directOffset;
    }

    public void ResetFOV()
    {
        targetFOV = defaultFOV;
    }

    public void ResetMaxVerticalAngle()
    {
        targetMaxVerticleAngle = verticalAngle;
    }

    public void BounceVertical(float degree)
    {
        recoilAngle = degree;
    }

    public void SetTargetOffset(Vector3 newPivotOffset, Vector3 newDirectOffset)
    {
        targetPivotOffset = newPivotOffset;
        targetDirectOffset = newDirectOffset;
    }

    public void SetFOV(float customFOV)
    {
        targetFOV = customFOV;
    }

    private bool ViewingPosCK(Vector3 ckPosition, float deltaPlayerHeight)
    {
        Vector3 target = playerTransform.position + (Vector3.up * deltaPlayerHeight);

        if (Physics.SphereCast(ckPosition, .2f, target - ckPosition, out var hit, realCameraPositionMag))
        {
            if (hit.transform != playerTransform && !hit.transform.GetComponent<Collider>().isTrigger)
                return false;
        }
        return true;
    }

    private bool ReverseViewingPosCk(Vector3 ckPosition, float deltaPlayerHeight, float maxDistance)
    {
        Vector3 origin = playerTransform.position + (Vector3.up * deltaPlayerHeight);

        if (Physics.SphereCast(origin, .2f, ckPosition - origin, out var hit, maxDistance))
        {
            if (hit.transform != playerTransform &&
                hit.transform != transform != !hit.transform.GetComponent<Collider>().isTrigger)
                return false;
        }
        return true;
    }

    private bool DoubleViewingPosCk(Vector3 ckPosition, float offset)
    {
        float playerFocusHeight = playerTransform.GetComponent<CapsuleCollider>().height * .75f;
        return ViewingPosCK(ckPosition, playerFocusHeight) && ReverseViewingPosCk(ckPosition, playerFocusHeight, offset);
    }

    private void Update()
    {
        float mouseX = Mathf.Clamp(Input.GetAxis("Mouse X"), -1f, 1f);
        horizontalAngle += mouseX * horizontalAimingSpd;
        
        float mouseY = Mathf.Clamp(Input.GetAxis("Mouse Y"), -1f, 1f);
        verticalAngle += mouseY * verticalAimingSpd;

        verticalAngle = Mathf.Clamp(verticalAngle, verticalAngleMin, targetMaxVerticleAngle);
        verticalAngle = Mathf.LerpAngle(verticalAngle, verticalAngle + recoilAngle, 10f * Time.deltaTime);
        
        Quaternion camYRotation = Quaternion.Euler(0, horizontalAngle, 0);
        Quaternion aimRotation = Quaternion.Euler(-verticalAngle, horizontalAngle, 0);

        cameraTransform.rotation = aimRotation;
        myCamera.fieldOfView = Mathf.Lerp(myCamera.fieldOfView, targetFOV, Time.deltaTime);

        Vector3 baseTempPosition = playerTransform.position + camYRotation * targetPivotOffset;
        Vector3 noCollisionOffset = targetDirectOffset;

        for (float zOffset = targetDirectOffset.z; zOffset <= 0; zOffset += .5f)
        {
            noCollisionOffset.z = zOffset;
            Vector3 vecCkPos = baseTempPosition + aimRotation * noCollisionOffset;
            
            if (DoubleViewingPosCk(vecCkPos, Mathf.Abs(zOffset)) || zOffset == 0f)
                break;
        }

        smoothPivotOffset = Vector3.Lerp(smoothPivotOffset, targetPivotOffset, smooth * Time.deltaTime);
        smoothCameraOffset = Vector3.Lerp(smoothCameraOffset, noCollisionOffset, smooth * Time.deltaTime);

        cameraTransform.position = playerTransform.position + camYRotation * smoothPivotOffset + aimRotation * smoothCameraOffset;

        if (recoilAngle > 0f)
            recoilAngle -= recoilAngleBounce * Time.deltaTime;
        else if (recoilAngle < 0f)
            recoilAngle += recoilAngleBounce * Time.deltaTime;
    }

    public float GetNowPivotMagnitude(Vector3 finalPivotOffset)
    {
        return Mathf.Abs((finalPivotOffset - smoothPivotOffset).magnitude);
    }
}
