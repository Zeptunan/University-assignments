-- allsh436: Sammarbetat med maxli926, Max Linder, samma program
with Ada.Text_IO;                  use Ada.Text_IO;
with Ada.Float_Text_IO;            use Ada.Float_Text_IO;
with Ada.Integer_Text_IO;          use Ada.Integer_Text_IO;

package body Date_Package is
   
   Length_Error : exception; 
   
   ---------------------------------------------
   -- Funktion för skottårs kontroll
   ---------------------------------------------
   function Check_Leap(Datum : in Date_type) return Boolean is 
      
      Bool: Boolean;
      
   begin
     
      if (Datum.Year mod 400) = 0 then 
         Bool := True;
   
      elsif
      (Datum.Year mod 4) = 0 and (Datum.Year mod 100)/= 0 then
   
         Bool := True;
      end if;

       return Bool;
      
   end Check_Leap;
   
   
   ---------------------------------------------------------
   -- Kontrollerar om dagen är gilltig 
   ---------------------------------------------------------
   function  Is_Day_Valid (Datum : in Date_type) return Boolean is
      type Month_type is array(1..12) of Integer;
      M: Month_Type := (31,28,31,30,31,30,31,31,30,31,30,31);
   begin
      
      if(not Check_Leap(Datum) and Datum.Day = 29) and Datum.Month = 2  then 
	 raise Day_Error;
      end if;
      if (Check_Leap(Datum) and Datum.Day = 29) then
	 return True;
      end if;
      if Datum.Day <= M(Datum.Month) and Datum.Day > 0 then 
	 return true;
      else
	 return False;
      end if;
      
   end Is_Day_Valid;
   
   
   ------------------------------------------------------
   -- Get för mellanrum innan inmatning av datum 
   ------------------------------------------------------
   procedure Get(Item: out String) is  
   begin
      loop 
	 Get(Item(Item'first));
	 if Item(Item'First) /= ' ' then
	    
	    for  I in Item'First+1 .. Item'last loop
	       if End_Of_Line then
		  raise length_Error;
	       end if;
	       
	       Get(Item(I));
	    end loop;
	    exit;
	 end if;
      end loop;
   end Get;
   
   
   ------------------------------------------------------
   -- Procedure get för angivet datum
   ------------------------------------------------------
   procedure Get(datum : out Date_Type) is 
      S : String(1..10);
   begin 
      Get(S);
      for I in 1..10 loop
	 if I /= 5 and  I /=8 then
	    if S(I) not in '0'..'9' then
      	       raise Format_Error; 
	    end if;
	 else
	    if S(I) /= '-' then
	       raise Format_Error;
	    end if;
	 end if;
      end loop;
      Skip_Line;

      datum.Year   := Integer'Value(S(1..4));
      datum.Month  := Integer'Value(S(6..7)); 
      datum.Day    := Integer'Value(S(9..10)); 

      if datum.Year < 1532 or datum.Year > 9000 then
	 raise Year_Error;
      end if;

      if datum.Month < 1 or datum.Month >12 then
	 raise Month_Error;
      end if; 

      if not Is_Day_Valid(Datum) then
	 raise Day_Error;
      end if;
   end Get;
   
   
   ------------------------------------------------------
   -- Procedure put för datum
   ------------------------------------------------------
   procedure Zero(Item : in Integer) is
      
   begin 
      
      Put("-");
      if Item < 10 then
	 Put("0");
      end if;
	 Put(Item, Width=>0);
	 
   end Zero;
   
   procedure  Put(datum : in date_Type)  is 

   begin
      
      Put(Datum.Year, Width => 0);
      Zero(Datum.Month);
      Zero(Datum.Day);
     
   end Put;
   
   
   -----------------------------------------------------
   -- Funktion som returnerar nästa dags datum
   -----------------------------------------------------
   function Next_Date (datum : in Date_type )return Date_Type is 
      type Month is array(1..12) of Integer;
      M: Month:= (31,28,31,30,31,30,31,31,30,31,30,31);
      D : Date_Type;   
   begin
      D:= datum;
      D.Day:= Datum.Day +1;
     
      if (datum.Month = 2 and  datum.Day = 28 and  Check_Leap(D)) then
	 
	 D.Day:= 29;
	 
      elsif (datum.Month = 2 and  datum.Day = 29 and  Check_Leap(D)) then
	 
         D.Month:= D.Month + 1 ;
         D.Day:= 1;
	 
      elsif (D.Month < 12) and datum.Day = M(Datum.Month) then
         D.Month:= D.Month + 1;
         D.Day := 1;
	 
      elsif (datum.month = 12 and datum.Day = 31)then
         D.Year:= D.Year + 1;
         D.Month:= 1;
         D.Day :=1;
      end if;
      return D;
   end Next_Date;
   
   
   ----------------------------------------------------
   -- Funktion som returnerar föregående dagens datum
   ----------------------------------------------------
   function Previous_date (datum : in Date_type )return Date_Type is 
      type Month is array(1..12) of Integer;
      M: Month:= (31,28,31,30,31,30,31,31,30,31,30,31);
      T: Date_Type;
   begin
      
      T := datum; 
      T.Day:= datum.Day -1; 
      if Is_Day_valid(T) then
	 return T;
	 
      elsif (datum.Month = 3 and  datum.Day = 1 and  Check_Leap(T)) then
         T.Month:= T.Month -1;
         T.Day:= 29;
	 
      elsif (datum.Month /=1) and (datum.Day =  1) then
         T.Month:= (T.Month -1);
         T.Day:= (M(T.month));
	 
      elsif (datum.Month = 1  and datum.Day = 1) then
         T.Year:= (T.Year -1);
         T.Day:= 31;
         T.Month:= 12;
      end if;
      return T;
   end Previous_Date;
   
   
   -----------------------------------------------------
   -- Kontroll om höger och vänster om = är lika
   -- returmerar True/False
   -----------------------------------------------------
   function "<" (left, right : in Date_Type) return Boolean is 
   begin
      if Left.Year < Right.Year then
	 return True;
      elsif 
	Left.Year =  Right.Year and
	Left.Month < Right.Month then
	 return True;
      elsif
	Left.Year =  Right.Year and
	Left.Month = Right.Month and
	Left.Day < Right.Day then
	 return True;
      else 
	 return 
	   False;
      end if;
   end "<";
   
   function ">" (left, right : in Date_Type) return Boolean is 
   begin
      return right < left;
   end ">";
   
   function "=" (Left, Right : in Date_Type) return Boolean is 
   begin
      if
	Left.year  =  Right.Year  and
	Left.month =  Right.month and
	Left.Day   =  Right.Day  then
	 return True; 
      else 
	 return False; 
      end if;
   end "=";   
   
end Date_Package;
