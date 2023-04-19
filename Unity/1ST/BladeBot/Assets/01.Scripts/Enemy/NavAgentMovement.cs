using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AI;

public class NavAgentMovement : MonoBehaviour
{
    [SerializeField] private float _knockBackSpeed = 20f, _gravity = -9.8f, _knockBackTime = 0.4f;
    private float _verticalVelocity;
    private Vector3 _knockBackVelocity;
    private Vector3 _movementVelocity;
    
    private NavMeshAgent _navAgent;
    public NavMeshAgent NavAgent => _navAgent;

    private CharacterController _characterController;
    private bool _isControllerMode = false;
    private float _knockBackStartTime;
    private Action EndKnockBackAction;

    private AIActionData _aiActionData;
    
    private void Awake()
    {
        _navAgent = GetComponent<NavMeshAgent>();
        _characterController = GetComponent<CharacterController>();
        _aiActionData = transform.Find("AI").GetComponent<AIActionData>();
    }

    public void SetSpeed(float speed)
    {
        _navAgent.speed = speed; //이동 속소 SO에 맞춰 실행
    }

    public void MoveToTarget(Vector3 pos)
    {
        _navAgent.SetDestination(pos);
    }

    public bool CheckIsArrived()
    {
        if (_navAgent.pathPending == false && _navAgent.remainingDistance <= _navAgent.stoppingDistance)
            return true;
        return false;
    }

    public void StopImmediately()
    {
        _navAgent.SetDestination(transform.position); //자기자신을 목적지로 놓으면 바로 정지
    }

    public void StopNavigation()
    {
        _navAgent.isStopped = true; //네브 에이전트 멈춰주고
    }

    public void KnockBack(Action EndAction = null)
    {
        //_navAgent.updatePosition = false;
        //_navAgent.updateRotation = false;
        
        _navAgent.enabled = false;
        _knockBackStartTime = Time.time; //넉백 시작 시간을 측정
        _isControllerMode = true;
        _knockBackVelocity = _aiActionData.HitNormal * -1 * _knockBackSpeed;

        EndKnockBackAction = EndAction;
    }

    private bool CalculateKnockBackMovement()
    {
        float spendTime = Time.time - _knockBackStartTime;
        float ratio = spendTime / _knockBackTime;
        _movementVelocity = Vector3.Lerp(_knockBackVelocity, Vector3.zero, ratio) * Time.fixedDeltaTime;

        return ratio < 1;
    }

    private void FixedUpdate()
    {
        if (_isControllerMode == false)
            return;
        ;
        if (_characterController.isGrounded == false)
        {
            _verticalVelocity = _gravity * Time.fixedDeltaTime;
        }
        else
        {
            _verticalVelocity = _gravity * 0.3f * Time.fixedDeltaTime;
        }

        if (CalculateKnockBackMovement())
        {
            Vector3 move = _movementVelocity + _verticalVelocity * Vector3.up;
            _characterController.Move(move);
        }
        else
        {
            _isControllerMode = false; //콘트롤러 모드 꺼주고
            _characterController.enabled = false;
            EndKnockBackAction?.Invoke();
        }
    }
}
