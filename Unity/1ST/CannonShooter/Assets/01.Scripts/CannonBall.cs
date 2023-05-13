using System;
using UnityEngine;

public class CannonBall : MonoBehaviour
{
    [SerializeField]
    private ParticleSystem _expParticlePrefab;

    private Rigidbody2D _rigidbody;

    [SerializeField]
    private LayerMask _whatIsTarget;

    [SerializeField]
    private float _expRadius = 2.5f;

    [SerializeField]
    private float _lifeTime = 4f;
    private float _fireTime = 0;

    public Action OnCannonBallEnd = null;

    private void Awake()
    {
        _rigidbody = GetComponent<Rigidbody2D>();
    }

    public void Fire(Vector2 dir, float power)
    {
        _fireTime = Time.time; //���� �ð� ����ϰ�
        _rigidbody.AddForce(dir * power, ForceMode2D.Impulse);
    }

    private void Update()
    {
        if(_fireTime + _lifeTime < Time.time)
        {
            OnCannonBallEnd?.Invoke();
            Destroy(gameObject);
        }
    }


    //��� ������ �ε����� ����.
    private void OnCollisionEnter2D(Collision2D collision)
    {
        ParticleSystem effect = Instantiate(_expParticlePrefab, transform.position, Quaternion.identity);
        effect.Play();

        Collider2D[] cols = Physics2D.OverlapCircleAll(transform.position, _expRadius, _whatIsTarget);

        float maxExpPower = 5f;
        float minExpPower = 1f;

        foreach(Collider2D c in cols)
        {
            Box box = c.GetComponent<Box>();

            Vector2 dir = box.transform.position - transform.position;

            float percent = dir.magnitude / _expRadius;
            float power = Mathf.Lerp(maxExpPower, minExpPower, percent);

            box.PlayExplosion(dir.normalized * power + new Vector2(0, 4f));
        }

        GameManager.Instance.CurrentBoxCount -= cols.Length;

        CameraManager.Instance.ShakeCam(intensity: 2f, duration: 0.8f);
        Destroy(effect, 2f);

        OnCannonBallEnd?.Invoke();
        Destroy(gameObject);
    }
}
