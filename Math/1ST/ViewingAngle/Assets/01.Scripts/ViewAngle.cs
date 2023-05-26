using UnityEngine;

public class ViewAngle : MonoBehaviour
{
    [Header("View Config")] 
    [SerializeField] private float _viewRadius = 1f;
    [Range(0f, 360f)] [SerializeField] private float _horizontalViewAngle = 0f;
    [Range(-180f, 180f)] [SerializeField] private float _viewRotateZ = 0f;
    private float _horizontalViewHalfAngle = 0f;

    private SpriteRenderer _spriteRenderer;
    
    private void Awake()
    {
        _horizontalViewHalfAngle = _horizontalViewAngle * 0.5f;
        _spriteRenderer = GetComponent<SpriteRenderer>();
    }
    
    private Vector3 AngleToDirZ(float angleInDegree)
    {
        float radian = (angleInDegree - transform.eulerAngles.z) * Mathf.Deg2Rad;
        return new Vector3(Mathf.Sin(radian), Mathf.Cos(radian), 0f);
    }

    private void OnDrawGizmos()
    {
        Vector3 originPos = transform.position;
 
        Gizmos.DrawWireSphere(originPos, _viewRadius);
        Vector3 horizontalRightDir = AngleToDirZ(-_horizontalViewHalfAngle + _viewRotateZ);
        Vector3 horizontalLeftDir  = AngleToDirZ(_horizontalViewHalfAngle + _viewRotateZ);
        Vector3 lookDir = AngleToDirZ(_viewRotateZ);
 
        Debug.DrawRay(originPos, horizontalLeftDir * _viewRadius, Color.cyan);
        Debug.DrawRay(originPos, lookDir * _viewRadius, Color.green);
        Debug.DrawRay(originPos, horizontalRightDir * _viewRadius, Color.cyan);

        FindViewTarget();
    }
    
    public void FindViewTarget()
    {
        Vector2 originPos = transform.position;
        Collider2D hitedTarget = Physics2D.OverlapCircle(originPos, _viewRadius);

        if (hitedTarget == null)
        {
            _spriteRenderer.color = Color.white;
            return;
        }
        
        Vector2 targetPos = hitedTarget.transform.position;
        Vector2 dir = (targetPos - originPos).normalized;
        Vector2 lookDir = AngleToDirZ(_viewRotateZ);
        
        float dot = Vector2.Dot(lookDir, dir);
        float angle = Mathf.Acos(dot) * Mathf.Rad2Deg;
        
        if (angle <= _horizontalViewHalfAngle)
        {
            Debug.DrawLine(originPos, hitedTarget.transform.position, Color.yellow);

            //Quaternion targetRotation = Quaternion.FromToRotation(Vector3.right, hitedTarget.transform.position - transform.position);
            //transform.rotation = Quaternion.Lerp(transform.rotation, targetRotation, 1);
            //transform.Translate(Vector3.right * 5 * Time.deltaTime, Space.Self);

            _spriteRenderer.color = Color.red;
        }
        else if (angle >= 90)
        {
            _spriteRenderer.color = Color.green;
        }
        else
        {
            _spriteRenderer.color = Color.white;
        }   
    }
}
