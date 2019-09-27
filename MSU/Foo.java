public class Foo {
  private int[] values;

  public Foo(int val1, int val2) {
    values = new int[] { val1, val2 };
  }

  public String toString() {
    return String.format("%d\n%d\n", values[0], values[1]);
  }

  public static void main(String[] args) {
    Foo var = new Foo(1, 2);

    System.out.println(var);
  }
}
