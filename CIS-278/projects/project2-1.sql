CREATE TABLE problems
(
code NUMBER(1, 0) CONSTRAINT prob_code_pk PRIMARY KEY,
description VARCHAR2(16) CONSTRAINT prob_desc_nn NOT NULL,
CONSTRAINT check_prob_code CHECK (code BETWEEN 1 AND 7)
);


CREATE TABLE services
(
code VARCHAR2(4) CONSTRAINT svc_code_pk PRIMARY KEY,
name VARCHAR2(36) CONSTRAINT svc_name_nn NOT NULL,
CONSTRAINT check_svc_code
  CHECK(code IN('PSEG', 'WTR', 'OEM', 'DPR', 'CSH'))
);


CREATE TABLE personnel
(
id VARCHAR2(2) CONSTRAINT psl_id_pk PRIMARY KEY,
first_name VARCHAR2(20),
last_name VARCHAR2(20) CONSTRAINT psl_lname_nn NOT NULL
);


CREATE TABLE call_status
(
code VARCHAR2(3) CONSTRAINT cst_code_pk PRIMARY KEY,
description VARCHAR2(18) CONSTRAINT cst_desc_nn NOT NULL,
CONSTRAINT check_cst_code CHECK (code IN ('RIP', 'INV', 'CMP'))
);


CREATE TABLE call_info
(
call_id NUMBER(4, 0) CONSTRAINT cinf_cid_pk PRIMARY KEY,
report_first VARCHAR2(20),
report_last VARCHAR2(20) CONSTRAINT cinf_rlast_nn NOT NULL,
report_date DATE CONSTRAINT cinf_rdate_nn NOT NULL,
report_time DATE CONSTRAINT cinf_rtime_nn NOT NULL,
problem_code NUMBER(1,0) CONSTRAINT cinf_prob_code_nn NOT NULL,
service_code VARCHAR2(4),
CONSTRAINT cinf_prob_code_fk FOREIGN KEY (problem_code)
  REFERENCES problems (code),
CONSTRAINT cinf_svc_code_fk FOREIGN KEY (service_code)
  REFERENCES services (code)
);


CREATE TABLE problem_status
(
call_id NUMBER(4, 0) CONSTRAINT prst_call_id_nn NOT NULL,
update_date DATE CONSTRAINT prst_update_date_nn NOT NULL,
update_time DATE CONSTRAINT prst_update_time_nn NOT NULL,
status VARCHAR2(3) CONSTRAINT prst_status_nn NOT NULL,
sign_off_id VARCHAR2(2) CONSTRAINT prst_sign_off_id_nn NOT NULL,
CONSTRAINT prst_call_id_fk FOREIGN KEY (call_id)
  REFERENCES call_info (call_id),
CONSTRAINT prst_status_fk FOREIGN KEY (status)
  REFERENCES call_status (code),
CONSTRAINT prst_sign_off_id_fk FOREIGN KEY (sign_off_id)
  REFERENCES personnel (id),
CONSTRAINT prst_comp_key PRIMARY KEY (call_id, update_date, update_time)
);
