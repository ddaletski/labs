using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace lab5
{
    public partial class Form2 : Form
    {
        public int index = 0;
        public Form2()
        {
            InitializeComponent();
        }

        private void groupBox1_Enter(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (radioButton1.Checked)
                index = 0;
            if (radioButton2.Checked)
                index = 1;
            if (radioButton3.Checked)
                index = 2;
            if (radioButton4.Checked)
                index = 3;
            Close();
        }
    }
}
