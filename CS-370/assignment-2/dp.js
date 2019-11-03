const { existsSync, readFileSync } = require("fs");
const { join } = require("path");

function DEEP_COPY(obj) {
	return JSON.parse(JSON.stringify(obj));
}

class DP {
	constructor(ATOMS, S, V) {
		this.ATOMS = ATOMS;
		this.S = S;
		this.V = V;
	}
}

function main() {
	if (process.argv.length < 3) {
		console.log("missing input file!");
		process.exit(-1);
	}

	fileName = process.argv[2];
	filePath = join(__dirname, fileName);

	if (!existsSync(filePath)) {
		console.log(`${fileName} does not exist`);
		process.exit(-2);
	}

	try {
		const lines = readFileSync(filePath, { encoding: "utf8" });

		const extraLines = [];

		const ATOMS = {};
		const S = {};
		const V = {};

		sawZero = false;
		for (let line of lines) {
			if (!sawZero) {
				line = line.trim();
			} else {
				extraLines.push(line);
			}

			if (line == "0") {
				sawZero = true;
				continue;
			}

			for (const literal of line) {
			}
		}
	} catch (error) {
		console.log("error reading input file");
		process.exit(-3);
	}
}

main();
