CREATE TABLE global_locations (
id NUMBER(4) CONSTRAINT gln_id_pk PRIMARY KEY,
loc_name VARCHAR2(20),
date_opened DATE CONSTRAINT gln_date_opened_nn NOT NULL,
address VARCHAR2(35) CONSTRAINT gln_address_nn NOT NULL,
city VARCHAR2(30) CONSTRAINT gln_city_nn NOT NULL,
zip CHAR(5),
phone NUMBER(10),
email VARCHAR2(30),
manager_id NUMBER(3),
emergency_contact VARCHAR2(20),
CONSTRAINT gln_email_ukk UNIQUE(email)
);