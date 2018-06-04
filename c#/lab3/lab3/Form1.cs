using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace lab3
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            inputForm = new FormInput();
            triangle = new TriangleData();
            inputForm.SetTriangle(triangle);
            resultForm = new FormResult();
        }

        private void inputToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }

        private void inputToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            inputForm.ShowDialog();
        }

        private void calcToolStripMenuItem_Click(object sender, EventArgs e)
        {
            resultForm.SetTriangle(triangle);
            resultForm.Show();
        }

        private FormInput inputForm;
        private FormResult resultForm;
        private TriangleData triangle;

        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Close();
        }
    }
}
