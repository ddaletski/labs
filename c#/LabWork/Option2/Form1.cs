using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;
using System.Windows.Forms.DataVisualization.Charting;

namespace Option2
{
    public partial class Form1 : Form
    {
        public List<string> listStr = new List<string>();
        public static Color c;
        public Form1()
        {
            InitializeComponent();
        }

        private void quitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void inputDataToolStripMenuItem_Click(object sender, EventArgs e)
        {
            listStr.Clear();

            OpenFileDialog dlg = new OpenFileDialog();
            dlg.FileName = "Data";
            dlg.DefaultExt = ".txt";
            dlg.Filter = "Text data base (.txt)|*.txt";
            DialogResult result = dlg.ShowDialog();

            if (result == DialogResult.OK)
            {
                foreach (string s in File.ReadAllLines(dlg.FileName))
                    listStr.Add(s);
            }
            
        }

        private void chooseToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Form2 f = new Form2();
            f.ShowDialog();
        }

        private void lineToolStripMenuItem_Click(object sender, EventArgs e)
        {
            chart1.Series.Clear();
            chart1.Series.Add("График");
            chart1.Series["График"].ChartType = SeriesChartType.Line;
            chart1.Series["График"].Color = c;
            foreach (string sxy in listStr)
            {
                string[] xy = sxy.Split(' ');
                chart1.Series["График"].Points.AddXY(Convert.ToDouble(xy[0]), Convert.ToDouble(xy[1]));
            }
        }

        private void barToolStripMenuItem_Click(object sender, EventArgs e)
        {
            chart1.Series.Clear();
            chart1.Series.Add("График");
            chart1.Series["График"].ChartType = SeriesChartType.Bar;
            chart1.Series["График"].Color = c;
            foreach (string sxy in listStr)
            {
                string[] xy = sxy.Split(' ');
                chart1.Series["График"].Points.AddXY(Convert.ToDouble(xy[0]), Convert.ToDouble(xy[1]));
            }
        }
    }
}
