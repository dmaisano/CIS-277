/* Number 1 */
SELECT title FROM books
WHERE (retail - cost) >= 10.00
ORDER BY (retail - cost) DESC;
/* profit = (retail - cost) */


/* Number 2 */
SELECT title FROM books
WHERE (category = 'COMPUTER' OR category = 'FAMILY LIFE')
  AND (pubid = 1 OR pubid = 3)
  AND retail > 45.00;
