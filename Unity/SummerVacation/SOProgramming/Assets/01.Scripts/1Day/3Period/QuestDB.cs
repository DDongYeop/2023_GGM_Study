using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[CreateAssetMenu (fileName = "QuestDataContainer")]
public class QuestDataContainer : ScriptableObject
{
    public List<QuestDB> questDatalist = new List<QuestDB>();
}

[System.Serializable]
public class QuestDB 
{
    public string questName;
    public string questDesciption;
    public int requiredLv;
}
