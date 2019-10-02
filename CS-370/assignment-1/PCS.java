import java.util.HashMap;
import java.util.ArrayList;

class Domino {
  private String top;
  private String bottom;
  private String key; // D1, D2, D3, or D4

  public Domino(String top, String bottom) {
    this.top = top;
    this.bottom = bottom;

    if (top == "c" && bottom == "cca") {
      this.key = "D1";
    } else if (top == "ac" && bottom == "ba") {
      this.key = "D2";
    } else if (top == "bb" && bottom == "b") {
      this.key = "D3";
    } else if (top == "ac" && bottom == "cb") {
      this.key = "D4";
    } else if (top == "" && bottom == "") {
      this.key = "(EMPTY)";
    } else {
      this.key = "???";
    }
  }

  public String Top() {
    return this.top;
  }

  public String Bottom() {
    return this.bottom;
  }

  public String Key() {
    return this.key;
  }

  public String toString() {
    return this.key;
  }
}

class State {
  private String topString;
  private String bottomString;
  private int depth;
  ArrayList<Domino> dominoes = new ArrayList<Domino>(); // current dominoes in state (e.g. { D3, D2 })
  ArrayList<Domino> children = new ArrayList<Domino>(); // max size of 4 (branching factor)

  public State(Domino domino, int depth, ArrayList<Domino> dominoes) {
    this.depth = depth;
    this.dominoes = dominoes;
    this.children = children;
  }

  // returns false if bottom is an invalid combination of the top
  public Boolean isValid() {
    for (Domino domino : this.dominoes) {
      System.out.println(domino.Bottom());
    }

    return false;
  }

  // finds any possible children for the current node
  public void bfs_branch() {

  }
}

/**
 * Post Correspondence Solver
 */
public class PCS {
  public static void main(String[] args) {
    Domino D1 = new Domino("c", "cca");
    Domino D2 = new Domino("ac", "ba");
    Domino D3 = new Domino("bb", "b");
    Domino D4 = new Domino("ac", "cb");

    Domino[] dominoPool = { D1, D2, D3, D4 };

    State empty = new State(new Domino("", ""), 0, new ArrayList<Domino>(), new ArrayList<Domino>() {
      {
        add(D1);
        add(D3);
      }
    });

    bfs_search(empty);
  }

  public static void bfs_search(State initialState) {

  }
}
