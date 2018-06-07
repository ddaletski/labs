using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Option3
{
    public partial class Form2 : Form
    {
        public Form2()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Form1.a = Convert.ToDouble(textBox1.Text);
            Form1.Xmin = Convert.ToDouble(textBox2.Text);
            Form1.Xmax = Convert.ToDouble(textBox3.Text);
            switch (listBox1.SelectedIndex)
            {
                case 0:
                    Form1.c = Color.Blue;
                    break;
                case 1:
                    Form1.c = Color.Black;
                    break;
                case 2:
                    Form1.c = Color.Red;
                    break;
                case 3:
                    Form1.c = Color.Green;
                    break;
            }
            switch (listBox2.SelectedIndex)
            {
                case 0:
                    if(Form1.Xmin * Form1.a <= 0 && Form1.Xmax * Form1.a >= 0)
                    {
                        MessageBox.Show("Invalid range or param 'a' for this function");
                        return;
                    }
                    Form1.f = 0;
                    break;
                case 1:
                    if((Form1.Xmin + Form1.a <= 0 && Form1.Xmax + Form1.a >= 0))
                    {
                        MessageBox.Show("Invalid range or param 'a' for this function");
                        return;
                    }
                    Form1.f = 1;
                    break;
                case 2:
                    if((Form1.Xmin + Form1.a <= 0 && Form1.Xmax + Form1.a >= 0)
                        || (Form1.Xmin + Form1.a <= 1 && Form1.Xmax + Form1.a >= 1))
                    {
                        MessageBox.Show("Invalid range or param 'a' for this function");
                        return;
                    }
                    Form1.f = 2;
                    break;
                case 3:
                    if(Form1.Xmin * Form1.a <= 0 && Form1.Xmax * Form1.a >= 0)
                    {
                        MessageBox.Show("Invalid range or param 'a' for this function");
                        return;
                    }
                    Form1.f = 3;
                    break;
            }
            (Application.OpenForms["Form1"].Controls["menuStrip1"] as MenuStrip).Items[1].Enabled = true;

            this.Close();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void Form2_Load(object sender, EventArgs e)
        {

        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void textBox1_KeyDown(object sender, KeyEventArgs e)
        {
        }
    }
}
