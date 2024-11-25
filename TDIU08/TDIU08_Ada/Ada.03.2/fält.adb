 -- Allsh436: Samarbetat med Saiah135, Said Ali Ahmed, samma program
with Ada.Text_Io, Ada.Integer_Text_IO;  use Ada.Text_Io, Ada.Integer_Text_IO;
with Ada.Integer_Text_IO;               use Ada.Integer_Text_IO;
with Ada.Float_Text_IO;                 use Ada.Float_Text_IO;

procedure Falt is
   
   -- Datastruktur 1
   type DS1_Type is
     array(31..35) of Float;
   
   -- Datatstruktur 2
   type False_Type is 
     array(Character range '5'..'9') of String (1..5);
   
   
   type DS2_Type is 
     array(Boolean) of False_Type;
   
   -- Datastruktur 3
   type DS3_Type is
     array(Character range '4'..'8', 73..74) of Integer;
   
   
   -- Datastruktur 1
   procedure Put(DS1: in DS1_Type) is    
      
   begin 
      
      for I in reverse DS1_Type'range loop
   	 Put(" ");
   	 Put(DS1(I), Fore=>0, Aft=>3, Exp=>0);
      end loop;
      
   end Put;
   
   procedure Get(DS1: out DS1_Type) is
      
   begin
      
      for I in reverse DS1_Type'range loop
   	 Get(DS1(I));
      end loop;
          
   end Get;
   
   -- Datastruktur 2  
   procedure Put(DS2: in DS2_Type) is
      
   begin 
      
      for I in Boolean loop 
   	 for M in reverse False_Type'range loop
   	    Put(" ");
   	    Put(DS2(I)(M));
   	 end loop;
      end loop;
                
   end Put;
   
   procedure Get(DS2: out DS2_Type) is 
      
      C: Character;
           
   begin 
      
      for I in Boolean loop
   	 for M in reverse False_Type'range loop
   	    if not I and M = '9'
   	    then 
   	       Get(DS2(I)(M));
   	    else 
   	       Get(C);
   	       Get(DS2(I)(M));
   	    end if;
   	 end loop;
      end loop;
           
   end Get;
   
   -- Datastruktur 3
   procedure Put(DS3: in DS3_Type) is 
           
   begin
      
      for I in Integer range 73..74 loop
	 for M in DS3_Type'range loop
	    Put(" ");
	    Put(DS3(M,I), Width=>0);
	 end loop;
      end loop;    
      
   end Put; 
   
   procedure Get(DS3: out DS3_Type) is
      
   begin
      
      for I in Integer range 73..74 loop
	 for M in DS3_Type'range loop
	    Get(DS3(M,I));
	 end loop;
      end loop;
           
   end Get;
   
   
   -- Datastruktur 1
   DS1: DS1_Type;
   
   -- Datastruktur 2
   DS2: DS2_Type; 
   
   -- Datstruktur 3
   DS3: DS3_Type;
   
begin
   
   -- Datastruktur 1
   Put_Line("För DS1:");
   Put("Mata in datamängd: ");
   
   Get(DS1);
   Put("Inmatad datamängd:");
   Skip_Line;
   Put(DS1);

   New_Line(2);
   
   
   -- Datastruktur 2
   Put_Line("För DS2:");
   Put("Mata in datamängd: ");
   
   Get(DS2);
   Put("Inmatad datamängd:");
   Skip_Line;

   Put(DS2);
   New_Line(2);
   
   
   -- Datastruktur 3
   Put_Line("För DS3:");
   Put("Mata in datamängd: ");
   
   Get(DS3);
   Put("Inmatad datamängd:");
   Skip_Line;
   
   Put(DS3);
   
end Falt; 
