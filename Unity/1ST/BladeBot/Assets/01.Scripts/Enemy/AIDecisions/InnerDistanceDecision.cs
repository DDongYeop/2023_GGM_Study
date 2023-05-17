using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class InnerDistanceDecision : AIDecision
{
    [SerializeField]
    private float _distance = 5f;

    [SerializeField]
    private bool isAlwaysVisible = false;  //얘는 디버깅용도
    
    public override bool MakeADecision()
    {
        if (_enemyController.TargetTrm == null) return false;

        float distance = Vector3.Distance(_enemyController.TargetTrm.position, transform.position);

        if(distance < _distance)  //시야 안으로 들어왔으니 추적 시작
        {
            _aiActionData.LastSpotPoint = _enemyController.TargetTrm.position; //마지막으로 본 시점으로 기록
            _aiActionData.TargetSpotted = true; //적을 발견했다.
        }else
        {
            _aiActionData.TargetSpotted = false;
        }
        return _aiActionData.TargetSpotted;
    }

#if UNITY_EDITOR
    private void OnDrawGizmos()
    {
        if(UnityEditor.Selection.activeObject == gameObject || isAlwaysVisible == true)
        {
            Color oldColor = Gizmos.color;
            Gizmos.color = Color.green;
            Gizmos.DrawWireSphere(transform.position, _distance);
            Gizmos.color = oldColor;
        }
    }
#endif
}
