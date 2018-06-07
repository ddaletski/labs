using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;

namespace lab5
{
    class Utils
    {
        public static Rectangle RelativeRect(Rectangle r, float xleft, float ybottom, float size)
        {
            float minDim = Math.Min(r.Width, r.Height) * size;
            int y = Convert.ToInt32(r.Bottom - ybottom * r.Height - minDim);
            int x = Convert.ToInt32(r.Left + xleft * r.Width);
            int w = Convert.ToInt32(minDim);
            int h = w;

            return new Rectangle( x, y, w, h );
        }
    }

    public abstract class Egg
    {
        public float y = 0;
        public float x = 0.5f - 0.05f; 
        public float size = 0.1f;
        public Egg(float x_, float y_)
        {
            x = x_;
            y = y_;
        }

        public abstract void Draw(ref Graphics g, Rectangle rect);
    }

    public class HenEgg : Egg
    {
        public Image img;
        public HenEgg(float x_, float y_) : base(x_, y_)
        {
            img = Image.FromFile("eggs.png");
        }
        public override void Draw(ref Graphics g, Rectangle rect)
        {
            g.DrawImage(img, Utils.RelativeRect(rect, x, y, size));
        }

        public float progress = 0;
        public void Sit()
        {
            progress = Math.Min(progress+0.4f, 1.0f);
        }
    }

    interface ILayer
    {
        Egg LayEgg();
    }

    public abstract class Bird
    {
        abstract public void Move(float x, float y);
        public float x = 0.4f;
        public float y;
        public float size = 0.2f;
        public bool right = false;
        public string left_img_path;
        public string right_img_path;
        public Image image_left;
        public Image image_right;
        abstract public string Sing();

        public void Draw(ref Graphics g, Rectangle rect)
        {
            if (right)
                g.DrawImage(image_right, Utils.RelativeRect(rect, x, y, size));
            else
                g.DrawImage(image_left, Utils.RelativeRect(rect, x, y, size));
        }

        public void ChangeDirection(float x)
        {
            if (x < 0)
                right = false;
            else
                right = true;
        }

        public void LoadImages()
        {
            image_left = Image.FromFile(left_img_path);
            image_right = Image.FromFile(right_img_path);
        }
    }

    public class Cock : Bird
    {
        public Cock()
        {
            left_img_path = "cock_left.png";
            right_img_path = "cock_right.png";
            LoadImages();
        }
        public override void Move(float x, float y)
        {
            ChangeDirection(x);
            this.x = Math.Min(Math.Max(this.x + x, 0), 1-this.size);
        }
        override public string Sing()
        {
            return "Кукареку";
        }
    }

    public class Hen : Bird, ILayer
    {
        public Hen()
        {
            left_img_path = "hen_left.png";
            right_img_path = "hen_right.png";
            LoadImages();
        }
        public override void Move(float x, float y)
        {
            ChangeDirection(x);
            this.x = Math.Min(Math.Max(this.x + x, 0), 1-this.size);
        }
        public Egg LayEgg()
        {
            return new HenEgg(x, y);
        }
        override public string Sing()
        {
            return "Ко ко ко";
        }
    }

    public class SitterHen : Hen, ILayer
    {
        public SitterHen()
        {
            left_img_path = "sitter_left.png";
            right_img_path = "sitter_right.png";
            LoadImages();
        }
        public void Sit(HenEgg egg)
        {
            left_img_path = "sitter_left_sit.png";
            right_img_path = "sitter_right_sit.png";
            LoadImages();
            egg.Sit();
        }
        public void Stand()
        {
            left_img_path = "sitter_left.png";
            right_img_path = "sitter_right.png";
            LoadImages();
        }
    }

    public class Cuckoo : Bird
    {
        public Cuckoo()
        {
            left_img_path = "cuckoo_left.png";
            right_img_path = "cuckoo_right.png";
            LoadImages();
        }
        public override void Move(float x, float y)
        {
            ChangeDirection(x);
            this.x = Math.Min(Math.Max(this.x + x, 0), 1-this.size);
            this.y = Math.Min(Math.Max(this.y + y, 0), 1-this.size);
        }

        override public string Sing()
        {
            return "ку-ку";
        }
        
    }
}
