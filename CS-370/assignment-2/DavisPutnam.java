import java.io.IOException;
import java.io.File;
import java.nio.charset.Charset;
import java.nio.file.Files;

import java.util.*;
import java.util.regex.*;

public class DavisPutnam {

  public enum Valuation {
    NULL, UNBOUND, TRUE, FALSE;
  }

  static class Literal {
    public String atom;
    public String literal;
    public boolean isNegated;

    public Literal() {
      atom = null;
      literal = null;
      isNegated = false;
    }

    public Literal(String literalString) {
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

    public Valuation truthEvaluation(Valuation valuation) {
      switch (valuation) {
      case TRUE:
        return isNegated ? Valuation.FALSE : Valuation.TRUE;
      case FALSE:
        return isNegated ? Valuation.TRUE : Valuation.FALSE;
      default:
        return Valuation.NULL;
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
    public boolean isSatisfied;

    public Clause() {
      literals = new LinkedList<Literal>();
      isSatisfied = false;
    }

    // copy constructor
    public Clause(Clause c) {
      literals = new LinkedList<Literal>();
      isSatisfied = c.isSatisfied;

      for (Literal literal : c.literals) {
        literals.add(literal);
      }
    }

    public boolean isNullClause(Valuation valuation) {
      if (literals.size() > 1) {
        return false;
      }

      return literals.get(0).truthEvaluation(valuation) == Valuation.TRUE;
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

    public String getLiteralString() {
      String res = "";

      for (Literal literal : literals) {
        res += literal;
      }

      return res;
    }

    @Override
    public String toString() {
      String res = "";

      for (int i = 0; i < literals.size(); i++) {
        Literal L = literals.get(i);

        if (i < literals.size() - 1) {
          res += (L.literal + ", ");
        } else {
          res += L.literal;
        }
      }

      return res;
    }
  }

  public static boolean evaluateClause(Clause clause, Map<String, Valuation> V) { // <ATOM, TRUTH_VALUE>

    for (Literal L : clause.literals) {
      Valuation valuation = V.get(L.atom);
      if (L.truthEvaluation(valuation) == Valuation.TRUE) {
        return true;
      }
    }

    return false;
  }

  public static class DP {
    LinkedHashSet<String> ATOMS; // set of atoms
    LinkedList<Clause> S; // unique set of clauses
    Stack<Map<String, Valuation>> V; // history of truth evaluations

    // history of the truth assignments
    // this is a representation of the current index of V, useful for backtracking
    int historyIndex;

    String currentAtomValuation;

    public DP(LinkedHashSet<String> ATOMS, LinkedList<Clause> S, Map<String, Valuation> V) {
      this.ATOMS = ATOMS;

      this.S = S;

      this.V = new Stack<Map<String, Valuation>>();
      this.V.add(V);

      historyIndex = 0;
    }

    public Map<String, Valuation> getTruthEvaluation() {
      return V.elementAt(historyIndex);
    }

    // returns whether or not the set of clauses is satisfiable
    public Valuation DP_HELPER() {
      // 1) solution found, S is null, assign remaining UNBOUNDED ATOMS to TRUE
      if (S.isEmpty() || S.size() < 1) {
        for (Map.Entry<String, Valuation> entry : getTruthEvaluation().entrySet()) {
          if (entry.getValue().equals(Valuation.UNBOUND)) {
            entry.setValue(Valuation.TRUE);
          }
        }

        return Valuation.TRUE;
      }

      // loop over clauses
      for (Clause clause : S) {
        // 2) if S contains NULL clause
        if (clause.isNullClause(valuation))
      }

      return Valuation.TRUE;
    }

    public static void main(String[] args) {
      if (args.length == 0) {
        System.out.println("missing input file");
        System.exit(0);
      }

      String filePath = args[0];

      try {
        List<String> lines = Files.readAllLines(new File(filePath).toPath(), Charset.defaultCharset());

        LinkedHashSet<String> ATOMS = new LinkedHashSet<String>(); // set of atoms
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

          // prevents adding duplicates (Sorted Set)
          S.add(clause);
        }

        if (ATOMS.size() < 1) {
          throw new Exception("NO ATOMS");
        }

        if (S.size() < 1) {
          throw new Exception("NO LITERALS");
        }

        DP davisPutnamSolver = new DP(ATOMS, S, V);

        for (Map.Entry<String, Valuation> entry : V.entrySet()) {
          System.out.printf("%s : %s\n", entry.getKey(), entry.getValue() == Valuation.TRUE ? "T" : "F");
        }

        // System.out.println("\n");
        // for (Clause clause : S) {
        // System.out.println(clause);
        // }

        // System.out.println("\n");
        // if (isSat.equals(Valuation.TRUE)) {
        // for (String line : extraLines) {
        // System.out.println(line);
        // }
        // }

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
}