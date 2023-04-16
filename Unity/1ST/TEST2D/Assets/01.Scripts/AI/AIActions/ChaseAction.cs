using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ChaseAction : AIAction
{
    private Vector3Int _beforePos = Vector3Int.zero;

    private SpriteRenderer _spriteRenderer;

    private readonly int _normalState = Shader.PropertyToID("_NormalState");

    public override void SetUp(AIBrain brain)
    {
        base.SetUp(brain);
        _spriteRenderer = brain.GetComponent<SpriteRenderer>();
    }
    
    public override void TakeAction()
    {
        //플레이어 타일 포지션 나옴
        Vector3Int nextPos = TileMapManager.Instance.GetTilePos(_brain.StateInfoCompo.LastEnemyPosition);

        if (nextPos != _beforePos)
        {
            //플레이어 타일 위치로 이동 했다고 판단하고 움직이 시작
            _brain.NavAgentCompo.Destination = nextPos;
            _beforePos = nextPos;
        }

        /*Material mat = _spriteRenderer.material;
        mat.SetInt(_normalState, 0);*/
    }
}
