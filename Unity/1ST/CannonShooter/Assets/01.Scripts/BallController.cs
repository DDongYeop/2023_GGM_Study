using System;
using System.Collections;
using System.Collections.Generic;
using Mono.Cecil;
using Unity.Mathematics;
using UnityEngine;

public enum BallState
{
    IDLE = 0,
    CHARGING =1,
    FIRE =2
}

public class BallController : MonoBehaviour
{
    public Transform BallDirectionTrn;
    public Transform PowerGuageTrm;
    
    [SerializeField] private float _maxPower = 15f, _chargeSpeed = 20f;
    private float _currentPower = 0;

    [SerializeField] private BallState _state = BallState.IDLE;
    private Rigidbody2D _rigidbody;
    private Vector2 _inputDir;
    private Camera _main;
    
    private void Awake()
    {
        _rigidbody = GetComponent<Rigidbody2D>();
        _main = Camera.main;
    }

    private void Update()
    {
        if (_state == BallState.IDLE)
        {
            //_inputDir = new Vector2(Input.GetAxisRaw("Horizontal"), Input.GetAxisRaw("Vertical"));
            _inputDir = (_main.ScreenToWorldPoint(Input.mousePosition) - transform.position).normalized;
                
            // _inpitDir이라는 벡턱를 가지고 각도 구하기
            //float c = Mathf.Sqrt(_inputDir.x * _inputDir.x + _inputDir.y * _inputDir.y);
            float c = _inputDir.magnitude; // 위에꺼랑 똑같음 
            float angle = 0;
            if (c > 0)
                angle = Mathf.Atan2(_inputDir.y, _inputDir.x); //2D게임에선 이거만 쓴다
                
            BallDirectionTrn.rotation = quaternion.Euler(0,0, angle);
            //BallDirectionTrn.rotation = Quaternion.Euler(0,0, angle * Mathf.Rad2Deg);
        }

        if (Input.GetMouseButtonDown(0) && _state == BallState.IDLE)
        {
            _state = BallState.CHARGING;
            TimeController.Instance.SetTimeScale(0.4f);
            CameraManager.Instance.Zoom(4f);
        }
        if (Input.GetMouseButton(0) && _state == BallState.CHARGING)
        {
            _currentPower += _chargeSpeed * Time.unscaledDeltaTime; //Time.Scale 상관 안 하는 얘
            _currentPower = Mathf.Clamp( _currentPower, 0, _maxPower);
            PowerGuageTrm.localScale = new Vector3(_currentPower / _maxPower, 1, 1);
        }
        if (Input.GetMouseButtonUp(0) && _state == BallState.CHARGING)
        {
            TimeController.Instance.SetTimeScale(1f);
            CameraManager.Instance.Zoom(7f);
            //_state = BallState.FIRE;
            Fire();
        }
    }
    
    private void Fire()
    {
        _rigidbody.velocity = Vector2.zero;
        _rigidbody.AddForce(_inputDir.normalized * _currentPower, ForceMode2D.Impulse); // Impulse 야구공 같이 빡 치면 날라감, Force 미는거  
        _currentPower = 0;
        PowerGuageTrm.localScale = new Vector3(0, 1, 1);
        _state = BallState.IDLE; // 나중에 제거
    }

    private void OnCollisionEnter2D(Collision2D col)
    {
        if (_state == BallState.FIRE)
            _state = BallState.IDLE;
    }
}
