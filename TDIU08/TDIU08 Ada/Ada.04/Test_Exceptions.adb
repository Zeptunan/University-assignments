-- Allsh436: Samarbetat med Saiah135, Said Ali Ahmed, samma program
with Ada.Text_IO;         use Ada.Text_IO;
with Ada.Integer_Text_IO; use Ada.Integer_Text_IO;
with Ada.Float_Text_IO;   use Ada.Float_Text_IO;

procedure Test_Exceptions is
   
   Length_Error, Format_Error, Year_Error, Month_Error, Day_Error :exception;
   
   type Date_Type is
      record 
	 Year, Month, Day: Integer;
      end record; 
   
   type Date_Arr_Type is
     array(1 .. 5) of Date_Type;
   
   
   -- Deluppgift 1
   procedure Get_Value_Safe(Min, Max: in Integer;			    
   			    Value: out Integer) is 
      
   begin 
      loop
   	 begin 
   	    Put("Mata in värde ");
   	    Put("(");
   	    Put(Min, Width=>0);
   	    Put(" - ");
   	    Put(Max,Width=>0);
   	    Put("): ");
   	    Get(value);
   	    if Value > Max then 
   	       Put("För stort värde. ");
   	    elsif Value < Min then
   	       Put("För litet värde. ");
   	    else
   	       exit;
   	    end if;
   	 exception
   	    when Data_Error =>
   	       Put("Fel datatyp. ");
   	       Skip_Line;	    
   	 end;	 
      end loop;
      
   end Get_Value_Safe;
   
   procedure Del1 is 
         Min, Max,Value :Integer;
   begin
      loop
   	 begin 
   	    Put_Line("Del 1:");
   	    Put("Mata in Min och Max: ");
   	    Get(Min);
   	    Get(Max);
   	    Skip_Line;
   	    Get_Value_Safe(Min, Max, Value);
   	    Put("Du matade in heltalet ");
   	    Put(Value, Width => 0);
   	    Put('.');
   	    New_Line(2);
   	    exit;
   	 end;
      end loop;
   end Del1;
      
   --Deluppgift 2
   procedure Get(Item: out String) is  
   begin
      loop 
   	 Get(Item(Item'first));
   	 if Item(Item'First) /= ' ' then
	    
   	    for I in Item'First+1 .. Item'last loop
   	       if End_Of_Line then
   		  raise Length_Error;
   	       end if;
	       
   	       Get(Item(I));
   	    end loop;
   	    exit;
   	 end if;
      end loop;
   end Get;
   
   procedure Del2 is   
      
      S_1 : String(1 .. 5);
      S_2 : String(2 .. 7);
      S_3 : String(1 .. 10); 
      
   begin    
      Put_Line("Del 2:");
      Put("Mata in en sträng på exakt 5 tecken: ");
      Get(S_1);
      Skip_Line;
      Put_Line("Du matade in " & S_1);
      Put("Mata in en sträng på exakt 6 tecken: ");
      Get(S_2);
      Skip_Line;
      Put_Line("Du matade in " & S_2);
      Put("Mata in en sträng på exakt 10 tecken: ");
      Get(S_3);
      Skip_Line;
      Put("Du matade in " & S_3);
      New_Line(2);  
   end Del2; 
   
   -- Deluppgift 3 
   procedure Format_Controll(S : in String) is
   begin
      
      for I in S'Range loop  
   	 if I /= 5 and  I /=8 then -- om inte är bindsträck kolla resten  
   	    if S(I) not in '0'..'9' then  
   	       raise Format_Error; 
   	    end if;
   	 else
   	    if S(I) /= '-' then   --kollar om 5 och 8 är bindsträck
   	       raise Format_Error;
   	    end if;
   	 end if;
      end loop;
   end Format_Controll;
   
   procedure Month_Controll (Month : in Integer) is
   begin
      if Month < 1 or Month >12 then
      	 raise Month_Error;
      end if; 
      
   end Month_Controll;
   
   procedure Year_Controll (Year :in Integer ) is
   begin
      
      if Year < 1532 or Year > 9000 then
	 raise Year_Error; 
      end if;
   end Year_Controll;
   
   function Cen_Controll(Item: in Date_Type) return Boolean is
   begin
      if Item.Year rem 100 /= 0 then
	 return False;
      elsif Item.Year rem 400 = 0 then	 
	 return False;
      end if;
      return True;
      
   end Cen_Controll;
   
   function  Leap_Controll (Item : in Date_Type) return Boolean is    
   begin
      if(Item.Day =29 and (( Item.Year rem 4) /=0) and Item.Month=2) then
	 
	 return False; 	 
      end if;
      
      if (Cen_Controll(Item)) and Item.Month=2 and Item.Day=29 then
	 return False;
      end if;
      if Item.Day = 30 and Item.Month =2 then
	 return False;
      end if ;
      
      return True;
      
   end Leap_Controll;
   
   procedure Day_Controll(Item: in Date_Type)is
   begin 
      
      if (Item.Day<1) or ( Item.Day>31) then
	 raise Day_Error;
      end if;
      
      if Item.Day = 31 then 
	 if
	   Item.Month=2 or Item.Month=4 or Item.Month=6 or Item.Month=9 or Item.Month=11 then
	    raise Day_Error;
	 end if;
      end if;
	 
	 if (not Leap_Controll(Item)) then	
	    raise Day_Error;
	 end if;	 
   end Day_Controll;
   
   procedure Date_Controll(Item: in Date_Type) is
      
   begin
      
      Year_Controll(Item.Year);
      Month_Controll(Item.Month);
      Day_Controll(Item);
      
   end Date_Controll;
   
   procedure Get(Item: out Date_Type)is
      S:String(1..10);       
   begin  
      begin 
	 Get(S);
	 Format_Controll(S);
	 
	 Item.Year   := Integer'Value(S(1..4));
	 Item.Month  := Integer'Value(S(6..7)); 
	 Item.Day    := Integer'Value(S(9..10)); 
	 Date_Controll(Item);
      exception
	 when Length_Error=>
	    raise Format_Error;
      end;
      
   end Get;
   
   procedure Put (Item: in Date_Type) is
   begin
      Put(Item.Year, Width => 0);
      Put("-");
      
      if Item.Month < 10 then
	 Put("0");
      end if;
      
      Put(Item.Month, Width => 0);
      Put("-");
      
      if Item.Day < 10 then
	 Put("0");
      end if;
      
      Put(Item.Day, Width => 0);
   end Put;
   
   procedure Del3 is
      Dates : Date_Arr_Type;
   begin 
      Put_Line("Del 3:");
      for I in Dates'range loop
	 loop
	    begin
	       Put("Mata in datum ");
	       Put(I, Width => 0);
	       Put(": ");
	       Get(Dates(I));
	       exit;
	    exception 
	       when Format_error => 
		  Put("Felaktigt format! ");
	       when year_error => 
		  Put("Felaktigt år! ");
	       when month_error => 
		  Put("Felaktig månad! ");
	       when day_error => 
		  Put("Felaktig dag! ");
   	    end;
	 end loop;
      end loop;  
      for I in Dates'range loop
	 Put("Datum nummer ");
	 Put(I, Width => 0);
	 Put(": ");
	 Put(Dates(I));
	 New_Line;
      end loop;
   end Del3;
   
   
begin
   
   Del1;
   Del2;
   Del3;
exception
   when 
     Length_Error =>
      Put("För få inmatade tecken!");

   
   
end Test_Exceptions;
