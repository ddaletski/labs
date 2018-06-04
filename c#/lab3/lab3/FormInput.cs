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
    public partial class FormInput : Form
    {
        public FormInput()
        {
            InitializeComponent();
        }

        public void SetTriangle(TriangleData triangle) {
            triangleData = triangle;
            textBox1.Text = Convert.ToString(triangleData.Side1);
            textBox2.Text = Convert.ToString(triangleData.Side2);
            textBox3.Text = Convert.ToString(triangleData.Side3);
            checkBox1.Checked = triangleData.calcPerimeter;
            checkBox2.Checked = triangleData.calcArea;
        }

    private void label1_Click(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            try
            {
                triangleData.Side1 = Convert.ToDouble(textBox1.Text);
                triangleData.Side2 = Convert.ToDouble(textBox2.Text);
                triangleData.Side3 = Convert.ToDouble(textBox3.Text);
                triangleData.calcPerimeter = checkBox1.Checked;
                triangleData.calcArea = checkBox2.Checked;
                Close();
            }
            catch (Exception exc)
            {
                MessageBox.Show(exc.Message);
            }
        }

        private TriangleData triangleData;
    }
}
