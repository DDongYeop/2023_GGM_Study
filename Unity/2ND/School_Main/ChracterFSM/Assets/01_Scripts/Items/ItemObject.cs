using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ItemObject : MonoBehaviour
{
    private Rigidbody2D _rigidbody;
    private SpriteRenderer _spriteRenderer;

    [SerializeField] private ItemDataSO _itemData;

#if UNITY_EDITOR
    //이건 편의성을 위한 기능
    private void OnValidate()
    {
        if (_itemData == null) return;
        if(_spriteRenderer == null)
        {
            _spriteRenderer = GetComponent<SpriteRenderer>();
        }
        _spriteRenderer.sprite = _itemData.itemIcon;
        gameObject.name = $"ItemObject[{_itemData.itemName}]";
    }
#endif

    private void Awake()
    {
        _rigidbody = GetComponent<Rigidbody2D>();
        _spriteRenderer = GetComponent<SpriteRenderer>();   
    }

    //아이템 드랍용이고 여기서 안쓸거고 근데 니들이 뭔가 할거면 해라.
    public void SetUpItem(ItemDataSO itemData, Vector2 velocity)
    {
        _itemData = itemData;
        _rigidbody.velocity = velocity;
        _spriteRenderer.sprite = itemData.itemIcon;
    }

    public void PickUpItem()
    {
        Inventory.Instance.AddItem(_itemData);
        Destroy(gameObject);
    }
}
