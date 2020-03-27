public class PolygonTransform {

   // Returns a new array object that is an exact copy of the given array.
   // The given array is not mutated.
   public static double[] copy(double[] array) {
     return array.clone();
   }

   // Scales the polygon by the factor alpha.
   public static void scale(double[] x, double[] y, double alpha) {
     for (int i = 0; i < x.length; i++) {
       x[i] *= alpha;
       y[i] *= alpha;
     }
   }

   // Translates the polygon by (dx, dy).
   public static void translate(double[] x, double[] y, double dx, double dy) {
     for (int i = 0; i < x.length; i++) {
       x[i] += dx;
       y[i] += dy;
     }
   }

   // Rotates the polygon theta degrees counterclockwise, about the origin.
   public static void rotate(double[] x, double[] y, double theta) {
     for (int i = 0; i < x.length; i++) {
       double xi = x[i];
       double yi = y[i];

       x[i] = (xi * Math.cos(theta)) - (yi * Math.sin(theta));
       y[i] = (yi * Math.cos(theta)) + (xi * Math.sin(theta));
     }
   }

   // Tests each of the API methods by directly calling them.
   public static void main(String[] args) {

   }
}
