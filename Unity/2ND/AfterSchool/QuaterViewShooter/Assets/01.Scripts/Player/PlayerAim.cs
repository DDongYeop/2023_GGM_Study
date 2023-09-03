using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerAim : MonoBehaviour
{
    [Header("참조 변수")] 
    [SerializeField] private InputReader _inputReader;
    [SerializeField] private Transform _visualTrm;
    [SerializeField] private PlayerAnimator _playerAnimator;
    [SerializeField] private PlayerMovement _playerMovement;

    [Header("셋팅 값")] 
    [SerializeField] private LayerMask _whatIsGround;

    private void LateUpdate()
    {
        Vector2 mousePos = _inputReader.AimPostion;

        Ray ray = CameraManager.MainCam.ScreenPointToRay(mousePos);
        if (Physics.Raycast(ray, out var hit, CameraManager.MainCam.farClipPlane, _whatIsGround))
        {
            Vector3 worldPos = hit.point;
            Vector3 dir = (worldPos - transform.position);
            dir.y = 0;
            _visualTrm.rotation = Quaternion.LookRotation(dir);
        }
        
        CalulateRotation();
    }

    private void CalulateRotation()
    {
        Vector3 visualDir = Quaternion.Inverse(_visualTrm.rotation) * _playerMovement.MoveVelocity;
        _playerAnimator.SetAnimationDirection(new Vector2(visualDir.x, visualDir.z).normalized);
    }
}
