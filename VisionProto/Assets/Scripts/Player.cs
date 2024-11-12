using System.Collections;
using System.Collections.Generic;
using TMPro;
using UnityEngine;

public class Player : MonoBehaviour
{
    public float speed;
    public float mouseSpeed;
    float gravity;
    float mouseX;

    float hAxis;
    float vAxis;
    bool run;
    bool dash;
    bool jump;

    bool isRunning;
    bool isDashing;
    bool isJumping;

    Vector3 moveVec;
    Vector3 runVec;

    Rigidbody rigid;
    Camera mainCamera;

    int absorptionCount;

    float doubleTapTime = 3f;
    int tapCount = 0;
    float lastTapTime = 0f;
    bool isCombo;
    bool isCollision;

    private void Awake()
    {
        rigid = GetComponent<Rigidbody>();
        gravity = 9.81f;
        moveVec = Vector3.zero;
        
    }
    private void Start()
    {
        mainCamera = Camera.main;
    }
    // Update is called once per frame
    void Update()
    {
        GetInput();
        Move();
        Jump();
        Run();
        Dash();
        if (Input.GetKeyDown(KeyCode.E))
        {
            Change();
        }

        //if (!isCombo && dash)
        //{
        //    print("예리나다녀감");
        //    if (Time.time - lastTapTime < doubleTapTime)
        //    {
        //        tapCount++;
        //        lastTapTime = Time.time;
        //    }
        //     else
        //        tapCount = 0;
        //}

        //if (tapCount == 2)
        //{
        //    isCombo = true;
        //    print("combo");
        //    Dash();
        //    tapCount = 0;
        //    isCombo = false;
        //}
    }

    private void FixedUpdate()
    {
        moveVec.y -= gravity * Time.deltaTime;
        transform.position += moveVec * Time.deltaTime * speed;
        DarkVision();
    }
    void GetInput()
    {
        hAxis = Input.GetAxisRaw("Horizontal");
        vAxis = Input.GetAxisRaw("Vertical");
        run = Input.GetButton("Dash");
        jump = Input.GetButtonDown("Jump");
        dash = Input.GetKeyDown(KeyCode.Q);
        
    }
    void Move()
    {
        float mouseX = Input.GetAxisRaw("Mouse X") * mouseSpeed;
        transform.Rotate(Vector3.up, mouseX);
        moveVec = new Vector3(hAxis, 0, vAxis).normalized;
        moveVec = transform.TransformDirection(moveVec);
    }
    void Jump()
    {
        if(jump && !isJumping)
        {
            rigid.AddForce(Vector3.up * 10, ForceMode.Impulse);
            isJumping = true;
        }
    }
    void Run()
    {
        if (!isRunning && run)
        {
            isRunning = true;
            runVec = moveVec;
            speed *= 2;
            Invoke("RunOut", 0.1f);
        }
    }
    void RunOut()
    {
        speed *= 0.5f;
        isRunning = false;
    }
    void Dash()
    {
        if (!isDashing && dash)
        {
            if(hAxis == -1)
            {
                isDashing = true;
                //transform.position -= transform.right * 3f;
                //isDashing = false;
                speed *= 3;
                Invoke("DashOut", 0.1f);
            }
            else if (hAxis == 1)
            {
                isDashing = true;
                //transform.position += transform.right * 3f;
                //isDashing = false;
                speed *= 3;
                Invoke("DashOut", 0.1f);
            }
            else if (vAxis == -1)
            {
                isDashing = true;
                //transform.position -= transform.forward * 3f;
                //isDashing = false;
                speed *= 3;
                Invoke("DashOut", 0.1f);
            }
            else if (vAxis == 1)
            {
                isDashing = true;
                //transform.position += transform.forward * 3f;
                //isDashing = false;
                speed *= 3;
                Invoke("DashOut", 0.1f);
            }
        }
    }
    void DashOut()
    {
        speed /= 3;
        isDashing = false;
    }
    private void OnCollisionEnter(Collision collision)
    {
        if(collision.gameObject.tag == "Floor" && collision.gameObject.tag == "Wall")
        {
            isJumping = false;
        }
        if(collision.gameObject.tag == "NPC")
        {
            Destroy(collision.gameObject);
        }
    }
    void Change()
    {
        RaycastHit hit;
        //Debug.DrawRay(transform.position, mainCamera.transform.forward * 100f, Color.red);
        if (Physics.Raycast(transform.position, mainCamera.transform.forward, out hit))
        {
            Debug.DrawRay(transform.position, mainCamera.transform.forward * hit.distance, Color.red);
            // 바라보는 대상이 NPC인 경우에만 이동
            if (hit.collider.CompareTag("NPC"))
            {
                transform.position = hit.point;
                absorptionCount++;
            }
        }
    }

    void DarkVision()
    {
        if(!isCollision && absorptionCount == 5)
        {
            isCollision = true;
            
            Physics.IgnoreLayerCollision(LayerMask.NameToLayer("Player"), LayerMask.NameToLayer("Wall"), true);

            StartCoroutine(EnableCollisionAfterDelay(3f));
            //Invoke("OutDarkVision", 3f);
        }
    }

    IEnumerator EnableCollisionAfterDelay(float delay)
    {
        yield return new WaitForSeconds(delay); // 일정 시간 동안 대기

        print("바꿔야돼");
        Physics.IgnoreLayerCollision(LayerMask.NameToLayer("Player"), LayerMask.NameToLayer("Wall"), false);
        isCollision = false;
        absorptionCount = 0;
    }
}
