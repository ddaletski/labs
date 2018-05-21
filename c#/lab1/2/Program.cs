using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _2
{
    class Program
    {

        static bool isInCircle(double x, double y, double r)
        {
            return x * x + y * y <= r * r;
        }

        static bool isInSector(double x, double y, bool neg=false)
        {
            double theta = Math.Atan(y / x);
            bool result = theta >= Math.PI / 4 && theta <= Math.PI / 2;
            if (neg)
                return !result;
            else
                return result;
        }

        static bool isInAim(double x, double y, double r)
        {
            return isInCircle(x, y, r) && (isInSector(x, y) || isInSector(-x, -y, true));
        }

        static void Main(string[] args)
        {
            Console.WriteLine("Enter radius: ");
            double radius = Convert.ToDouble(Console.ReadLine());


            for (int i = 0; i < 10; ++i)
            {
                Console.WriteLine("Enter x: ");
                double x = Convert.ToDouble(Console.ReadLine());

                Console.WriteLine("Enter y: ");
                double y = Convert.ToDouble(Console.ReadLine());

                Console.WriteLine("In aim: {0}", isInAim(x, y, radius));
            }
        }
    }
}
