using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class boneItemManager  : MonoBehaviour 
{ 
    public List<Transform> itemLists = new List<Transform>();
     
    private void OnDestroy()
    { 
        foreach (Transform item in itemLists)
        {
            Destroy(item.gameObject);
        }
    }
}
