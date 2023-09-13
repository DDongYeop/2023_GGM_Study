using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;

namespace _20230913_TreadLifeCS
{
    static class Constants
    {
        public const int mainThread = 3;
        public const int workerThread = 10;
    }

    internal class Program
    {
        static void Main(string[] args)
        {
            Thread lifeThread = new Thread(CounterThread);
            lifeThread.Start();

            for (int i = 0; i < Constants.mainThread; i++)
            {
                Console.WriteLine($"메인 쓰레드 카운터: {i}");
                Thread.Sleep(5);
            }
            lifeThread.Join();
            Console.WriteLine("쓰레드가 종료됩니다.");
            Console.ReadLine();
        }

        private static void CounterThread()
        {
            for (int i = 0; i < Constants.workerThread; i++)
            {
                Console.WriteLine($"외부 쓰레드 카운터: {i}");
                Thread.Sleep(5);
            }
        }
    }
}
