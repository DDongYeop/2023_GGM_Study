using DG.Tweening;
using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public enum CannonState : short
{
    IDLE = 0,
    MOVING = 1, 
    CHARGING = 2,
    FIRE = 3
}

public class Cannon : MonoBehaviour
{
    [SerializeField]
    private float _rotateSpeed = 90f;
    private float _currentRotation;
    
    private Transform _barrelTrm;

    [SerializeField]
    private CannonBall _ballPrefab;
    private Transform _firePosition;

    [SerializeField]
    private float _chargingSpeed, _maxPower = 90f;
    private float _currentPower = 0;

    [SerializeField] 
    private CannonState _currentState;

    public Action<float, float> OnPowerChanged = null;
    public Action<float> OnAngleChanged = null;

    [SerializeField]
    private float _viewRigSpeed = 8f;
    private Transform _viewRig;

    private void Awake()
    {
        _barrelTrm = transform.Find("CannonBarrel");
        _firePosition = _barrelTrm.Find("FirePosition");
        _currentState = CannonState.IDLE;

        _viewRig = transform.Find("ViewRig");
    }

    private void Start()
    {
        //UI���� �˾�â�� �����ٴ� �̺�Ʈ�� ������ �丮�� ī�޶� ����
        UIManager.Instance.OnCloseMessagePopup += () =>
        {
            Sequence seq = DOTween.Sequence();
            seq.AppendCallback(() =>
            {
                CameraManager.Instance.SetActiveCam(CameraCategory.RigCam);
            });
            seq.AppendInterval(1f);
            seq.AppendCallback(() =>
            {
                _currentState = CannonState.IDLE;
            });
        };
    }

    private void Update()
    {
        if((short)_currentState < 2)
        {
            CheckRotate();
            CheckViewMove();
        }
        
        CheckFire();
    }

    private void CheckViewMove()
    {
        float x = Input.GetAxisRaw("Horizontal");

        _viewRig.Translate(new Vector3(x * _viewRigSpeed * Time.deltaTime, 0, 0), Space.World);
    }

    private void CheckFire()
    {
        //���߻��Ұų�?, ���� �߻��Ҳ���? ������� �߻��Ҳ���?

        if(Input.GetButtonDown("Jump") &&  (short)_currentState < 2 )
        {
            _currentPower = 0;
            _currentState = CannonState.CHARGING;
            _viewRig.transform.position = transform.position; //���� �߻縦 ���� �̸� ���ܵα�
        }

        if(Input.GetButton("Jump") && _currentState == CannonState.CHARGING)
        {
            _currentPower += _chargingSpeed * Time.deltaTime;
            _currentPower = Mathf.Clamp(_currentPower, 0, _maxPower);
            
            OnPowerChanged?.Invoke(_currentPower, _maxPower);
        }

        if(Input.GetButtonUp("Jump") && _currentState == CannonState.CHARGING)
        {
            StartCoroutine(FireSequence());
        }
    }

    private IEnumerator FireSequence()
    {
        _currentState = CannonState.FIRE;
        CameraManager.Instance.SetActiveCam(CameraCategory.CannonCam);
        _viewRig.localPosition = Vector3.zero;

        yield return new WaitForSeconds(1f); //�丮��ķ���� ĳ��ķ���� ���µ� �ɸ��� �ð� 1��

        CannonBall ball = Instantiate(_ballPrefab, _firePosition.position, Quaternion.identity);
        ball.OnCannonBallEnd += CannonBallExlosionHandle; //���� ���� ĳ������ ������.
        ball.Fire(_firePosition.right, _currentPower);

        CameraManager.Instance.SetActiveCam(CameraCategory.BallCam, ball.transform); //��ī�޶� ���󰡰�
    }

    private void CannonBallExlosionHandle()
    {
        UIManager.Instance.ShowMessagePopup("����Ͻ÷��� Space�� �����ּ���");
        
    }

    private void CheckRotate()
    {
        float y = Input.GetAxisRaw("Vertical");
        _currentRotation += y * _rotateSpeed * Time.deltaTime;
        _currentRotation = Mathf.Clamp(_currentRotation, 0, 90f);

        OnAngleChanged?.Invoke(_currentRotation);

        if(Mathf.Abs(y) > 0 )
        {
            _currentState = CannonState.MOVING;
        }else
        {
            _currentState = CannonState.IDLE;
        }

        _barrelTrm.rotation = Quaternion.Euler(0, 0, _currentRotation);
    }
}
 