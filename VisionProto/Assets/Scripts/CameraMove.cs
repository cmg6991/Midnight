using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraMove : MonoBehaviour
{
    [SerializeField] private float mouseSpeed = 5f;
    float mouseX = 0f;
    float mouseY = 0f;
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        mouseX += Input.GetAxis("Mouse X")*mouseSpeed;
        mouseY += Input.GetAxis("Mouse Y")*mouseSpeed;
        mouseY = Mathf.Clamp(mouseY, -30f, 30f);
    }
}
