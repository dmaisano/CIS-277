/* Section 4 Lesson 1 Practice */

/* Number 2 */
SELECT SUBSTR('Oracle Internet Academy', 13, 3) AS "The Net"
FROM DUAL;


/* Number 3 */
SELECT LENGTH('Oracle Internet Academy') AS "String Length"
FROM DUAL;


/* Number 4 */
SELECT INSTR('Oracle Internet Academy', 'I') AS "Position"
FROM DUAL;


/* Number 5 */
SELECT LPAD('Oracle', 10, '*') || LPAD('Internet', 12, '*') || LPAD('Academy', 11, '*') || '****' AS "Left Padding"
FROM DUAL;


/* Section 4 Lesson 2 Practice */
SELECT salary
FROM TABLE_NAME
WHERE MOD(salary, 3) = 0;