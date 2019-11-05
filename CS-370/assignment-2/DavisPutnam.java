import java.io.IOException;
import java.io.File;
import java.nio.charset.Charset;
import java.nio.file.Files;

import java.util.*;

// reference: https://www.wikiwand.com/en/DPLL_algorithm

public class DavisPutnam {

  public enum Valuation {
    NULL, UNBOUND, FALSE, TRUE
  }

  // ? global variables
  private static boolean satIsSolved = false, endOfClauses = false;
  private static TreeSet<Integer> ATOMS;
  private static LinkedList<HashMap<Integer, Valuation>> S;
  private static HashMap<Integer, Valuation> V;

  public static void DP(LinkedList<HashMap<Integer, Valuation>> S, int atom, Valuation atomValuation) {
    LinkedList<HashMap<Integer, Valuation>> nextSetOfClauses = new LinkedList<HashMap<Integer, Valuation>>();
    TreeSet<Integer> remainingAtoms = new TreeSet<Integer>();

    for (HashMap<Integer, Valuation> clause : S) {
      // assume the clause to be null
      boolean isNullClause = true;

      // determine if clause will be removed
      boolean removeClause = false;

      TreeSet<Integer> tmpAtoms = new TreeSet<Integer>();
      for (Map.Entry<Integer, Valuation> entry : clause.entrySet()) {
        int literal = entry.getKey();
        int entryAtom = Math.abs(literal);
        Valuation entryAtomValuation = entry.getValue();

        if (entryAtomValuation != Valuation.NULL) {
          if (entryAtom == atom) {
            if (literal == atom) {
              // TODO: use switch here
              if (atomValuation == Valuation.TRUE) {
                isNullClause = false;
                removeClause = true;
              } else {
                clause.replace(literal, Valuation.NULL);
              }
            } else {
              if (atomValuation == Valuation.FALSE) {
                isNullClause = false;
                removeClause = true;
              } else {
                clause.replace(literal, Valuation.NULL);
              }
            }
          } else {
            tmpAtoms.add(entryAtom);
            isNullClause = false;
          }
        }
      }

      if (isNullClause) {
        for (Map.Entry<Integer, Valuation> entry : clause.entrySet()) {
          int literal = entry.getKey();
          int entryAtom = Math.abs(literal);

          if (entryAtom == atom) {
            clause.replace(literal, Valuation.UNBOUND);
          }
        }
        return;
      }

      if (removeClause) {
        removeClause = false;
      } else {
        nextSetOfClauses.add(clause);
        remainingAtoms.addAll(tmpAtoms);
      }
    }

    // S in NULL, clauses have been satisfied
    if (nextSetOfClauses.size() == 0) {
      satIsSolved = true;
      V.replace(atom, atomValuation);
      return;
    }

    DP_HELPER(nextSetOfClauses, remainingAtoms);
  }

  public static void DP_HELPER(LinkedList<HashMap<Integer, Valuation>> clauses, TreeSet<Integer> atoms) {
    for (int atom : atoms) {
      boolean isPureLiteral = true;
      Valuation pureValuation = Valuation.UNBOUND;

      // loop and check for either pure literals or clause with only one literal
      for (HashMap<Integer, Valuation> clause : clauses) {
        for (Map.Entry<Integer, Valuation> entry : clause.entrySet()) {
          int literal = entry.getKey();
          int entryAtom = Math.abs(literal);
          Valuation entryAtomValuation = entry.getValue();

          if (clause.size() == 1 && literal == atom) {
            // positive litral
            if (literal > 0) {
              DP(clauses, literal, Valuation.UNBOUND);
              if (satIsSolved) {
                V.replace(literal, Valuation.TRUE);
              } else {
                for (Map.Entry<Integer, Valuation> atomToUndo : clause.entrySet()) {
                  if (Math.abs(atomToUndo.getKey()) == literal) {
                    clause.replace(atomToUndo.getKey(), Valuation.UNBOUND);
                  }
                }
              }

              return;
            }
          }

          if (entryAtom == atom) {
            // positive literal
            if (literal > 0) {
              if (pureValuation == Valuation.UNBOUND) {
                pureValuation = Valuation.TRUE;
              } else if (pureValuation != Valuation.TRUE) {
                isPureLiteral = false;
              }
            } else {
              if (pureValuation == Valuation.UNBOUND) {
                pureValuation = Valuation.FALSE;
              } else if (pureValuation != Valuation.FALSE) {
                isPureLiteral = false;
              }
            }
          }
        }
      }
      if (isPureLiteral) {
        DP(clauses, atom, pureValuation);
        if (satIsSolved) {
          V.replace(atom, pureValuation);
        } else {
          for (HashMap<Integer, Valuation> clause : clauses) {
            for (Map.Entry<Integer, Valuation> atomToUndo : clause.entrySet()) {
              if (Math.abs(atomToUndo.getKey()) == atom) {
                clause.replace(atomToUndo.getKey(), Valuation.UNBOUND);
              }
            }
          }
        }
        return;
      }
    }

    DP(clauses, atoms.first(), Valuation.TRUE);

    if (satIsSolved) {
      V.replace(atoms.first(), Valuation.TRUE);
      return;
    } else {
      for (HashMap<Integer, Valuation> clause : clauses) {
        for (Map.Entry<Integer, Valuation> atomToUndo : clause.entrySet()) {
          int literal = atomToUndo.getKey();
          int entryAtom = Math.abs(literal);
          Valuation entryAtomValuation = atomToUndo.getValue();

          if (entryAtom == atoms.first()) {
            clause.replace(entryAtom, Valuation.UNBOUND);
          }
        }
      }
    }

    DP(clauses, atoms.first(), Valuation.FALSE);

    if (satIsSolved) {
      V.replace(atoms.first(), Valuation.FALSE);
    } else {
      for (HashMap<Integer, Valuation> clause : clauses) {
        for (Map.Entry<Integer, Valuation> atomToUndo : clause.entrySet()) {
          if (Math.abs(atomToUndo.getKey()) == atoms.first()) {
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

    try {
      ATOMS = new TreeSet<Integer>();
      S = new LinkedList<HashMap<Integer, Valuation>>();
      V = new HashMap<Integer, Valuation>();

      List<String> lines = Files.readAllLines(new File(filePath).toPath(), Charset.defaultCharset());
      List<String> extraLines = new LinkedList<String>();
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

        if (line.isEmpty()) {
          continue;
        }

        HashMap<Integer, Valuation> clause = new HashMap<Integer, Valuation>();
        for (String literalString : line.split("\\s")) {
          int literal = Integer.valueOf(literalString);

          V.put(Math.abs(literal), Valuation.NULL);
          clause.put(literal, Valuation.NULL);

          if (!ATOMS.contains(literal)) {
            ATOMS.add(literal);
          }
        }

        S.add(clause);
      }

      DP_HELPER(S, ATOMS);

      if (satIsSolved) {
        for (Map.Entry<Integer, Valuation> entry : V.entrySet()) {
          String truthAssignment = "???";
          int atom = entry.getKey();

          switch (entry.getValue()) {
          // UNBOUNDS are assumed to be TRUE (can really be TRUE OR FALSE)
          case UNBOUND:
          case TRUE:
            truthAssignment = "T";
            break;
          case FALSE:
            truthAssignment = "F";
            break;
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