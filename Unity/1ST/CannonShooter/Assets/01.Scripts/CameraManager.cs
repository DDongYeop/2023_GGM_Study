using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Cinemachine;
using DG.Tweening;
using System;

public enum CameraCategory
{
    CannonCam = 0,
    BallCam = 1,
    RigCam = 2
}

public struct CameraSet
{
    public CameraCategory Category;
    public CinemachineVirtualCamera VCam;
}

public class CameraManager : MonoBehaviour
{
    public static CameraManager Instance;

    private List<CameraSet> _camList = new List<CameraSet>();

    private CinemachineBasicMultiChannelPerlin _bPerlin;

    public void Init(Transform managerTrm)
    {
        //managerTrm���� ���� �޾ƾ� ��
        var cannonCam = managerTrm.Find("CannonCam").GetComponent<CinemachineVirtualCamera>();
        var ballCam = managerTrm.Find("BallCam").GetComponent<CinemachineVirtualCamera>();
        var rigCam = managerTrm.Find("RigCam").GetComponent<CinemachineVirtualCamera>();

        _camList.Add(new CameraSet { Category = CameraCategory.CannonCam, VCam = cannonCam });
        _camList.Add(new CameraSet { Category = CameraCategory.BallCam, VCam = ballCam });
        _camList.Add(new CameraSet { Category = CameraCategory.RigCam, VCam = rigCam });

        _bPerlin = ballCam.GetCinemachineComponent<CinemachineBasicMultiChannelPerlin>();
    }

    private Tween _prevTween = null;

    public void ShakeCam(float intensity, float duration)
    {
        if(_prevTween != null && _prevTween.IsActive())
        {
            _prevTween.Kill();
        }

        _bPerlin.m_AmplitudeGain = intensity;

        _prevTween = DOTween.To(getter: () => _bPerlin.m_AmplitudeGain,
            setter: value => _bPerlin.m_AmplitudeGain = value,
            endValue: 0, duration: duration);
    }

    public void ChangeFollowTarget( CameraCategory cat, Transform target)
    {
        foreach(CameraSet cs in _camList)
        {
            if(cs.Category == cat)
            {
                cs.VCam.Priority = 15;
                break;
            }
        }
    }

    public void SetActiveCam(CameraCategory cat, Transform target = null)
    {
        foreach(CameraSet cs in _camList)
        {
            if(cs.Category == cat)
            {
                cs.VCam.Priority = 15;
                if(target != null)
                {
                    cs.VCam.m_Follow = target;
                }
            }
            else
            {
                cs.VCam.Priority = 10;
            }
        }
    }

}
