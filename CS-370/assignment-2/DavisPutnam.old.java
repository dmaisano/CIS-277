import java.io.IOException;
import java.io.File;
import java.nio.charset.Charset;
import java.nio.file.Files;

import java.util.*;
import java.util.regex.*;

public class DavisPutnam {

  public enum Valuation {
    UNBOUND, TRUE, FALSE;
  }

  static class Literal {
    public String atom;
    public String literal;
    public boolean isNegated;
    public boolean isBackTracked;

    public Literal() {
      atom = null;
      literal = null;
      isNegated = false;
      isBackTracked = false;
    }

    public Literal(String literalString) {
      setLiteralString(literalString);

      isBackTracked = false;
    }

    public Literal(String literalString, boolean isBackTracked) {
      setLiteralString(literalString);

      this.isBackTracked = isBackTracked;
    }

    // copy constructor
    public Literal(Literal L) {
      atom = L.atom;
      literal = L.literal;
      isNegated = L.isNegated;
      isBackTracked = L.isBackTracked;
    }

    private void setLiteralString(String literalString) {
      literal = literalString;

      Matcher matcher = Pattern.compile("\\d+").matcher(literal);

      if (matcher.find()) {
        atom = matcher.group(0);
      } else {
        System.out.printf("INVALID LITERAL: %s\n", literal);
        System.exit(-1);
      }

      if (literal.contains("-")) {
        isNegated = true;
      } else {
        isNegated = false;
      }
    }

    /**
     * If a literal is negated, it may only be TRUE, if the assignment of that atom
     * is FALSE, else TRUE
     */
    public Valuation appropriateValuation() {
      if (isNegated) {
        return Valuation.FALSE;
      }

      return Valuation.TRUE;
    }

    /**
     * Returns TRUE based on the current set of assignments and negation of the
     * literal
     * 
     * @param V truth assignment map
     * @return appropriate valuation
     */
    public Valuation truthEvaluation(Map<String, Valuation> V) {
      switch (V.get(atom)) {
      case TRUE:
        if (isNegated) {
          return Valuation.FALSE;
        } else {
          return Valuation.TRUE;
        }
      case FALSE:
        if (isNegated) {
          return Valuation.TRUE;
        } else {
          return Valuation.FALSE;
        }
      default:
        return Valuation.UNBOUND;
      }
    }

    @Override
    public int hashCode() {
      return literal.hashCode();
    }

    @Override
    public boolean equals(Object obj) {
      if (obj instanceof Literal) {
        return ((Literal) obj).literal.equals(literal);
      }

      return false;
    }
  }

  static class Clause {
    public LinkedList<Literal> literals;

    public Clause() {
      literals = new LinkedList<Literal>();
    }

    // copy constructor
    public Clause(Clause c) {
      literals = new LinkedList<Literal>();

      for (Literal literal : c.literals) {
        literals.add(new Literal(literal));
      }
    }

    public boolean isNullClause(Map<String, Valuation> V) {
      for (Literal literal : literals) {
        switch (V.get(literal.atom)) {
        case TRUE:
        case UNBOUND:
          return false;
        default:
          break;
        }
      }

      Literal L = literals.get(0);

      return L.truthEvaluation(V) != Valuation.TRUE;
    }

    public boolean hasOnlyOneLiteral() {
      return literals.size() == 1;
    }

    public Literal getLiteral(String literalString) {
      for (Literal literal : literals) {
        if (literal.literal.equals(literalString)) {
          return literal;
        }
      }

      return null;
    }

    @Override
    public int hashCode() {
      String res = "";

      for (Literal literal : literals) {
        res += literal;
      }

      return res.hashCode();
    }

    @Override
    public boolean equals(Object obj) {
      if (obj instanceof Clause) {
        Clause otherClause = (Clause) obj;

        if (literals.size() != otherClause.literals.size()) {
          return false;
        }

        for (int i = 0; i < literals.size(); i++) {
          Literal lit1 = literals.get(i);
          Literal lit2 = otherClause.literals.get(i);

          if (!lit1.equals(lit2)) {
            return false;
          }
        }

        return true;
      }

      return false;
    }

    @Override
    public String toString() {
      String res = "";

      for (int i = 0; i < literals.size(); i++) {
        Literal L = literals.get(i);

        if (i < literals.size() - 1) {
          res += (L.literal + " ");
        } else {
          res += L.literal;
        }
      }

      return res;
    }
  }

  public static class DP {
    LinkedList<String> ATOMS;
    LinkedList<Clause> ORIGINAL_S;
    Map<String, Valuation> ORIGINAL_V;

    LinkedList<Clause> S;
    Map<String, Valuation> V;

    LinkedList<Literal> ASSIGNED_ATOMS;

    int NUM_BACKTRACKED_ATOMS;

    boolean IS_SATISFIED;

    public DP(LinkedList<String> ATOMS, LinkedList<Clause> S, Map<String, Valuation> V) {
      this.ATOMS = ATOMS;

      ORIGINAL_S = S;
      ORIGINAL_V = V;

      this.S = DP.DEEP_COPY(ORIGINAL_S);
      this.V = DP.DEEP_COPY(ORIGINAL_V);

      ASSIGNED_ATOMS = new LinkedList<Literal>();

      NUM_BACKTRACKED_ATOMS = 0;

      IS_SATISFIED = DP_HELPER();
    }

    public static LinkedList<Clause> DEEP_COPY(LinkedList<Clause> S) {
      LinkedList<Clause> copy = new LinkedList<Clause>();

      for (Clause clause : S) {
        copy.add(new Clause(clause));
      }

      return copy;
    }

    public static HashMap<String, Valuation> DEEP_COPY(Map<String, Valuation> V) {
      HashMap<String, Valuation> copy = new HashMap<String, Valuation>();

      for (Map.Entry<String, Valuation> entry : V.entrySet()) {
        String atom = entry.getKey();
        Valuation valuation;

        switch (entry.getValue()) {
        case TRUE:
          valuation = Valuation.TRUE;
        case FALSE:
          valuation = Valuation.FALSE;
        default:
          valuation = Valuation.UNBOUND;
          break;
        }

        copy.put(atom, valuation);
      }

      return copy;
    }

    /**
     * Reassign existing assigned valuations
     */
    private void valuationAssignment() {
      for (Literal L : ASSIGNED_ATOMS) {
        V.replace(L.atom, L.truthEvaluation(V));
      }
    }

    private void findLiteralsWithOneSign() {
      // <atom, isNegated>
      Map<String, Boolean> foundLiterals = new HashMap<String, Boolean>();

      // <atom, valuation>
      Map<String, Valuation> uniqueLiterals = new HashMap<String, Valuation>();

      for (Clause clause : S) {
        for (Literal L : clause.literals) {
          if (!foundLiterals.containsKey(L.atom)) {
            foundLiterals.put(L.atom, L.isNegated);
            uniqueLiterals.put(L.atom, L.appropriateValuation());
          } else {
            // determine if existing literal is of same sign, else remove from the unique
            // set
            if (foundLiterals.get(L.atom) != L.isNegated) {
              if (foundLiterals.containsKey(L.atom)) {
                uniqueLiterals.remove(L.atom);
                // TODO: check if backtracking logic is necessary
              }
            }
          }
        }
      }

      for (Map.Entry<String, Valuation> entry : uniqueLiterals.entrySet()) {
        String atom = entry.getKey();
        Valuation valuation = entry.getValue();

        if (V.get(atom) == Valuation.UNBOUND) {
          V.replace(atom, valuation);
        } else {
          System.out.printf("ALREADY ASSIGNED ATOM: %S, %S\n", atom, valuation);
        }
      }
    }

    /**
     * Searches the clauses in S, For every clause with one literal, we assign the
     * appropriate value. Returns true is no errors, false is backtrack failed (no
     * solution)
     */
    private boolean oneLiteralEvaluation() {
      for (Clause clause : S) {
        if (clause.literals.size() > 1) {
          return true;
        }

        Literal L = clause.literals.get(0);

        // null clause, valuation already assigned to atom, so backtrack
        if (V.get(L.atom) != Valuation.UNBOUND) {
          if (!backTrack()) {
            return false;
          }
          ;
        } else {
          V.replace(L.atom, L.appropriateValuation());
        }
      }

      return true;
    }

    private boolean backTrack() {
      for (int i = ASSIGNED_ATOMS.size() - 1; i >= 0; i--) {
        Literal L = ASSIGNED_ATOMS.get(i);

        if (L.isBackTracked == false) {
          // set the last assigned valuation to false and propagate
          Valuation newValuation = L.truthEvaluation(V) == Valuation.TRUE ? Valuation.FALSE : Valuation.TRUE;

          // reset V
          this.V = DEEP_COPY(ORIGINAL_V);

          valuationAssignment();

          V.replace(L.atom, newValuation);
          NUM_BACKTRACKED_ATOMS++;
          return true;
        }
      }

      return false;
    }

    private boolean propagate() {
      ListIterator<Clause> clauses = S.listIterator();
      while (clauses.hasNext()) {
        Clause clause = clauses.next();

        boolean clauseIsSat = false;

        ListIterator<Literal> literals = clause.literals.listIterator();
        while (literals.hasNext()) {
          Literal L = literals.next();

          Valuation valuation = L.truthEvaluation(V);

          if (valuation == Valuation.TRUE) {
            clauseIsSat = true;
            break;
          }

          if (valuation == Valuation.FALSE) {
            literals.remove();
          }

          // ! null clause, backtrack
          // if (!literals.hasNext()) {
          // return backTrack();
          // }
        }

        if (clauseIsSat) {
          clauses.remove();
        }
      }

      return true;
    }

    /**
     * Returns true if able to assign a new UNBOUND atom, else false
     */
    private boolean assignUnbound() {
      boolean assignedUnboundAtom = false;
      for (Map.Entry<String, Valuation> entry : V.entrySet()) {
        String atom = entry.getKey();
        Valuation valuation = entry.getValue();

        if (valuation != Valuation.UNBOUND) {
          continue;
        } else {
          assignedUnboundAtom = true;
          V.replace(atom, Valuation.TRUE);
          ASSIGNED_ATOMS.push(new Literal);
          break;
        }
      }

      return assignedUnboundAtom;
    }

    /**
     * loop through all clauses and checks if any clause is not satisfied
     */
    private boolean isSatisfied() {

      for (Clause clause : ORIGINAL_S) {
        boolean clauseIsSat = false;

        for (Literal L : clause.literals) {
          if (L.truthEvaluation(V) == Valuation.TRUE) {
            clauseIsSat = true;
            break;
          }
        }

        if (clauseIsSat == false) {
          return false;
        }
      }

      return true;
    }

    private boolean DP_HELPER() {
      valuationAssignment();

      // ? 1) S is null (solved)
      if (S.size() < 1) {
        return true;
      }

      // ? 2) S contains a NULL clause
      for (Clause clause : S) {
        if (clause.isNullClause(V)) {
          System.out.println("NULL CLAUSE, BACKTRACK");
          if (!backTrack()) {
            return false;
          }
        }
      }

      // ? 3) Some literal, L, appears with only one sign
      findLiteralsWithOneSign();

      // ? 4) S contains a clause with one literal
      if (!oneLiteralEvaluation()) {
        return false;
      }

      // ? 5) propagate
      if (!propagate()) {
        return false;
      }

      // ? check if original clauses are satisfied
      if (isSatisfied()) {
        return true;
      }

      S = DEEP_COPY(S);
      V = DEEP_COPY(V);

      // ? 6) choose UNBOUND ATOM A, assign A = TRUE
      assignUnbound();

      if (!propagate()) {
        return false;
      }

      return DP_HELPER();
    }
  }

  public static void main(String[] args) {
    if (args.length == 0) {
      System.out.println("missing input file");
      System.exit(0);
    }

    String filePath = args[0];

    try {
      List<String> lines = Files.readAllLines(new File(filePath).toPath(), Charset.defaultCharset());

      LinkedList<String> ATOMS = new LinkedList<String>(); // set of atoms
      LinkedList<Clause> S = new LinkedList<Clause>(); // unique set of clauses

      Map<String, Valuation> V = new HashMap<String, Valuation>(); // truth assignments per atoms

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

        Clause clause = new Clause();

        for (String literal : line.split("\\s")) {
          Literal L = new Literal(literal);

          // set initial atoms in V to UNBOUND
          if (!V.containsKey(L.atom)) {
            ATOMS.add(L.atom);
            V.put(L.atom, Valuation.UNBOUND);
          }

          clause.literals.add(L);
        }

        if (!S.contains(clause)) {
          S.add(clause);
        }
      }

      if (ATOMS.size() < 1) {
        throw new Exception("NO ATOMS");
      }

      if (S.size() < 1) {
        throw new Exception("NO LITERALS");
      }

      DP davisPutnamSolver = new DP(ATOMS, S, V);

      if (davisPutnamSolver.IS_SATISFIED == true) {
        for (Map.Entry<String, Valuation> entry : davisPutnamSolver.V.entrySet()) {
          System.out.printf("%S %S\n", entry.getKey(), entry.getValue().equals(Valuation.TRUE) ? "T" : "F");
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