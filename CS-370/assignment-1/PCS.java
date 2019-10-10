import java.io.IOException;
import java.io.File;
import java.nio.charset.Charset;
import java.nio.file.Files;

import java.util.*;

class Domino {
  String label;
  String top;
  String bottom;

  Domino(String top, String bottom, String label) {
    this.top = top;
    this.bottom = bottom;
    this.label = label;
  }

  @Override
  public int hashCode() {
    // overriding hashcode returned by Domino objects
    String dominoString = this.top + this.bottom;

    return dominoString.hashCode();
  }

  @Override
  public boolean equals(Object obj) {
    if (this == obj)
      return true;

    if (obj == null)
      return false;

    if (getClass() != obj.getClass())
      return false;

    Domino other = (Domino) obj;
    if (this.top == other.top && this.bottom == other.bottom)
      return false;

    return true;
  }

}

// BFS & DFS Nodes in the graph
class State {
  String diff;
  ArrayList<Domino> dominoList;
  LinkedList<State> adjList[];

  State(String diff, ArrayList<Domino> dominoList) {
    this.diff = diff;
    this.dominoList = dominoList;
  }

  State(String diff, ArrayList<Domino> dominoList, int depth) {
    this.diff = diff;
    this.dominoList = dominoList;
  }

  // returns true is domino can be added & adds domino
  Boolean addDomino(Domino newDomino) {
    String topString;
    String bottomString;

    List<Domino> dominoList = this.dominoes;

    dominoList.add(newDomino);

    for (Domino d : this.dominoes) {
      topString += d.top;
      bottomString += d.bottom;
    }

    int len = topString.length() >= bottomString.length() ? topString.length() : bottomString.length();

    if (!topString.substring(0, len).equals(bottomString.substring(0, len))) {
      return false;
    }

    // add the domino to the list
    this.dominoList.add(newDomino);

    return true;
  }
}

class Graph {
  private int maxQueueSize;
  private int maxNumStates;
  private int numDominoes;
  private Boolean verboseMode;
  private ArrayList<Domino> dominoPool = new ArrayList<Domino>(); // given dominoes from input file

  private State startingNode;
  private Queue<Domino> states = new LinkedList<Domino>(); // queue of dominoes in the graph

  Graph(int maxQueueSize, int maxNumStates, int numDominoes, Boolean verboseMode, ArrayList<Domino> dominoPool) {
    this.maxQueueSize = maxQueueSize;
    this.maxNumStates = maxNumStates;
    this.numDominoes = numDominoes;
    this.verboseMode = verboseMode;
    this.dominoPool = dominoPool;

    this.startingNode = new State("", new ArrayList<Domino>()); // empty starting state
  }

  // fill out the frontier
  void BFS_SEARCH() {
    // for (Domino d : dominoPool) {
    // this.dominoPool
    // }
  }
}

public class PCS {

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
    ArrayList<Domino> dominoPool = new ArrayList<Domino>();

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

    Graph g = new Graph(maxQueueSize, maxNumStates, numDominoes, verboseMode, dominoPool);
  }
}
