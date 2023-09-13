using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;
using System.Diagnostics;

namespace _20230913_Assignment
{
    internal class Program
    {
        static int num = 0;
        static int two = 0;
        static void Main(string[] args)
        {
            Stopwatch time = new Stopwatch();
            time.Start();
            Thread t1 = new Thread(Add1);
            Thread t2 = new Thread(Add2);
            Thread t3 = new Thread(Add3);

            t1.Start();
            t2.Start();
            t3.Start();
            t1.Join();
            t2.Join();
            t3.Join();
            time.Stop();
            Console.WriteLine($"멀티쓰레드\n값: {num}\n시간: {time.ElapsedMilliseconds}\n");

            time.Restart();
            time.Start();
            for (int i = 1; i <= 10000; i++)
                two += i;
            time.Stop();
            Console.WriteLine($"tldrmf쓰레드\n값: {two}\n시간: {time.ElapsedMilliseconds}");

            Console.ReadLine();
        }

        static void Add1()
        {
            for (int i = 1; i <= 3333; i++)
                num += i;
        }

        static void Add2()
        {
            for (int i = 3334; i <= 6666; i++)
                num += i;
        }

        static void Add3()
        {
            for (int i = 6667; i <= 10000; i++)
                num += i;
        }
    }
}
