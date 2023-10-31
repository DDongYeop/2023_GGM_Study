using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _20231031
{
    internal class Program
    {
        static void Main(string[] args)
        {
            //delegate
            OnGet onGet = CallGet;
            onGet = (str) => { Console.WriteLine($"이것이 람다다 희망편 : {str}"); };
            onGet("델리게이트 시러요");

            OnSet onSet = CallSet;
            onSet = (value) => { return value + value; };
            Console.WriteLine(onSet(10));

            Console.WriteLine();

            //List FIndAll from lambda
            List<int> listDB = new List<int> { 1, 2, 3, 100, 200, 300 };
            List<int> listFindAall = listDB.FindAll((i) => { return i < 100; });
            foreach(int i in listFindAall)
                Console.WriteLine($"a: {i}");

            Console.WriteLine();

            //Action
            Action action;
            action = CallAction;
            action();

            Console.ReadLine();
        }

        //Lambda
        //매개변수와 리턴
        //() => { return  }

        //delegate
        //대리자 | 함수를 들고 있다 답 해주는 
        delegate void OnGet(string str);
        delegate int OnSet(int a);

        static public void CallGet(string str)
        {
            Console.WriteLine(str);
        }

        static public int CallSet(int a)
        {
            return a + a;
        }

        //Action
        public static void CallAction()
        {
            Console.WriteLine("Action");
        }
    }
}
