using Core;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.VFX;

public class Beam : PoolableMono
{
    private VisualEffect _beamMuzzle;
    private VisualEffect _beamFlare;

    private LineRenderer _lineRenderer;
    private Light _beamLight;

    [SerializeField]
    private float _beamLength = 10f;
    private LayerMask _whatIsEnemy;

    [SerializeField]
    private float _beamTime = 0.6f;
    [SerializeField]
    private int _beamDamage = 5;

    public override void Init()
    {
        _lineRenderer.enabled = false;
        _beamLight.enabled = false;
        _beamMuzzle.Stop();
        _beamFlare.Stop();
    }

    private void Awake()
    {
        _lineRenderer = GetComponent<LineRenderer>();
        _beamMuzzle = transform.Find("BeamMuzzle").GetComponent<VisualEffect>();
        _beamFlare = transform.Find("BeamFlare").GetComponent<VisualEffect>();
        _beamLight = _beamMuzzle.transform.Find("BeamLight").GetComponent<Light>();

        Init();
    }

    public void SetUpLayerMask(LayerMask target)
    {
        _whatIsEnemy = target;
    }

    public void PreCharging()
    {
        _beamLight.enabled = true;
        _beamMuzzle.Play(); //차징시작
    }

    public void FireBeam(int damage, Vector3 targetDir)
    {
        float r = _lineRenderer.startWidth; //라인이 그려지는 시작 두께

        RaycastHit hit;
        bool isHit = Physics.SphereCast(
            transform.position, r, targetDir.normalized,
            out hit, _beamLength, _whatIsEnemy);

        _lineRenderer.enabled = true;
        _lineRenderer.SetPosition(0, transform.position);

        if(isHit)
        {
            _lineRenderer.SetPosition(1, hit.point);
            _beamFlare.transform.position = hit.point;

            if(hit.collider.TryGetComponent<IDamageable>(out IDamageable health))
            {
                health.OnDamage(_beamDamage, hit.point, hit.normal);
            }
        }else
        {
            Vector3 endPos = transform.position + targetDir * _beamLength;
            _lineRenderer.SetPosition(1, endPos);
            _beamFlare.transform.position = endPos;
        }
        _beamFlare.Play();
        StartCoroutine(DelayStop());
    }

    private IEnumerator DelayStop()
    {
        yield return new WaitForSeconds(_beamTime);
        StopBeam();
    }

    public void StopBeam()
    {
        StartCoroutine(StopSequence());
    }

    private IEnumerator StopSequence()
    {
        _lineRenderer.enabled = false;
        _beamLight.enabled = false;

        yield return new WaitForSeconds(0.1f);
        _beamMuzzle.Stop();
        _beamFlare.Stop();

        yield return new WaitForSeconds(0.3f);
        PoolManager.Instance.Push(this);
    }

    private void Update()
    {
        if(Input.GetKeyDown(KeyCode.Q))
        {
            PreCharging();
        }

        if(Input.GetKeyDown(KeyCode.R))
        {
            Ray ray = Define.MainCam.ScreenPointToRay(Input.mousePosition);
            RaycastHit hit;

            bool result = Physics.Raycast(ray, out hit, Define.MainCam.farClipPlane,
                1 << LayerMask.NameToLayer("Ground"));

            Vector3 point = hit.point;
            point.y = transform.position.y;
            Vector3 dir = (point - transform.position).normalized;
            FireBeam(5, dir);
        }
    }
}
