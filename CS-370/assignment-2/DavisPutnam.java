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

    public Literal() {
      this.atom = null;
      this.literal = null;
      this.isNegated = false;
    }

    public Literal(String literalString) {
      this.literal = literalString;

      Matcher matcher = Pattern.compile("[1-9]+").matcher(literal);

      if (matcher.find()) {
        this.atom = matcher.group(0);
      } else {
        System.out.printf("INVALID LITERAL: %s\n", literal);
        System.exit(-1);
      }

      if (literal.contains("-")) {
        this.isNegated = true;
      } else {
        this.isNegated = false;
      }
    }

    @Override
    public int hashCode() {
      return literal.hashCode();
    }

    @Override
    public boolean equals(Object obj) {
      if (obj instanceof Literal) {
        return ((Literal) obj).literal.equals(this.literal);
      }

      return false;
    }
  }

  static class Clause implements Comparable<Clause> {
    public LinkedList<Literal> literals;
    public boolean isSatisfied;

    public Clause() {
      this.literals = new LinkedList<Literal>();
      this.isSatisfied = false;
    }

    // copy constructor
    public Clause(Clause c) {
      this.literals = new LinkedList<Literal>();
      this.isSatisfied = c.isSatisfied;

      for (Literal literal : c.literals) {
        this.literals.add(literal);
      }
    }

    public Literal getLiteral(String literalString) {
      for (Literal literal : literals) {
        if (literal.literal.equals(literalString)) {
          return literal;
        }
      }

      return new Literal();
    }

    @Override
    public int hashCode() {
      String res = "";

      for (Literal literal : this.literals) {
        res += literal;
      }

      return res.hashCode();
    }

    @Override
    public boolean equals(Object obj) {
      if (obj instanceof Clause) {
        Clause otherClause = (Clause) obj;

        if (this.literals.size() != otherClause.literals.size()) {
          return false;
        }

        for (int i = 0; i < this.literals.size(); i++) {
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

      for (Literal literal : this.literals) {
        res += literal;
      }

      return res;
    }

    @Override
    public int compareTo(Clause clause) {
      return this.getLiteralString().compareTo(clause.getLiteralString());
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

  // returns whether or not the set of clauses is satisfiable
  public static boolean DP_HELPER(SortedSet<String> ATOMS, SortedSet<Clause> S, Map<String, Valuation> V) {
    // solution found, S is null
    // if (S.isEmpty()) {
    for (Map.Entry<String, Valuation> entry : V.entrySet()) {
      entry.setValue(Valuation.TRUE);
    }
    // }

    return true;
  }

  public static void main(String[] args) {
    if (args.length == 0) {
      System.out.println("missing input file");
      System.exit(0);
    }

    String filePath = args[0];

    try {
      List<String> lines = Files.readAllLines(new File(filePath).toPath(), Charset.defaultCharset());

      SortedSet<String> ATOMS = new TreeSet<String>(); // set of atoms
      SortedSet<Clause> S = new TreeSet<Clause>(); // unique set of clauses
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

      boolean isSat = DP_HELPER(ATOMS, S, V);

      for (Map.Entry<String, Valuation> entry : V.entrySet()) {
        System.out.printf("%s : %s\n", entry.getKey(), entry.getValue() == Valuation.TRUE ? "T" : "F");
      }

      System.out.println("\n");
      for (Clause clause : S) {
        System.out.println(clause);
      }

      System.out.println("\n");
      if (isSat) {
        for (String line : extraLines) {
          System.out.println(line);
        }
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