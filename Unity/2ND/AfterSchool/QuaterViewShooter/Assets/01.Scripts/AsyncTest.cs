using System.Threading;
using System.Threading.Tasks;
using UnityEngine;
using UnityEngine.InputSystem;

public class AsyncTest : MonoBehaviour
{
    private void Start()
    {
        if(Thread.CurrentThread.Name == null)
            Thread.CurrentThread.Name = "MainUnityThread";

    }
    void Update()
    {
        if(Keyboard.current.spaceKey.wasPressedThisFrame)
        {
            Debug.Log("มกวม!!!");
        }

        if(Keyboard.current.qKey.wasPressedThisFrame)
        {
            Debug.Log($"My Delay Job started!  {Thread.CurrentThread.Name}");
            AsyncMethod();        
        }
    }

    private async void AsyncMethod()
    {
        int a = await MyDelayJob(1);
        Debug.Log(a);
        int b = await MyDelayJob(2);
        Debug.Log(b);
        int c = await MyDelayJob(3);
        Debug.Log(c);
    }

    private async Task<int> MyDelayJob(int count)
    {
        await Task.Delay(1000);
        Debug.Log($"My Delay Job complete! ${Thread.CurrentThread.Name}");
        return count + 100;
    }
}
