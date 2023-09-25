using System;
using System.Collections;
using System.Collections.Generic;
using Unity.VisualScripting;
using UnityEngine;

public struct ViewCastInfo
{
    public bool hit;
    public Vector3 point;
    public float distance;
    public float angle;
}

public struct EdgeInfo
{
    public Vector3 pointA;
    public Vector3 pointB;
}

public class PlayerFOV : MonoBehaviour
{
    [Range(0, 360)] public float viewAngle;
    public float viewRadius;

    [SerializeField] private LayerMask _enemyMask;
    [SerializeField] private LayerMask _obstacleMask;
    [SerializeField] private float _enemyFindDelay = 0.3f;
    [SerializeField] private float _meshResolution;
    [SerializeField] private int _edgeResolveIteration; //2분 탐색을 몇번 반복할거냐?
    [SerializeField] private float _edgeDistanceThreshold;
    
    public List<Transform> visibleTargets = new List<Transform>();

    private MeshFilter _viewMeshFilter;
    private Mesh _viewMesh;

    private void Awake()
    {
        _viewMeshFilter = transform.Find("ViewVisual").GetComponent<MeshFilter>();
        _viewMesh = new Mesh();
        _viewMesh.name = "View Mesh";
        _viewMeshFilter.mesh = _viewMesh;
    }

    public Vector3 DirFromAngle(float degree, bool angleIsGlobal)
    {
        if (!angleIsGlobal)
        {
            degree += transform.eulerAngles.y;
        }

        float rad = degree * Mathf.Deg2Rad;
        return new Vector3(Mathf.Sin(rad), 0, Mathf.Cos(rad));
    }

    public void Start()
    {
        StartCoroutine(FindEnemyWithDelay(_enemyFindDelay));
    }

    private IEnumerator FindEnemyWithDelay(float delay)
    {
        var time = new WaitForSeconds(delay);
        while (true)
        {
            yield return time;
            FindVisibleEnemy();
        }
    }

    private void FindVisibleEnemy()
    {
        visibleTargets.Clear();
        Collider[] enemiesInView = new Collider[6];
        int cnt = Physics.OverlapSphereNonAlloc(transform.position, viewRadius, enemiesInView, _enemyMask);

        for (int i = 0; i < cnt; ++i)
        {
            Transform enemy = enemiesInView[i].transform;
            Vector3 dir = enemy.position - transform.position;
            Vector3 dirToEnemy = dir.normalized;

            if (Vector3.Angle(transform.forward, dirToEnemy) < viewAngle * 0.5f)
            {
                //시아를 가리고 있는 장애물이 있는지 
                if (!Physics.Raycast(transform.position, enemy.position, dir.magnitude, _obstacleMask))
                    visibleTargets.Add(enemy);
            }
        }
    }

    private void LateUpdate()
    {
        DrawFieldOfView();
    }

    private EdgeInfo FindEdge(ViewCastInfo minViewCast, ViewCastInfo maxViewCast)
    {
        float minAngle = minViewCast.angle;
        float maxAngle = maxViewCast.angle;

        Vector3 minPoint = Vector3.zero;
        Vector3 maxPoint = Vector3.zero;

        for (int i = 0; i < _edgeResolveIteration; ++i)
        {
            float angle = (minAngle + maxAngle) * 0.5f;
            var castInfo = ViewCast(angle); //새로운 중간각으로 캐슽 시작
            bool thresholdExceeded = Mathf.Abs(minViewCast.distance - castInfo.distance) > _edgeDistanceThreshold;

            //두개의 레이가 모두 피격상태가 같고 거리도 일정 이내야
            if (castInfo.hit == minViewCast.hit && !thresholdExceeded)
            {
                minAngle = angle;
                minPoint = castInfo.point;
            }
            else
            {
                maxAngle = angle;
                maxPoint = castInfo.point;
            }
        }

        return new EdgeInfo { pointA = minPoint, pointB = maxPoint };
    }

    private void DrawFieldOfView()
    {
        int stepCount = Mathf.RoundToInt(viewAngle * _meshResolution);
        float stepAngleSize = viewAngle / stepCount;

        Vector3 pos = transform.position;
        List<Vector3> viewPoints = new List<Vector3>();

        var oldViewCastInfo = new ViewCastInfo(); //예전 정보를 기억할 변수
        
        for (int i = 0; i <= stepCount; ++i)
        {
            float angle = transform.eulerAngles.y - viewAngle * .5f + stepAngleSize * i;
            //현재 돌아가있는 만큼을 돌려서 계산
            //Debug.DrawLine(pos, pos + DirFromAngle(angle, true) * viewRadius, Color.red);
            var info = ViewCast(angle);

            if (i > 0) //첫 캐스트가 아니라면, 이전 정보가 저장 되어있다
            {
                bool thresholdExceeded = Mathf.Abs(oldViewCastInfo.distance - info.distance) > _edgeDistanceThreshold;
                //이전과 지금에서 달라진거다

                if (oldViewCastInfo.hit != info.hit || (oldViewCastInfo.hit && info.hit && thresholdExceeded))
                {
                    var edge = FindEdge(oldViewCastInfo, info);

                    if (edge.pointA != Vector3.zero)
                    {
                        viewPoints.Add(edge.pointA);
                    }
                    
                    if (edge.pointB != Vector3.zero)
                    {
                        viewPoints.Add(edge.pointB);
                    }
                }
            }
            
            viewPoints.Add(info.point);

            oldViewCastInfo = info; //이전 정보에 현재 정보 넣어준다
        }

        int vertCount = viewPoints.Count + 1;
        Vector3[] vertices = new Vector3[vertCount];
        int[] triangles = new int[(vertCount - 2) * 3];
        vertices[0] = Vector3.zero;
        for (int i = 0; i < vertCount - 1; ++i)
        {
            vertices[i + 1] = transform.InverseTransformPoint(viewPoints[i]);

            if (i < vertCount - 2)
            {
                int tIndex = i * 3;
                triangles[tIndex + 0] = 0;
                triangles[tIndex + 1] = i + 1;
                triangles[tIndex + 2] = i + 2;
            }
        }
        _viewMesh.Clear();
        _viewMesh.vertices = vertices;
        _viewMesh.triangles = triangles;
        _viewMesh.RecalculateNormals(); // 노말 재계산 
    }

    private ViewCastInfo ViewCast(float globalAngle)
    {
        Vector3 dir = DirFromAngle(globalAngle, true);
        if (Physics.Raycast(transform.position, dir, out RaycastHit hit, viewRadius, _obstacleMask))
        {
            return new ViewCastInfo { hit = true, point = hit.point, distance = hit.distance, angle = globalAngle };
        }
        else
        {
            return new ViewCastInfo { hit = false, point = transform.position + dir*viewRadius, distance = viewRadius, angle = globalAngle };
        }
    }
}
