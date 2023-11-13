using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class UIManager : Singleton<UIManager>
{
    public GameObject loginUI;
    public GameObject registerUI;
    public GameObject playUI;
    public GameObject User;

    public void LoginPanel()
    {
        loginUI.SetActive(true);
        registerUI.SetActive(false);
    }

    public void RegisterPanel()
    {
        registerUI.SetActive(true);
        loginUI.SetActive(false);
    }

    public void CloseLogin()
    {
        loginUI.SetActive(false);
        User.SetActive(true);
        playUI.SetActive(true);
    }

}
