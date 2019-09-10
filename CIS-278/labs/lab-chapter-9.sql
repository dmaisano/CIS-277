/* Number 2 */
/* Oracle Join */
SELECT order# AS "Order Number", c.firstname || ', ' || c.lastname AS "Customer"
FROM orders o, customers c
WHERE SHIPDATE IS NULL AND o.customer# = c.customer#
ORDER BY orderdate DESC;

/* Join Clause */
SELECT order# AS "Order Number", c.firstname || ', ' || c.lastname AS "Customer"
FROM orders o JOIN customers c
ON SHIPDATE IS NULL AND o.customer# = c.customer#
ORDER BY orderdate DESC;


/* Number 6 */
/* Oracle Join */
SELECT title
FROM author a, books b, bookauthor ba
WHERE a.authorid = ba.authorid
  AND a.lname = 'ADAMS'
  AND ba.isbn = b.isbn
ORDER BY title DESC;

/* Join Clause */
SELECT title
FROM bookauthor ba
  JOIN author a
    ON a.authorid = ba.authorid
      AND a.lname = 'ADAMS'
  JOIN books b
    ON ba.isbn = b.isbn
ORDER BY title DESC;


/* Number 9 */
/* Oracle Join */
SELECT o.order# AS "Order Number", title, c.state
FROM books b, orderitems oi, orders o, customers c
WHERE oi.order# = o.order#
  AND oi.isbn = b.isbn
  AND o.customer# = c.customer#
ORDER BY o.order#;

/* Join Clause */
SELECT o.order# AS "Order Number", title, c.state
FROM orderitems oi
  JOIN orders o
    ON oi.order# = o.order#
  JOIN books b
    ON oi.isbn = b.isbn
  JOIN customers c
    ON o.customer# = c.customer#
ORDER BY o.order#;