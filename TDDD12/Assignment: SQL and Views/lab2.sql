/* allsh436, behbe027*/

/*Assignment: SQL and Views

1. List all employees, i.e., all tuples in the jbemployee relation.*/ 

SELECT * 
FROM jbemployee;

/*too big	

------------------------------------------------------------------
2.List the name of all departments in alphabetical order. Note: by “name” we mean the name attribute in the jbdept relation */
SELECT name 
FROM jbdept 
ORDER BY name;

/*	+------------------+
	| name             |
	+------------------+
	| Bargain          |
	| Book             |
	| Candy            |
	| Children's       |
	| Children's       |
	| Furniture        |
	| Giftwrap         |
	| Jewelry          |
	| Junior Miss      |
	| Junior's         |
	| Linens           |
	| Major Appliances |
	| Men's            |
	| Sportswear       |
	| Stationary       |
	| Toys             |
	| Women's          |
	| Women's          |
	| Women's          |
	+------------------+
	19 rows in set (0.01 sec) */
-------------------------------------------------------------------
/*3. What parts are not in store? Note that such parts have the value 0 (zero)
for the qoh attribute (qoh = quantity on hand). */

SELECT id, name 
FROM jbparts 
WHERE qoh = 0;
	
	/*
    +----+-------------------+
    | id | name              |
    +----+-------------------+
    | 11 | card reader       |
    | 12 | card punch        |
    | 13 | paper tape reader |
    | 14 | paper tape punch  |
    +----+-------------------+
    4 rows in set (0.00 sec)

    */

-------------------------------------------------------------------
/*4. List all employees who have a salary between 9000 (included) and
10000 (included)? */

SELECT name 
FROM jbemployee 
WHERE salary 
BETWEEN 9000 AND 10000;

/*	+----------------+
	| name           |
	+----------------+
	| Edwards, Peter |
	| Smythe, Carol  |
	| Williams, Judy |
	| Thomas, Tom    |
	+----------------+
	4 rows in set (0.01 sec)*/

------------------------------------------------------------------
/*5. List all employees together with the age they had when they started
working? Hint: use the startyear attribute and calculate the age in the
SELECT clause. */

SELECT name, startyear - birthyear AS age_when_started 
FROM jbemployee;

/*	+--------------------+------------------+
	| name               | age_when_started |
	+--------------------+------------------+
	| Ross, Stanley      |               18 |
	| Ross, Stuart       |                1 |
	| Edwards, Peter     |               30 |
	| Thompson, Bob      |               40 |
	| Smythe, Carol      |               38 |
	| Hayes, Evelyn      |               32 |
	| Evans, Michael     |               22 |
	| Raveen, Lemont     |               24 |
	| James, Mary        |               49 |
	| Williams, Judy     |               34 |
	| Thomas, Tom        |               21 |
	| Jones, Tim         |               20 |
	| Bullock, J.D.      |                0 |
	| Collins, Joanne    |               21 |
	| Brunet, Paul C.    |               21 |
	| Schmidt, Herman    |               20 |
	| Iwano, Masahiro    |               26 |
	| Smith, Paul        |               21 |
	| Onstad, Richard    |               19 |
	| Zugnoni, Arthur A. |               21 |
	| Choy, Wanda        |               23 |
	| Wallace, Maggie J. |               19 |
	| Bailey, Chas M.    |               19 |
	| Bono, Sonny        |               24 |
	| Schwarz, Jason B.  |               15 |
	+--------------------+------------------+
	25 rows in set (0.01 sec)*/

------------------------------------------------------------------
/*6.List all employees who have a last name ending with “son”. */

SELECT name 
FROM jbemployee 
WHERE name LIKE '%son,%';

/*	+---------------+
	| name          |
	+---------------+
	| Thompson, Bob |
	+---------------+
	1 row in set (0.00 sec) */

-------------------------------------------------------------------
/*7. Which items (note items, not parts) have been delivered by a supplier
called Fisher-Price? Formulate this query by using a subquery in the
WHERE clause.*/

SELECT id, name
FROM jbitem
WHERE supplier IN (
SELECT id
FROM jbsupplier
WHERE name = 'Fisher-Price'
);

/*	+-----+-----------------+
	| id  | name            |
	+-----+-----------------+
	|  43 | Maze            |
	| 107 | The 'Feel' Book |
	| 119 | Squeeze Ball    |
	+-----+-----------------+
	3 rows in set (0.01 sec)*/

----------------------------------------------------------------
/*8. Formulate the same query as above, but without a subquery. */

SELECT jbitem.id, jbitem.name
FROM jbitem
JOIN jbsupplier ON jbitem.supplier = jbsupplier.id
WHERE jbsupplier.name = 'Fisher-Price';

/*
	+-----+-----------------+
	| id  | name            |
	+-----+-----------------+
	|  43 | Maze            |
	| 107 | The 'Feel' Book |
	| 119 | Squeeze Ball    |
	+-----+-----------------+
	3 rows in set (0.01 sec) */

-------------------------------------------------------------------
/*9.List all cities that have suppliers located in them. Formulate this query
using a subquery in the WHERE clause.*/

SELECT name 
FROM jbcity
WHERE id IN (
SELECT city 
FROM jbsupplier
);

/*	+----------------+
	| name           |
	+----------------+
	| Amherst        |
	| Boston         |
	| New York       |
	| White Plains   |
	| Hickville      |
	| Atlanta        |
	| Madison        |
	| Paxton         |
	| Dallas         |
	| Denver         |
	| Salt Lake City |
	| Los Angeles    |
	| San Diego      |
	| San Francisco  |
	| Seattle        |
	+----------------+
	15 rows in set (0.01 sec) */

-------------------------------------------------------------------
/*10. What is the name and the color of the parts that are heavier than a card
reader? Formulate this query using a subquery in the WHERE clause.
(The query must not contain the weight of the card reader as a constant;
instead, the weight has to be retrieved within the query.) */

SELECT name, color  
FROM jbparts  
WHERE weight >( 
SELECT weight 
FROM jbparts 
WHERE name = 'card reader');

/*	+--------------+--------+
	| name         | color  |
	+--------------+--------+
	| disk drive   | black  |
	| tape drive   | black  |
	| line printer | yellow |
	| card punch   | gray   |
	+--------------+--------+
	4 rows in set (0.01 sec) */

-------------------------------------------------------------------
/*11. Formulate the same query as above, but without a subquery. Again, the
query must not contain the weight of the card reader as a constant.*/

SELECT A.name, A.color 
FROM jbparts AS A 
JOIN jbparts AS B ON B.name = 'card reader' 
WHERE A.weight > B.weight;

/*	+--------------+--------+
	| name         | color  |
	+--------------+--------+
	| disk drive   | black  |
	| tape drive   | black  |
	| line printer | yellow |
	| card punch   | gray   |
	+--------------+--------+
	4 rows in set (0.01 sec) */
-------------------------------------------------------------------
/*12. What is the average weight of all black parts?*/

SELECT AVG(weight)
FROM jbparts
WHERE color = 'black';

/* +-------------+
   | AVG(weight) |
   +-------------+
   |    347.2500 |
   +-------------+
   1 row in set (0.01 sec)
*/

-------------------------------------------------------------------
/*13. For every supplier in Massachusetts (“Mass”), retrieve the name and the
total weight of all parts that the supplier has delivered? Do not forget to
take the quantity of delivered parts into account. Note that one row
should be returned for each supplier */

SELECT s.name, SUM(p.weight * sp.quan) AS total_weight
FROM jbsupplier s  
JOIN jbcity c ON c.id = s.city
JOIN jbsupply sp ON sp.supplier = s.id
JOIN jbparts p ON p.id = sp.part
WHERE c.state = 'Mass'
GROUP BY s.name;

/*	+--------------+--------------+
	| name         | total_weight |
	+--------------+--------------+
	| DEC          |         3120 |
	| Fisher-Price |      1135000 |
	+--------------+--------------+
	2 rows in set (0.01 sec) */

-------------------------------------------------------------------
/*14. Create a new relation with the same attributes as the jbitems relation by
using the CREATE TABLE command where you define every attribute
explicitly (i.e., not as a copy of another table). Then, populate this new
relation with all items that cost less than the average price for all items.
Remember to define the primary key and foreign keys in your table!*/

CREATE TABLE new_jbitem (
id INT,
name VARCHAR(100),
dept INT,
price INT, 
qoh INT,
supplier INT,
CONSTRAINT pk_jbitem PRIMARY KEY (id),
CONSTRAINT fk_jbitem_debt FOREIGN KEY (dept) REFERENCES jbdept (id),
CONSTRAINT fk_jbitem_supplier FOREIGN KEY (supplier) REFERENCES jbsupplier (id)
);


INSERT INTO new_jbitem
SELECT *
FROM jbitem 
WHERE price < (SELECT AVG(price) FROM jbitem);
SELECT * 
FROM new_jbitem;


SELECT * 
FROM new_jbitem;

/*
+-----+-----------------+------+-------+------+----------+
| id  | name            | dept | price | qoh  | supplier |
+-----+-----------------+------+-------+------+----------+
|  11 | Wash Cloth      |    1 |    75 |  575 |      213 |
|  19 | Bellbottoms     |   43 |   450 |  600 |       33 |
|  21 | ABC Blocks      |    1 |   198 |  405 |      125 |
|  23 | 1 lb Box        |   10 |   215 |  100 |       42 |
|  25 | 2 lb Box, Mix   |   10 |   450 |   75 |       42 |
|  26 | Earrings        |   14 |  1000 |   20 |      199 |
|  43 | Maze            |   49 |   325 |  200 |       89 |
| 106 | Clock Book      |   49 |   198 |  150 |      125 |
| 107 | The 'Feel' Book |   35 |   225 |  225 |       89 |
| 118 | Towels, Bath    |   26 |   250 | 1000 |      213 |
| 119 | Squeeze Ball    |   49 |   250 |  400 |       89 |
| 120 | Twin Sheet      |   26 |   800 |  750 |      213 |
| 165 | Jean            |   65 |   825 |  500 |       33 |
| 258 | Shirt           |   58 |   650 | 1200 |       33 |
+-----+-----------------+------+-------+------+----------+
*/

-------------------------------------------------------------------
/*15. Create a view that contains the items that cost less than the average
price for items.*/

CREATE VIEW cheap_items AS 
SELECT *
FROM jbitem
WHERE price < (SELECT AVG(price) FROM jbitem);

/* mysql> SELECT * FROM cheap_items;
+-----+-----------------+------+-------+------+----------+
| id  | name            | dept | price | qoh  | supplier |
+-----+-----------------+------+-------+------+----------+
|  11 | Wash Cloth      |    1 |    75 |  575 |      213 |
|  19 | Bellbottoms     |   43 |   450 |  600 |       33 |
|  21 | ABC Blocks      |    1 |   198 |  405 |      125 |
|  23 | 1 lb Box        |   10 |   215 |  100 |       42 |
|  25 | 2 lb Box, Mix   |   10 |   450 |   75 |       42 |
|  26 | Earrings        |   14 |  1000 |   20 |      199 |
|  43 | Maze            |   49 |   325 |  200 |       89 |
| 106 | Clock Book      |   49 |   198 |  150 |      125 |
| 107 | The 'Feel' Book |   35 |   225 |  225 |       89 |
| 118 | Towels, Bath    |   26 |   250 | 1000 |      213 |
| 119 | Squeeze Ball    |   49 |   250 |  400 |       89 |
| 120 | Twin Sheet      |   26 |   800 |  750 |      213 |
| 165 | Jean            |   65 |   825 |  500 |       33 |
| 258 | Shirt           |   58 |   650 | 1200 |       33 |
+-----+-----------------+------+-------+------+----------+
*/ 

-------------------------------------------------------------------
/* 16. What is the difference between a table and a view? One is static and the
other is dynamic. Which is which and what do we mean by static
respectively dynamic?

The difference between a table and a view is that a table stores data physically while a view is virtual 
and always has to retrieve it dynamically from other tables. A table is static because you have to manually 
update what it contains but a view is dynamic because it always reflects what the latest version of the other tables are containing.
A table can be modified directly a view cant, it will simply "view" the current result of the query. */

-------------------------------------------------------------------
/*17. Create a view that calculates the total cost of each debit, by considering
price and quantity of each bought item. (To be used for charging
customer accounts). The view should contain the sale identifier (debit)
and the total cost. In the query that defines the view, capture the join
condition in the WHERE clause (i.e., do not capture the join in the
FROM clause by using keywords inner join, right join or left join).*/

CREATE VIEW total_cost AS 
SELECT debit, SUM(quantity * price) AS total_cost 
FROM jbsale, jbitem
WHERE jbsale.item = jbitem.id
GROUP BY debit; 


SELECT * 
FROM total_cost;
/*
+--------+-------------+
| debit  | total price |
+--------+-------------+
| 100581 |        2050 |
| 100582 |        1000 |
| 100586 |       13446 |
| 100592 |         650 |
| 100593 |         430 |
| 100594 |        3295 |
+--------+-------------+
*/

-------------------------------------------------------------------
/*18. Do the same as in the previous point, but now capture the join conditions
in the FROM clause by using only left, right or inner joins. Hence, the
WHERE clause must not contain any join condition in this case. Motivate
why you use type of join you do (left, right or inner), and why this is the
correct one (in contrast to the other types of joins) */

CREATE VIEW total_cost2 AS 
SELECT debit, SUM(quantity * price) AS total_cost 
FROM jbsale  
INNER JOIN jbitem ON jbitem.id = jbsale.item 
GROUP BY jbsale.debit;

SELECT * 
FROM total_cost2;

/*
+--------+-------------+
| debit  | total price |
+--------+-------------+
| 100581 |        2050 |
| 100582 |        1000 |
| 100586 |       13446 |
| 100592 |         650 |
| 100593 |         430 |
| 100594 |        3295 |
+--------+-------------+
*/

/*
 Q: Motivate why you use type of join you do (left, right or inner), and why this is the
    correct one (in contrast to the other types of joins).

 A: We used inner join since we want matching rows from both tables knowing that data exists for every match.
    
    Left join would also work for this assignment but inner join is more fitting since we know
    that there exists item data corresponding to each debit. If we didn't know this left join would be more suitable
    since it would show an entry for every debit (which we want either way), filling item data as null if there were none.

    Right and full join would be completely wrong to use here since they would fill the result
    with items that were not part of any debit (making the query focus more on items instead of the debits), 
    giving unnecessary entries with null values in their debit parts.
*/

-----------------------------------------------------------------
/*19. Oh no! An earthquake!
a) Remove all suppliers in Los Angeles from the jbsupplier table. This
will not work right away. Instead, you will receive an error with error
code 23000 which you will have to solve by deleting some other
related tuples. However, do not delete more tuples from other tables
than necessary, and do not change the structure of the tables (i.e.,
do not remove foreign keys). Also, you are only allowed to use “Los
Angeles” as a constant in your queries, not “199” or “900”.
b) Explain what you did and why. */

DELETE FROM jbsale
WHERE item IN (
SELECT id FROM jbitem
WHERE supplier IN (
SELECT id FROM jbsupplier
WHERE city IN (
SELECT id FROM jbcity WHERE name = 'Los Angeles'
)
)
);

DELETE FROM jbitem
WHERE supplier IN (
SELECT id FROM jbsupplier
WHERE city IN (
SELECT id FROM jbcity WHERE name = 'Los Angeles'
)
);

DELETE FROM new_jbitem
WHERE supplier IN (
SELECT id FROM jbsupplier
WHERE city IN (
SELECT id FROM jbcity WHERE name = 'Los Angeles'
)
);


DELETE FROM jbsupplier
WHERE city IN (
SELECT id FROM jbcity WHERE name = 'Los Angeles'
);

/* b) We started off by trying to delete the suppliers from the jbsupplier table located in Los Angeles, 
but this failed because foreign keys in other tables were still referencing those suppliers.

The first error we got was related to the jbitem table, which has a foreign key to jbsupplier.
We tried to delete those items, but this also failed because jbsale contains rows 
that reference items in jbitem.

We first deleted the rows in jbsale that referenced items which in turn were 
supplied by suppliers in Los Angeles. After that, we were able to delete the rows from jbitem.

However, we had previously created a new table called new_jbitem which also had a foreign key 
to jbsupplier, and it still contained items referencing those suppliers. 
So we had to delete those rows from new_jbitem as well.

After all these dependencies were removed we were finally able to delete the suppliers 
from the jbsupplier table. 


PS: Ideally you would also check in jbsupply and delete potential entries there since
    that table also has data refering to suppliers. In this case it was not needed because
    there was no entry refering to the supplier in Los Angeles.

*/
-------------------------------------------------------------------

/*20. An employee has tried to find out which suppliers have delivered items
that have been sold. To this end, the employee has created a view and
a query that lists the number of items sold from a supplier.
---
Now, the employee also wants to include the suppliers that have
delivered some items, although for whom no items have been sold so
far. In other words, he wants to list all suppliers that have supplied any
item, as well as the number of these items that have been sold. Help
him! Drop and redefine the jbsale_supply view to also consider suppliers
that have delivered items that have never been sold.
Hint: Notice that the above definition of jbsale_supply uses an (implicit)
inner join that removes suppliers that have not had any of their delivered
items sold. */
CREATE OR REPLACE VIEW jbsale_supply AS
SELECT jbsupplier.name AS supplier_name, jbitem.name AS item_name, jbsale.quantity
FROM jbsupplier
JOIN jbitem ON jbitem.supplier = jbsupplier.id
LEFT JOIN jbsale ON jbsale.item = jbitem.id;

SELECT supplier, sum(quantity) AS sum FROM jbsale_supply
GROUP BY supplier;

/*
+--------------+------+
| supplier     | sum  |
+--------------+------+
| Cannon       |    6 |
| Fisher-Price | NULL |
| Levi-Strauss |    1 |
| Playskool    |    2 |
| White Stag   |    4 |
| Whitman's    |    2 |
+--------------+------+
*/