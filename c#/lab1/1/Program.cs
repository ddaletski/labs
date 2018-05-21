using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _1
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Enter radius: ");
            double radius = Convert.ToDouble(Console.ReadLine());

            Console.WriteLine("Enter step: ");
            double stepSize = Convert.ToDouble(Console.ReadLine());

            double left = -3 * radius;
            double right = 3 * radius;

            List<Func<double, double>> funcs = new List<Func<double, double>>();
            funcs.Add(
                x =>
                {
                    double x_ = x + 2 * radius;
                    double theta = Math.Acos(x_ / radius);
                    double y = -radius * Math.Sin(theta);
                    return y;
                }
            );
            funcs.Add (
                x =>
                {
                    double x_ = x + 2 * radius;
                    double y = x_ - radius;
                    return y;
                }
            );
            funcs.Add(
                x =>
                {
                    double theta = Math.Acos(x / radius);
                    double y = radius * Math.Sin(theta);
                    return y;
                }
            );
            funcs.Add( x => radius - x );
            funcs.Add(
                x =>
                {
                    double x_ = x - radius;
                    double y = x_ / 2;
                    return y;
                }
            );
            funcs.Add(
                x =>
                {
                    double x_ = x - radius;
                    double y = x_ / 2;
                    return y;
                }
            );


            List<string[]> strings = new List<string[]>();
            strings.Add(new[] { "x", "y"});

            for (int i = 0; i <= (right-left) / stepSize; i++)
            {
                double x = left + i * stepSize;
                int funcIdx = Math.Min(Convert.ToInt32(Math.Floor((x - left) / radius)), funcs.Count()-1);
                double y = Math.Round(funcs[funcIdx](x), 3);

                string[] kv = { Convert.ToString(x), Convert.ToString(y) };
                strings.Add(kv);
            }

            Console.WriteLine(tableView.ArrayPrinter.GetDataInTableFormat(strings, "Value table"));
        }
    }
}
