/******************************************************************************************
 Question 10, concurrency
 This is the second of two scripts that tests that the BryanAir database can handle concurrency.
 This script sets up a valid reservation and tries to pay for it in such a way that at most 
 one such booking should be possible (or the plane will run out of seats). This script should 
 be run in both terminals, in parallel. 
**********************************************************************************************/

SELECT "Testing script for Question 10, Adds a booking, should be run in both terminals" as "Message";
SELECT "Adding a reservations and passengers" as "Message";
CALL addReservation("MIT","HOB",2010,1,"Monday","09:00:00",21,@a); 
CALL addPassenger(@a,000004001337,"Saruman");
CALL addPassenger(@a,0000056002,"Orch1");
CALL addPassenger(@a,000040003,"Orch2");
CALL addPassenger(@a,000030004,"Orch3");
CALL addPassenger(@a,000006005,"Orch4");
CALL addPassenger(@a,000008006,"Orch5");
CALL addPassenger(@a,000003007,"Orch6");
CALL addPassenger(@a,000200008,"Orch7");
CALL addPassenger(@a,000500009,"Orch8");
CALL addPassenger(@a,000600010,"Orch9");
CALL addPassenger(@a,0006700011,"Orch10");
CALL addPassenger(@a,000800012,"Orch11");
CALL addPassenger(@a,0000230013,"Orch12");
CALL addPassenger(@a,00005660014,"Orch13");
CALL addPassenger(@a,0000120015,"Orch14");
CALL addPassenger(@a,0000660016,"Orch15");
CALL addPassenger(@a,0007800017,"Orch16");
CALL addPassenger(@a,00002340018,"Orch17");
CALL addPassenger(@a,00006770019,"Orch18");
CALL addPassenger(@a,00000948020,"Orch19");
CALL addPassenger(@a,0000644350021,"Orch20");
CALL addContact(@a,000004001337,"saruman@magic.mail",080667989); 
SELECT SLEEP(5);
SELECT "Making payment, supposed to work for one session and be denied for the other" as "Message";

START TRANSACTION;

SELECT Flight.* FROM Flight, Reservation
WHERE ReservationID = @a AND Reservation.FlightID = Flight.FlightID
FOR UPDATE;

CALL addPayment (@a, "Sauron",7878787878);

COMMIT;


SELECT "Nr of free seats on the flight (should be 19 if no overbooking occured, otherwise -2): " as "Message", (SELECT nr_of_free_seats from allFlights where departure_week = 1) as "nr_of_free_seats";


