using UnityEngine;
using Core;

[CreateAssetMenu(menuName = "SO/Item/ResourceData")]
public class ResourceDataSO : ScriptableObject
{
    public float Rate;
    public GameObject ItemPrefab;

    public ResourceType ResourceType;
    
    public int MinAmount = 1, MaxAmount = 5;

    public int GetAmount()
    {
        return Random.Range(MinAmount, MaxAmount + 1);
    }

    public AudioClip UseSound;
    public Color PopupTextColor;
}
