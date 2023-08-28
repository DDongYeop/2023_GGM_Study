using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AI;
using UnityEngine.Rendering;

public abstract class EnemyBrain : MonoBehaviour
{
    [SerializeField] protected Transform _targetTrm;

    public NavMeshAgent NavAgent { get; private set; }

    protected UIStatusBar _statusBar;
    protected Camera _mainCam;

    protected virtual void Awake()
    {
        NavAgent = GetComponent<NavMeshAgent>();
        _statusBar = transform.Find("Status").GetComponent<UIStatusBar>();
        _mainCam = Camera.main;
    }

    protected void LateUpdate()
    {
        _statusBar.LookToCamera(); //이건 update에서 호출하면 지터링 발생
    }

    private Coroutine _coroutine;

    public void TryToTalk(string text, float timer = 1)
    {
        _statusBar.DialogText = text;
        if (_coroutine != null)
            StopCoroutine(_coroutine);
        _coroutine = StartCoroutine(PanelFade(timer));
    }

    private IEnumerator PanelFade(float timer)
    {
        _statusBar.IsOn = true;
        yield return new WaitForSeconds(timer);
        _statusBar.IsOn = false;
    }
}
