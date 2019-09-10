/* Section 8 Lesson 1 Practice */

/* Number 2
Create a query that will show the average cost of the DJs on Demand events. Round to
two decimal places. */

SELECT ROUND(AVG(cost), 2)
FROM d_events;


/* Number 4
Find the sum of the salaries for Global Fast Foods staff members whose IDs are 12 and 9 */

SELECT SUM(salary)
FROM f_staffs
WHERE id = 12 OR id = 9;

/* or */

SELECT SUM(salary)
FROM f_staffs
WHERE id IN (9, 12);

/* Number 5 
Using the Oracle database, select the lowest salary, the most recent hire date, the last
name of the person who is at the top of an alphabetical list of employees, and the last
name of the person who is at the bottom of an alphabetical list of employees. Select only
employees who are in departments 50 or 60. */

SELECT MIN(salary), MAX(hire_date), MIN(last_name), MAX(last_name)
FROM employees
WHERE department_id IN (50, 60);

/* Section 9 Lesson 2 */

/* Number 2
Each of the following SQL queries has an error. Find the error and correct it. Use Oracle
Application Express to verify that your corrections produce the desired results. */

/* a */
SELECT manager_id,AVG(salary)
FROM employees
GROUP BY manager_id
HAVING AVG(salary) <16000;

/* b */
SELECT COUNT(*)
FROM d_cds
WHERE cd_number < 93;

/* c */
SELECT type_code, MAX(TO_NUMBER(REPLACE(duration,' min',''))) || ' min' as "max duration"
FROM d_songs
WHERE duration IN('3 min', '6 min', '10 min') AND id < 50
GROUP BY type_code;

/* d */
SELECT loc_type, AVG(
CASE
 WHEN INSTR(rental_fee, '/hour') != 0 THEN  TO_NUMBER(REPLACE(rental_fee,'/hour',''))*5
  WHEN INSTR(rental_fee, '/flat fee') != 0 THEN  TO_NUMBER(REPLACE(rental_fee,'/flat fee',''))
  WHEN INSTR(rental_fee, '/per person') != 0 THEN  TO_NUMBER(REPLACE(rental_fee,'/per person',''))*10
 ELSE 0
 END
) AS Fee
FROM d_venues
WHERE id <100
GROUP BY loc_type
ORDER BY 2;


/* Section 9 Lesson 2 */

/* Number 1
Within the Employees table, each manager_id is the manager of one or more employees
who each have a job_id and earn a salary. For each manager, what is the total salary
earned by all of the employees within each job_id? Write a query to display the Manager_id,
job_id, and total salary. Include in the result the subtotal salary for each manager
and a grand total of all salaries. */

SELECT  manager_id, job_id, SUM(salary) "total salary", manager_id, job_id
FROM employees
GROUP BY ROLLUP(manager_id, job_id);

/* Number 2 
Amend the previous query to also include a subtotal salary for each job_id regardless of
the manager_id. */

SELECT  manager_id, job_id, SUM(salary) "total salary", GROUPING(manager_id), GROUPING(job_id)
FROM employees
GROUP BY CUBE(manager_id, job_id);
