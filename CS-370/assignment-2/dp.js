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
		return new RegExp().test(literal);
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
		return literal.match(new RegExp("\\d+"))[0];
	}
}

class DP {
	/**
	 * @param {Array<string>} ATOMS
	 * @param {Array<Array<String>>} S
	 * @param {Object} V
	 */
	constructor(S, V) {
		/** @public {Array<string>} */
		this.ATOMS = Object.keys(V);
		/** @public {Array<Array<String>>} S */
		this.ORIGINAL_S = S;
		/** @public {Object} V */
		this.ORIGINAL_V = V;

		/** @public {Array<Array<String>>} S */
		this.S = DEEP_COPY(this.ORIGINAL_S);
		/** @public {Array<Array<String>>} S */
		this.V = DEEP_COPY(this.ORIGINAL_V);

		/** @public {boolean} */
		this.isSatisfied = true;

		// this.isSatisfied = this.DP_HELPER();
	}

	propagate() {
		let i = this.S.length;
		while (i--) {
			const clause = this.S[i];

			let isSatisfied = false;
			let j = clause.length;
			while (j--) {
				const literal = clause[j];
				const valuation = this.V[Literal.GetAtom(literal)];

				if (valuation === true) {
					isSatisfied = true;
					break;
				}

				if (valuation === false) {
					clause.splice(j, 1);
					continue;
				}
			}

			if (isSatisfied) {
				this.S.splice(j, 1);
				continue;
			}
		}
	}

	DP_HELPER() {
		// console.log(this.S);
		// console.log(this.V);
		// console.log(this.ORIGINAL_V);

		// 1) S is null (already solved)
		if (this.S.length < 1) return true;
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
				console.log(atom, valuation);
			}
		}

		console.log(0);
		for (const line of extraLines) {
			console.log(line);
		}
	} catch (error) {
		console.log(error);
		process.exit(-1);
	}
}

main();
