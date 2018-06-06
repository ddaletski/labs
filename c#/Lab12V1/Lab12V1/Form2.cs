using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace Lab12V1
{
    public partial class Form2 : Form
    {
        public Form1 f1;
        public Form2()
        {
            InitializeComponent();
        }

        private void Form2_Load(object sender, EventArgs e)
        {

        }

        private void textBox1_KeyPress(object sender, KeyPressEventArgs e)
        {
            if ((e.KeyChar < 48 || e.KeyChar >= 59) && e.KeyChar != 8)
                e.Handled = true;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            f1.speed = 1000 / Convert.ToInt32(textBox1.Text);
            if (f1.speed == 0)
                f1.speed = 1;
            if (f1.stop)
            {
                f1.stop = false;
                f1.Animate(radioButton1.Checked, radioButton4.Checked, f1.Width / 2, (f1.Height - 30) / 2 + 30, true);

                this.Close();
            }
        }
    }
}
