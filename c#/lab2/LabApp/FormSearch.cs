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
    public partial class FormSearch : Form
    {
        private List<Student> students;

        public FormSearch(List<Student> students)
        {
            InitializeComponent();
            this.students = students;
            rbFullname.Checked = true;
            tbGrade.Visible = false;
            tbGroup.Visible = false;
        }

        private void rb_CheckedChanged(object sender, EventArgs e)
        {
            if (rbFullname.Checked)
            {
                tbFullname.Visible = true;
                tbGrade.Visible = false;
                tbGroup.Visible = false;
            }
            else if (rbGrade.Checked)
            {
                tbFullname.Visible = false;
                tbGrade.Visible = true;
                tbGroup.Visible = false;
            }
            else
            {
                tbFullname.Visible = false;
                tbGrade.Visible = false;
                tbGroup.Visible = true;
            }
        }

        private void tb_KeyPress(object sender, KeyPressEventArgs e)
        {
            char number = e.KeyChar;

            if (!Char.IsDigit(number))
            {
                e.Handled = true;
            }
        }

        private void tbGrade_TextChanged(object sender, EventArgs e)
        {
            if (tbGrade.Text != "")
                Print(students.Where(i => i.rating[0] == Convert.ToUInt16(tbGrade.Text)).ToList());
        }

        private void tbGroup_TextChanged(object sender, EventArgs e)
        {
            if (tbGroup.Text != "")
                Print(students.Where(i => i.group == Convert.ToUInt16(tbGroup.Text)).ToList());
        }

        private void tbFullname_TextChanged(object sender, EventArgs e)
        {
            if (tbFullname.Text != "")
                Print(students.Where(i => i.fullName == tbFullname.Text).ToList());
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

        private void btnClose_Click(object sender, EventArgs e)
        {
            this.Close();
        }
    }
}
