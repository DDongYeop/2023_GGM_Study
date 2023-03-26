using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

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

public class Student2 : Student
{
    public override void Introduce() //수정을 위해 overriade를 해줘야한다 
    {
        //base.Introduce();
        Debug.Log("안녕하세요. 2학년 학생입니다.");
    }
}

public class Test : MonoBehaviour
{
    public void PrintMsg()
    {
        //GC.Collect(); //수동으로 가비지컬렋터 작동
        // int a = 10; //스택 변수
        Student s = new Student(); // 힙 변수 
        s.Introduce();
        Student2 s2 = new Student2();
        s2.Introduce();
    }
}
