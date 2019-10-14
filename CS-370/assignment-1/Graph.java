import java.io.IOException;
import java.io.File;
import java.nio.charset.Charset;
import java.nio.file.Files;

import java.util.*;

public class Graph {
  int maxQueueSize = 0; // max frontier size
  int maxNumStates = 0; // max number of states during Iterative Deepening
  boolean verboseMode = false;
  int numDominoes = 0;
  LinkedList<Domino> dominoPool;

  Queue<State> frontier; // returned after BFS, used for Iterative Deepening
  HashMap<String, State> explored; // map of explored states, key is the diff of the state

  Graph(int maxQueueSize, int maxNumStates, boolean verboseMode, LinkedList<Domino> dominoPool) {
    this.maxQueueSize = maxQueueSize;
    this.maxNumStates = maxNumStates;
    this.verboseMode = verboseMode;
    this.dominoPool = dominoPool;

    this.frontier = new LinkedList<State>(); // frontier of states returned used in Iterative Deepening
    this.explored = new HashMap<String, State>(); // key is the diff of the state
  }

  // should return frontier queue
  // explore frontier using BFS
  Queue<State> BFS() {
    State initialState = new State();

    this.frontier.add(initialState);

    int counter = 0;
    while (!this.frontier.isEmpty() && counter <= this.maxNumStates) {
      if (this.frontier.size() >= this.maxQueueSize) {
        break;
      }

      State currentState = this.frontier.remove();

      for (Domino d : this.dominoPool) {
        State nextState = currentState.getNextState(currentState, d);

        if (nextState.isValid() && !this.explored.containsKey(nextState.diff)) {
          counter++;

          // this.states.add(nextState);
          this.frontier.add(nextState);
          this.explored.put(nextState.diff, nextState);

          if (this.verboseMode)
            System.out.println(nextState);
        }
      }
    }

    return this.frontier;
  }

  void DFS(State s) {
    if (this.verboseMode) {
      System.out.printf("\nPERFORMING DFS ON NODE:\n*** %s ***\n\n", s);
    }

    Stack<State> stateStack = new Stack<State>();

    stateStack.push(s);

    int counter = 0;
    while (!stateStack.isEmpty() && counter <= this.maxNumStates) {
      State currentState = stateStack.pop();

      for (Domino d : this.dominoPool) {
        State nextState = currentState.getNextState(currentState, d);

        if (nextState.isValid() && !this.explored.containsKey(nextState.diff)) {
          counter++;

          stateStack.push(nextState);
          this.explored.put(nextState.diff, nextState);

          if (this.verboseMode)
            System.out.println(nextState);
        }
      }
    }
  }

  // runs BFS and then DFS for each node in the frontier
  void solve() {
    if (this.verboseMode) {
      System.out.println("====BFS SEARCH====");
    }
    Queue<State> frontier = this.BFS();

    // reset explored
    this.explored = new HashMap<String, State>();

    if (this.verboseMode) {
      System.out.println("\n====BEGIN ITERATIVE DEEPENING====\n");
    }
    while (!frontier.isEmpty()) {
      this.DFS(frontier.remove());
    }

    // no solution was found
    System.out.println("\n====No Solution Found====\n");
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
    LinkedList<Domino> dominoList;
    String topString = "";
    String bottomString = "";
    String diff = "";

    // root node
    State() {
      this.dominoList = new LinkedList<Domino>();
    }

    State(LinkedList<Domino> dominoList) {
      this.dominoList = dominoList;

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
      LinkedList<Domino> dominoList = new LinkedList<Domino>();

      // deep copy
      for (Domino domino : s.dominoList) {
        dominoList.add(domino);
      }

      dominoList.add(d);

      State newState = new State(dominoList);

      if (newState.isGoalState()) {
        System.out.println(newState);
        System.out.println("\n====FOUND GOAL STATE====");
        System.out.printf("Goal State: %s\n\n", newState);
        System.exit(0);
      }

      return newState;
    }

    // returns false is the combinations of dominoes is not allowed
    boolean isValid() {
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

    boolean isGoalState() {
      if (this.dominoList.size() < 1)
        return false;

      if (this.topString.length() != this.bottomString.length())
        return false;

      return this.isValid();
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

    @Override
    public String toString() {
      String res = "{ ";

      for (int i = 0; i < this.dominoList.size(); i++) {
        Domino d = this.dominoList.get(i);

        res += d.label;

        if (i != this.dominoList.size() - 1) {
          res += ", ";
        }
      }

      return res + " }";
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
    boolean verboseMode = false;
    int numDominoes = 0;
    LinkedList<Domino> dominoPool = new LinkedList<Domino>();

    // read the input file
    try {
      List<String> lines = Files.readAllLines(new File(fileName).toPath(), Charset.defaultCharset());

      maxQueueSize = Integer.parseInt(lines.get(0).trim());
      maxNumStates = Integer.parseInt(lines.get(1).trim());
      verboseMode = lines.get(2).trim().equals("1") ? true : false;
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

    Graph g = new Graph(maxQueueSize, maxNumStates, verboseMode, dominoPool);

    g.solve();
  }
}
