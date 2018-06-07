using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab5
{
    class Egg
    {
        public double x = 0.5;
        public double y = 0;
        public Egg(double x_, double y_)
        {
            x = x_;
            y = y_;
        }
    }

    class HenEgg : Egg
    {
        public HenEgg(double x_, double y_) : base(x_, y_) { }
    }
    class CuckooEgg : Egg
    {
        public CuckooEgg(double x_, double y_) : base(x_, y_) { } 
    }

    interface IBrood
    {
        Egg NewEgg();
    }

    abstract class Bird
    {
        abstract public void Move(double x, double y);
        public double x = 0.5;
        public double y;
        public double size = 0.1;
    }

    class Cock : Bird
    {
        public override void Move(double x, double y)
        {
            this.x = Math.Min(Math.Max(this.x + x, 0), 1-this.size);
        }
    }

    class Hen : Bird
    {
        public override void Move(double x, double y)
        {
            this.x = Math.Min(Math.Max(this.x + x, 0), 1-this.size);
        }
    }

    class BroodHen : Hen, IBrood
    {
        public Egg NewEgg()
        {
            return new HenEgg(x, y);
        }
    }

    class Cuckoo : Bird, IBrood
    {
        public override void Move(double x, double y)
        {
            this.x = Math.Min(Math.Max(this.x + x, 0), 1-this.size);
            this.y = Math.Min(Math.Max(this.y + y, 0), 1-this.size);
        }

        public Egg NewEgg()
        {
            return new CuckooEgg(x, y);
        }
    }
}
