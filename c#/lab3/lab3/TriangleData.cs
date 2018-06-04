using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab3
{
    public class TriangleData
    {
        public TriangleData()
        {
            side1 = 1;
            side2 = 1;
            side3 = 1;
            calcArea = true;
            calcPerimeter = true;
        }

        double side1;
        double side2;
        double side3;

        public bool calcPerimeter;
        public bool calcArea;

        public double Side1
        {
            get { return side1; }
            set { side1 = CheckSide(value); }
        }

        public double Side2
        {
            get { return side2; }
            set { side2 = CheckSide(value); }
        }

        public double Side3
        {
            get { return side3; }
            set { side3 = CheckSide(value); }
        }

        public double Area()
        {
            double p = Perimeter() / 2;
            return Math.Sqrt(p * (p - side1) * (p - side2) * (p - side3));
        }

        public double Perimeter()
        {
            return side1 + side2 + side3;
        }
       
        private double CheckSide(double value) 
        {
            if (value <= 0)
            {
                throw new Exception("Сторона должна быть > 0");
            }
            return value;
        }
    }
}
