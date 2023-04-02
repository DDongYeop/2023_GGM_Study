using System;
using System.Collections;
using System.Collections.Generic;
using System.Threading;
using System.Threading.Tasks;
using UnityEngine;

public class AsyncTest : MonoBehaviour
{
    private bool _start = false;
    private int _number = 0;
    private void Awake()
    {
        Debug.Log($"Awake : {Thread.CurrentThread.ManagedThreadId}");
    }

    private void Update()
    {
        if (Input.GetButtonDown("Jump"))
        {
            Debug.Log("점프 !");
        }

        if (Input.GetKeyDown(KeyCode.A))
        {
            //MyJob();
            //Debug.Log($"Update : {Thread.CurrentThread.ManagedThreadId}");
            //StartCoroutine(MyJob());
            //Task.Run(() => MyJob());

            /*if (!_start)
            {
                _start = true;
                _number = 0;
                Task.Run(() => MyJob());
                for (int i = 0; i < 500000; i++)
                    _number++;
            }*/
            JobSequnce();
        }
        
        if (Input.GetKeyDown(KeyCode.D))
            Debug.Log(_number);
    }

    private async void JobSequnce()
    {
        Debug.Log($"Job : {Thread.CurrentThread.ManagedThreadId}");
        Debug.Log("JobStart");
        await Task.Run(() => MyJob(1));
        await Task.Run(() => MyJob(2));
        await Task.Run(() => MyJob(3));
        await Task.Run(() => MyJob(4));
        Debug.Log("JobComplete");
    }

    private void MyJob(int num)
    {
        Debug.Log($"Job {num} : {Thread.CurrentThread.ManagedThreadId}");
        for (int i = 0; i < 500000; i++)
            _number--;
        Debug.Log($"MyJob End : {num}");
        /*Debug.Log($"MyJob : {Thread.CurrentThread.ManagedThreadId}");
        //Thread.Sleep(3000);
        ulong timer = 0;
        while (true)
        {
            timer++;
            Debug.Log(timer);
            if (timer >= 900000000)
                break;
        }
        Debug.Log("Job Complete");*/
    }
}
 