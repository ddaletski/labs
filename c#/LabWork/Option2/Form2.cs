using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Option2
{
    public partial class Form2 : Form
    {
        public Form2()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
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
            if (radioButton1.Checked == true)
            {
                (Application.OpenForms["Form1"].Controls["menuStrip1"] as MenuStrip).Items[2].Enabled = true;
                (Application.OpenForms["Form1"].Controls["menuStrip1"] as MenuStrip).Items[3].Enabled = false;
                this.Close();
            }
            else
            {
                (Application.OpenForms["Form1"].Controls["menuStrip1"] as MenuStrip).Items[2].Enabled = false;
                (Application.OpenForms["Form1"].Controls["menuStrip1"] as MenuStrip).Items[3].Enabled = true;
                this.Close();
            }
        }

        private void Form2_Load(object sender, EventArgs e)
        {
            listBox1.SetSelected(0, true);
        }
    }
}
