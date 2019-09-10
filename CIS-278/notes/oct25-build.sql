INF-217 Chap 9

CREATE TABLE b_students
(
  id CHAR(8) PRIMARY KEY,
  last VARCHAR2(20),
  first VARCHAR2(15)
);

CREATE TABLE b_lenders
(
  lender_id CHAR(2) PRIMARY KEY,
  lender_name VARCHAR2(30) NOT NULL
);

CREATE TABLE b_financial_aid
(
  id CHAR(8),
  lender_id CHAR(2) CONSTRAINT fad_lender_id_NN NOT NULL,
  loan CHAR(1) CONSTRAINT fad_loan_CK CHECK (loan IN ('Y','N')),
  amount NUMBER (7,2),
  CONSTRAINT fad_id_lender_id_PK PRIMARY KEY (id, lender_id),
  CONSTRAINT fad_id_FK FOREIGN KEY (id) REFERENCES b_students(id),
  CONSTRAINT fad_lender_id_FK FOREIGN KEY (lender_id) REFERENCES b_lenders(lender_id)
);

----------------------

BEGIN
INSERT INTO b_students
VALUES ('123001','Doe','Jane');
INSERT INTO b_students
VALUES ('146217','Smith','Peter');
INSERT INTO b_students
VALUES ('173458','Valley','Sam');
END;

BEGIN
INSERT INTO b_lenders
VALUES ('TD','TD Bank');
INSERT INTO b_lenders
VALUES ('CB','Columbia Bank');
INSERT INTO b_lenders
VALUES ('BF','Bergen Foundation');
INSERT INTO b_lenders
VALUES ('FD','Federal Government');
INSERT INTO b_lenders
VALUES ('NJ','State of NJ');
END;

BEGIN
INSERT INTO b_financial_aid
VALUES('123001','TD','Y',100);
INSERT INTO b_financial_aid
VALUES('123001','FD','Y',250);
INSERT INTO b_financial_aid
VALUES('123001','BF','N',75);
INSERT INTO b_financial_aid
VALUES('146217','CB','Y',200);
INSERT INTO b_financial_aid
VALUES('146217','TD','Y',50);
END;

----------------------

SELECT *
FROM b_students;

SELECT *
FROM b_lenders;

SELECT *
FROM b_financial_aid;


