using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LabApp
{
    public struct Student
    {
        public string fullName;
        public ushort group;
        public ushort[] rating;
        public double meanRating()
        {
            double sum = 0;
            for(int i = 0; i < 5; ++i)
            {
                sum += rating[i];
            }
            return sum / rating.Length;
        }
    };
}
