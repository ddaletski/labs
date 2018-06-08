using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Threading;

namespace lab5
{
    public partial class Form1 : Form
    {
        public Graphics g;
        public Bird currentBird;
        public List<Egg> eggs;

        float DistanceToEgg(ref Bird b, Egg e)
        {
            return Math.Abs((b.x + b.size / 2) - (e.x + e.size / 2));
        }

        int ClosestEgg(ref Bird b)
        {
            if (eggs.Count == 0)
                return -1;

            int closest = 0;
            float distance = DistanceToEgg(ref b, eggs[0]);
            for(int i = 1; i < eggs.Count; ++i)
            {
                float d = DistanceToEgg(ref b, eggs[i]);
                if(d < distance)
                {
                    distance = d;
                    closest = i;
                }
            }

            if (distance < b.size / 2)
                return closest;
            else
                return -1;
        }

        public Form1()
        {
            InitializeComponent();
            eggs = new List<Egg>();
            g = this.CreateGraphics();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
        }

        public void Redraw()
        {
            g.Clear(Color.White);
            for(int i = 0; i < eggs.Count; ++i)
            {
                eggs[i].Draw(ref g, this.ClientRectangle);
            }
            try
            {
                currentBird.Draw(ref g, this.ClientRectangle);
            }
            catch (Exception) { }
        }

        private void Form1_Click(object sender, EventArgs e)
        {
        }


        private void Form1_SizeChanged(object sender, EventArgs e)
        {
            g = this.CreateGraphics();
            Redraw();
        }

        private void выбратьПтицуToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Form2 form2 = new Form2();
            form2.ShowDialog();
            switch(form2.index)
            {
                case 0:
                    {
                        currentBird = new Cuckoo();
                        break;
                    }
                case 1:
                    {
                        currentBird = new Cock();
                        break;
                    }
                case 2:
                    {
                        currentBird = new Hen();
                        break;
                    }
                case 3:
                    {
                        currentBird = new SitterHen();
                        break;
                    }
            }
            Redraw();
        }

        private void Form1_KeyDown(object sender, KeyEventArgs e)
        {
            try
            {
                var kdata = e.KeyData;
                switch (kdata)
                {
                    case Keys.Return:
                        string song = currentBird.Sing();
                        MessageBox.Show(song);
                        break;
                    case Keys.Left:
                        currentBird.Move(-0.05f, 0);
                        break;
                    case Keys.Right:
                        currentBird.Move(0.05f, 0);
                        break;
                    case Keys.Up:
                        currentBird.Move(0, 0.05f);
                        break;
                    case Keys.Down:
                        currentBird.Move(0, -0.05f);
                        try
                        {
                            int closest = ClosestEgg(ref currentBird);
                            if (closest < 0)
                                break;
                            (currentBird as SitterHen).Sit(eggs[closest] as HenEgg);
                            Redraw();
                            Thread.Sleep(500);
                            (currentBird as SitterHen).Stand();
                            Redraw();
                            if ((eggs[closest] as HenEgg).progress == 1)
                            {
                                eggs.RemoveAt(closest);
                            }
                        }
                        catch (Exception) { }
                        break;
                    case Keys.Space:
                        try
                        {
                            eggs.Add((currentBird as ILayer).LayEgg());
                        }
                        catch (Exception) { }
                        break;
                }
            }
            catch (Exception) { }
            Redraw();
        }
    }
}
