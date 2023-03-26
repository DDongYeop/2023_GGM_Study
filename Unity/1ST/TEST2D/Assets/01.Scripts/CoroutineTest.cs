using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CoroutineTest : MonoBehaviour
{
    private List<string> list = new List<string>();
    private IEnumerator t;
    
    /*private void Start()
    {
        t = Test();
    }*/

    private IEnumerator Start()
    {
        var t1 = this.RunCoroutine(CoA());
        var t2 = this.RunCoroutine(CoB());
        while(!t1.IsDone && !t2.IsDone)
        {
            yield return null;
        }
        Debug.Log("Complete");
    }

    private void Update()
    {
        bool ground = transform.IsInGround(.2f);
        if (ground)
            Debug.Log("땅바닥");
        
        return;
        if (Input.GetButtonDown("Jump"))
        {
            /*t.MoveNext();
            Debug.Log(t.Current);*/
            StartCoroutine(DelayCall(3f));
        }
        
        if (Input.GetKeyDown(KeyCode.A))
            Debug.Log("A 늘림");
    }

    IEnumerator Test()
    {
        Debug.Log("Something!");
        yield return 1;
        Debug.Log("Something!");
        yield return 2;
        Debug.Log("Something!");
        yield return 3;
        Debug.Log("Something!");
        yield return 4;
    }

    IEnumerator CoA()
    {
        yield return new WaitForSeconds(1f);
        Debug.Log("Co A Complete");
    }
    
    IEnumerator CoB()
    {
        yield return new WaitForSeconds(3f);
        Debug.Log("Co B Complete");
    }
    
    private IEnumerator DelayCall(float time)
    {
        ulong number = 0;
        while (true)
        {
            number++;
            if (number >= 90000000000)
                break;
        }
        
        /*yield return null;
        yield return new WaitUntil(() => true);
        yield return new WaitForEndOfFrame();*/
        yield return new WaitForSeconds(time);
        Debug.Log("Call");
    }
}
