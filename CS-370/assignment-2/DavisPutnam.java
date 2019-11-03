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

    public Clause() {
      literals = new LinkedList<Literal>();
    }

    // copy constructor
    public Clause(Clause c) {
      literals = new LinkedList<Literal>();

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

  public static class DP {
    LinkedList<String> ATOMS;
    Stack<LinkedList<Clause>> S;
    Stack<Map<String, Valuation>> V;

    // history of the truth assignments
    // this is a representation of the current index of V, useful for backtracking
    int historyIndex;
    int currentAtomIndex;

    String currentAtomValuation;

    // boolean isSatisfied;

    public DP(LinkedList<String> ATOMS, LinkedList<Clause> S, Map<String, Valuation> V) {
      this.ATOMS = ATOMS;
      this.S = new Stack<LinkedList<Clause>>();
      this.V = new Stack<Map<String, Valuation>>();

      this.S.add(S);
      this.V.add(V);

      historyIndex = 0;
      currentAtomIndex = 0; // used to keep track of the current atom

      // isSatisfied = true;

      // call DP Helper
      DP_HELPER();
    }

    // evaluate a clause using the current valuation from V at the current index in
    // the history
    public boolean evaluateClause(Clause clause) {

      boolean result = false;

      Valuation valuation = getTruthEvaluation().get(getCurrentValuationAtom());

      for (Literal L : clause.literals) {
        if (L.truthEvaluation(valuation) == Valuation.TRUE) {
          return true;
        }
      }

      return result;
    }

    private String getCurrentValuationAtom() {
      return ATOMS.get(currentAtomIndex);
    }

    private Valuation getCurrentValuation() {
      return getTruthEvaluation().get(ATOMS.get(currentAtomIndex));
    }

    private LinkedList<Clause> getS() {
      return S.elementAt(historyIndex);
    }

    private Map<String, Valuation> getTruthEvaluation() {
      return V.elementAt(historyIndex);
    }

    private void backTrack() {

    }

    private void propagate() {
      if (getCurrentValuation().equals(Valuation.UNBOUND)) {
        return;
      }

      for (String string : ATOMS) {

      }
    }

    private boolean isNullClause(Clause clause) {
      if (!clause.hasOnlyOneLiteral()) {
        return true;
      }

      Literal L = clause.literals.getLast();
      Valuation valuation = L.truthEvaluation(getTruthEvaluation().get(L.atom));

      return !valuation.equals(Valuation.TRUE);
    }

    private boolean isSatisfied() {

      for (Clause clause : getS()) {
        for (Literal L : clause.literals) {
          if (getTruthEvaluation().get(L.atom).equals(Valuation.TRUE)) {
            return true;
          }
        }
      }

      return true;
    }

    // returns whether or not the set of clauses is satisfiable
    public void DP_HELPER() {
      // 1) solution found, S is null, assign remaining UNBOUNDED ATOMS to TRUE
      if (S.isEmpty() || S.size() < 1) {
        for (Map.Entry<String, Valuation> entry : getTruthEvaluation().entrySet()) {
          if (entry.getValue().equals(Valuation.UNBOUND)) {
            entry.setValue(Valuation.TRUE);
          }
        }
      }

      // used for checking if there are any literals with only one sign
      LinkedHashSet<String> literalSet = new LinkedHashSet<String>();

      // loop over clauses
      for (Clause clause : getS()) {
        // 2) if S contains NULL clause, backtrack
        if (isNullClause(clause)) {
          backTrack();
        }

        for (Literal literal : clause.literals) {
          if (!literalSet.contains(literal.literal)) {
            literalSet.add(literal.literal);
          }
        }

        // 4) S contains a clause with only one literal
        if (clause.hasOnlyOneLiteral()
            && getTruthEvaluation().get(clause.literals.get(0).atom).equals(Valuation.UNBOUND)) {
          Valuation val = clause.literals.get(0).isNegated ? Valuation.FALSE : Valuation.TRUE;
          getTruthEvaluation().replace(clause.literals.get(0).atom, val);
        }
      }

      for (String literalString : literalSet) {
        boolean isNegated = literalString.contains("-");
        boolean isOnlyOneSign = !literalSet.contains(isNegated ? literalString.substring(1) : "-" + literalString);
        String atom = isNegated ? literalString.substring(1) : literalString;

        if (isOnlyOneSign && getTruthEvaluation().get(atom).equals(Valuation.UNBOUND)) {

          getTruthEvaluation().replace(atom, isNegated ? Valuation.FALSE : Valuation.TRUE);
          System.out.printf("FOUND ONLY ONE SIGN, %S, %S\n", atom, isNegated ? Valuation.FALSE : Valuation.TRUE);
        }
      }

      propagate();

      int i = 0;
      for (Map.Entry<String, Valuation> entry : getTruthEvaluation().entrySet()) {
        Valuation valuation = entry.getValue();

        if (valuation.equals(Valuation.UNBOUND)) {
          getTruthEvaluation().replace(entry.getKey(), Valuation.TRUE);
          break;
        }

        // can't assign true to any remaining items in V
        if (i == ATOMS.size() - 1) {
          backTrack();
        }

        i++;
      }

      if (isSatisfied()) {
        return;
      }

      LinkedList<Clause> SC = new LinkedList<Clause>();
      for (Clause clause : getS()) {
        SC.push(new Clause(clause));
      }
      S.add(SC);

      Map<String, Valuation> VC = new HashMap<String, Valuation>();
      for (Map.Entry<String, Valuation> entry : getTruthEvaluation().entrySet()) {
        Valuation valuation = Valuation.UNBOUND;

        switch (entry.getValue()) {
        case TRUE:
          valuation = Valuation.TRUE;
          break;
        case FALSE:
          valuation = Valuation.FALSE;
        case NULL:
          valuation = Valuation.NULL;
        default:
          break;
        }

        VC.put(entry.getKey(), valuation);
      }
      V.add(VC);

      historyIndex++;

      DP_HELPER();
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

      // for (Map.Entry<String, Valuation> entry : V.entrySet()) {
      // System.out.printf("%s : %s\n", entry.getKey(), entry.getValue() ==
      // Valuation.TRUE ? "T" : "F");
      // }

      // System.out.println("\n");
      // for (Clause clause : S) {
      // System.out.println(clause);
      // }

      if (davisPutnamSolver.isSatisfied()) {
        for (Map.Entry<String, Valuation> entry : davisPutnamSolver.V.lastElement().entrySet()) {
          System.out.printf("%S : %S\n", entry.getKey(), entry.getValue());
        }
      } else {
        System.out.println("0");
      }

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