/* Number 3 */
CREATE SEQUENCE MY_FIRST_SEQ
INCREMENT BY -3
START WITH 5
MAXVALUE 5
MINVALUE 0
NOCYCLE;

/* Number 4 */
SELECT MY_FIRST_SEQ.NEXTVAL
FROM DUAL;

SELECT MY_FIRST_SEQ.NEXTVAL
FROM DUAL;

SELECT MY_FIRST_SEQ.NEXTVAL
FROM DUAL;
/*
The eror generated after the third select statement is due to the starting posiiton being 5 and decrementing each value in the sequence by 3.
The minimum value that can be obtained is zero. The third iteration would yield -1 which is restricted by the specified 'MINVALUE' of zero.
*/


/* Number 5 */
ALTER SEQUENCE MY_FIRST_SEQ
MINVALUE -1000;


/* Number 6 */
CREATE SYNONYM NUMGEN
FOR MY_FIRST_SEQ;


/* Number 7 */
SELECT NUMGEN.CURRVAL
FROM DUAL;


DROP SYNONYM NUMGEN;


DROP SEQUENCE MY_FIRST_SEQ;
