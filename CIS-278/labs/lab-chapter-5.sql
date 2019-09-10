/* Part 1 */
CREATE TABLE category (
catcode VARCHAR(3) CONSTRAINT ccn_pk PRIMARY KEY,
catdesc VARCHAR(11) CONSTRAINT ccn_nn NOT NULL
);


/* Part 2 */
BEGIN
INSERT INTO category
VALUES ('BUS', 'BUSINESS');

INSERT INTO category
VALUES ('CHN', 'CHILDREN');

INSERT INTO category
VALUES ('COK', 'COOKING');

INSERT INTO category
VALUES ('COM', 'COMPUTER');

INSERT INTO category
VALUES ('FAL', 'FAMILY LIFE');

INSERT INTO category
VALUES ('FIT', 'FITNESS');

INSERT INTO category
VALUES ('SEH', 'SELF HELP');

INSERT INTO category
VALUES ('LIT', 'LITERATURE');
END;


/* Part 3 */
ALTER TABLE books
ADD catcode VARCHAR(3);


/* Part 4 */
ALTER TABLE books
ADD CONSTRAINT books_catcode_fk
FOREIGN KEY(catcode)
REFERENCES category(catcode);


/* Part 5 */
BEGIN

UPDATE books
SET catcode = 'BUS'
WHERE category = 'BUSINESS';

UPDATE books
SET catcode = 'CHN'
WHERE category = 'CHILDREN';

UPDATE books
SET catcode = 'COK'
WHERE category = 'COOKING';

UPDATE books
SET catcode = 'COM'
WHERE category = 'COMPUTER';

UPDATE books
SET catcode = 'FAL'
WHERE category = 'FAMILY LIFE';

UPDATE books
SET catcode = 'FIT'
WHERE category = 'FITNESS';

UPDATE books
SET catcode = 'SEH'
WHERE category = 'SELF HELP';

UPDATE books
SET catcode = 'LIT'
WHERE category = 'LITERATURE';

COMMIT;

END;

/* part 6 */
ALTER TABLE books
DROP COLUMN category;