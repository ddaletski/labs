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
    public partial class FormAddFromKeyboard : Form
    {
        public bool isClose;
        public bool isNew;
        private static Student student = new Student();

        public FormAddFromKeyboard()
        {
            InitializeComponent();
            isNew = false;
        }

        private void btnCancel_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void btnAdd_Click(object sender, EventArgs e)
        {
            bool isError = false;

            foreach (var item in this.Controls)
            {
                if (item is TextBox && (item as TextBox).Text == "")
                {
                    MessageBox.Show(
                    "Не все поля заполнены!",
                    "Ошибка",
                    MessageBoxButtons.OK,
                    MessageBoxIcon.Error,
                    MessageBoxDefaultButton.Button1);
                    isError = true;
                    break;
                }
            }

            if (!isError)
            {
                isNew = true;
                student.fullName = GetName();
                student.group = GetGroup();
                student.rating = GetGrades();
                this.Close();
            }
        }

        public Student GetStudent()
        {
            return student;
        }

        private string GetName()
        {
            return tbFullname.Text.ToString();
        }

        private ushort GetGroup()
        {
            ushort.TryParse(tbGroup.Text.ToString(), out ushort group);
            return group;
        }

        private ushort[] GetGrades()
        {
            ushort[] arr = new ushort[5];
            for (int i = 1; i < 6; i++)
            {
                ushort.TryParse((this.Controls.Find("tbGrade" + i, false).First() as TextBox).Text, out arr[i - 1]);
            }
            return arr;
        }

        private void tb_KeyPress(object sender, KeyPressEventArgs e)
        {
            char number = e.KeyChar;

            if (!Char.IsDigit(number))
            {
                e.Handled = true;
            }
        }
    }
}
