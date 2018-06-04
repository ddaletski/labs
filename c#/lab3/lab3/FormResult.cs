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
    public partial class FormResult : Form
    {
        public FormResult()
        {
            InitializeComponent();
        }

        public void SetTriangle(TriangleData triangle)
        {
            triangleData = triangle;
            textBox1.Text = Convert.ToString(triangleData.Side1);
            textBox2.Text = Convert.ToString(triangleData.Side2);
            textBox3.Text = Convert.ToString(triangleData.Side3);

            if (triangleData.calcPerimeter)
                textBox4.Text = Convert.ToString(triangleData.Perimeter());
            else
                textBox4.Text = " - ";


            if (triangleData.calcArea)
                textBox5.Text = Convert.ToString(triangleData.Area());
            else
                textBox5.Text = " - ";
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Close();
        }

        private TriangleData triangleData;
    }
}
