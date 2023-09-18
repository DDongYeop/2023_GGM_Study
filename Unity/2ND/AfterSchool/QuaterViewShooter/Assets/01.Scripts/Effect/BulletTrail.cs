using System.Collections;
using UnityEngine;

public class BulletTrail : PoolableMono
{
    [SerializeField] private float _lifeTime = 0.2f;

    private TrailRenderer _trailRenderer;

    private void Awake()
    {
        _trailRenderer = GetComponent<TrailRenderer>();
    }

    public void DrawTrail(Vector3 startPos, Vector3 endPos, float lifeTime)
    {
        _trailRenderer.Clear(); //Ʈ���Ϸ����� ���� ��� ���� �����Ѵ�.
        _trailRenderer.AddPosition(startPos);
        transform.position = endPos;
        _trailRenderer.time = lifeTime;
        _lifeTime = lifeTime;
        StartCoroutine(DestroyTimer());
    }

    private IEnumerator DestroyTimer()
    {
        yield return new WaitForSeconds(_lifeTime);
        //Destroy(gameObject); //���߿� Ǯ�Ŵ����� �־���� �Ѵ�.
        PoolManager.Instance.Push(this);
    }

    public override void Init()
    {
        
    }
}
