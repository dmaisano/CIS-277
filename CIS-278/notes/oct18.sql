CREATE TABLE copy_d_cds
  AS SELECT * FROM d_cds;


/*
CREATE TABLE copy_d_cds
  AS (SELECT * FROM d_cds);
*/


INSERT INTO copy_d_cds
  (cd_number, title, producer, year) 
  VALUES(97, 'Celebrate the Day', 'R & B Inc.', 2003);


INSERT INTO copy_d_cds
  (cd_number, title, producer, year) 
  VALUES(98, 'Holiday Tunes for All', 'Ages Tunes are Us', 2004);


INSERT INTO copy_d_cds
  (cd_number, title, producer, year) 
  VALUES(99, 'Party Music', 'Old Town Records', 2004);


INSERT INTO copy_d_cds
  (cd_number, title, producer, year) 
  VALUES(100, 'Best of Rock and Roll', 'Old Town Records', 2004);

/*
Monique Tuttle, the manager of Global Fast Foods, sent a memo requesting an immediate
change in prices. The price for a strawberry shake will be raised from $3.59 to $3.75, and
the price for fries will increase to $1.20. Make these changes to the copy_f_food_items table.
*/

CREATE TABLE copy_f_food_items
  AS SELECT * FROM f_food_items;


UPDATE copy_f_food_items
  SET price = 1.20
  WHERE food_item_number = 90;


UPDATE copy_f_food_items
  SET price = 3.75
  WHERE food_item_number = 93;


SELECT *
  FROM d_cds
  WHERE title = 'Carpe Diem';

SELECT first_name, last_name, salary
  FROM f_staffs
  WHERE salary BETWEEN 5 AND 10;