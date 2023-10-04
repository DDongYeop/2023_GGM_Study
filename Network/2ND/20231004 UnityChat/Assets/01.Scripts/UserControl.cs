using System.Collections;
using UnityEngine;

public class UserControl : MonoBehaviour
{
    private bool _isMoving = false;
    private Camera _mainCam;

    private float _currentTime = 0;
    [SerializeField] private float _moveTime;

    [SerializeField] private int _maxHp = 100;
    [SerializeField] private RectTransform _hpField;
    private int _currentHp;
    public int CurrentHp
    {
        get => _currentHp;
        set
        {
            //UI update
            _currentHp = value;
            _hpField.localScale = new Vector3(_currentHp / (float)_maxHp, 1f, 1f);
        }
    }

    private void Awake()
    {
        _mainCam = Camera.main;
        CurrentHp = _maxHp;
        StartCoroutine(HpMinusCo());
    }

    private void Update()
    {
        Movement();
    }

    private void Movement()
    {
        if (Input.GetMouseButtonDown(1) && !_isMoving)
        {
            _isMoving = true;
            Vector3 pos = _mainCam.ScreenToWorldPoint(Input.mousePosition);  
            pos.z = 0;
            StartCoroutine(MovementCo(pos));
        }
    }

    private IEnumerator MovementCo(Vector3 pos)
    {
        _currentTime = 0;
        Vector3 startPos = transform.position;

        while (_currentTime < _moveTime)
        {
            yield return null;
            _currentTime += Time.deltaTime;
            _currentTime = Mathf.Clamp(_currentTime, 0, _moveTime);

            float value = _currentTime / _moveTime;
            transform.position = Vector3.Lerp(startPos, pos, value);
        }

        transform.position = pos;
        _isMoving = false;
    }

    private IEnumerator HpMinusCo()
    {
        while (true)
        {
            yield return new WaitForSeconds(1);
            CurrentHp--;
        }
    }

    public void Revive()
    {
        CurrentHp = _maxHp;
    }
}
