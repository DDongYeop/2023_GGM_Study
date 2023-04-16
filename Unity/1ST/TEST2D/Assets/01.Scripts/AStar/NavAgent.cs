using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using UnityEngine;

public class NavAgent : MonoBehaviour
{
    [SerializeField] private float _speed = 5f;
    [SerializeField] private bool _cornerCheck = false;

    private Vector3 _nextPos;
    private int _moveIndex = 0;
    private bool _isMoving = false; //이동중인지 

    public bool IsArrived = false;
    
    private LineRenderer _lineRenderer;

    private PriorityQueue<Node> _openList;
    private List<Node> _closeList;
    //좀 더 성능향상을 원하면 _closeList를 Dictionary로 구현해도 된다.

    private List<Vector3Int> _routePath; //계산된 경로

    private Vector3Int _currentPosition; //현재 타일 위치
    private Vector3Int _destination; //목적지 위치
    public Vector3Int Destination
    {
        get => _destination;
        set
        {
            //여기 뭔가 작업들이 들어가야 한다.
            SetCurrentPos();
            _destination = value;
            _isMoving = CalcRoute();
            _moveIndex = 0;
            if (_routePath.Count > 0)
                _nextPos = TileMapManager.Instance.GetWorldPos(_routePath[0]);
            DrawRoutePath();
            IsArrived = false;
        }
    }

    private void Update()
    {
        if(Input.GetMouseButtonDown(0))
        {
            Vector3 pos = Camera.main.ScreenToWorldPoint(Input.mousePosition);
            pos.z = 0;
            Vector3Int cellPos = TileMapManager.Instance.GetTilePos(pos);
            Destination = cellPos;
        }

        if (_isMoving)
        {
            Vector2 dir = (_nextPos - transform.position).normalized;
            transform.Translate(dir * (_speed * Time.deltaTime), Space.World);
            if (Vector2.Distance(_nextPos, transform.position) < 0.1f)
            {
                if (GetNextTarget() == false) // 도착 
                {
                    IsArrived = true; //도착했을을 표기
                    _isMoving = false;
                }
            }
        }
    }

    private bool GetNextTarget()
    {
        _moveIndex++;
        if (_moveIndex >= _routePath.Count)
            return false;
        _nextPos = TileMapManager.Instance.GetWorldPos(_routePath[_moveIndex]);
        return true;
    }

    //내 월드좌표를 타일좌표로 바꿔서 셋팅하는 거
    private void SetCurrentPos()
    {
        _currentPosition = TileMapManager.Instance.GetTilePos(transform.position);
    }

    private void Awake()
    {
        _openList = new PriorityQueue<Node>();
        _closeList = new List<Node>();
        _routePath = new List<Vector3Int>();
        _lineRenderer = transform.Find("LineRenderer").GetComponent<LineRenderer>();
    }

    private void Start()
    {
        SetCurrentPos();
        transform.position = TileMapManager.Instance.GetWorldPos(_currentPosition);
    }

    private void DrawRoutePath()
    {
        //_routePath에 저장되어 있는 것에 시작점은 내 현재 _currentPosition으로 하고
        //그전에 라인렌더를 활성화 해줘야 한다.
        // 저장된 포지션을 넣을때는 TileMapManager를 통해 world좌표로 변경해서 넣어야 한다.
        // 저장된 값들을 _lineRenderer에 SetPosition을 통해서 넣어주면 된다.
        _lineRenderer.enabled = true;
        _lineRenderer.positionCount = _routePath.Count;
        _lineRenderer.SetPositions(_routePath.Select(p => TileMapManager.Instance.GetWorldPos(p)).ToArray());
    }

    public void StopImmediately()
    {
        _isMoving = false;
    }

    #region ASTAR 알고리즘 관련

    public bool CalcRoute()
    {
        _openList.Clear();  //기존꺼 다 지우고 시작
        _closeList.Clear();

        _openList.Push(new Node
        {
            Cellpos = _currentPosition,
            Parent = null,
            G = 0,
            F = CalcH(_currentPosition)
        }); //맨 처음 오픈리스트에 내가 있는 곳을 넣는다.

        bool result = false;  //길을 찾았냐?
        int cnt = 0;
        while(_openList.Count > 0)
        {

            Node n = _openList.Pop(); //가장 가깝게 갈 수 있는 녀석을 뽑아온다.
            FindOpenList(n);
            
            _closeList.Add(n);

            if(n.Cellpos == _destination)
            {
                result = true;
                break;
            }

            cnt++;
            if(cnt >= 10000)
            {
                Debug.Log("1만번 넘게 루프!");
                break;
            }
        }
        
        
        if(result)
        {
            _routePath.Clear();
            Node last = _closeList[_closeList.Count - 1]; //마지막 노드
            while(last.Parent != null)
            {
                _routePath.Add(last.Cellpos);
                last = last.Parent;
            }
            //_routePath.Add(_currentPosition);

            _routePath.Reverse();

        }

        return result;
    }

    //얘는 n노드에 연결된 갈 수 있는 모든 길을 찾아낸다.
    private void FindOpenList(Node n)
    {
        /* O O O
         * O X O
         * O O O */

        for(int y = -1; y <= 1; y++)
        {
            for(int x = -1; x <= 1; x++)
            {
                if (x == y && x == 0) continue;

                if (_cornerCheck && (Mathf.Abs(x) + Mathf.Abs(y) == 2))
                {
                    Vector3Int corner = n.Cellpos + new Vector3Int(x, 0);
                    if (TileMapManager.Instance.CanMove(corner) == false) continue;
                    corner = n.Cellpos + new Vector3Int(0, y);
                    if (TileMapManager.Instance.CanMove(corner) == false) continue;
                }
                
                Vector3Int nextPos = n.Cellpos + new Vector3Int(x, y, 0);
                Node temp = _closeList.Find(x => x.Cellpos == nextPos);
                if (temp != null) continue; //이미 방문한 곳이면 리턴

                //그곳이 실제로 충돌체도 없고 맵안쪽 위치라면
                if(TileMapManager.Instance.CanMove(nextPos))
                {
                    float g = (n.Cellpos - nextPos).magnitude + n.G;

                    Node nextOpenNode = new Node
                    {
                        Cellpos = nextPos,
                        Parent = n,
                        G = g,
                        F = g + CalcH(nextPos)
                    };

                    Node exist = _openList.Contains(nextOpenNode);
                    if(exist == null)
                    {
                        _openList.Push(nextOpenNode);
                    }
                }
            }
        }
    }

    private float CalcH(Vector3Int pos)
    {
        Vector3Int distance = _destination - pos;
        return distance.magnitude;
    }

    #endregion

}
