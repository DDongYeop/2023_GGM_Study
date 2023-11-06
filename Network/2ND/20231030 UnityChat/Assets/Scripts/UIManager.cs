using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Serialization;

public class UIManager : MonoBehaviour
{
    public static UIManager Instance;

    public GameObject LoginUI;
    public GameObject RegisterUI;
    public GameObject PlayUI;
    public GameObject User;
    
    private void Awake()
    {
        if (Instance != null)
            Debug.LogError("Multiple UIManager is running");
        Instance = this;
    }

    public void LoginPanel()
    {
        LoginUI.SetActive(true);
        RegisterUI.SetActive(false);
    }

    public void RegisterPanel()
    {
        RegisterUI.SetActive(true);
        LoginUI.SetActive(false);
    }

    public void CloseLogin()
    {
        LoginUI.SetActive(false);
        User.SetActive(true);
        PlayUI.SetActive(true);
    }
}
