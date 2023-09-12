using System;
using UnityEngine;

public class FirstCamera : MonoBehaviour
{
    public Transform firstCamTarget = null;

    public float spdMouseX = 5f;
    public float spdMouseY = 5f;

    public float rotationMouseX = .0f;
    public float rotationMouseY = .0f;

    private void FirstCam()
    {
        float mouseX = Input.GetAxis("Mouse X");
        rotationMouseX = transform.localEulerAngles.y + mouseX * spdMouseX;
        rotationMouseX = (rotationMouseX > 180f) ? rotationMouseX - 360f : rotationMouseX;
        
        float mouseY = Input.GetAxis("Mouse Y");
        rotationMouseY = transform.localEulerAngles.x + mouseY * spdMouseY;
        rotationMouseY = (rotationMouseY > 180f) ? rotationMouseY - 360f : rotationMouseY;

        transform.localEulerAngles = new Vector3(rotationMouseY, rotationMouseX, 0f);
        transform.position = firstCamTarget.position;
    }

    private void LateUpdate()
    {
        FirstCam();
    }
}
