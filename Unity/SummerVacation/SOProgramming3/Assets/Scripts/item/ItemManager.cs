using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ItemManager : MonoBehaviour
{
    public List<Transform> items = new List<Transform>();

    private void OnDestroy()
    {
        foreach (Transform item in items)
        {
            Destroy(item.gameObject);
        }
    }
}
