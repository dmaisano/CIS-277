-- CLAUSES --
/*
SELECT
FROM
WHERE
GROUP BY
HAVING
ORDER BY
*/

-- ORDER OF PRIORITY --
/*
Fred      -> FROM
Will      -> WHERE
Grow      -> GROUP BY
Hair      -> HAVING
Some      -> SELECT
October   -> ORDER BY
*/

SELECT INITCAP(CONCAT(shipcity, CONCAT(', ', CONCAT(shipstate, 
CONCAT(' ', shipzip)))))
FROM orders;