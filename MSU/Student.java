//********************************************************************
//  Student.java       Author: Lewis/Loftus
//
//  Represents a college student.
//********************************************************************

public class Student
{
   private String firstName, lastName;
   private Address homeAddress, schoolAddress;
   private double[] testScores;

   //-----------------------------------------------------------------
   //  Constructor: Sets up this student with the specified values.
   //-----------------------------------------------------------------
   public Student (String first, String last, Address home,
                   Address school)
   {
      firstName = first;
      lastName = last;
      homeAddress = home;
      schoolAddress = school;

      testScores = new double[] {0, 0, 0}; // initialize default test scores to zero
   }

   public Student (String first, String last, Address home,
                   Address school, double testScoreOne, double testScoreTwo, double testScoreThree)
   {
      firstName = first;
      lastName = last;
      homeAddress = home;
      schoolAddress = school;

      testScores = new double[] { testScoreOne, testScoreTwo, testScoreThree }; // initialize default test scores to zero
   }

   public void setTestScore(int testNumber, double testScore) {
      testScores[testNumber - 1] = testScore;
   }

   public double getTestScore(int testNumber) {
      return testScores[testNumber - 1]; // offset 1
   }

   // adding method for PP 7.3
   // in order to retreive the average in the Course class
   public double getAverage()
   {
      double average = 0;

      for (int i = 0; i < 3; i++) {
         average += testScores[i];
      }

      return average / 3;
   }

   //-----------------------------------------------------------------
   //  Returns a string description of this Student object.
   //-----------------------------------------------------------------
   public String toString()
   {
      String result;
      double average = 0;

      result = firstName + " " + lastName + "\n";
      result += "Home Address:\n" + homeAddress + "\n";
      result += "School Address:\n" + schoolAddress + "\n";

      for (int i = 0; i < 3; i++) {
         result += String.format("Test %d Score: %.2f\n", i, testScores[i]);
         
         average += testScores[i];
      }

      average /= 3; // divide by the 3 exams to get the average

      result += String.format("Average: %.2f\n", average);

      return result;
   }
}
