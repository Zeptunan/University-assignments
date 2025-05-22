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
CALL addPassenger(@a,000000011,"Saruman");
CALL addPassenger(@a,000000022,"Orch1");
CALL addPassenger(@a,000000033,"Orch2");
CALL addPassenger(@a,000000044,"Orch3");
CALL addPassenger(@a,000000055,"Orch4");
CALL addPassenger(@a,000000066,"Orch5");
CALL addPassenger(@a,000000077,"Orch6");
CALL addPassenger(@a,000000088,"Orch7");
CALL addPassenger(@a,000000099,"Orch8");
CALL addPassenger(@a,000000100,"Orch9");
CALL addPassenger(@a,000000110,"Orch10");
CALL addPassenger(@a,000000120,"Orch11");
CALL addPassenger(@a,000000130,"Orch12");
CALL addPassenger(@a,000000140,"Orch13");
CALL addPassenger(@a,000000150,"Orch14");
CALL addPassenger(@a,000000160,"Orch15");
CALL addPassenger(@a,000000170,"Orch16");
CALL addPassenger(@a,000000180,"Orch17");
CALL addPassenger(@a,000000190,"Orch18");
CALL addPassenger(@a,000000200,"Orch19");
CALL addPassenger(@a,000000210,"Orch20");
CALL addContact(@a,000000011,"saruman@magic.mail",080667989); 
SELECT SLEEP(5);
SELECT "Making payment, supposed to work for one session and be denied for the other" as "Message";

START TRANSACTION;

SELECT Flight.* FROM Flight, Reservation
WHERE ReservationID = @a AND Reservation.FlightID = Flight.FlightID
FOR UPDATE;

CALL addPayment (@a, "Sauron",7878787878);

COMMIT;
SELECT "Nr of free seats on the flight (should be 19 if no overbooking occured, otherwise -2): " as "Message", (SELECT nr_of_free_seats from allFlights where departure_week = 1) as "nr_of_free_seats";



