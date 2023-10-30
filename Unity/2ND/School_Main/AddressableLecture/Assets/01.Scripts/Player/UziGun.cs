using UnityEngine;
using UnityEngine.Events;

public class UziGun : MonoBehaviour
{
    [SerializeField] private Transform _firePos;
    
    [SerializeField] private float _shootRange = 10f;
    [SerializeField] private float _cooltime = 0.2f;
   

    public UnityEvent onFire; //발사 
    
    private float _lastFireTime;
    private bool _isFire = false; //발사중인가?
    
    public Vector3 HitPoint { get; private set; }
    
    public void OnFireHandle(bool value)
    {
        _isFire = value;
    }
    
    private void Update()
    {
        //발사가능하면
        bool canFire = _isFire && _lastFireTime + _cooltime < Time.time; 
        if (canFire)
        {
            if(Physics.Raycast(_firePos.position, _firePos.forward, out RaycastHit hitInfo, _shootRange))
            {
                HitPoint = hitInfo.point;
                onFire?.Invoke();

            }
            else
            {
                HitPoint = _firePos.position + _firePos.forward * _shootRange;
                onFire?.Invoke();
            }
            
            _lastFireTime = Time.time;
        }
    }
}