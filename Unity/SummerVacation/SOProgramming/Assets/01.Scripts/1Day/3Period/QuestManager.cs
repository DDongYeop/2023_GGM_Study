using System.Collections.Generic;
using UnityEngine;

public class QuestManager : MonoBehaviour
{
    public QuestDataContainer questDataContainer;
    
    private void Start()
    {
        questDataContainer = Resources.Load<QuestDataContainer>("QuestDataContainer");
        
        //LoadQuestDB();
        foreach (var questDB in questDataContainer.questDatalist)
        {
            Debug.Log($"퀘스트 이름 {questDB.questName}");
            Debug.Log($"퀘스트 설명 {questDB.questDesciption}");
            Debug.Log($"퀘스트 보상 {questDB.requiredLv}");
        }
    }

    /*
    private void LoadQuestDB()
    {
        _questDataList = new List<QuestDB>();
        _questDataList.Add(new QuestDB { questName = "첫 번쨰 퀘스트", questDesciption = "몬스터를 처치하세요", requiredLv = 5});
        _questDataList.Add(new QuestDB { questName = "두 번쨰 퀘스트", questDesciption = "아이템을 차지하세요", requiredLv = 10});
    }
    */
}
