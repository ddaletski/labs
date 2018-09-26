
public class NonLinearEquation {
    /*
    Non-linear equation prior to (x, y) of kind "ax + bxy + cy - d = 0"
     */


    public class Solution {
        /* equation solution */
        public double x;
        public double y;
    };


    public NonLinearEquation (double a, double b, double c, double d) {
        this.a = a;
        this.b = b;
        this.c = c;
        this.d = d;
    }

    public Solution solve() {
        Solution solution;

        return solution;
    }

    private double a, b, c, d;
}
