import java.io.IOException;
import java.io.File;
import java.lang.Math;
import java.nio.charset.Charset;
import java.nio.file.Files;
import java.util.*;

public class DavisPutnam {

  public enum Valuation {
    TRUE, FALSE, UNBOUND, NULL, TRUEORFALSE
  }

  // ? global variables
  private static boolean satIsSolved = false;
  private static LinkedList<HashMap<Integer, Valuation>> S;
  private static HashMap<Integer, Valuation> V;

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

      // while (!endOfClauses) {
      // String nextLine = input.nextLine();
      // else {
      // String[] clauseString = nextLine.split(" ");
      // try {
      // int[] clause = new int[clauseString.length];
      // HashMap<Integer, Valuation> tempMap = new HashMap<Integer, Valuation>();
      // for (int index = 0; index < clause.length; index++) {
      // clause[index] = Integer.valueOf(clauseString[index]);
      // tempMap.put(clause[index], Valuation.UNBOUND);
      // V.put(Math.abs(clause[index]), Valuation.UNBOUND);
      // }
      // S.add(tempMap);
      // } catch (Exception e) {
      // System.out.println("Invalid Atom! Davis Putnam cannot be applied");
      // System.exit(0);
      // }
      // }
      // }

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

      // System.out.println(Arrays.toString(S.toArray()));
      // System.out.println(V);
      //
      // for (Map.Entry<Integer, Valuation> atomC : V.entrySet()) {
      // allAtoms.add(atomC.getKey());
      // }

      DPHelper(S, ATOMS);
      if (satIsSolved) {
        for (Map.Entry<Integer, Valuation> atomC : V.entrySet()) {
          if (atomC.getValue() == Valuation.UNBOUND)
            V.replace(atomC.getKey(), Valuation.TRUEORFALSE);
        }
        System.out.println("SATISFIABLE BY: " + V);
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

  public static void DP(LinkedList<HashMap<Integer, Valuation>> currentSet, int atom, Valuation val) {
    LinkedList<HashMap<Integer, Valuation>> nextSet = new LinkedList<HashMap<Integer, Valuation>>();
    TreeSet<Integer> remainingAtoms = new TreeSet<Integer>();
    System.out.println("Applying atom " + atom + " as " + val + "...");
    for (HashMap<Integer, Valuation> clause : currentSet) {
      boolean nullClause = true;
      boolean removeClause = false;
      Set<Integer> tempAtoms = new TreeSet<Integer>();
      for (Map.Entry<Integer, Valuation> atomC : clause.entrySet()) {
        if (atomC.getValue() != Valuation.NULL) {
          if (Math.abs(atomC.getKey()) == atom) {
            if (atomC.getKey() == atom) { // Apply atom and truth expression to current set of clauses
              if (val == Valuation.TRUE) {
                removeClause = true;
                nullClause = false;
              } else
                clause.replace(atomC.getKey(), Valuation.NULL);
            } else {
              if (val == Valuation.FALSE) {
                removeClause = true;
                nullClause = false;
              } else
                clause.replace(atomC.getKey(), Valuation.NULL);
            }
          } else {
            tempAtoms.add(Math.abs(atomC.getKey()));
            nullClause = false;
          }
        }
      }
      if (nullClause) {
        System.out.println("Null clause: " + clause);
        for (Map.Entry<Integer, Valuation> atomC : clause.entrySet()) {
          if (Math.abs(atomC.getKey()) == atom)
            clause.replace(atomC.getKey(), Valuation.UNBOUND);
        }
        return;
      }
      if (removeClause)
        removeClause = false;
      else {
        nextSet.add(clause);
        remainingAtoms.addAll(tempAtoms);
      }
    }
    System.out.println("New set is: ");
    System.out.println(Arrays.toString(nextSet.toArray()));
    System.out.println("Remaining atoms are: ");
    System.out.println(Arrays.toString(remainingAtoms.toArray()));
    if (nextSet.size() == 0) { // Check if Set is empty, if so return values for satisfiable atoms
      satIsSolved = true;
      V.replace(atom, val);
      return;
    }
    DPHelper(nextSet, remainingAtoms);
  }

  public static void DPHelper(LinkedList<HashMap<Integer, Valuation>> nextSet, TreeSet<Integer> remainingAtoms) {
    for (int currentAtom : remainingAtoms) { // Apply DavisPutnam logic to determine next move
      boolean pureLiteral = true, singleClause = false;
      Valuation pureVal = Valuation.UNBOUND;
      for (HashMap<Integer, Valuation> clause : nextSet) { // Check for pure literal and/or single literal clause,
                                                           // perform
        // next
        for (Map.Entry<Integer, Valuation> atomC : clause.entrySet()) { // DavisPutnam step, otherwise default to next
          // unbound atom
          if (clause.size() == 1 && Math.abs(atomC.getKey()) == currentAtom) {
            if (atomC.getKey() > 0) {
              DP(nextSet, atomC.getKey(), Valuation.TRUE);
              if (satIsSolved)
                V.replace(atomC.getKey(), Valuation.TRUE);
              else {
                for (Map.Entry<Integer, Valuation> atomUndo : clause.entrySet()) {
                  if (Math.abs(atomUndo.getKey()) == atomC.getKey())
                    clause.replace(atomUndo.getKey(), Valuation.UNBOUND);
                }
              }
              return;
            } else {
              DP(nextSet, Math.abs(atomC.getKey()), Valuation.FALSE);
              if (satIsSolved)
                V.replace(Math.abs(atomC.getKey()), Valuation.FALSE);
              else {
                for (Map.Entry<Integer, Valuation> atomUndo : clause.entrySet()) {
                  if (Math.abs(atomUndo.getKey()) == atomC.getKey())
                    clause.replace(atomUndo.getKey(), Valuation.UNBOUND);
                }
              }
              return;
            }
          }
          if (Math.abs(atomC.getKey()) == currentAtom) {
            if (atomC.getKey() > 0) {
              if (pureVal == Valuation.UNBOUND)
                pureVal = Valuation.TRUE;
              else if (pureVal != Valuation.TRUE)
                pureLiteral = false;
            } else {
              if (pureVal == Valuation.UNBOUND)
                pureVal = Valuation.FALSE;
              else if (pureVal != Valuation.FALSE)
                pureLiteral = false;
            }
          }
        }
      }
      if (pureLiteral) {
        DP(nextSet, currentAtom, pureVal);
        if (satIsSolved)
          V.replace(currentAtom, pureVal);
        else {
          for (HashMap<Integer, Valuation> clause : nextSet) {
            for (Map.Entry<Integer, Valuation> atomUndo : clause.entrySet()) {
              if (Math.abs(atomUndo.getKey()) == currentAtom)
                clause.replace(atomUndo.getKey(), Valuation.UNBOUND);
            }
          }
        }
        return;
      }
    }
    DP(nextSet, remainingAtoms.first(), Valuation.TRUE);
    if (satIsSolved) {
      V.replace(remainingAtoms.first(), Valuation.TRUE);
      return;
    } else {
      for (HashMap<Integer, Valuation> clause : nextSet) {
        for (Map.Entry<Integer, Valuation> atomUndo : clause.entrySet()) {
          if (Math.abs(atomUndo.getKey()) == remainingAtoms.first())
            clause.replace(atomUndo.getKey(), Valuation.UNBOUND);
        }
      }
    }
    DP(nextSet, remainingAtoms.first(), Valuation.FALSE);
    if (satIsSolved)
      V.replace(remainingAtoms.first(), Valuation.FALSE);
    else {
      for (HashMap<Integer, Valuation> clause : nextSet) {
        for (Map.Entry<Integer, Valuation> atomUndo : clause.entrySet()) {
          if (Math.abs(atomUndo.getKey()) == remainingAtoms.first())
            clause.replace(atomUndo.getKey(), Valuation.UNBOUND);
        }
      }
    }
  }
}