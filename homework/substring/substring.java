import java.util.Scanner; // allows us to get input from the user

public class substring {
  public static void main(String[] args) {
    menu(); // calls the main program
  }

  public static void menu() {
    // prompts and validates the user input string
    String userInput = validateString(prompt("Enter a binary string: "));
    // stores a boolean value depending if the string is valid
    boolean result = isSubstr(userInput);

    if(result == true)
      System.out.println(userInput + " contains the valid substring of '1101'");

    else
      System.out.println(userInput + " does not contain a valid substring of '1101'");

    // prompts user if they wish to restart the program
    String choice = prompt("Restart program?\n1 = Yes\n2 = No\nEnter choice: ");

    // if the user enters 1, recursively call the menu function
    if(choice.contains("1"))
      menu();

    else {
      System.out.println("Exiting program...");
      prompt.close(); // closes the scanner to prevent resource leaks 
    }
  }

  public static Scanner prompt = new Scanner(System.in); // scanner object

  // function to get input from the user
  public static String prompt(String phrase) {
    System.out.print(phrase);

    String str = prompt.next(); // gets input from user

    return str; 
  }

  public static String validateString(String str) {
    // uses regex to check if the string contains illegal characters
    while(!str.matches("[01]+")) {
      System.out.println("Invalid string!");
      str = prompt("Enter a binary string: "); // recursively calls the function until a valid string is entered
    }

    return str;
  }

  public static boolean isSubstr(String str) {
    // if the string contains the substring '1101' return true
    if(str.contains("1101"))
      return true;

    // else return false
    return false;
  }
}
