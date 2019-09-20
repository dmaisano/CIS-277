import java.util.Scanner;

class Account {
  private double balance;

  public Account(double initialBalance) {
    if (initialBalance > 0.0)
      this.balance = initialBalance;
  }

  // add amount to balance
  public void credit(double amount) {
    this.balance += amount;
  }

  public double getBalance() {
    return this.balance;
  }
}

// 3b, page 373
public class AccountTest {
  public static void main(String args[]) {
    Account account1 = new Account(50.00);
    Account account2 = new Account(-7.53);

    System.out.printf("account1 balance $%.2f\n", account1.getBalance());
    System.out.printf("account2 balance $%.2f\n", account2.getBalance());

    // scanner obj
    Scanner input = new Scanner(System.in);

    System.out.print("Enter deposit amount for account1: ");
    account1.credit(input.nextDouble());

    System.out.printf("account1 balance $%.2f\n", account1.getBalance());
    System.out.printf("account2 balance $%.2f\n", account2.getBalance());

    System.out.print("Enter deposit amount for account2: ");
    account2.credit(input.nextDouble());

    System.out.printf("account1 balance $%.2f\n", account1.getBalance());
    System.out.printf("account2 balance $%.2f\n", account2.getBalance());

    input.close();
  }
}
