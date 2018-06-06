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
    public partial class Form1 : Form
    {
        int x;
        int y;
        public bool stop = true;
        public bool top = true;
        public bool left = true;
        public int speed = 20;
        public Form1()
        {
            InitializeComponent();
        }

        private void quitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        public void Draw(int x, int y)
        {            
            Graphics g = this.CreateGraphics();
            g.Clear(Color.White);

            Pen blackPen = new Pen(Color.Black, 1);

            //морда
            Rectangle rect1 = new Rectangle(x - 10, y - 10, 20, 20);
            g.DrawEllipse(blackPen, rect1);

            //левый глаз
            Rectangle rect2 = new Rectangle(x - 5, y - 4, 3, 3);
            g.DrawEllipse(blackPen, rect2);

            //правый глаз
            Rectangle rect3 = new Rectangle(x + 2, y - 4, 3, 3);
            g.DrawEllipse(blackPen, rect3);

            //рот
            Rectangle rect4 = new Rectangle(x - 5, y + 2, 10, 5);
            float startAngle = 180.0F;
            float sweepAngle = 180.0F;
            g.DrawArc(blackPen, rect4, startAngle, sweepAngle);

        }

        private void showPictureToolStripMenuItem_Click(object sender, EventArgs e)
        {

            Draw(this.Width / 2, (this.Height - 30) / 2 + 30);
        }

        private void animateToolStripMenuItem_Click(object sender, EventArgs e)
        {
            //Width = 430;
            //Height = 400;
            if (stop)
            {
                stop = false;
                x = this.Width / 2;
                y = (this.Height - 30) / 2 + 30;
                Animate(top, left, x, y, true);
            }
        }

        public void Animate(bool top, bool left, int hor, int ver, bool repeate)
        {
            x = hor;
            y = ver;
            Timer timer = new Timer();
            timer.Interval = speed;
            int count = 0;
            int max = 100;
            timer.Tick += new EventHandler((o, ev) =>
            {
                if (stop)
                {
                    timer.Stop();
                }

                if (left)
                    x = (int)(hor - count * ((this.Width / 2) / 100.0));
                else
                    x = (int)(hor + count * ((this.Width / 2) / 100.0));
                if (top)
                    y = (int)(ver - count * ((this.Height / 2 - 15) / 100.0));
                else
                    y = (int)(ver + count * ((this.Height / 2 - 15) / 100.0));

                Draw(x, y);                
                count++;
                /*
                if (top && (y < 0 || y > this.Height / 2 - 20) ||
                    !top && (y < this.Height - 20 || y > this.Height / 2 - 20) ||
                    left && (x < 0 || x > this.Width / 2 - 20) ||
                    !left && (x < this.Width - 20 || x > this.Width / 2 - 20)) 
                */
                if (count > 3 && (x < 10 || x > this.Width - 10 || y < 40 || y > this.Height - 10)) 
                {
                    count = 0;

                    if (left)
                        x += (int)((this.Width / 2 ) / 100.0);
                    else
                        x -= (int)((this.Width / 2 ) / 100.0);
                    if (top)
                        y += (int)((this.Height / 2 - 15) / 100.0);
                    else
                        y -= (int)((this.Height / 2 - 15) / 100.0);

                    timer.Stop();
                    if (repeate)
                        Animate(!top, !left, x, y, true);
                }
            });
            timer.Start();
        }

        private void stopToolStripMenuItem_Click(object sender, EventArgs e)
        {
            stop = true;
        }

        private void chooseToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Form2 f2 = new Form2();
            f2.f1 = this;
            f2.ShowDialog();
        }
    }
}
