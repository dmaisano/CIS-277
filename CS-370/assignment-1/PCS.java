import java.io.IOException;
import java.io.File;
import java.nio.charset.Charset;
import java.nio.file.Files;

import java.util.List;
import java.util.ArrayList;
import java.util.HashMap;

class Domino {
  public String top;
  public String bottom;
}

class State {
  String diff;
  ArrayList<Domino> dominoes;
  State parent;
}

class Graph {
  private int maxQueueSize;
  private int maxNumStates;
  private int numDominoes;
  private Boolean verboseMode;
  private HashMap<String, Domino> dominoPool;
}

public class PCS {

  public static void main(String[] args) {
    if (args.length == 0) {
      System.out.println("missing input file name");
      System.exit(0);
    }

    String fileName = args[0];

    readInputFile(fileName);
  }

  public static void readInputFile(String fileName) {
    private int maxQueueSize;
    private int maxNumStates;
    private int numDominoes;
    private Boolean verboseMode;

    try {
      List<String> lines = Files.readAllLines(new File(fileName).toPath(), Charset.defaultCharset());

      for (String line : lines) {
        System.out.println(line);
      }
    } catch (IOException e) {
      System.out.printf("Unable to open file, \"%s\"\n", fileName);
    } catch (Exception e) {
      System.out.println("Error parsing input file");
    }
  }

}
