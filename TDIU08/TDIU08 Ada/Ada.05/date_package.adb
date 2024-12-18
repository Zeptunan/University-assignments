-- allsh436: Arbetat enskilt
with Ada.Text_IO;		  use Ada.Text_IO;
with Ada.Integer_Text_IO;         use Ada.Integer_Text_IO;

package body Date_Package is
   
   Length_Error: exception; -- Undantag för mellanslag
   
   ---------------------------------------------
   -- Funktion för skottårs kontroll
   ---------------------------------------------  
   function Check_Leap (Date: in Date_type) return Boolean is
   begin
      
      if ((Date.Year mod 4 = 0 and 
	     Date.Year mod 100 > 0) or 
	    (Date.Year mod 400 = 0)) then 
         return true;
      end if;
      
      return false;
      
   end Check_Leap;
   
   
   ---------------------------------------------------------
   -- Kontrollerar om dagen är gilltig 
   ---------------------------------------------------------
   function  Check_Day(Date: in Date_type) return Boolean is
      
      type Month_type is array(1..12) of Integer;
      Month: Month_Type:= (31,29,31,30,31,30,31,31,30,31,30,31); 
      
   begin  
      
      if Date.Day <= Month(Date.Month) and Date.Day > 0 then 
	 return true;
      end if;
      
      return false;
      
   end Check_Day;
   
   
   ----------------------------------------------
   -- Procedur för format kontroll
   ----------------------------------------------
   procedure Check_Format(Item: in String) is
   begin 
      
      for I in Item'First..Item'Last loop 
	 if I /= 5 and  I /=8 then 
	    if Item(I) not in '0'..'9' then  
	       raise Format_Error; 
	    end if;
	 else
	    if Item(I) /= '-' then   
	       raise Format_Error;
	    end if;
	 end if;
      end loop;
      
   end Check_Format;
   
   
   ------------------------------------------------------
   -- Procedur för format kontroll av datum samt format
   ------------------------------------------------------  
   procedure Check_Date(Date: in Date_Type) is
   begin 
      
      if Date.Year < 1532 or Date.Year > 9000 then 
	 raise Year_Error;
      elsif Date.Month < 1 or Date.Month > 12 then
	 raise Month_Error;
      elsif not Check_Leap(Date) and Date.Day = 29 then 
	 raise Day_Error; 
      elsif not Check_Day(Date) and not Check_Leap(Date) then 
	 raise Day_Error;
      elsif not Check_Day(Date) then 
	 raise Day_Error;
      end if; 
      
   end Check_Date;
   
   
   ------------------------------------------------------
   -- Get för mellanrum innan inmatning av datum 
   ------------------------------------------------------ 
   Procedure  Get(Date: out Date_type) is
      
      S: String(1..10);
      
   begin
      
      loop 
	 Get(S(S'first));
	 if S(S'First) /= ' ' then  
	    for  I in S'First+1 .. S'last loop
	       Get(S(I));
	    end loop;
	    exit;
	 end if;
      end loop;
      
      Check_format(S);
      Date.Year   := Integer'Value(S(1..4));
      Date.Month  := Integer'Value(S(6..7)); 
      Date.Day    := Integer'Value(S(9..10)); 
      Check_Date(Date); 
      
   end Get;
   
   
   ------------------------------------------------------
   -- Procedure put för datum
   ------------------------------------------------------
   procedure Zero(Item: in Integer) is
   begin
      
      Put("-");
      if Item < 10 then
	 Put("0");
      end if;
      Put(Item, Width=>0);
      
   end Zero;
   
   procedure Put (Date: in Date_Type) is
   begin
      
      Put(date.Year, Width=>0);
      Zero(Date.Month);
      Zero(Date.Day);
      
   end Put;
   
   
   -----------------------------------------------------
   -- Funktion som returnerar nästa dags datum
   -----------------------------------------------------
   function Next_Date (Date: in Date_type)return Date_Type is
      type Month is array(1..12) of Integer;
      
      M: Month:= (31,29,31,30,31,30,31,31,30,31,30,31);
      D: Date_Type; 
      
   begin
      
      D:= Date;
      D.Day:= Date.Day +1;
      
      if Date.Month = 2 
	and Check_Leap(D) then 
	    if Date.Day = 28 then
	       D.Day:= 29;
	    elsif Date.Day = 29 then
	       D.Month:= D.Month + 1;
	       D.Day:= 1;
	    end if;
      elsif Date.Month < 12 
	and Date.Day = M(Date.Month) then
	    D.Month:= D.Month + 1;
	    D.Day:= 1;
      elsif Date.Month = 12 
	and Date.Day = 31 then
	    D.Year:= D.Year + 1;
	    D.Month:= 1;
	    D.Day:= 1;
      end if;
      
      
      return D;
      
   end Next_Date;
   
   
   ----------------------------------------------------
   -- Funktion som returnerar föregående dagens datum
   ----------------------------------------------------
   function Previous_date (Date: in Date_type)return Date_Type is
      type Month is array(1..12) of Integer;
      
      M: Month:= (31,28,31,30,31,30,31,31,30,31,30,31);
      D: Date_Type;
      
   begin
      
      D:= Date;
      D.Day:= Date.Day - 1;     
            
      if Check_Day(D) then
      	 return D; 
      elsif (Date.Month = 3 and D.Day < 1 and Check_Leap(D)) then
      	 D.Month:= D.Month - 1;
      	 D.Day:= 29;  
      elsif (Date.Month /=1) and (D.Day < 1) then
      	 D.Month:= (D.Month) - 1;
      	 D.Day:= M(D.Month) ;    
      elsif (Date.Month = 1  and  Date.Day = 1) then   
      	 D.Year:= (D.Year - 1);
      	 D.Day:= 31;
      	 D.Month:= 12;
      end if;
      
      return D;
      
   end Previous_Date;
   
   
   -----------------------------------------------------
   -- Kontroll om höger och vänster om = är lika
   -- returmerar True/False
   -----------------------------------------------------
   function "<" (Left, Right: in Date_Type) return Boolean is
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
	 return False;
      end if;
      
   end "<";  
   
   function ">" (Left, Right: in Date_Type) return Boolean is
   begin
      
      return right < left;
      
   end ">";
   
   function "="(Left, Right: in Date_Type) return Boolean is
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
