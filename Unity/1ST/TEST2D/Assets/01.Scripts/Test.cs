using System;
using System.Collections;
using System.Collections.Generic;
using Unity.VisualScripting;
using UnityEngine;

public interface Human
{
    public bool PassCertificate();
}

public class Student
{
    public string name;
    public int code;
    public string phone;
    public Sprite picture;

    public virtual void Introduce() //수정을 하기위해 virtual을 써야한다
    {
        Debug.Log("안녕하세요. 학생입니다.");
    }
    
    // 접근제어자 나중에 편하게 쓰려고 
    // public, private, protected, internal >> 같은 어셈블리 안에서 통한다  
}

public class Student2 : Student, Human
{
    public override void Introduce() //수정을 위해 overriade를 해줘야한다 
    {
        //base.Introduce();
        Debug.Log("안녕하세요. 2학년 학생입니다.");
    }

    public bool PassCertificate()
    {
        return true;
    }
}

public class Test : MonoBehaviour
{
    private Collision2D _col;
    
    public void PrintMsg()
    {
        //GC.Collect(); //수동으로 가비지컬렋터 작동
        // int a = 10; //스택 변수
        Student s = new Student(); // 힙 변수 
        s.Introduce();
        Student2 s2 = new Student2();
        s2.Introduce();
        Human s3 = new Student2();
        if (s3.PassCertificate())
            Debug.Log("정처기합격. 난 자유.");
        else
            Debug.Log("난 망함. 떨어짐 ㅂㅂ");
    }

    private void OnCollisionEnter2D(Collision2D collision)
    {
        _col = collision;
        Debug.Log("충돌");
    }

    private void Update()
    {
        if (Input.GetKeyDown(KeyCode.Space))
            Debug.Log(_col.gameObject.name);
    }
}
