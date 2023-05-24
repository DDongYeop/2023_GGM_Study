using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Serialization;

public class ViewAngle : MonoBehaviour
{
    [SerializeField] private bool _bDebugMode = false;
 
    [Header("View Config")] [Range(0f, 360f)] [SerializeField] private float _horizontalViewAngle = 0f;
    [SerializeField] private float _viewRadius = 1f;
    [Range(-180f, 180f)] [SerializeField] private float _viewRotateZ = 0f;
 
    private List<Collider2D> _hitedTargetContainer = new List<Collider2D>();
 
    private float _horizontalViewHalfAngle = 0f;
 
    private void Awake()
    {
        _horizontalViewHalfAngle = _horizontalViewAngle * 0.5f;
    }
    
    private Vector3 AngleToDirZ(float angleInDegree)
    {
        float radian = (angleInDegree - transform.eulerAngles.z) * Mathf.Deg2Rad;
        return new Vector3(Mathf.Sin(radian), Mathf.Cos(radian), 0f);
    }

    private void OnDrawGizmos()
    {
        if (_bDebugMode)
        {
            _horizontalViewHalfAngle = _horizontalViewAngle * 0.5f;
 
            Vector3 originPos = transform.position;
 
            Gizmos.DrawWireSphere(originPos, _viewRadius);
 
            Vector3 horizontalRightDir = AngleToDirZ(-_horizontalViewHalfAngle + _viewRotateZ);
            Vector3 horizontalLeftDir  = AngleToDirZ(_horizontalViewHalfAngle + _viewRotateZ);
            Vector3 lookDir = AngleToDirZ(_viewRotateZ);
 
            Debug.DrawRay(originPos, horizontalLeftDir * _viewRadius, Color.cyan);
            Debug.DrawRay(originPos, lookDir * _viewRadius, Color.green);
            Debug.DrawRay(originPos, horizontalRightDir * _viewRadius, Color.cyan);

            FindViewTargets();
        }
    }
    
    public void FindViewTargets()
    {
        _hitedTargetContainer.Clear();
 
        Vector2      originPos    = transform.position;
        Collider2D[] hitedTargets = Physics2D.OverlapCircleAll(originPos, _viewRadius);
        
        foreach (Collider2D hitedTarget in hitedTargets)
        {
            Vector2 targetPos = hitedTarget.transform.position;
            Vector2 dir = (targetPos - originPos).normalized;
            Vector2 lookDir = AngleToDirZ(_viewRotateZ);
            
            float dot = Vector2.Dot(lookDir, dir);
            float angle = Mathf.Acos(dot) * Mathf.Rad2Deg;
 
            if (angle <= _horizontalViewHalfAngle)
            {
                RaycastHit2D rayHitedTarget = Physics2D.Raycast(originPos, dir, _viewRadius);
                if (rayHitedTarget)
                {
                    if (_bDebugMode)
                        Debug.DrawLine(originPos, rayHitedTarget.point, Color.yellow);
                }
                else
                {
                    _hitedTargetContainer.Add(hitedTarget);
                    if (_bDebugMode)
                        Debug.DrawLine(originPos, targetPos, Color.red);
                }
            }
        }
    }

}
