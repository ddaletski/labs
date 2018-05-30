using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab2
{
    public class Student
    {
        string name;
        UInt16 group;
        UInt16[] rating;

        public Student(string name, UInt16 group, UInt16[] rating)
        {
            Name = name;
            Group = group;
            Rating = rating;
        }

        public string Name
        {
            get { return name; }
            set { name = value; }
        }

        public ushort Group
        {
            get { return group; }
            set { group = value; }
        }

        public ushort[] Rating
        {
            get { return rating; }
            set {
                if (value.Length != 5)
                    throw new Exception("Wrong count of student marks");
                rating = value;
            }
        }

        /**********public***************/

        public override string ToString()
        {
            return string.Format("{0}, {1} group : ", name, group) + RatingToString();
        }

        /**********static***************/

        public static Student FromString(string s)
        {
            string[] splitted = s.Split(';');

            string name = splitted[0].Trim();
            UInt16 group = Convert.ToUInt16(splitted[1].Trim());
            UInt16[] rating = ParseRating(splitted[2]);

            Student stud = new Student(name, group, rating);
            return stud;
        }

        /**********private***************/

        private string RatingToString()
        {
            return String.Format("{0}, {1}, {2}, {3}, {4}", rating);
        }

        private static UInt16[] ParseRating(string s)
        {
            UInt16[] rating = new UInt16[5];
            string[] marksStr = s.Split(',');
            for(int i = 0; i < 5; ++i)
            {
                rating[i] = Convert.ToUInt16(marksStr[i]);
            }
            return rating;
        }
    }
}
