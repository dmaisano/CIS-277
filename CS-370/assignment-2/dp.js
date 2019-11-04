const { existsSync, readFileSync } = require("fs");
const { join } = require("path");

function DEEP_COPY(obj) {
  return JSON.parse(JSON.stringify(obj));
}

class Literal {
  /**
   * @param {string} literal
   * @returns {boolean}
   */
  static IsValidLiteral(literal) {
    return new RegExp("\\d+").test(literal);
  }

  /**
   * @param {string} literal
   */
  static IsNegated(literal) {
    return literal.includes("-");
  }

  /**
   * @param {string} literal
   */
  static GetAtom(literal) {
    // console.log({
    //   literal,
    // });
    return literal.match(new RegExp("\\d+"))[0];
  }

  /**
   * @param {string} literal
   * @param {Object} V
   */
  static IsSatisfied(V, literal) {
    const isNegated = Literal.IsNegated(literal);
    const atom = Literal.GetAtom(literal);

    if (isNegated) {
      return V[atom] === false;
    } else {
      return V[atom] === true;
    }
  }
}

class DP {
  /**
   * @param {Array<string>} ATOMS
   * @param {Array<Array<String>>} S
   * @param {Object} V
   */
  constructor(S, V) {
    /** @type {Array<string>} */
    this.ATOMS = Object.keys(V);
    /** @type {Array<Array<String>>} */
    this.ORIGINAL_S = S;
    /** @type {Object} */
    this.ORIGINAL_V = V;

    /** @private {Array<Array<String>>} */
    this.S = DEEP_COPY(this.ORIGINAL_S);
    /** @private {Array<Array<String>>} */
    this.V = DEEP_COPY(this.ORIGINAL_V);

    // console.log("=== S ===");
    // console.log(this.S);
    // console.log("=== V ===");
    // console.log(this.V);

    /**
     * @constant
     * @private {Array<Object>}
     */
    this.assignedAtoms = [];

    /**
     * @private {number}
     */
    this.backTrackedAtoms;

    this.isSatisfied = this.DP_HELPER();
  }

  /**
   * @private
   * @param {Array<string>} clause
   * @returns {boolean}
   */
  isNullClause(clause) {
    if (clause.length > 1) return false;

    const literal = clause[0];

    const valuation = this.V[Literal.GetAtom(literal)];

    if (valuation === "UNBOUND") {
      return false;
    }

    if (Literal.IsNegated(literal)) {
      return valuation === true;
    } else {
      return valuation === false;
    }
  }

  propagate() {
    // loop over clauses in S
    for (let i = this.S.length - 1; i >= 0; i--) {
      let isSatisfied = false;

      for (let j = this.S[i].length - 1; j >= 0; j--) {
        const literal = this.S[i][j];
        const valuation = this.V[Literal.GetAtom(literal)];

        // clause is satisfiable
        if (Literal.IsSatisfied(this.V, literal)) {
          isSatisfied = true;
          break;
        }

        // remove false literals
        if (valuation === false) {
          // console.log("Removing literal:", this.S[i][j]);
          this.S[i].splice(j, 1);

          // remove empty clauses
          if (this.S[i]) continue;
        }
      }

      // remove satisfied clause from S
      if (isSatisfied) {
        // console.log("Removing Sat Clause:", this.S[i]);
        this.S.splice(i, 1);
      }
    }
  }

  /**
   * returns false if can't backtrack any further
   * else returns true (successful backtrack)
   * @private
   * @return {boolean}
   */
  backTrack() {
    // already backtracked all existing atoms
    if (this.backTrackedAtoms === this.ATOMS.length - 1) return null;

    if (this.assignedAtoms.length < 1) return null;

    for (let i = this.assignedAtoms.length - 1; i >= 0; i--) {
      const assignedAtom = this.assignedAtoms[i];

      // console.log()

      if (assignedAtom.backTracked === false) {
        assignedAtom.valuation = !assignedAtom.valuation;
        assignedAtom.backTracked = true;

        // reset V
        this.V = this.ORIGINAL_V;

        for (const { atom, valuation } of this.assignedAtoms) {
          this.V[atom] = valuation;
        }

        this.V[assignedAtom.atom] = !assignedAtom.valuation;
        this.backTrackedAtoms++;
        // console.log(this.V);
        return true;
      }
    }

    return null;
  }

  /**
   * @private
   */
  DP_HELPER() {
    // console.log("=== S ===");
    // console.log(this.S);
    // console.log("=== V ===");
    // console.log(this.V);

    // console.log("=== ASSIGNED ATOMS ===");
    // console.log(this.assignedAtoms);
    // reassign any previously assigned values
    for (const { atom, valuation } of this.assignedAtoms) {
      this.V[atom] = valuation;
    }

    // ? S is null (already solved)
    if (this.S.length < 1) return true;

    // used to keep track of literals with only one sign
    const literalTracker = {};

    for (let i = this.S.length - 1; i >= 0; i--) {
      /** @type {Array<string>} */
      const clause = this.S[i];

      // ? S contains a NULL clause
      if (this.isNullClause(clause)) {
        const res = this.backTrack();

        if (res === false || res === null) {
          return null;
        }

        // propagate before continuing with the alg
        this.propagate();
      }

      for (const literal of clause) {
        if (literalTracker[literal] === undefined) {
          literalTracker[literal] = Literal.IsNegated(literal);
        }
      }

      // ? S contains a clause with only one literal
      if (clause.length == 1) {
        // this.V[Literal.GetAtom(clause[0])] === "UNBOUND"
        const literal = clause[0];
        const atom = Literal.GetAtom(literal);

        if (this.V[atom] === "UNBOUND") {
          this.V[atom] = !Literal.IsNegated(literal);
        }
      }
    }

    const literals_with_one_sign = [];

    // find the literals that appear with only one sign
    for (const [literal, isNegated] of Object.entries(literalTracker)) {
      const inverseLiteral = isNegated ? literal.substr(1) : "-" + literal;

      if (literalTracker[inverseLiteral] === undefined) {
        literals_with_one_sign.push(literal);
        // console.log(literals_with_one_sign);
      }
    }

    // ? some literal, L, appears with only one sign
    for (const literal of literals_with_one_sign) {
      this.V[Literal.GetAtom(literal)] = !Literal.IsNegated(literal);
    }

    // ? propagate
    this.propagate();

    let clausesSatisfied = true;
    for (const clause of this.ORIGINAL_S) {
      let clauseIsSat = false;
      for (const literal of clause) {
        if (Literal.IsSatisfied(this.V, literal)) {
          clauseIsSat = true;
          break;
        }
      }

      if (clauseIsSat === false) {
        clausesSatisfied = false;
        break;
      }
    }

    if (clausesSatisfied === true) {
      // console.log("CLAUSES ARE SATISFIED");
      // console.log(this.V);
      return true;
    }

    this.S = DEEP_COPY(this.S);
    this.V = DEEP_COPY(this.V);

    // console.log(this.V);
    // console.log(Object.entries(this.V));
    // process.exit(0);
    for (const [atom, valuation] of Object.entries(this.V)) {
      // console.log([atom, valuation]);
      if (valuation === "UNBOUND") {
        this.assignedAtoms.push({ atom, valuation: true, backTracked: false });
        break;
      }
    }

    return this.DP_HELPER();
  }
}

function main() {
  if (process.argv.length < 3) {
    console.log("missing input file!");
    process.exit(-2);
  }

  fileName = process.argv[2];
  filePath = join(__dirname, fileName);

  if (!existsSync(filePath)) {
    console.log(`${fileName} does not exist`);
    process.exit(-3);
  }

  try {
    const lines = readFileSync(filePath, { encoding: "utf8" });

    const extraLines = [];

    let S = {};
    const V = {};

    sawZero = false;
    for (let line of lines.split("\n")) {
      if (!sawZero) {
        line = line.trim();
      } else {
        extraLines.push(line);
        continue;
      }

      if (line == "0") {
        sawZero = true;
        continue;
      }

      const clause = [];
      for (const literal of line.split(" ")) {
        if (!Literal.IsValidLiteral(literal)) {
          console.log("Invalid literal: ${literal}");
          process.exit(-4);
        }

        const atom = Literal.GetAtom(literal);

        if (V[atom] === undefined) {
          V[atom] = "UNBOUND";
        }

        clause.push(literal);
      }

      const key = clause.join(",");
      if (S[key] === undefined) {
        S[key] = clause;
      }
    }

    S = Object.values(S);

    if (Object.keys(V).length < 1) {
      console.log("ERROR: NO ATOMS!");
      process.exit(-5);
    }

    if (S.length < 1) {
      console.log("ERROR: NO LITERALS");
      process.exit(-6);
    }

    const dpSolver = new DP(S, V);

    if (dpSolver.isSatisfied === true) {
      for (const [atom, valuation] of Object.entries(dpSolver.V)) {
        console.log(atom, valuation ? "T" : "F");
      }
    }

    console.log("0");
    for (const line of extraLines) {
      console.log(line);
    }
  } catch (error) {
    console.log(error);
    process.exit(-1);
  }
}

main();
