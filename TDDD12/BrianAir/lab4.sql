SET FOREIGN_KEY_CHECKS = 0;

DROP TABLE IF EXISTS Ticket;
DROP TABLE IF EXISTS Booking; 
DROP TABLE IF EXISTS Payer;
DROP TABLE IF EXISTS Contact; 
DROP TABLE IF EXISTS Passenger_reservation;
DROP TABLE IF EXISTS Reservation;
DROP TABLE IF EXISTS Passenger;
DROP TABLE IF EXISTS Flight;
DROP TABLE IF EXISTS WeeklySchedule;
DROP TABLE IF EXISTS Route; 

DROP TABLE IF EXISTS Contact;
DROP TABLE IF EXISTS Passenger;
DROP TABLE IF EXISTS Payer;
DROP TABLE IF EXISTS ProfitFactor;
DROP TABLE IF EXISTS WeekDay;
DROP TABLE IF EXISTS Airport;

SET FOREIGN_KEY_CHECKS = 1;

CREATE TABLE Airport (
    AirportCode VARCHAR(3),
    AirportName VARCHAR(30),
    Country VARCHAR(30), 

    constraint pk_airport
        PRIMARY KEY (AirportCode)
);

CREATE TABLE WeekDay (
    Day VARCHAR(10),
    WeekdayFactor DOUBLE,
    Year INTEGER,

    constraint pk_weekday
        PRIMARY KEY (Day, Year)
);

CREATE TABLE ProfitFactor (
    Year INT,
    Factor DOUBLE, 
    
    constraint pk_profitfactor
        PRIMARY KEY (Year)
);

CREATE TABLE Payer (
    CCNo BIGINT,
    CCHolder VARCHAR(30),

    constraint pk_payer
        PRIMARY KEY (CCNo)
);

CREATE TABLE Passenger (
    PassportNo INT,
    Name VARCHAR(30), 

    constraint pk_passenger
        PRIMARY KEY (PassportNo)
);

CREATE TABLE Contact (
    Email VARCHAR(30),
    PhoneNo BIGINT,
    PassportNo INTEGER PRIMARY KEY,
    
    constraint fk_contact_passport
        FOREIGN KEY (PassportNo) references Passenger(PassportNo)
);

CREATE TABLE Route (
    ID INT AUTO_INCREMENT PRIMARY KEY,
    RoutePrice DOUBLE, 
    Departure VARCHAR(3),
    Arrival VARCHAR(3),
    Year INT, 
    constraint fk_route_AirportCode_departure
        FOREIGN KEY (Departure) references Airport(AirportCode),
    constraint fk_route_AirportCode_arrival
        FOREIGN KEY (Arrival) references Airport(AirportCode)
); 

CREATE TABLE WeeklySchedule (
    ID INT AUTO_INCREMENT,
    Year INT,
    TimeOfDep TIME,
    RouteID INT,
    WeekDay VARCHAR(10),

    constraint pk_weeklyschedule
        PRIMARY KEY (ID),
    constraint fk_weeklyschedule_route
        FOREIGN KEY (RouteID) references Route(ID),
    constraint fk_weeklyschedule_weekday
        FOREIGN KEY (WeekDay) references WeekDay(Day)
);

CREATE TABLE Flight (
    FlightID INT AUTO_INCREMENT PRIMARY KEY, 
    EmptySeats INT, 
    WeeklyFlight INT, 
    WeekNo INT, 
    constraint fk_flight_WeeklySchedule
        FOREIGN KEY (WeeklyFlight) references WeeklySchedule(ID)
);

CREATE TABLE Reservation (
    ReservationID INT AUTO_INCREMENT,
    TotalPrice    DOUBLE,
    FlightID      INT,                       

    constraint pk_reservation
        PRIMARY KEY (ReservationID),

    constraint fk_reservation_flight        
        FOREIGN KEY (FlightID) references Flight(FlightID)
);


CREATE TABLE Booking (
    BookingID INT PRIMARY KEY, 
    FlightNo INT, 
    Payer BIGINT,
    Contact INT, 

    constraint fk_booking_id
        FOREIGN KEY (BookingID) references Reservation(ReservationID),
    constraint fk_booking_FlightNumber
        FOREIGN KEY (FlightNo) references Flight(FlightID),
    constraint fk_booking_Payer
        FOREIGN KEY (Payer) references Payer(CCNo),
    constraint fk_booking_Contact
        FOREIGN KEY (Contact) references Contact(PassportNo)
);

CREATE TABLE Ticket (
    TicketNo INT DEFAULT 0,
    PassportNo INT,
    BookingID INT,

    constraint pk_ticket
        PRIMARY KEY (TicketNo), 
    constraint fk_ticket_passport
        FOREIGN KEY (PassportNo) references Passenger(PassportNo),
    constraint fk_ticket_booking
        FOREIGN KEY (BookingID) references Booking(BookingID)
);

CREATE TABLE Passenger_reservation (
    ReservationID INT,
    PassportNo INT,
    constraint pk_passenger_reservation
        PRIMARY KEY (ReservationID, PassportNo), 
    constraint fk_passenger_reservation_ReservationID
        FOREIGN KEY (ReservationID) references Reservation(ReservationID),
    constraint fk_passenger_reservation_PassportNo
        FOREIGN KEY (PassportNo) references Passenger(PassportNo)
);


-- Procedures ------------------------------------------------------------------

DROP PROCEDURE IF EXISTS addYear;
delimiter //
CREATE PROCEDURE addYear(IN year_value INT, IN factor_value DOUBLE)
BEGIN
INSERT INTO ProfitFactor(Year, Factor) VALUES (year_value, factor_value);
END;
//
delimiter ; 

DROP PROCEDURE IF EXISTS addDay;
delimiter //
CREATE PROCEDURE addDay(IN year_value INT, IN day_value VARCHAR(10), IN factor_value DOUBLE)
BEGIN
INSERT INTO WeekDay(Day, Year, WeekdayFactor) VALUES (day_value, year_value, factor_value);
END;
//
delimiter ; 

DROP PROCEDURE IF EXISTS addDestination;
delimiter //
CREATE PROCEDURE addDestination(In airport_code VARCHAR(3), IN name VARCHAR(30), IN country VARCHAR(30))
BEGIN 
INSERT INTO Airport(AirportCode, AirportName, Country) VALUES (airport_code, name, country);
END;
//
delimiter ; 

DROP PROCEDURE IF EXISTS addRoute;
delimiter //
CREATE PROCEDURE addRoute(IN departure_airport_code VARCHAR(3), IN arrival_airport_code VARCHAR(3), 
                          IN year INTEGER, IN routeprice DOUBLE)
BEGIN
INSERT INTO Route(Departure, Arrival, Year, RoutePrice) VALUES (departure_airport_code, arrival_airport_code, year, routeprice);
END;
//
delimiter ;


DROP PROCEDURE IF EXISTS addFlight;
delimiter //
CREATE PROCEDURE addFlight(IN departure_airport_code VARCHAR(3), 
                            IN arrival_airport_code VARCHAR(3), 
                            IN year_in INT, 
                            IN day_in VARCHAR(10),
                            IN departure_time TIME)
BEGIN
-- hitta route_id
DECLARE route_id INT;
DECLARE schedule_id INT;
DECLARE i INT DEFAULT 1;

SELECT ID INTO route_id
FROM Route
WHERE Departure = departure_airport_code AND Arrival = arrival_airport_code  AND Year = year_in;
-- skapa veckoschema
INSERT INTO WeeklySchedule(Year, TimeOfDep, RouteID, Weekday) 
    VALUES (year_in, departure_time, route_id, day_in);
-- skapa flyg

SET schedule_id = LAST_INSERT_ID();
WHILE i <= 52 DO
    INSERT INTO Flight (EmptySeats, WeeklyFlight, WeekNo)
    VALUES (40, schedule_id, i);
    SET i = i + 1;
END WHILE;
END;
//
delimiter ;

-- Helper functions ------------------------------------------------------------

DROP FUNCTION IF EXISTS calculateFreeSeats;
delimiter //

CREATE FUNCTION calculateFreeSeats(flightnumber_in INT)
RETURNS INT
DETERMINISTIC
BEGIN
-- DECLARE Booked_seats INT;

-- SELECT COUNT(*) INTO Booked_seats 
-- FROM Ticket, Booking
-- WHERE Ticket.BookingID = Booking.BookingID AND Booking.FlightNo = flightnumber_in;

-- RETURN 40 - Booked_seats;  
DECLARE empty_seats INT;
SELECT EmptySeats INTO empty_seats
FROM Flight WHERE FlightID = flightnumber_in;
RETURN empty_seats;
END;
//
delimiter ;




-- Calculate the price of the next seat on a flight: Function call:
-- calculatePrice(flightnumber);
-- The output of this function is the price (i.e., a double) of the next seat,
-- calculated as specified in point 1e above
DROP FUNCTION IF EXISTS calculatePrice;
delimiter //
CREATE FUNCTION calculatePrice(flightnumber_in INT)
RETURNS DOUBLE
DETERMINISTIC
BEGIN
DECLARE route_price DOUBLE;
DECLARE week_day_factor DOUBLE;
DECLARE profit_factor DOUBLE;
DECLARE price DOUBLE;
DECLARE year_var INT; 
DECLARE booked_seats INT;
DECLARE day_var VARCHAR(10);

-- get booked seats
SET booked_seats = 40 - calculateFreeSeats(flightnumber_in); 

-- get route price
SELECT Route.Year, RoutePrice, WeeklySchedule.Weekday INTO year_var, route_price, day_var
FROM WeeklySchedule, Flight, Route
WHERE Flight.FlightID = flightnumber_in AND Flight.WeeklyFlight = WeeklySchedule.ID
      AND Route.ID = WeeklySchedule.RouteID;

-- get weekday factor
SELECT WeekdayFactor INTO week_day_factor
FROM WeekDay
WHERE Day = day_var AND Year = year_var;

-- get profit factor
SELECT Factor INTO profit_factor
FROM ProfitFactor
WHERE Year = year_var;

RETURN route_price * week_day_factor * ((booked_seats + 1)/40) * profit_factor;

END;
//
delimiter ;


-- Create a trigger that issues unique, unguessable ticket-numbers (of type integer)
-- for each passenger on a reservation once it is paid. An appropriate SQL function to
-- find unguessable numbers is rand()
-- DROP TRIGGER IF EXISTS newTicketNumberTrigger;
-- CREATE TRIGGER newTicketNumberTrigger
-- DECLARE ticket_number INT DEFAULT 0; 
-- AFTER booking 
-- ON Ticket
-- FOR EACH ROW
-- WHEN booked
-- ticket_number = rand();
DROP TRIGGER IF EXISTS set_ticket_number;
delimiter //
CREATE TRIGGER set_ticket_number
BEFORE INSERT ON Ticket
FOR EACH ROW
BEGIN
    -- generate a random number between 100000000 and 999999999
    DECLARE ticket INT;
    REPEAT
        SET ticket = FLOOR(RAND()*900000000) + 100000000; 
    UNTIL NOT EXISTS (SELECT 1 FROM Ticket WHERE TicketNo = ticket)
    END REPEAT;
    SET NEW.TicketNo = ticket;
END;
//
delimiter ;


-- Create a reservation on a specific flight. Procedure call:
-- addReservation(departure_airport_code, arrival_airport_code, year, week,
-- day, time, number_of_passengers, output_reservation_nr); where the
-- number_of_passengers is the number of passengers the reservation is for (and
-- only used to check that enough unpaid seats are available) and
-- output_reservation_nr is an output-variable and should contain the assigned
-- reservation number.
DROP PROCEDURE IF EXISTS addReservation;
delimiter //
CREATE PROCEDURE addReservation(IN departure_airport_code VARCHAR(3), 
                                IN arrival_airport_code VARCHAR(3), 
                                IN year_in INT, 
                                IN week_in INT, 
                                IN day_in VARCHAR(10), 
                                IN time_in TIME, 
                                IN number_of_passengers INT, 
                                OUT output_reservation_nr INT)

BEGIN
DECLARE route_id INT;
DECLARE weeklyschedule_id INT;
DECLARE flight_id INT;
DECLARE empty_seats INT; 

SELECT ID INTO route_id
FROM Route
WHERE departure_airport_code = Departure AND arrival_airport_code = Arrival AND year_in = Year;

IF route_id IS NULL THEN
    SIGNAL SQLSTATE '45000'
    SET MESSAGE_TEXT = "Route was not found.";
END IF;
-- check if route is in schedule
SELECT ID INTO weeklyschedule_id
FROM WeeklySchedule
WHERE time_in = TimeOfDep AND RouteID = route_id AND Year = year_in AND WeekDay = day_in;
IF weeklyschedule_id IS NULL THEN
    SIGNAL SQLSTATE '45000' 
    SET MESSAGE_TEXT = "There exist no schedule for the given route, date and time";
END IF; 
-- check if flight exists
SELECT FlightID INTO flight_id
FROM Flight
WHERE WeeklyFlight = weeklyschedule_id AND WeekNo = week_in;
IF flight_id IS NULL THEN
    SIGNAL SQLSTATE '45000' 
    SET MESSAGE_TEXT = "There exist no flight for the given route, date and time";
END IF; 
-- check if seats are empty
IF number_of_passengers > calculateFreeSeats(flight_id) THEN
    SIGNAL SQLSTATE '45000' 
    SET MESSAGE_TEXT = "There are not enough seats available on the chosen flight";
END IF;
-- finally create a reservation if all checks are passed.
INSERT INTO Reservation(TotalPrice, FlightID) VALUES (calculatePrice(flight_id), flight_id);

SET output_reservation_nr = LAST_INSERT_ID();

END;
//
delimiter ;


-- HELPER proc FOR FINDING IF RESERVATION ID EXISTS OR NOT
DROP PROCEDURE IF EXISTS checkReservation;
delimiter //
CREATE PROCEDURE checkReservation(reservation_nr INT)
BEGIN
DECLARE reservation_id INT;

-- check if reservation id exists
SELECT ReservationID INTO reservation_id
FROM Reservation WHERE ReservationID = reservation_nr;

IF reservation_id IS NULL THEN
    SIGNAL SQLSTATE '45000'
    SET MESSAGE_TEXT = 'The given reservation number does not exist';
END IF;
END;
//
delimiter ;



-- Add a passenger to a reservation: Procedure call to handle:
-- addPassenger(reservation_nr, passport_number, name);
DROP PROCEDURE IF EXISTS addPassenger;
delimiter //
CREATE PROCEDURE addPassenger(IN reservation_nr INT, IN passport_number INT, IN name VARCHAR(30))
BEGIN
DECLARE passanger_pass_no INT;

CALL checkReservation(reservation_nr); -- call helper proc which checks if the reservation nr exists

IF EXISTS (SELECT 1 FROM Booking WHERE BookingID = reservation_nr) THEN
        SIGNAL SQLSTATE '45000'
        SET MESSAGE_TEXT ='The booking has already been payed and no futher passengers can be added';
END IF;

-- check if passenger already exists
SELECT PassportNo INTO passanger_pass_no
FROM Passenger WHERE PassportNo = passport_number;
-- if exists only add in passenger_reservation
IF passanger_pass_no IS NOT NULL THEN
    INSERT INTO Passenger_reservation(ReservationID, PassportNo) VALUES (reservation_nr, passport_number);
ELSE -- if not, add both in passenger and passenger_reservation
    INSERT INTO Passenger(PassportNo, Name) VALUES (passport_number, name);
    INSERT INTO Passenger_reservation(ReservationID, PassportNo) VALUES (reservation_nr, passport_number);
END IF;
END;
//
delimiter ;


-- Add a contact: Procedure call to handle: addContact(reservation_nr,
-- passport_number, email, phone); where the contact already must be added as
-- a passenger to the reservation.
DROP PROCEDURE IF EXISTS addContact;
delimiter //
CREATE PROCEDURE addContact(IN reservation_nr INT, IN passport_number INT, IN email VARCHAR(30), IN phone BIGINT)
BEGIN
DECLARE passanger_pass_no INT;

CALL checkReservation(reservation_nr); -- check first if reservation exists

-- check if there exists a passenger for the reservation with the given passNo
SELECT PassportNo INTO passanger_pass_no
FROM Passenger_reservation
WHERE ReservationID = reservation_nr AND PassportNo = passport_number;

IF passanger_pass_no IS NULL THEN
    SIGNAL SQLSTATE '45000'
    SET MESSAGE_TEXT = 'The person is not a passenger of the reservation';
END IF;

INSERT INTO Contact(Email, PhoneNo, PassportNo) VALUES (email, phone, passport_number);
END;
//
delimiter ;


-- Add a payment: Procedure call to handle: addPayment (reservation_nr,
-- cardholder_name, credit_card_number); This procedure should, if the
-- reservation has a contact and there are enough unpaid seats on the plane, add
-- payment information to the reservation and save the amount to be drawn from
-- the credit card in the database. If the conditions above are not fulfilled the
-- appropriate error message should be shown
DROP PROCEDURE IF EXISTS addPayment;
delimiter //
CREATE PROCEDURE addPayment(IN reservation_nr INT, IN cardholder_name VARCHAR(30), IN credit_card_number BIGINT)
BEGIN
DECLARE contact_passNo INT;
DECLARE flight_id INT;
DECLARE passenger_cnt INT;
DECLARE ticket_price DOUBLE;
DECLARE done INT DEFAULT 0;
DECLARE cur_pass_no INT;

CALL checkReservation(reservation_nr); -- check if reservation exists


-- check if reservation has a contact passenger
SELECT Contact.PassportNo INTO contact_passNo
FROM Contact, Passenger_reservation
WHERE Passenger_reservation.ReservationID = reservation_nr AND Passenger_reservation.PassportNo = Contact.PassportNo;

IF contact_passNo IS NULL THEN
    SIGNAL SQLSTATE '45000'
    SET MESSAGE_TEXT = 'The reservation has no contact yet';
END IF;


-- get flight id
SELECT FlightID INTO flight_id
FROM Reservation
WHERE ReservationID = reservation_nr;

-- count number of passengers
SELECT COUNT(*) INTO passenger_cnt
FROM Passenger_reservation
WHERE ReservationID = reservation_nr;

IF passenger_cnt > calculateFreeSeats(flight_id) THEN
    DELETE FROM Passenger_reservation
    WHERE ReservationID = reservation_nr;
    DELETE FROM Reservation
    WHERE ReservationID = reservation_nr;

    SIGNAL SQLSTATE '45000'
    SET MESSAGE_TEXT = 'There are not enough seats available on the flight anymore, deleting reservation';
END IF;


-- ---------------------------> ONLY FOR QUESTION 10 c) <---------------------------------------
-- SELECT sleep(5);

-- all checks passed, create payer IF payer does not already exists, if exists ignore this line
INSERT IGNORE INTO Payer(CCNo, CCHolder) VALUES (credit_card_number, cardholder_name);


-- create booking
INSERT INTO Booking(BookingID, FlightNo, Payer, Contact)
VALUES (reservation_nr, flight_id, credit_card_number, contact_passNo);

-- create tickets
INSERT INTO Ticket(PassportNo, BookingID)
SELECT PassportNo, reservation_nr
FROM Passenger_reservation
WHERE ReservationID = reservation_nr;

-- reduce empty seats
UPDATE Flight
SET EmptySeats = EmptySeats - passenger_cnt
WHERE FlightID = flight_id;
END;
//
delimiter ;


-- View: allFlights
-- departure_city_name
-- destination_city_name
-- departure_time
-- departure_day
-- departure_week
-- departure_year
-- nr_of_free_seats
-- current_price_per_seat
delimiter //

DROP VIEW IF EXISTS allFlights;
CREATE VIEW allFlights AS
SELECT
    dep.AirportName AS departure_city_name,
    arr.AirportName AS destination_city_name,
    WS.TimeOfDep AS departure_time,
    WS.WeekDay AS departure_day,
    F.WeekNo AS departure_week,
    WS.Year AS departure_year,
    calculateFreeSeats(F.FlightID) AS nr_of_free_seats,
    calculatePrice(F.FlightID) AS current_price_per_seat
FROM Flight         F,
     WeeklySchedule WS,
     Route          R,
     Airport        dep,
     Airport        arr
WHERE F.WeeklyFlight = WS.ID
  AND WS.RouteID     = R.ID
  AND R.Departure    = dep.AirportCode
  AND R.Arrival      = arr.AirportCode;

// 
delimiter ;  




/*
8. Answer the following theoretical questions:
a) How can you protect the credit card information in the database from hackers?
b) Give three advantages of using stored procedures in the database (and thereby
execute them on the server) instead of writing the same functions in the
frontend of the system (in for example JavaScript on a Web page)?*/

/* 
a) To protect credit card info, you should never store it as plain text. 
Hash it so it’s not easy to crack. Also, always use a secure connection to the database, like with SSL.
Keep permissions minimal, don’t give apps or users more access than they need, so if something gets hacked, 
the damage is limited. Sanitize all input properly to avoid SQL injections, and use stored procedures instead of writing raw queries. 
That way, you have more control over what the user can actually do.

b) Stored procedures improve security since the SQL runs on the server, reducing the risk of things like SQL injection. 
They’re also faster because the database handles everything directly. And they’re convenient, 
you can update logic without changing the frontend code.
*/ 


/*
9. Open two SQL sessions in two terminals. We call one of them A and the other one
B. Write START TRANSACTION; in both terminals.
a) In session A, add a new reservation.
b) Is this reservation visible in session B? Why? Why not?
c) What happens if you try to modify the reservation from A in B? Explain what
happens and why this happens and how this relates to the concept of isolation
of transactions.

a) 
TERMINAL A
mysql> START TRANSACTION;
Query OK, 0 rows affected (0.00 sec)
mysql> CALL addReservation("MIT", "HOB", 2010, 1, "Monday", "09:00:00", 1, @res);
Query OK, 1 row affected (0.00 sec)

mysql> SELECT @res;
+------+
| @res |
+------+
|    5 |
+------+
1 row in set (0.00 sec)

b) 
TERMINAL B
mysql> SELECT * FROM Reservation
    -> ;
+---------------+--------------------+----------+
| ReservationID | TotalPrice         | FlightID |
+---------------+--------------------+----------+
|             1 | 114.99999999999999 |        1 |
|             2 | 114.99999999999999 |       53 |
|             3 | 229.99999999999997 |        1 |
+---------------+--------------------+----------+
3 rows in set (0.00 sec)

No, the reservation is not visible in session B because it is part of a transaction that has not been committed yet. 
Until the transaction is committed, the changes are not visible to other transactions.

c) 
If we try to modify the same reservation in Terminal B, the query hangs until it eventually fails with a timeout error:
TERMINAL B
mysql> UPDATE Reservation SET TotalPrice = 9999 WHERE ReservationID = 5;
ERROR 1205 (HY000): Lock wait timeout exceeded; try restarting transaction
mysql> 
This happens because Terminal A is holding a lock on that row, and Terminal B can’t access it until A commits or rolls back. 
This is how MySQL ensures isolation between concurrent transactions — changes must be isolated and consistent.
*/ 





/*
10. Is your BryanAir implementation safe when handling multiple concurrent
transactions? Let two customers try to simultaneously book more seats than what are
available on a flight and see what happens. This is tested by executing the testscripts
available on the course-page using two different MySQL sessions. Note that you
should not use explicit transaction control unless this is your solution on 10c.

Q: 
a) Did overbooking occur when the scripts were executed? If so, why? If not,
why not?

A: 
No it doesnt seem like overbookings occured when running the test scripts.
We assume its because MySQL has Repeatable-Read as default which adds write and read locks on used tuples.
Since the scripts run so fast, the first transaction locks tuples needed (specificallly the free seats attribute) before the second
transaction reaches the calculateFreeSeats line in our addPayment, and therefore the tuple can only be accessed after
the first transaction is commited.

Q:
b) Can an overbooking theoretically occur? If an overbooking is possible, in what
order must the lines of code in your procedures/functions be executed.

A:
Yes. Since we check free seats first (in addPayment) and then update it in a later statement it is possible that another transaction can in between this read and write, read the
free seats (also in addPayment) before it is updated. In that case there would be an overbooking.

The order would be something like:
1. T1 - calls calculateFreeSeats
2. T2 - also calls calculateFreeSeats (which will be the same as it was for T1)
3. T1 - completes booking and reduces the seats.
4. T2 - also (INCORRECTLY) completes booking and further reduces the seats.  



Q:
c) Try to make the theoretical case occur in reality by simulating that multiple
sessions call the procedure at the same time. To specify the order in which the
lines of code are executed use the MySQL query SELECT sleep(5); which
makes the session sleep for 5 seconds. Note that it is not always possible to
make the theoretical case occur, if not, motivate why.

A: We made the theoretical case occur by adding sleep right after the calculateFreeSeat method is called. This gives 
the second transaction enought time to call its calculateFreeSeats before the first transaction reaches its seat update statement and locks the attribute.



Q:
d) Modify the testscripts so that overbookings are no longer possible using
(some of) the commands START TRANSACTION, COMMIT, LOCK TABLES, UNLOCK
TABLES, ROLLBACK, SAVEPOINT, and SELECT…FOR UPDATE. Motivate why your
solution solves the issue, and test that this also is the case using the sleep
implemented in 10c. Note that it is not ok that one of the sessions ends up in a
deadlock scenario. Also, try to hold locks on the common resources for as
short time as possible to allow multiple sessions to be active at the same time.


A:
code that fixes the overbooking issue:

START TRANSACTION;

SELECT Flight.* FROM Flight, Reservation
WHERE ReservationID = @a AND Reservation.FlightID = Flight.FlightID
FOR UPDATE;

CALL addPayment (@a, "Sauron",7878787878);

COMMIT;

What we do here is that we lock the specific flight tuple that is to be updated on each transaction.
This forces every other transaction to wait for the first transaction to release the lock before they can
read and call calculateFreeSeats, making it so that they will always read an updated tuple that is in a consistent state.


Q:
Identify one case where a secondary index would be useful. Design the index,
describe and motivate your design. (Do not implement this.)


A:
SELECT Route.Year, RoutePrice, WeeklySchedule.Weekday INTO year_var, route_price, day_var
FROM WeeklySchedule, Flight, Route
WHERE Flight.FlightID = flightnumber_in AND Flight.WeeklyFlight = WeeklySchedule.ID
      AND Route.ID = WeeklySchedule.RouteID;

This is from calculatePrice and is used to get the route price from a given flight number.
The query has a join on 3 tables and 3 compare requirements to find the correct route (route price) corresponding to the flight,
which could be heavy on performance if the schedule and route tables are large since it would need to cross compare the tuples.

This could be optimized with secondary indexing by making it so that each flight has an index to its schedule (secondary index on Flight(WeeklyFlight)), and each schedule has
an index to its route (secondary index on WeeklySchedule(RouteID)), which would avoid unnecessary comparisons and give more direct access to the wanted route tuple.
*/






/*
ADDITIONAL HANDIN INFO:

The relational db schema is changed slightly (added FlightID on Reservation table) after initial approval.
*/


