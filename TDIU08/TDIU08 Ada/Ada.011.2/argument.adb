-- allsh436: Arbetat enskilt
with Ada.Text_IO; use Ada.Text_IO;
with Ada.Integer_Text_IO; use Ada.Integer_Text_IO;
with Ada.Float_Text_IO; use Ada.Float_Text_IO;
with Ada.Command_Line; use Ada.Command_Line;

procedure Argument is
   
begin 
   
   if  Argument_count = 0 then
      Put("Inga argument angivna."); 
   elsif   Argument_count /= 2 then 
      Put("Fel antal argument angivna.");
   else
      Put("Meddelande: ");
      for I in 1..Integer'Value(Argument(1)) loop
	 Put(Argument(2));
      end loop;
      New_Line;
      Put("Programmet ");
      Put('"');
      Put(Command_Name);
      Put(""" ");
      Put("avslutas.");
   end if;
   
end Argument; 
