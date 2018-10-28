/**
 * Assign the project to an employee.
 * @param {Object} employee - The employee who is responsible for the project.
 * @param {string} employee.name - The name of the employee.
 * @param {string} employee.department - The employee's department.
 */
function selectionSort(items) {
	let len = items.length;
	let min;

	for (i in len) {
		//set minimum to this position
		min = i;

		//check the rest of the array to see if anything is smaller
		for (j = i + 1; j < len; j++) {
			if (items[j] < items[min]) {
				min = j;
			}
		}

		//if the minimum isn't in the position, swap it
		if (i != min) {
			swap(items, i, min);
		}
	}

	return items;
}
