using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ItemTrigger : MonoBehaviour
{
    private ItemObject _itemObject;

    private void Awake()
    {
        _itemObject = transform.parent.GetComponent<ItemObject>();
    }

    private void OnTriggerEnter2D(Collider2D other)
    {
        if (other.TryGetComponent<Player>(out Player player))
            _itemObject.PickUpItem();
    }
}
