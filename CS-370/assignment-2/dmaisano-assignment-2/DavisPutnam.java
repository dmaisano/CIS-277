import java.io.IOException;
import java.io.File;
import java.lang.Math;
import java.nio.charset.Charset;
import java.nio.file.Files;
import java.util.*;

// ? reference: https://www.wikiwand.com/en/DPLL_algorithm

public class DavisPutnam {

  public enum Valuation {
    NULL, UNBOUND, FALSE, TRUE
  }

  // ? global variables
  private static boolean satIsSolved = false;
  private static LinkedList<HashMap<Integer, Valuation>> S;
  private static HashMap<Integer, Valuation> V;

  public static void DP(LinkedList<HashMap<Integer, Valuation>> clauses, int atom, Valuation atomValuation) {
    LinkedList<HashMap<Integer, Valuation>> remainingClauses = new LinkedList<HashMap<Integer, Valuation>>();
    TreeSet<Integer> remainingAtoms = new TreeSet<Integer>();

    for (HashMap<Integer, Valuation> clause : clauses) {
      boolean isNullClause = true;
      boolean removeClause = false;

      Set<Integer> tempAtoms = new TreeSet<Integer>();
      for (Map.Entry<Integer, Valuation> entry : clause.entrySet()) {
        if (entry.getValue() != Valuation.NULL) {
          if (Math.abs(entry.getKey()) == atom) {
            // apply / propagate the current truth assignments from V to the set of clauses
            if (entry.getKey() == atom) {
              if (atomValuation == Valuation.TRUE) {
                removeClause = true;
                isNullClause = false;
              } else {
                clause.replace(entry.getKey(), Valuation.NULL);
              }
            } else {
              if (atomValuation == Valuation.FALSE) {
                removeClause = true;
                isNullClause = false;
              } else {
                clause.replace(entry.getKey(), Valuation.NULL);
              }
            }
          } else {
            tempAtoms.add(Math.abs(entry.getKey()));
            isNullClause = false;
          }
        }
      }
      if (isNullClause) {
        for (Map.Entry<Integer, Valuation> entry : clause.entrySet()) {
          if (Math.abs(entry.getKey()) == atom) {
            clause.replace(entry.getKey(), Valuation.UNBOUND);
          }
        }
        return;
      }
      if (removeClause) {
        removeClause = false;
      } else {
        remainingClauses.add(clause);
        remainingAtoms.addAll(tempAtoms);
      }
    }

    // S is NULL (solution was found)
    if (remainingClauses.size() == 0) {
      satIsSolved = true;
      V.replace(atom, atomValuation);
      return;
    }

    DPHelper(remainingClauses, remainingAtoms);
  }

  public static void DPHelper(LinkedList<HashMap<Integer, Valuation>> remainingClauses,
      TreeSet<Integer> remainingAtoms) {

    for (int currentAtom : remainingAtoms) {

      boolean isPureLiteral = true;
      Valuation pureVal = Valuation.UNBOUND;

      // loop and check for pure literal / clause with single literal conditions
      for (HashMap<Integer, Valuation> clause : remainingClauses) {

        for (Map.Entry<Integer, Valuation> entry : clause.entrySet()) {
          if (clause.size() == 1 && Math.abs(entry.getKey()) == currentAtom) {
            if (entry.getKey() > 0) {
              DP(remainingClauses, entry.getKey(), Valuation.TRUE);
              if (satIsSolved) {
                V.replace(entry.getKey(), Valuation.TRUE);
              } else {
                for (Map.Entry<Integer, Valuation> atomToUndo : clause.entrySet()) {
                  if (Math.abs(atomToUndo.getKey()) == entry.getKey()) {
                    clause.replace(atomToUndo.getKey(), Valuation.UNBOUND);
                  }
                }
              }
              return;
            } else {
              DP(remainingClauses, Math.abs(entry.getKey()), Valuation.FALSE);
              if (satIsSolved) {
                V.replace(Math.abs(entry.getKey()), Valuation.FALSE);
              } else {
                for (Map.Entry<Integer, Valuation> atomToUndo : clause.entrySet()) {
                  if (Math.abs(atomToUndo.getKey()) == entry.getKey()) {
                    clause.replace(atomToUndo.getKey(), Valuation.UNBOUND);
                  }
                }
              }
              return;
            }
          }

          if (Math.abs(entry.getKey()) == currentAtom) {
            if (entry.getKey() > 0) {
              if (pureVal == Valuation.UNBOUND) {
                pureVal = Valuation.TRUE;
              } else if (pureVal != Valuation.TRUE) {
                isPureLiteral = false;
              }
            } else {
              if (pureVal == Valuation.UNBOUND) {
                pureVal = Valuation.FALSE;
              } else if (pureVal != Valuation.FALSE) {
                isPureLiteral = false;
              }
            }
          }
        }
      }

      if (isPureLiteral) {
        DP(remainingClauses, currentAtom, pureVal);

        if (satIsSolved) {
          V.replace(currentAtom, pureVal);
        }

        else {
          for (HashMap<Integer, Valuation> clause : remainingClauses) {
            for (Map.Entry<Integer, Valuation> atomToUndo : clause.entrySet()) {
              if (Math.abs(atomToUndo.getKey()) == currentAtom) {
                clause.replace(atomToUndo.getKey(), Valuation.UNBOUND);
              }
            }
          }
        }

        return;
      }
    }
    DP(remainingClauses, remainingAtoms.first(), Valuation.TRUE);
    if (satIsSolved) {
      V.replace(remainingAtoms.first(), Valuation.TRUE);

      return;
    } else {
      for (HashMap<Integer, Valuation> clause : remainingClauses) {
        for (Map.Entry<Integer, Valuation> atomToUndo : clause.entrySet()) {
          if (Math.abs(atomToUndo.getKey()) == remainingAtoms.first()) {
            clause.replace(atomToUndo.getKey(), Valuation.UNBOUND);
          }
        }
      }
    }

    DP(remainingClauses, remainingAtoms.first(), Valuation.FALSE);

    if (satIsSolved) {
      V.replace(remainingAtoms.first(), Valuation.FALSE);
    } else {
      for (HashMap<Integer, Valuation> clause : remainingClauses) {
        for (Map.Entry<Integer, Valuation> atomToUndo : clause.entrySet()) {
          if (Math.abs(atomToUndo.getKey()) == remainingAtoms.first()) {
            clause.replace(atomToUndo.getKey(), Valuation.UNBOUND);
          }
        }
      }
    }
  }

  public static void main(String[] args) {
    if (args.length == 0) {
      System.out.println("missing input file");
      System.exit(0);
    }

    String filePath = args[0];

    S = new LinkedList<HashMap<Integer, Valuation>>();
    V = new HashMap<Integer, Valuation>();
    TreeSet<Integer> ATOMS = new TreeSet<Integer>();

    List<String> extraLines = new LinkedList<String>();

    try {
      List<String> lines = Files.readAllLines(new File(filePath).toPath(), Charset.defaultCharset());

      boolean sawZero = false;

      for (String line : lines) {
        if (!sawZero) {
          line = line.trim();
        }

        if (line.equals("0")) {
          sawZero = true;
          continue;
        }

        if (sawZero) {
          extraLines.add(line);
          continue;
        }

        if (!sawZero && line.isEmpty()) {
          continue;
        }

        HashMap<Integer, Valuation> clause = new HashMap<Integer, Valuation>();

        for (String literalString : line.split("\\s")) {
          int literal = Integer.valueOf(literalString);
          int atom = Math.abs(literal);

          if (!clause.containsKey(literal)) {
            clause.put(literal, Valuation.UNBOUND);
          }

          if (!ATOMS.contains(atom)) {
            ATOMS.add(atom);
          }

          if (!V.containsKey(atom)) {
            V.put(atom, Valuation.UNBOUND);
          }
        }

        S.add(clause);
      }

      DPHelper(S, ATOMS);

      if (satIsSolved) {
        for (Map.Entry<Integer, Valuation> entry : V.entrySet()) {
          int atom = entry.getKey();
          String truthAssignment = "???";

          switch (entry.getValue()) {
          // set UNBOUNDS to "T" (could really be either "T" or "F")
          case UNBOUND:
          case TRUE:
            truthAssignment = "T";
            break;
          case FALSE:
            truthAssignment = "F";
          default:
            break;
          }

          System.out.printf("%d %s\n", atom, truthAssignment);
        }
      }

      System.out.println("0");
      for (String line : extraLines) {
        System.out.println(line);
      }
    } catch (IOException e) {
      System.out.printf("Unable to open file, \"%s\"\n", filePath);
      System.exit(1);
    } catch (Exception e) {
      System.out.println("===CAUGHT EXCEPTION===");
      System.out.println(e);
      System.exit(2);
    }
  }
}