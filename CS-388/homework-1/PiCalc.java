public class PiCalc {
  public static void main(String[] args) {
    double pi = 4.0; // starting value in series
    double divisor = 3.0; // starting divisor

    for (int i = 1; i < 200000; i++) {
      if (i % 2 != 0) { // odd iteration
        pi -= (4.0 / divisor);
        divisor += 2;
      } else { // even iteration
        pi += (4.0 / divisor);
        divisor += 2;
      }

      String piDouble = String.format("%.5f", pi);
      System.out.printf("%d %s\t%f/%f\n", i, piDouble, 4.0, divisor);

      if (piDouble.equals("3.14159")) {
        break;
      }
    }
  }
}
