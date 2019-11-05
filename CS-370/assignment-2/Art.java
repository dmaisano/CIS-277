import java.util.*;
import java.io.File;
import java.io.FileNotFoundException;
import java.lang.Math;

public class Art {
  private static Scanner input;

  private static boolean endOfClauses = false, solvedSet = false;
  private static int numClauses, numAtoms;
  private static ArrayList<HashMap<Integer, AtomVal>> clauseList;
  private static HashMap<Integer, AtomVal> atomList;
  private static ArrayList<String> fileLines;

  public enum AtomVal {
    TRUE, FALSE, UNBOUND, NULL, TRUEORFALSE
  }

  public static void main(String[] args) {
    clauseList = new ArrayList<HashMap<Integer, AtomVal>>();
    atomList = new HashMap<Integer, AtomVal>();
    fileLines = new ArrayList<String>();
    try {
      File inputText = new File(args[0]);
      input = new Scanner(inputText);
      while (!endOfClauses) {
        String nextLine = input.nextLine();
        if (nextLine.equalsIgnoreCase("0"))
          endOfClauses = true;
        else {
          String[] clauseString = nextLine.split(" ");
          try {
            int[] clause = new int[clauseString.length];
            HashMap<Integer, AtomVal> tempMap = new HashMap<Integer, AtomVal>();
            for (int index = 0; index < clause.length; index++) {
              clause[index] = Integer.valueOf(clauseString[index]);
              tempMap.put(clause[index], AtomVal.UNBOUND);
              atomList.put(Math.abs(clause[index]), AtomVal.UNBOUND);
            }
            clauseList.add(tempMap);
          } catch (Exception e) {
            System.out.println("Invalid Atom! Davis Putnam cannot be applied");
            System.exit(0);
          }
        }
      }
      System.out.println(Arrays.toString(clauseList.toArray()));
      System.out.println(atomList);
      TreeSet<Integer> allAtoms = new TreeSet<Integer>();
      for (Map.Entry<Integer, AtomVal> atomC : atomList.entrySet()) {
        allAtoms.add(atomC.getKey());
      }
      DPHelper(clauseList, allAtoms);
      if (solvedSet) {
        for (Map.Entry<Integer, AtomVal> atomC : atomList.entrySet()) {
          if (atomC.getValue() == AtomVal.UNBOUND)
            atomList.replace(atomC.getKey(), AtomVal.TRUEORFALSE);
        }
        System.out.println("SATISFIABLE BY: " + atomList);
      } else
        System.out.println("Not satisfiable");
      while (input.hasNext()) {
        System.out.println(input.nextLine());
      }
    } catch (FileNotFoundException e) {
      System.out.println("ERROR: File not found");
    }
  }

  public static void DP(ArrayList<HashMap<Integer, AtomVal>> currentSet, int atom, AtomVal val) {
    ArrayList<HashMap<Integer, AtomVal>> nextSet = new ArrayList<HashMap<Integer, AtomVal>>();
    TreeSet<Integer> remainingAtoms = new TreeSet<Integer>();
    System.out.println("Applying atom " + atom + " as " + val + "...");
    for (HashMap<Integer, AtomVal> clause : currentSet) {
      boolean nullClause = true;
      boolean removeClause = false;
      Set<Integer> tempAtoms = new TreeSet<Integer>();
      for (Map.Entry<Integer, AtomVal> atomC : clause.entrySet()) {
        if (atomC.getValue() != AtomVal.NULL) {
          if (Math.abs(atomC.getKey()) == atom) {
            if (atomC.getKey() == atom) { // Apply atom and truth expression to current set of clauses
              if (val == AtomVal.TRUE) {
                removeClause = true;
                nullClause = false;
              } else
                clause.replace(atomC.getKey(), AtomVal.NULL);
            } else {
              if (val == AtomVal.FALSE) {
                removeClause = true;
                nullClause = false;
              } else
                clause.replace(atomC.getKey(), AtomVal.NULL);
            }
          } else {
            tempAtoms.add(Math.abs(atomC.getKey()));
            nullClause = false;
          }
        }
      }
      if (nullClause) {
        System.out.println("Null clause: " + clause);
        for (Map.Entry<Integer, AtomVal> atomC : clause.entrySet()) {
          if (Math.abs(atomC.getKey()) == atom)
            clause.replace(atomC.getKey(), AtomVal.UNBOUND);
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
      solvedSet = true;
      atomList.replace(atom, val);
      return;
    }
    DPHelper(nextSet, remainingAtoms);
  }

  public static void DPHelper(ArrayList<HashMap<Integer, AtomVal>> nextSet, TreeSet<Integer> remainingAtoms) {
    for (int currentAtom : remainingAtoms) { // Apply DavisPutnam logic to determine next move
      boolean pureLiteral = true, singleClause = false;
      AtomVal pureVal = AtomVal.UNBOUND;
      for (HashMap<Integer, AtomVal> clause : nextSet) { // Check for pure literal and/or single literal clause, perform
                                                         // next
        for (Map.Entry<Integer, AtomVal> atomC : clause.entrySet()) { // DavisPutnam step, otherwise default to next
                                                                      // unbound atom
          if (clause.size() == 1 && Math.abs(atomC.getKey()) == currentAtom) {
            if (atomC.getKey() > 0) {
              DP(nextSet, atomC.getKey(), AtomVal.TRUE);
              if (solvedSet)
                atomList.replace(atomC.getKey(), AtomVal.TRUE);
              else {
                for (Map.Entry<Integer, AtomVal> atomUndo : clause.entrySet()) {
                  if (Math.abs(atomUndo.getKey()) == atomC.getKey())
                    clause.replace(atomUndo.getKey(), AtomVal.UNBOUND);
                }
              }
              return;
            } else {
              DP(nextSet, Math.abs(atomC.getKey()), AtomVal.FALSE);
              if (solvedSet)
                atomList.replace(Math.abs(atomC.getKey()), AtomVal.FALSE);
              else {
                for (Map.Entry<Integer, AtomVal> atomUndo : clause.entrySet()) {
                  if (Math.abs(atomUndo.getKey()) == atomC.getKey())
                    clause.replace(atomUndo.getKey(), AtomVal.UNBOUND);
                }
              }
              return;
            }
          }
          if (Math.abs(atomC.getKey()) == currentAtom) {
            if (atomC.getKey() > 0) {
              if (pureVal == AtomVal.UNBOUND)
                pureVal = AtomVal.TRUE;
              else if (pureVal != AtomVal.TRUE)
                pureLiteral = false;
            } else {
              if (pureVal == AtomVal.UNBOUND)
                pureVal = AtomVal.FALSE;
              else if (pureVal != AtomVal.FALSE)
                pureLiteral = false;
            }
          }
        }
      }
      if (pureLiteral) {
        DP(nextSet, currentAtom, pureVal);
        if (solvedSet)
          atomList.replace(currentAtom, pureVal);
        else {
          for (HashMap<Integer, AtomVal> clause : nextSet) {
            for (Map.Entry<Integer, AtomVal> atomUndo : clause.entrySet()) {
              if (Math.abs(atomUndo.getKey()) == currentAtom)
                clause.replace(atomUndo.getKey(), AtomVal.UNBOUND);
            }
          }
        }
        return;
      }
    }
    DP(nextSet, remainingAtoms.first(), AtomVal.TRUE);
    if (solvedSet) {
      atomList.replace(remainingAtoms.first(), AtomVal.TRUE);
      return;
    } else {
      for (HashMap<Integer, AtomVal> clause : nextSet) {
        for (Map.Entry<Integer, AtomVal> atomUndo : clause.entrySet()) {
          if (Math.abs(atomUndo.getKey()) == remainingAtoms.first())
            clause.replace(atomUndo.getKey(), AtomVal.UNBOUND);
        }
      }
    }
    DP(nextSet, remainingAtoms.first(), AtomVal.FALSE);
    if (solvedSet)
      atomList.replace(remainingAtoms.first(), AtomVal.FALSE);
    else {
      for (HashMap<Integer, AtomVal> clause : nextSet) {
        for (Map.Entry<Integer, AtomVal> atomUndo : clause.entrySet()) {
          if (Math.abs(atomUndo.getKey()) == remainingAtoms.first())
            clause.replace(atomUndo.getKey(), AtomVal.UNBOUND);
        }
      }
    }
  }
}