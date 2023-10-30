using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _20231030
{
    internal class Program
    {
        static void Main(string[] args)
        {
            //indexer
            P p = new P();
            //Console.WriteLine(p[2]);

            Console.WriteLine();

            for (int i = 0; i < 10; i++)
                p[i] = i;
            p[0] = 100;
            p[11] = 1000;

            for (int i = 0; i < p.GetCount; ++i)
                Console.WriteLine(p[i]);

            Console.WriteLine();

            //Generic
            PrintValue(10);
            PrintValue(10.0f);
            PrintValue("10");

            Console.WriteLine();

            //boxing 
            object o1 = 10;
            object o2 = "two";
            //unboxing
            int n = (int)o1;
            string s = (string)o2;
            //Generic << 빠르고, 성능저하 들하고 
            n = Casting(3);
            s = Casting("Three");

            MonsterHP<int> hp_int = new MonsterHP<int>();
            hp_int.hp = 10;
            MonsterHP<string> hp_str = new MonsterHP<string>();
            hp_str.hp = "10";
            
            Console.WriteLine();

            //dynamic and default

            //where
            WhereStruct<Ref> rf = new WhereStruct<Ref>();
            
            Console.ReadLine();
        }


        // Generic
        static public void PrintValue<T>(T value)
        {
            Console.WriteLine($"{value}");
        }

        static public T Casting<T>(T value)
        {
            return value;
        }

        //dynamic and default
        //dynamic 그냥 형변형 짱짱하게 해주는애 
        static T SetArray<T>(T[] array)
        {
            T temp = default(T);
            for (int i = 0; i < array.Length; ++i)
                temp += (dynamic)array[i];
            return temp;
        }
    }

    class P
    {
        //프로퍼티
        int a = 0;
        public int A
        {
            get => a; 
            set => a = value;
        }

        //배열 프로퍼티 >> indexer
        /*int[] arr = { 1, 2, 3, 4, 5 };
        public int this[int i] //indexer
        {
            get { return arr[i]; }
            set { arr[i] = value; }
        }*/ //같은 자료형은 중복 불가. 다른 자료형만 여러개 가능 

        ArrayList arrayList = new ArrayList();
        public int GetCount => arrayList.Count;
        public int this[int i]
        {
            get 
            { 
                if (i >= 0 && i < arrayList.Count)
                    return (int)arrayList[i];
                return -1;

            }
            set 
            {
                if (i >= 0 && i < arrayList.Count)
                    arrayList[i] = value; 
                else if (i >= arrayList.Count)
                    arrayList.Add(value);
            }
        }
    }

    public class MonsterHP<T>
    {
        public T hp;
    }

    //Where
    class Ref
    {

    }

    class WhereStruct<T> where T : class
    {
        private T data;

        public WhereStruct()
        {
            data = default(T);
        }
    }

    interface II
    {
        void GetData();
    }

    class InterfaceClass : II
    {
        public void GetData()
        {
            Console.WriteLine("AAA");
        }
    }
}
