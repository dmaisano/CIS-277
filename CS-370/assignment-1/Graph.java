import java.io.IOException;
import java.io.File;
import java.nio.charset.Charset;
import java.nio.file.Files;

import java.util.*;

public class Graph {

  static class Domino {
    String label;
    String top;
    String bottom;

    Domino(String top, String bottom, String label) {
      this.top = top;
      this.bottom = bottom;
      this.label = label;
    }
  }

  static class State {
    LinkedList<Domino> dominoList;
    String topString = "";
    String bottomString = "";
    String diff;

    State(LinkedList<Domino> dominoList) {
      this.dominoList = dominoList;

      for (Domino d : dominoList) {
        this.topString += d.top;
        this.bottomString += d.bottom;
      }

      if (dominoList.size() < 1 || this.topString.equals(this.bottomString)) {
        this.diff = "";
      } else if (this.topString.length() >= this.bottomString.length()) {
        // top heavy string
        this.diff = "+" + this.topString.substring(this.bottomString.length(), this.topString.length());
      } else {
        // bottom heavy string
        this.diff = "-" + this.bottomString.substring(this.topString.length(), this.bottomString.length());
      }
    }

    // returns false is the combinations of dominoes is not allowed
    Boolean isValid() {
      int len = this.topString.length() >= this.bottomString.length() ? this.topString.length()
          : this.bottomString.length();

      for (int i = 0; i < len; i++) {
        if (this.topString.charAt(i) != this.bottomString.charAt(i))
          return false;
      }

      return true;
    }
  }

  public static void main(String[] args) {
    if (args.length == 0) {
      System.out.println("missing input file name");
      System.exit(0);
    }

    String fileName = args[0];

    int maxQueueSize = 0;
    int maxNumStates = 0;
    Boolean verboseMode = false;
    int numDominoes = 0;
    LinkedList<Domino> dominoPool = new LinkedList<Domino>();

    // read the input file
    try {
      List<String> lines = Files.readAllLines(new File(fileName).toPath(), Charset.defaultCharset());

      maxQueueSize = Integer.parseInt(lines.get(0).trim());
      maxNumStates = Integer.parseInt(lines.get(1).trim());
      verboseMode = Boolean.parseBoolean(lines.get(2).trim());
      numDominoes = Integer.parseInt(lines.get(3).trim());

      for (int i = 1; i <= numDominoes; i++) {
        String[] line = lines.get(i + 3).trim().split("\\s+");

        String top = line[line.length - 2];
        String bottom = line[line.length - 1];

        dominoPool.add(new Domino(top, bottom, "D" + i));
      }
    } catch (IOException e) {
      System.out.printf("Unable to open file, \"%s\"\n", fileName);
      System.exit(1);
    } catch (Exception e) {
      System.out.println("Error parsing input file");
      System.exit(1);
    }

    LinkedList<State> states = new LinkedList<State>();

    for (Domino d : dominoPool) {
      System.out.println(d.label);
    }

    LinkedList<Domino> sample = new LinkedList<Domino>();

    sample.add(dominoPool.get(dominoPool.size() - 1));

    State s = new State(sample);

    System.out.println(s.topString);
    System.out.println(s.bottomString);
    System.out.println(s.diff);
    System.out.println(s.isValid());
  }
}
