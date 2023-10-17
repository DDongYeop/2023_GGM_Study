using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CSharp
{
    internal class Program
    {
        static void Main(string[] args)
        {
            // decimal << 고정소수  
            decimal pi = 3.141592653589793238462643383279m; //16바이트 짜리 뒤에 m붙여야함 
            string decimalStr = pi.ToString();
            int decimalInt = int.Parse(decimalStr); //Parse << 정수형, 부동소수 친구들에게 다 있다 
            Console.WriteLine(pi);

            //Literal
            /*
            10진수 표기     : 그냥 숫자 123
            16진수 표기     : 0x12
            8진수 표기      : 012
            int, long       : 그냥 숫자 111
            unsigned int    : 1111u
            unsigned long   : 1111ul
            double          : 그냥 소수 2.11
            float           : 111.1f
            decimal         : 111.1m
            */ 

            // Nullable
            double? d = 3.14; //뒤에 ? 붙여주면 널 넣을 수 있다. 
            d = null;
            Console.WriteLine(d.HasValue); //HasValue == 값 존재하는지 안 하는지 | Value == 값 출력 < 비어있으면 출력 안됨

            //boxing unboxing
            int boxingINT = 111;
            object boxing = boxingINT;
            int unboxing = (int)boxingINT;
            Console.WriteLine($"boxingINT: {boxingINT}   boxing: {boxing}");
            Console.WriteLine(object.ReferenceEquals(boxingINT, unboxing));

            //this, base
            //this << 자신의 클래스
            //base << 부모의 클래스 

            Console.ReadLine();
        }
    }
}
