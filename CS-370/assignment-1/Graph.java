import java.io.IOException;
import java.io.File;
import java.nio.charset.Charset;
import java.nio.file.Files;

import java.util.*;

public class Graph {
  int maxQueueSize = 0;
  int maxNumStates = 0; // max number of vertices in adj list
  Boolean verboseMode = false;
  int numDominoes = 0;
  LinkedList<Domino> dominoPool;

  Queue<State> states; // states traversed during BFS
  Queue<State> frontier; // queue returned after BFS
  Set<String> explored; // stores a set of domino sequences

  Graph(int maxQueueSize, int maxNumStates, Boolean verboseMode, LinkedList<Domino> dominoPool) {
    this.maxQueueSize = maxQueueSize;
    this.maxNumStates = maxNumStates;
    this.verboseMode = verboseMode;
    this.dominoPool = dominoPool;

    this.states = new LinkedList<State>();
    this.frontier = new LinkedList<State>(); // frontier of states returned used in iter
    this.explored = new HashSet<String>();
  }

  // should return frontier queue
  // explore frontier using BFS
  Queue<State> BFS() {
    State initialState = new State();

    // add initial domino nodes from the pool
    for (Domino d : this.dominoPool) {
      LinkedList<Domino> dominoList = new LinkedList<Domino>();
      dominoList.add(d);

      State newState = new State(dominoList, initialState);

      if (newState.isValid()) {
        this.states.add(newState);
        this.frontier.add(newState);
        this.explored.add(newState.getSequenceString());
      }
    }

    while (!this.states.isEmpty()) {
      if (this.explored.size() >= this.maxNumStates)
        break;

      if (this.frontier.size() >= this.maxQueueSize)
        break;

      State currentState = this.states.remove();

      for (Domino d : this.dominoPool) {
        State nextState = currentState.getNextState(currentState, d);

        if (nextState.isValid() && !this.explored.contains(nextState.getSequenceString())) {

        }
      }
    }

    return this.frontier;
  }

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
    LinkedList<Domino> dominoList = new LinkedList<Domino>();
    String topString = "";
    String bottomString = "";
    String diff = "";
    State parent;
    LinkedList<State> children; // list possible children nodes

    // root node
    State() {
      this.parent = null;
      this.children = new LinkedList<State>();
    }

    // State(State parent) {
    // this.parent = parent;
    // this.children = new LinkedList<State>();
    // }

    State(LinkedList<Domino> dominoList, State parent) {
      this.dominoList = dominoList;

      this.children = new LinkedList<State>();
      this.parent = parent;

      for (Domino d : this.dominoList) {
        this.topString += d.top;
        this.bottomString += d.bottom;
      }

      if (dominoList.size() < 1 || this.topString.equals(this.bottomString)) {
      } else if (this.topString.length() >= this.bottomString.length()) {
        // top heavy string
        this.diff = "+" + this.topString.substring(this.bottomString.length(), this.topString.length());
      } else {
        // bottom heavy string
        this.diff = "-" + this.bottomString.substring(this.topString.length(), this.bottomString.length());
      }
    }

    State getNextState(State s, Domino d) {
      LinkedList<Domino> dominoList = s.dominoList;

      dominoList.add(d);

      State newState = new State(dominoList, s);

      return newState;
    }

    // returns false is the combinations of dominoes is not allowed
    Boolean isValid() {
      int len = 0;

      if (this.topString.length() <= this.bottomString.length()) {
        len = this.topString.length();
      } else {
        len = this.bottomString.length();
      }

      for (int i = 0; i < len; i++) {
        if (this.topString.charAt(i) != this.bottomString.charAt(i))
          return false;
      }

      return true;
    }

    // returns the string representation of dominoes in the list
    // e.g. D1D2D3
    String getSequenceString() {
      String res = "";

      for (Domino d : this.dominoList) {
        res += d.label;
      }

      return res;
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

    // for (Domino d : dominoPool) {
    // System.out.println(d.label);
    // }

    LinkedList<Domino> sample = new LinkedList<Domino>();

    sample.add(dominoPool.get(0));
    sample.add(dominoPool.get(0));

    Graph g = new Graph(maxQueueSize, maxNumStates, verboseMode, dominoPool);

    g.BFS();
  }
}
