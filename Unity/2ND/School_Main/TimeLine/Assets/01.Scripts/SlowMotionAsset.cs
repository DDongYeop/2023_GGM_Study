using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Playables;

public class SlowMotionAsset : PlayableAsset
{
    public float timeValue = 0.3f;
    
    //드레그해서 트랙에 올리는 순간 실행
    public override Playable CreatePlayable(PlayableGraph graph, GameObject owner)
    {
        var playable = ScriptPlayable<SlowMotion>.Create(graph); //막대 그래프 생성해서 넣어주는 역할을 한다

        var behaviour = playable.GetBehaviour();

        behaviour.timeValue = timeValue;
        return playable;
    }
}
