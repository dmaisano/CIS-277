public class UsingExceptions {
  public static void main(String[] args) {
    try {
      throwException();
    } catch (Exception e) {
      System.err.println("Exception handled in main");
    }
  }

  public static void throwException() throws Exception {
    try {
      System.out.println("Method throwException");
      throw new Exception();
    } catch (Exception e) {
      System.err.println("Exception handled in method throwException");
      throw e;
    } finally {
      System.err.println("Finally executed in throwException");
    }
  }
}