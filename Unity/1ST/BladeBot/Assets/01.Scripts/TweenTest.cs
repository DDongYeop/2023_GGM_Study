using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using DG.Tweening;

public class TweenTest : MonoBehaviour
{
    [SerializeField]
    private Transform _startTrm, _endTrm, _startControlTrm, _endControlTrm;

    private LineRenderer _line;
    private List<Vector3> _pointList;


    private Transform _coinTrm;

    private void Awake()
    {
        _line = GetComponent<LineRenderer>();
        _pointList = new List<Vector3>();
        _coinTrm = transform.Find("CoinTemplate");
    }
    void Update()
    {
        if(Input.GetKeyDown(KeyCode.P))
        {
            _pointList.Clear();

            DOCurve.CubicBezier.GetSegmentPointCloud(
                _pointList, _startTrm.position, _startControlTrm.position, 
                _endTrm.position, _endControlTrm.position, 30);

            _line.positionCount = _pointList.Count;
            _line.SetPositions(_pointList.ToArray());

            // 이 라인을 통해서 큐브가 움직이게 해보자.
            StartCoroutine(Moving(2f));
        }
    
        if(Input.GetKeyDown(KeyCode.O)) //코인생성기
        {
            for(int i = 0; i < 20; i++)
            {
                Vector2 pos = Random.insideUnitCircle * 2f;

                Vector3 targetPos = transform.position + new Vector3(pos.x, 0, pos.y);
                Transform trm = Instantiate(_coinTrm, transform);
                trm.gameObject.SetActive(true);
                trm.DOJump(targetPos, 4f, 1, 1.2f).SetEase(Ease.InQuad);
            }
        }
    }

    private IEnumerator Moving(float time)
    {
        float animateTime = time / _pointList.Count;
        for (int i = 0; i < _pointList.Count; i++)
        {
            yield return new WaitForSeconds(animateTime);
            transform.position = _pointList[i];
        }
    }
}
