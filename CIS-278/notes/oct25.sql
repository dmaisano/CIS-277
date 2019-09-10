/* Students getting loans - id, first AND last name, 
lender code, amount Join ON ALL cols WITH same name IN both TABLES
(ONLY returns ROWS WHERE a student has a loan) */
SELECT id, first, last, lender_id, amount
FROM b_students NATURAL JOIN b_financial_aid;


/* shows NULL values */
SELECT id, first, last, lender_id, amount
FROM b_students LEFT OUTER JOIN b_financial_aid
USING (id);
<<<<<<< HEAD

/* Same as before but want the lender name as well */ 

SELECT id, first, last, lender_id, lender_name, amount
FROM b_students JOIN b_financial_aid USING (id)
  JOIN b_lenders USING(lender_id);
=======
>>>>>>> 9d33fc6825eb8cc8a998b3278a4ef7c1f24de6f5
