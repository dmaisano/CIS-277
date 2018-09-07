// Source code of the FMS function that includes the inline comments
let prompt = require('prompt');

// finite state machine func() to find a substring containing '1101'
// the function accepts any particular string and is not restricted to binary strings
function fms(str) {
	str = str
		.split('') // splits the string up into a character array

		.filter(char => char == '0' || char == '1') // filters the results of the array to include only binary numbers

		.join(''); // joins the character array into one string contained inside of an array

	return str.includes('1101') ? true : false; // returns true is the string contains a substring of '1101'

	// The return statement above has the same behavior as the snippet below...
	// if(str.str.includes('1101'))
	//   return true

	// return false
}

function fsm() {
	let letters = /^[A-Za-z]+$/;
	let str = '';

	prompt.start();
	prompt.get(['string'], (err, result) => {
		str = string;
	});

	// regex that contains the set of all letters (case sensitive)
	if (str.match(letters)) {
		console.log('Illegal string, please enter a BINARY string');
		test();
	}

	return str.includes('1101') ? true : false;
}
