using System;
using System.Collections;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using System.Threading;
using System.Threading.Tasks;
using UnityEngine;

public class AsyncAwait : MonoBehaviour
{
    private int _num = 0;
    
    private void Start()
    {
        if (Thread.CurrentThread.Name == null)
        {
            Thread.CurrentThread.Name = "MainThread";
        }
    }

    private void Update()
    {
        if (Input.GetKeyDown(KeyCode.Space))
        {
            //Task.Run(() => MyJob()); //메인 쓰레드가 꺼져도 실행된다. (Play상태가 아니여도 돌아간다)
            
            //Task.Run(() => MyJobA());
            //Task.Run(() => MyJobB());

            StartTask();
        }

        if (Input.GetKeyDown(KeyCode.A))
        {
            //Debug.Log("살아있습니다.");
            Debug.Log("Num : " + _num);
        }
    }

    private async void StartTask()
    {
        Task t1 = Task.Run(() => MyJobA());
        Task t2 = Task.Run(() => MyJobB());

        await Task.WhenAll(new[] { t1, t2 });
        Debug.Log("Job Complete");
    }

    /*IEnumerator MyJob()
    {
        yield return new WaitForSeconds(3f);
        Debug.Log(Thread.CurrentThread.Name);
        Debug.Log("Job Complete");
    }*/

    private void MyJob()
    {
        Thread.Sleep(3000);
        Debug.Log(Thread.CurrentThread.Name);
        Debug.Log("Job complete");
    }

    private object obj = new object(); //진짜 아무 의미없는 객체 하나가 필요
    //얘는 깃발로 쓴다 

    private void MyJobA()
    {
        for (int i = 0; i < 9999999; ++i)
        {
            lock (obj)
            {
                _num++;
            }
        }
    }
    
    private void MyJobB()
    {
        for (int i = 0; i < 9999999; ++i)
        {
            lock (obj)
            {
                _num--;
            }
        }
    }
}
