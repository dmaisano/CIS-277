// 3b, page 421
class SquareCube {
  public static void main(String[] args) {
    double pi = 4.0;
    double denominator = 3.0;

    // start at offset of 1
    for (int i = 1; i < 200000; i++) {
      if (i % 2 != 0) {
        pi -= (4.0 / denominator);
      } else {
        pi += (4.0 / denominator);
      }

      // increase denominator by 2 in the series
      denominator += 2;

      String piString = String.format("%.5f", pi);
      System.out.printf("%d %s\n", i, piString);

      // terminate if match found
      if (piString.equals("3.14159")) {
        break;
      }
    }
  }
}
