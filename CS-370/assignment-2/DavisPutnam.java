import java.io.IOException;
import java.io.File;
import java.nio.charset.Charset;
import java.nio.file.Files;

import java.util.*;
import java.util.regex.*;

public class DavisPutnam {

  public enum AtomValue {
    UNBOUND, TRUE, FALSE;
  }

  static class Atom {
    public String atom;

    public Atom() {
      this.atom = null;
    }

    public Atom(String literal) {
      Matcher matcher = Pattern.compile("[1-9]+").matcher(literal);

      if (matcher.find()) {
        this.atom = matcher.group(0);
      } else {
        System.out.printf("INVALID LITERAL: %s\n", literal);
        System.exit(-1);
      }
    }

    public Atom getAtomObj() {
      return this;
    }

    @Override
    public int hashCode() {
      return this.atom.hashCode();
    }

    @Override
    public boolean equals(Object obj) {
      if (obj instanceof Atom) {
        return ((Atom) obj).atom.equals(this.atom);
      }

      return false;
    }
  }

  static class Literal extends Atom {
    public String literal;
    public boolean isNegated;

    public Literal() {
      super();
      this.literal = null;
      this.isNegated = false;
    }

    public Literal(String literalString) {
      super(literalString);
      this.literal = literalString;

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

  static class Clause {
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

  public void DP_HELPER() {

  }

  public static void main(String[] args) {
    if (args.length == 0) {
      System.out.println("missing input file");
      System.exit(0);
    }

    String filePath = args[0];

    try {
      List<String> lines = Files.readAllLines(new File(filePath).toPath(), Charset.defaultCharset());

      List<Clause> S = new LinkedList<Clause>(); // unique set of clauses
      Map<String, AtomValue> V = new HashMap<String, AtomValue>(); // truth assignments per atoms

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

        Clause clause = new Clause();

        for (String literal : line.split("\\s")) {
          Literal L = new Literal(literal);

          if (!V.containsKey(L.atom)) {
            V.put(L.atom, AtomValue.UNBOUND);
          }

          clause.literals.add(L);
        }

        /*
         * I didn't want to use Set interface as I want to have the ability to retrieve
         * elements by index
         */
        if (!S.contains(clause)) {
          S.add(clause);
        }
      }

      for (Map.Entry<String, AtomValue> entry : V.entrySet()) {
        System.out.printf("%s : %s\n", entry.getKey(), entry.getValue());
      }

      for (Clause clause : S) {
        System.out.println(clause);
      }

    } catch (IOException e) {
      System.out.printf("Unable to open file, \"%s\"\n", filePath);
      System.exit(1);
    } catch (Exception e) {
      System.out.println("Error parsing input file");
      System.out.println(e);
      System.exit(1);
    }
  }
}