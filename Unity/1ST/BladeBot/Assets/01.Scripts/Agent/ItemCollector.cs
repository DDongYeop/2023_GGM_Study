using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Events;

public class ItemCollector : MonoBehaviour
{
    public UnityEvent<int> OnHeal;

    [SerializeField]
    private float _magneticRadius = 1f, _magneticPower = 3f;

    [SerializeField]
    private LayerMask _whatIsResource;
    private List<Resource> _collectingList = new List<Resource>();

    private void Update()
    {
        Collider[] resources = Physics.OverlapSphere(transform.position, _magneticRadius, _whatIsResource);

        foreach(Collider r in resources)
        {
            if(r.TryGetComponent<Resource>(out Resource res))
            {
                _collectingList.Add(res);
                res.gameObject.layer = 0; //더 이상 리스트에 안들어가게
            }
        }

        for(int i = 0; i < _collectingList.Count; i++)
        {
            Resource r = _collectingList[i];
            Vector3 nextStep = (transform.position - r.transform.position).normalized
                                    * Time.deltaTime * _magneticPower;
            r.transform.Translate(nextStep, Space.World);

            if(Vector3.Distance(r.transform.position, transform.position) < 0.3f)
            {
                ConsumeResource(r);
                _collectingList.RemoveAt(i);
                i--;
            }
        }
    }

    private void ConsumeResource(Resource resource)
    {
        ResourceDataSO so = resource.ResourceData;
        switch(so.ResourceType)
        {
            case Core.ResourceType.HealOrb:
                int hpValue = so.GetAmount();
                OnHeal?.Invoke(hpValue);
                resource.PickUpResource();
                break;

        }
    }

}
