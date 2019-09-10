/* Insert into problems */
INSERT ALL
INTO problems VALUES(1, 'Tree down')
INTO problems VALUES(2, 'Power out')
INTO problems VALUES(3, 'No heat')
INTO problems VALUES(4, 'No water')
INTO problems VALUES(5, 'Flooding')
INTO problems VALUES(6, 'Power line down')
INTO problems VALUES(7, 'Other')
SELECT * FROM dual


/* Insert into services */
INSERT ALL
INTO services VALUES('PSEG', 'Public Service Electric and Gas')
INTO services VALUES('WTR', 'Water Department ')
INTO services VALUES('OEM', 'Office of Emergency Management')
INTO services VALUES('DPR', 'Department of Parks and Recreation')
INTO services VALUES('CSH', 'Community Shelter')
SELECT * FROM dual


/* Insert into personnel */
INSERT ALL
INTO personnel VALUES('JS', 'John', 'Smith')
INTO personnel VALUES('JD', 'Jane', 'Doe')
INTO personnel VALUES('JJ', 'Janet', 'Jackson')
INTO personnel VALUES('PL', 'Peter', 'Lee')
INTO personnel VALUES('KM', 'Katy', 'McQuire')
SELECT * FROM dual;


/* Insert into call_status */
INSERT ALL
INTO call_status VALUES('RIP', 'Repair in process')
INTO call_status VALUES('INV', 'Investigating')
INTO call_status VALUES('CMP', 'Completed repair')
SELECT * FROM dual;


/* Insert into call_info */
INSERT ALL
INTO call_info
  VALUES(1102, 'Bill', 'Madden', TO_DATE('29‐OCT‐17', 'DD/MM/YY'), TO_DATE('07:00 PM', 'HH:MI AM'), 2, 'PSEG')

INTO call_info
  VALUES(1103, 'Anita', 'Verno', TO_DATE('29‐OCT‐17', 'DD/MM/YY'), TO_DATE('07:01 PM', 'HH:MI AM'), 2, 'PSEG')

INTO call_info
  VALUES(1200, 'Emily', 'Vandalovsky', TO_DATE('29‐OCT‐17', 'DD/MM/YY'), TO_DATE('07:45 PM', 'HH:MI AM'), 2, 'PSEG')

INTO call_info
  VALUES(1111, 'Gary', 'Correa', TO_DATE('29‐OCT‐17', 'DD/MM/YY'), TO_DATE('08:10 PM', 'HH:MI AM'), 1, 'DPR')

INTO call_info
  VALUES(1101, 'Mickey', 'Mouse', TO_DATE('29‐OCT‐17', 'DD/MM/YY'), TO_DATE('11:00 PM', 'HH:MI AM'), 6, 'PSEG')

INTO call_info
  VALUES(1012, 'Minnie', 'Mouse', TO_DATE('29‐OCT‐17', 'DD/MM/YY'), TO_DATE('11:21 PM', 'HH:MI AM'), 1, 'DPR')

INTO call_info
  VALUES(1013, 'Goofy', 'Disney', TO_DATE('29‐OCT‐17', 'DD/MM/YY'), TO_DATE('11:47 PM', 'HH:MI AM'), 5, 'OEM')

INTO call_info
  VALUES(1040, 'Donald', 'Duck', TO_DATE('30‐OCT‐17', 'DD/MM/YY'), TO_DATE('02:34 AM', 'HH:MI AM'), 4, 'OEM')

INTO call_info
  VALUES(1501, 'Cinderella', 'Disney', TO_DATE('30‐OCT‐17', 'DD/MM/YY'), TO_DATE('03:15 AM', 'HH:MI AM'), 3, 'CSH')

INTO call_info
  VALUES(1506, 'Ernie', 'Sesame', TO_DATE('30‐OCT‐17','DD/MM/YY') ,TO_DATE('03:16 AM', 'HH:MI AM'), 3, 'CSH')

INTO call_info
  VALUES(1007, 'Burt', 'Sesame', TO_DATE('30‐OCT‐17','DD/MM/YY'), TO_DATE('03:18 AM', 'HH:MI AM'), 3, 'CSH')

INTO call_info
  VALUES(1081, 'Bruce', 'Springsteen',TO_DATE('30‐OCT‐17','DD/MM/YY'),TO_DATE('04:10 AM', 'HH:MI AM'),  2, 'PSEG')

INTO call_info
  VALUES(1910, 'Chris', 'Christie', TO_DATE('30‐OCT‐17','DD/MM/YY'),TO_DATE('04:25 AM', 'HH:MI AM'),  7, 'OEM')

INTO call_info
  VALUES( 1010, 'Mitt',  'Romney', TO_DATE('30‐OCT‐17','DD/MM/YY'), TO_DATE('05:15 AM', 'HH:MI AM'), 1, 'DPR')

INTO call_info
  VALUES(1015, 'Barack', 'Obama', TO_DATE('30‐OCT‐17','DD/MM/YY'), TO_DATE('05:17 AM','HH:MI AM'),  1, 'DPR')

INTO call_info
  VALUES(1019, 'Bruce', 'Wayne', TO_DATE('30‐OCT‐17','DD/MM/YY'), TO_DATE('07:57 AM','HH:MI AM'),  5, 'OEM')

INTO call_info
  VALUES(1314, 'Minas', 'Kousoulis', TO_DATE('30‐OCT‐17','DD/MM/YY'), TO_DATE('8:01 AM','HH:MI AM'),  4,  'WTR')
SELECT * FROM dual;


/* Insert into problem_status */
/*
INTO problem_status(call_id, update_date, update_time, status, sign_off_id)
  VALUES (1102, TO_DATE('10/29', 'MM/DD'), TO_DATE('7:15 PM', 'HH:MM AM'), 'INV', 'JD')
*/
/* call_id, update_date, update_time, status, sign_off_id */
INSERT ALL
INTO problem_status
  VALUES (1102, TO_DATE('10/29', 'MM/DD'), TO_DATE('07:15 PM', 'HH:MI AM'), 'INV', 'JD')

INTO problem_status
  VALUES (1103, TO_DATE('10/29', 'MM/DD'), TO_DATE('07:15 PM', 'HH:MI AM'), 'INV', 'JJ')

INTO problem_status
  VALUES (1200, TO_DATE('10/29', 'MM/DD'), TO_DATE('08:01 PM', 'HH:MI AM'), 'INV', 'JJ')

INTO problem_status
  VALUES (1111, TO_DATE('11/01', 'MM/DD'), TO_DATE('08:17 PM', 'HH:MI AM'), 'INV', 'PM')

INTO problem_status
  VALUES (1111, TO_DATE('11/04', 'MM/DD'), TO_DATE('02:56 PM', 'HH:MI AM'), 'CMP', 'PM')

INTO problem_status
  VALUES (1101, TO_DATE('11/01', 'MM/DD'), TO_DATE('12:02 AM', 'HH:MI AM'), 'INV', 'JJ')

INTO problem_status
  VALUES (1101, TO_DATE('11/02', 'MM/DD'), TO_DATE('03:45 PM', 'HH:MI AM'), 'RIP', 'JD')

INTO problem_status
  VALUES (1012, TO_DATE('10/31', 'MM/DD'), TO_DATE('04:42 AM', 'HH:MI AM'), 'INV', 'JD')

INTO problem_status
  VALUES (1040, TO_DATE('11/03', 'MM/DD'), TO_DATE('05:56 AM', 'HH:MI AM'), 'INV', 'KM')

INTO problem_status
  VALUES (1013, TO_DATE('11/02', 'MM/DD'), TO_DATE('07:22 PM', 'HH:MI AM'), 'CMP', 'KM')

INTO problem_status
  VALUES (1040, TO_DATE('11/03', 'MM/DD'), TO_DATE('08:00 AM', 'HH:MI AM'), 'RIP', 'JJ')

INTO problem_status
  VALUES (1501, TO_DATE('10/30', 'MM/DD'), TO_DATE('04:10 AM', 'HH:MI AM'), 'CMP', 'KM')

INTO problem_status
  VALUES (1506, TO_DATE('10/30', 'MM/DD'), TO_DATE('04:10 AM', 'HH:MI AM'), 'CMP', 'PL')

INTO problem_status
  VALUES (1007, TO_DATE('10/30', 'MM/DD'), TO_DATE('04:10 AM', 'HH:MI AM'), 'CMP', 'PL')

INTO problem_status
  VALUES (1081, TO_DATE('10/30', 'MM/DD'), TO_DATE('08:19 AM', 'HH:MI AM'), 'INV', 'JD')

INTO problem_status
  VALUES (1910, TO_DATE('10/30', 'MM/DD'), TO_DATE('05:13 AM', 'HH:MI AM'), 'CMP', 'JJ')

INTO problem_status
  VALUES (1010, TO_DATE('10/30', 'MM/DD'), TO_DATE('01:57 PM', 'HH:MI AM'), 'INV', 'PL')

INTO problem_status
  VALUES (1010, TO_DATE('11/01', 'MM/DD'), TO_DATE('01:57 AM', 'HH:MI AM'), 'RIP', 'KM')

INTO problem_status
  VALUES (1015, TO_DATE('11/01', 'MM/DD'), TO_DATE('01:58 AM', 'HH:MI AM'), 'INV', 'JD')

INTO problem_status
  VALUES (1019, TO_DATE('10/30', 'MM/DD'), TO_DATE('08:02 AM', 'HH:MI AM'), 'INV', 'KM')

INTO problem_status
  VALUES (1314, TO_DATE('10/30', 'MM/DD'), TO_DATE('10:15 AM', 'HH:MI AM'), 'INV', 'PL')

INTO problem_status
  VALUES (1102, TO_DATE('11/05', 'MM/DD'), TO_DATE('02:00 PM', 'HH:MI AM'), 'CMP', 'PL')

INTO problem_status
  VALUES (1103, TO_DATE('11/05', 'MM/DD'), TO_DATE('03:10 PM', 'HH:MI AM'), 'CMP', 'JS')

INTO problem_status
  VALUES (1200, TO_DATE('11/01', 'MM/DD'), TO_DATE('08:36 AM', 'HH:MI AM'), 'CMP', 'JJ')

INTO problem_status
  VALUES (1102, TO_DATE('11/02', 'MM/DD'), TO_DATE('01:10 PM', 'HH:MI AM'), 'RIP', 'JJ')

INTO problem_status
  VALUES (1103, TO_DATE('11/02', 'MM/DD'), TO_DATE('02:15 PM', 'HH:MI AM'), 'RIP', 'JS')

INTO problem_status
  VALUES (1200, TO_DATE('10/31', 'MM/DD'), TO_DATE('04:15 PM', 'HH:MI AM'), 'RIP', 'JJ')
SELECT * FROM dual;



/* Aaron Judge */
INSERT ALL
INTO call_info
  VALUES(2001, 'Aaron', 'Judge', TO_DATE('29‐OCT‐17','DD/MM/YY'), TO_DATE('06:18 PM', 'HH:MI AM'), 5, 'OEM')

INTO problem_status
  VALUES(2001, TO_DATE('10/29', 'MM/DD'), TO_DATE('07:30 PM', 'HH:MI AM'), 'INV', 'JJ')

INTO problem_status
  VALUES(2001, TO_DATE('10/29', 'MM/DD'), TO_DATE('08:15 PM', 'HH:MI AM'), 'RIP', 'JJ')

INTO problem_status
  VALUES(2001, TO_DATE('10/29', 'MM/DD'), TO_DATE('02:30 AM', 'HH:MI AM'), 'CMP', 'JJ')
SELECT * FROM dual;


/* John Raul */
INSERT ALL
INTO call_info
  VALUES(2002, 'John', 'Raul', TO_DATE('03‐NOV‐17','DD/MM/YY'), TO_DATE('03:34 AM', 'HH:MI AM'), 2, 'PSEG')

INTO problem_status
  VALUES(2002, TO_DATE('11/03', 'MM/DD'), TO_DATE('04:01 AM', 'HH:MI AM'), 'INV', 'JS')
SELECT * FROM dual;


/* Mickey Mouse */
INSERT ALL
INTO call_info
  VALUES(2003, 'Mickey', 'Mouse', TO_DATE('30‐OCT‐17','DD/MM/YY'), TO_DATE('04:45 PM', 'HH:MI AM'), 6, 'PSEG')

INTO problem_status
  VALUES(2003, TO_DATE('10/30', 'MM/DD'), TO_DATE('04:50 PM', 'HH:MI AM'), 'INV', 'KM')

INTO problem_status
  VALUES(2003, TO_DATE('10/30', 'MM/DD'), TO_DATE('04:55 PM', 'HH:MI AM'), 'RIP', 'KM')

INTO problem_status
  VALUES(2003, TO_DATE('10/30', 'MM/DD'), TO_DATE('06:00 PM', 'HH:MI AM'), 'CMP', 'KM')
SELECT * FROM dual;


/* Question 4 */
SELECT c.call_id, c.report_date, c.report_time, p.description, s.name, ps.update_date, ps.update_time
FROM call_info c, problem_status ps, problems p, services s
WHERE ps.status = 'CMP'
  AND c.call_id = ps.call_id
  AND c.problem_code = p.code
  AND c.service_code = s.code
ORDER BY c.service_code, c.call_id


/* Question 5 */
SELECT c.call_id, c.report_date, c.report_time, p.code, ps.status, cs.description, ps.update_date, ps.update_time
FROM call_info c, problem_status ps, problems p, call_status cs
WHERE c.service_code = 'PSEG'
  AND c.call_id = ps.call_id
  AND ps.status = cs.code
  AND c.problem_code = p.code
ORDER BY c.call_id;


/* Question 7 */
SELECT COUNT(c.problem_code) "PROBLEM COUNT", p.description
FROM call_info c, problems p
WHERE c.problem_code = p.code 
GROUP BY p.description
ORDER BY p.description


/* Question 8 */
SELECT p.last_name, p.first_name, COUNT(p.last_name)
FROM problem_status ps, personnel p
WHERE ps.sign_off_id = p.id
GROUP BY p.last_name, p.first_name
ORDER BY p.last_name, p.first_name;


/* Question 9 */
SELECT report_last "LAST NAME", COUNT(report_last) "CALL COUNT"
FROM call_info
GROUP BY report_last
HAVING report_last IN ('Mouse', 'Sesame')
ORDER BY COUNT(report_last) DESC;
