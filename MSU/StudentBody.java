//********************************************************************
//  StudentBody.java       Author: Lewis/Loftus
//
//  Demonstrates the use of an aggregate class.
//********************************************************************

public class StudentBody 
{
   //-----------------------------------------------------------------
   //  Creates some Address and Student objects and prints them.
   //-----------------------------------------------------------------
   public static void main (String[] args)
   {
      Address school = new Address ("800 Lancaster Ave.", "Villanova",
                                    "PA", 19085);
      Address jHome = new Address ("21 Jump Street", "Lynchburg",
                                   "VA", 24551);
      Student john = new Student ("John", "Smith", jHome, school);

      Address mHome = new Address ("123 Main Street", "Euclid", "OH",
                                   44132);
      Student marsha = new Student ("Marsha", "Jones", mHome, school);

      System.out.println (john);
      System.out.println ();
      System.out.println (marsha);

      Student scott = new Student ("Scott", "Pilgrim",
         new Address("??? Albert Avenue", "Peterborough", "Ontario", 44132),
         school, 70, 75, 80
      );

      // System.out.println(scott);

      System.out.println("Scott's exam 2 results: " + scott.getTestScore(2));

      System.out.println("Scott cheated, new exam 2 score is zero");
      scott.setTestScore(2, 0);

      System.out.println(scott);
   }
}
