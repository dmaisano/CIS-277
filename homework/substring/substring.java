import java.util.Scanner; // allows us to get input from the user

public class substring {
  public static void main(String[] args) {
    menu(); // calls the main program
  }

  public static void menu() {
    // prompts and validates the user input string
    String userInput = validateString(prompt("Enter a binary string: "));
    boolean result = validString(userInput);

    if(result == true)
      System.out.println(userInput + " contains the valid substring of '1101'");

    else
      System.out.println(userInput + " does not contain a valid substring of '1101'");

    // prompts user if they wish to restart the program
    String choice = prompt("Restart program?\n1 = Yes\n2 = No\nEnter choice: ");

    // if the user enters 1 recursively calls the menu function
    if(choice.matches("1"))
      menu();

    else
      System.out.println("Exiting program...");
  }

  public static String prompt(String phrase) {
    // variable to get input from user
    Scanner prompt = new Scanner(System.in);

    System.out.print(phrase);
    String str = prompt.next(); // gets input from the console

    return str;
  }

  public static String validateString(String str) {
    // uses regex to check if the string contains illegal characters
    while(str.matches("[a-zA-Z]+") || str.matches("[2-9]+")) {
      System.out.println("Invalid string!");
      str = prompt("Enter a binary string: "); // recursively calls the function until valid substring is entered
    }

    return str;
  }

  public static boolean validString(String str) {
    // if the string contains the substring '1101' return true
    if(str.matches("1101"))
      return true;

    return false;
  }
}
