
public class Sierpinski
{
    // Height of an equilateral triangle whose sides are of the specified length.
    public static double height(double length) {
        return 0;
    }

    // Draws a filled equilateral triangle whose bottom vertex is (x, y)
    // of the specified side length.
    public static void filledTriangle(double x, double y, double length) {

    }

    // Draws a Sierpinski triangle of order n, such that the largest filled
    // triangle has bottom vertex (x, y) and sides of the specified length.
    public static void sierpinski(int n, double x, double y, double length) {

    }

    // Takes an integer command-line argument n;
    // draws the outline of an equilateral triangle (pointed upwards) of length 1;
    // whose bottom-left vertex is (0, 0) and bottom-right vertex is (1, 0); and
    // draws a Sierpinski triangle of order n that fits snugly inside the outline.
    public static void main(String[] args) {

    }
    // public static void filledTriangle(double x, double y, double s)
    // {
    //     double[] xCoords = new double[]
    //     {
    //         x -
    //     };

    //     // StdDraw.fill

    //     // double[] xl = new double[4];
    //     // xl[0] = x - s/2; xl[1]= x + s/2;  xl[2]  = x; xl[3] = x-s/2;
    //     // double[] yl = new double[4];
    //     // yl[0] =Math.sqrt(3)/2*s+y; yl[1] = yl[0]; yl[2] = y; yl[3] = yl[0];
    //     // StdDraw.filledPolygon(xl,yl);
    // }
    // public static void sierpinski(int n, double x, double y, double s)
    // {
    //     if(n == 0)
    //     {
    //         return;
    //     }
    //     filledTriangle(x, y, s);
    //     sierpinski(n-1, x - s/2, y, s/2);
    //     sierpinski(n-1, x + s/2, y, s/2);
    //     sierpinski(n-1, x, y+Math.sqrt(3)/2*s, s/2);
    // }

    // public static void main(String[] args)
    // {
    //     int n = Integer.parseInt(args[0]);

    //     StdDraw.line(0,0, 1,0);
    //     StdDraw.line(1,0, 0.5, Math.sqrt(3)/2);
    //     StdDraw.line(0.5, Math.sqrt(3)/2, 0, 0);
    //     sierpinski(n,  0.5, 0,0.5);;
    // }
}
