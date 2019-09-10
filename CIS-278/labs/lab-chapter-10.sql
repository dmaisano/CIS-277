/* Number 1 */
SELECT INITCAP(firstname) "FIRST NAME", INITCAP(lastname) "LAST NAME"
FROM customers;


/* Number 6 */
SELECT title, LPAD(cost, 12, '*') "COST"
FROM books;


/* Number 8 */
SELECT title,
  pubdate "PUBLICATION DATE",
  SYSDATE "CURRENT DATE",
  TRUNC(MONTHS_BETWEEN(SYSDATE, pubdate), 0) "AGE (IN MONTHS)"
FROM books;


/* Number 10 */
SELECT customer# "CUSTOMER #",
  SUBSTR(zip, 3, 2) "ZIP",
  INSTR(customer#, 3) "POS OF 3 IN CUSTOMER #"
FROM customers;