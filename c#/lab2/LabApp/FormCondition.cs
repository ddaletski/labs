using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace LabApp
{
    public partial class FormCondition : Form
    {
        private List<Student> students;

        public FormCondition(List<Student> students)
        {
            InitializeComponent();
            this.students = students;
            this.cbOperation.SelectedIndex = 2;
        }

        private void tb_KeyPress(object sender, KeyPressEventArgs e)
        {
            char number = e.KeyChar;

            if (!Char.IsDigit(number))
            {
                e.Handled = true;
            }
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {
            SearchByCondition();
        }

        private void SearchByCondition()
        {
            if (tbGroup.Text != "")
            {
                int operation = cbOperation.SelectedIndex;
                switch (operation)
                {
                    case 0:
                        Print(students.Where(i => i.group < Convert.ToUInt16(tbGroup.Text)).ToList());
                        break;
                    case 1:
                        Print(students.Where(i => i.group <= Convert.ToUInt16(tbGroup.Text)).ToList());
                        break;
                    case 2:
                        Print(students.Where(i => i.group == Convert.ToUInt16(tbGroup.Text)).ToList());
                        break;
                    case 3:
                        Print(students.Where(i => i.group >= Convert.ToUInt16(tbGroup.Text)).ToList());
                        break;
                    case 4:
                        Print(students.Where(i => i.group > Convert.ToUInt16(tbGroup.Text)).ToList());
                        break;
                    default:
                        break;
                }
            }
        }

        private void Print(List<Student> students)
        {
            rtbCollection.Clear();
            if (students.Count > 0)
                foreach (var item in students)
                {
                    rtbCollection.Text += "Fullname: " + item.fullName + "\n";
                    rtbCollection.Text += "Group: " + item.group + "\n";
                    rtbCollection.Text += "Grade:";
                    for (int i = 0; i < item.rating.Length; i++)
                    {
                        rtbCollection.Text += " " + item.rating[i];
                    }
                    rtbCollection.Text += "\n\n";
                }
        }

        private void cbOperation_SelectedIndexChanged(object sender, EventArgs e)
        {
            SearchByCondition();
        }

        private void btnClose_Click(object sender, EventArgs e)
        {
            this.Close();
        }
    }
}
