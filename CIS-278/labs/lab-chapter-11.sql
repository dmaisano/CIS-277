/* Number 2 */
SELECT COUNT(*) "NUM OF BOOKS"
FROM books
WHERE retail > 30;


/* Number 6 */
SELECT AVG( SUM((retail-cost) * quantity) ) "AVG PROFIT"
FROM orders
  JOIN orderitems USING (order#)
  JOIN books USING (isbn)
GROUP BY order#;


/* Number 8 */
SELECT name, category, AVG (retail) "AVG RETAIL"
FROM books JOIN publisher USING(pubid) 
WHERE category IN('COMPUTER', 'CHILDREN')
GROUP BY name, category
HAVING AVG (RETAIL) > 50;


/* Number 10 */
SELECT MAX(retail) "MAX RETAIL"
FROM books
  JOIN bookauthor USING(isbn)
  JOIN author USING(authorid)
WHERE lname = 'WHITE'
AND fname = 'LISA';