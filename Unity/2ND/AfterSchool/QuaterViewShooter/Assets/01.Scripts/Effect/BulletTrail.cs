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
        _trailRenderer.Clear(); //트레일렌더러 상의 모든 점을 제거한다.
        _trailRenderer.AddPosition(startPos);
        transform.position = endPos;
        _trailRenderer.time = lifeTime;
        _lifeTime = lifeTime;
        StartCoroutine(DestroyTimer());
    }

    private IEnumerator DestroyTimer()
    {
        yield return new WaitForSeconds(_lifeTime);
        //Destroy(gameObject); //나중에 풀매니저로 넣어줘야 한다.
        PoolManager.Instance.Push(this);
    }

    public override void Init()
    {
        
    }
}
