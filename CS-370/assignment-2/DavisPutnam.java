import java.io.IOException;
import java.io.File;
import java.nio.charset.Charset;
import java.nio.file.Files;

import java.util.*;

public class DavisPutnam {

  static class Atom {
    String ident; // atom identifier
    boolean isNegated;

    public Atom(String atom) {
      this.ident = atom;

      if (ident.contains("-")) {
        this.isNegated = true;
      } else {
        this.isNegated = false;
      }
    }
  }

  static class Clause {
    Atom[] atoms;
    boolean isSatisfied;

    public Clause() {
      this.atoms = new Atom[] {};
      this.isSatisfied = false;
    }

    public Clause(Atom[] atoms) {
      this.atoms = atoms;
      this.isSatisfied = false;
    }

    @Override
    public String toString() {
      String res = "";

      for (int i = 0; i < atoms.length; i++) {
        Atom atom = this.atoms[i];

        if (i < atoms.length - 1) {
          res += (atom.ident + " ");
        } else {
          res += atom.ident;
        }
      }

      return res;
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

      LinkedList<Clause> clauses = new LinkedList<Clause>();

      for (String line : lines) {
        line = line.trim();

        if (line.equals("0")) {
          break;
        }

        LinkedList<Atom> atoms = new LinkedList<Atom>();
        String[] atomStrings = line.split(" ");

        for (String atom : atomStrings) {
          atoms.add(new Atom(atom));
        }

        clauses.add(new Clause(atoms.toArray(new Atom[atoms.size()])));
      }

      for (Clause clause : clauses) {
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