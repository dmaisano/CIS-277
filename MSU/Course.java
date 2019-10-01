import java.util.ArrayList;

public class Course
{
  private String courseName;
  private ArrayList<Student> students;

  public Course(String name)
  {
    courseName = name;
    students = new ArrayList<Student>();
  }

  public void addStudent(Student student)
  {
    students.add(student);
  }

  public double average()
  {
    double classAvg = 0;

    int numStudents = students.size();

    for (int i = 0; i < numStudents; i++) {
      classAvg += students.get(i).getAverage();
    }

    return classAvg / numStudents;
  }

  public void roll()
  {
    for (Student student : students) {
      System.out.println(student);
    }
  }

  // main / driver func
  public static void main(String[] args) {
    Address school = new Address ("800 Lancaster Ave.", "Villanova", "PA", 19085);

    Student adam = new Student("Adam", "Smith", new Address("123 Generic Street", "Generic Town", "NJ", 12345), school, 80.0, 85.0, 90.0);

    Student john = new Student("John", "Doe", new Address("124 Generic Street", "Generic Town", "NJ", 12345), school, 50.0, 75.0, 90.0);

    Student stephen = new Student("Stephen", "Stills", new Address("125 Generic Street", "Generic Town", "NJ", 12345), school, 90.0, 75.0, 90.0);

    Student kim = new Student("Kimberly", "Pines", new Address("321 Generic Street", "Generic Town", "NJ", 12345), school, 90.0, 85.0, 92.0);

    Course english101 = new Course("English 101");

    english101.addStudent(adam);
    english101.addStudent(john);
    english101.addStudent(stephen);
    english101.addStudent(kim);

    english101.roll();

    System.out.printf("\nCourse average: %.2f\n", english101.average());
  }
}
