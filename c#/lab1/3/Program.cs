using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _3
{
    class Program
    {
        static double Taylor(double x, double eps)
        {
            double multiplier = 1 / x;
            double sum = 0;

            for(double i = 1; Math.Abs(multiplier) >= eps; ++i)
            {
                sum += multiplier;
                multiplier *= (i * 2 - 1) / (i * 2 + 1) / x / x;
            }
            return 2 * sum;
        }

        static double Library(double x)
        {
            return Math.Log((x + 1) / (x - 1));
        }


        static void Main(string[] args)
        {

            Console.WriteLine("Enter xmin: ");
            double xl = Convert.ToDouble(Console.ReadLine());

            Console.WriteLine("Enter xmax: ");
            double xr = Convert.ToDouble(Console.ReadLine());

            Console.WriteLine("Enter step size: ");
            double stepSize = Convert.ToDouble(Console.ReadLine());

            Console.WriteLine("Enter eps: ");
            double eps = Convert.ToDouble(Console.ReadLine());

            int steps = Convert.ToInt32(Math.Floor((xr - xl) / stepSize));

            List<string[]> table = new List<string[]>();
            table.Add(new[] { "x", "taylor", "library" });

            for(double i = 0; i <= steps; ++i)
            {
                double x = xl + stepSize * i;
                table.Add(new[] { Convert.ToString(x), Convert.ToString(Taylor(x, eps)), Convert.ToString(Library(x)) });
            }

            string result = tableView.ArrayPrinter.GetDataInTableFormat(table, "ln((1-x)/(1+x))");
            Console.WriteLine(result);
        }
    }
}
