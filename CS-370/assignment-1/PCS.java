import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.io.File;

import java.nio.charset.Charset;
import java.nio.file.Files;

import java.util.List;

class Domino {
  public String top;
  public String bottom;
}

class Graph {
  private int maxQueueSize;
  private int maxNumStates;
  private int numDominoes;
  private Boolean verboseMode;
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

    try {
      List<String> lines = Files.readAllLines(new File(fileName).toPath(), Charset.defaultCharset());

      for (String line : lines) {
        System.out.println(line);
      }

      System.out.printf("lines: %d", lines.size());
    } catch (IOException e) {
      System.out.printf("Unable to open file, \"%s\"\n", fileName);
    } catch (Exception e) {
      System.out.println("Error parsing input file");
    }
  }

}
