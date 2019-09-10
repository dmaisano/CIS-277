/* Number 1 */
SELECT title, retail
FROM books
WHERE retail <
(SELECT AVG(retail)
FROM books);


/* Number 3 */
SELECT order# "ORDER NUMBER"
FROM orders
WHERE shipstate =
(SELECT shipstate
FROM orders
WHERE order# = 1014);


/* Number 8 */
SELECT firstname, lastname, title, customer#
FROM customers
  JOIN orders USING(customer#)
  JOIN orderitems USING(order#)
  JOIN books USING(isbn)
WHERE retail =
(SELECT MIN(retail)
FROM books);


/* Number 10 */
SELECT title, pubid
FROM books
WHERE pubid =
(SELECT pubid
FROM books
WHERE title = 'THE WOK WAY TO COOK');
