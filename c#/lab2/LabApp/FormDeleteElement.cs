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
    public partial class FormDeleteElement : Form
    {
        public int index = 0;
        public bool isDelete;

        public FormDeleteElement()
        {
            InitializeComponent();
            isDelete = false;
        }

        private void btnCancel_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void btnDelete_Click(object sender, EventArgs e)
        {
            bool isError = false;

            foreach (var item in this.Controls)
            {
                if (item is TextBox && (item as TextBox).Text == "")
                {
                    MessageBox.Show(
                    "Введите индекс элемента!",
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
                isDelete = true;
                index = Convert.ToUInt16(textBox1.Text);
                this.Close();
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
    }
}
