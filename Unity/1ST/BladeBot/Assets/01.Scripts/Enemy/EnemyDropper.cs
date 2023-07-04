using System;
using System.Collections;
using System.Collections.Generic;
using DG.Tweening;
using UnityEditor.Experimental.GraphView;
using UnityEngine;
using UnityEngine.Events;

public class EnemyDropper : MonoBehaviour
{
    [SerializeField] private LayerMask _whatIsGround;
    [SerializeField] private float _maxDistance = 20f;

    public UnityEvent OnDropComplete = null;

    private EnemyController _enemyController;

    private void Awake()
    {
        _enemyController = GetComponent<EnemyController>();
    }

    public void ReadyToDrop(Vector3 pos)
    {
        SetNavInfo(false);
        transform.position = pos;
    }

    private void SetNavInfo(bool value)
    {
        _enemyController.NavMovement.enabled = false;
        _enemyController.NavMovement.NavAgent.updatePosition = value;
        _enemyController.NavMovement.NavAgent.updateRotation = value;
        _enemyController.NavMovement.NavAgent.enabled = value;
    }
    
    public bool Drop()
    {
        Vector3 currentPosition = transform.position;
        RaycastHit hit;
        bool isHit = Physics.Raycast(currentPosition, Vector3.down, out hit, _maxDistance, _whatIsGround);

        if (isHit)
        {
            DropDecal decal = PoolManager.Instance.Pop("GroundDecal") as DropDecal;
            decal.transform.position = hit.point + new Vector3(0, 2f, 0);
            decal.SetUpSize(new Vector3(3, 3, 4));
            
            decal.StartSeq(() => 
            {
                decal.FadeOut(0.3f);
                transform.DOMove(hit.point, 0.5f).SetEase(Ease.InCubic).OnComplete(() =>
                {
                    SetNavInfo(true);
                    OnDropComplete?.Invoke();
                });
            });
            return true;
        }
        else
        {
            return false;
        }
    }

    private void Update()
    {
        if (Input.GetKeyDown(KeyCode.K))
        {
            ReadyToDrop(new Vector3(6, 11, 11));
            Drop();
        }
    }
}
