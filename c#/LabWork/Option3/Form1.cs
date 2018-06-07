using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Windows.Forms.DataVisualization.Charting;

namespace Option3
{
    public partial class Form1 : Form
    {
        public static Color c;
        public static int f;
        public static double a = 1;
        public static double Xmin = -Math.PI / 2;
        public static double Xmax = Math.PI / 2;

        public Form1()
        {
            InitializeComponent();
        }

        private void quitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void buildToolStripMenuItem_Click(object sender, EventArgs e)
        {
            chart1.Series.Clear();
            chart1.Series.Add("func");
            chart1.Series["func"].ChartType = SeriesChartType.Line;
            chart1.Series["func"].Color = c;

            double Step = (Xmax - Xmin) / 10;

            int count = (int)Math.Ceiling((Xmax - Xmin) / Step) + 1;

            double[] x = new double[count];
            double[] y = new double[count];

            for (int i = 0; i < count; i++)
            {
                x[i] = Xmin + Step * i;
                switch (f)
                {
                    case 0:
                        y[i] = Math.Log(x[i] * a);
                        chart1.Series["func"].LegendText = "ln(ax)";
                        break;
                    case 1:
                        y[i] = Math.Log(x[i] + a);
                        chart1.Series["func"].LegendText = "ln(a+x)";
                        break;
                    case 2:
                        y[i] = 1.0 / Math.Log(x[i] + a);
                        chart1.Series["func"].LegendText = "1/ln(a+x)";
                        break;
                    case 3:
                        y[i] = Math.Pow(Math.Log(x[i] * a), 2);
                        chart1.Series["func"].LegendText = "ln^2(ax)";
                        break;
                }
                
            }

            chart1.ChartAreas[0].AxisX.Minimum = Xmin;
            chart1.ChartAreas[0].AxisX.Maximum = Xmax;

            chart1.ChartAreas[0].AxisX.MajorGrid.Interval = Step;

            chart1.Series[0].Points.DataBindXY(x, y);
        }

        private void chartToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Form2 form = new Form2();
            form.ShowDialog();
        }

        private void clearToolStripMenuItem_Click(object sender, EventArgs e)
        {
            chart1.Series.Clear();
        }

        private void aboutToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Form3 form = new Form3();
            form.ShowDialog();
        }
    }
}
