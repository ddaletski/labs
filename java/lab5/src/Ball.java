import java.util.Iterator;

class DoubleIterator implements Iterator<Double> {
    private double[] _numbers;
    private int _idx;

    public DoubleIterator(double[] numbers) {
        _numbers = numbers;
        _idx = 0;
    }

    @Override
    public boolean hasNext() {
        return _idx < _numbers.length;
    }

    @Override
    public Double next() {
        return _numbers[_idx];
    }
}

public class Ball implements Body, Comparable<Ball>, Iterable<Double> {
    private double x;
    private double y;
    private double r;

    public Ball(double radius) {
        x = 0;
        y = 0;
        r = radius;
    }

    public Ball(double radius, double x, double y) {
        r = radius;
        this.x = x;
        this.y = y;
    }

    public double getArea() {
        return 4 * Math.PI * r * r;
    }

    public double getVolume() {
        return 4 * Math.PI * r * r * r / 3;
    }

    public int compareTo(Ball b) {
        if(r > b.r)
            return 1;
        else if (r < b.r)
            return -1;
        else
            return 0;
    }

    public Iterator<Double> iterator() {
        double[] numbers = {x, y, r};
        return new DoubleIterator(numbers);
    }

    public String toString() {
        return "" + x + "; " + y + "; " + r;
    }

    public static Ball fromString(String s) {
        return new Ball(0);
    }
}
