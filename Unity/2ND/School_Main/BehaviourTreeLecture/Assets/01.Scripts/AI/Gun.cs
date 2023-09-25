using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Gun : MonoBehaviour
{
    public int totalAmmo = 50;
    public int maxAmmo = 8;
    public int currentAmmo;

    public bool IsEnpty => currentAmmo == 0;
    public int EmptyCount => maxAmmo - currentAmmo;

    private bool _isReloading = false;
    
    private void Start()
    {
        currentAmmo = maxAmmo;
    }

    public void Reload()
    {
        _isReloading = true;
        int cnt = Mathf.Min(EmptyCount, totalAmmo);
        totalAmmo -= cnt;
        currentAmmo += cnt;
        _isReloading = false;
    }
}
