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

  public static void DP(LinkedList<HashMap<Integer, Valuation>> S, int atom, Valuation atomValuation) {
    LinkedList<HashMap<Integer, Valuation>> nextSetOfClauses = new LinkedList<HashMap<Integer, Valuation>>();
    Set<Integer> remainingAtoms = new TreeSet<Integer>();

    for (HashMap<Integer, Valuation> clause : S) {
      // assume the clause to be null
      boolean isNullClause = true;

      // determine if clause will be removed
      boolean removeClause = false;

      Set<Integer> tmpAtoms = new TreeSet<Integer>();
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
          Valuation entryAtomValuation = entry.getValue();
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
  }

  public static void main(String[] args) {
    if (args.length == 0) {
      System.out.println("missing input file");
      System.exit(0);
    }

    String filePath = args[0];

    try {
      Set<Integer> ATOMS = new TreeSet<Integer>();
      LinkedList<HashMap<Integer, Valuation>> S = new LinkedList<HashMap<Integer, Valuation>>();
      HashMap<Integer, Valuation> V = new HashMap<Integer, Valuation>();

      List<String> lines = Files.readAllLines(new File(filePath).toPath(), Charset.defaultCharset());

      // LinkedList<String> ATOMS = new LinkedList<String>(); // set of atoms
      // LinkedList<Clause> S = new LinkedList<Clause>(); // unique set of clauses

      // Map<String, Valuation> V = new HashMap<String, Valuation>(); // truth
      // assignments per atoms

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