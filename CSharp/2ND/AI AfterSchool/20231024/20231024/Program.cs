using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _20231024
{
    internal class Program
    {
        static void Main(string[] args)
        {
            //Collection

            //Arraylist
            Console.WriteLine("\nArrayList");
            ArrayList arrayList = new ArrayList();
            arrayList.Add("Hello Dongyeop");
            arrayList.Add(10.0f);
            foreach (var i in arrayList)
                Console.WriteLine(i);

            Console.WriteLine();

            int[] arrData = { 10, 20, 30 };
            ArrayList arrayList1 = new ArrayList(arrData);
            foreach (var i in arrayList1)
                Console.WriteLine(i);

            //Queue
            Console.WriteLine("\nQueue");
            Queue queue = new Queue();
            queue.Enqueue('a');
            for (int i = 0; i < 10; i++)
                queue.Enqueue(i);
            while (queue.Count > 0)
            {
                Console.WriteLine(queue.Peek()); //앞값 줌
                queue.Dequeue(); //앞값 주면서 삭제
            }

            //Stack
            Console.WriteLine("\nStack");
            Stack stack = new Stack();
            stack.Push('a');
            for (int i = 0; i < 10; i++)
                stack.Push(i);
            while (stack.Count > 0)
            {
                Console.WriteLine(stack.Peek()); //앞값 줌
                stack.Pop(); //앞값 주면서 삭제
            }

            //HashTable
            Console.WriteLine("\nHashTable");
            Hashtable hashtable = new Hashtable();
            hashtable.Add("key", "value");
            hashtable["key2"] = 10;
            foreach (var i in hashtable.Keys)
                Console.WriteLine(i);
            foreach (var i in hashtable.Values)
                Console.WriteLine(i);

            Console.ReadLine();
        }
    }
}
