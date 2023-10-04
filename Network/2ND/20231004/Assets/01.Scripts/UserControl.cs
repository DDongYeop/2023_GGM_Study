using System.Collections;
using UnityEngine;

public class UserControl : MonoBehaviour
{
    private bool _isMoving = false;
    private Camera _mainCam;

    private float _currentTime = 0;
    [SerializeField] private float _moveTime;

    private void Awake()
    {
        _mainCam = Camera.main;
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
}
