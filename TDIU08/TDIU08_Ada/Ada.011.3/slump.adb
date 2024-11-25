-- allsh436: Arbetat enskilt
with Ada.Text_IO;             use Ada.Text_Io;
with Ada.Integer_Text_IO;     use Ada.Integer_Text_Io;
with Ada.Float_Text_Io;       use Ada.Float_Text_Io;
with Ada.Numerics.Discrete_Random;  
with Ada.Numerics.Float_Random;

procedure Slump is
   
   -------------------------------------------------------------------   
   subtype Mitt_Teckenintervall is
     Character range 'a' .. 'z';
   
   package Mitt_Slumptecken is
      new Ada.Numerics.Discrete_Random(Mitt_Teckenintervall);
   --------------------------------------------------------------------   
   
   
   procedure Slumpheltal (Number_Of_Dice, Tarningssort : in Integer) is
      
      subtype Mitt_Teckenintervall is
	Integer range 1 .. Tarningssort;
      
      package Mitt_slumpheltal is
	 new Ada.Numerics.Discrete_Random(Mitt_Teckenintervall);
      
      use Mitt_slumpheltal;
      
      G: Generator;
      Sum : Integer :=0;
      Rand : Integer;
   begin
      -- Reset(G);
      
      Put ("Summa: ");
      for I in 1 .. Number_Of_Dice loop
	 Rand := Integer(Random(G));
	 Sum := Sum + Rand;
      end loop;
      
      Put(Sum, Width => 1);
      
      
   end Slumpheltal;
   --------------------------------------------------------
   procedure Slumptecken (A, B : out Character; G : in Mitt_Slumptecken.Generator) is 
      
      use Mitt_Slumptecken;
      
   begin
      -- Reset(G);
      
      A := Random(G);
      B := Random(G);
      
   end Slumptecken;   
   
   ---------------------------------------------------
   
   procedure Slumpflyt (F: in Ada.Numerics.Float_Random.generator) is
      
      use Ada.Numerics.Float_Random;
      
   begin
      -- Reset(G);   
      Put((Random(F)*100.0),0,2,0);
      
   end Slumpflyt;   
   ----------------------------------------------------  
   
   procedure Crazy_Slumpflyt (X, Y : in Float; F : in Ada.Numerics.Float_Random.generator) is
      use Ada.Numerics.Float_Random;
      Rand: Float;
   begin
      --Reset(F);
      Rand:= Random(F) * (Y-X) + X;
      Put(Rand,0,2,0);
      
   end Crazy_Slumpflyt;

   ---------------------------------------------------

   procedure Swap (Tecken_1, Tecken_2 : in out Character) is
      
      Tecken : Character;
   begin
      
      Tecken := Tecken_1;
      Tecken_1 := Tecken_2;
      Tecken_2 := Tecken;
      
      
   end Swap;
   -------------------------------------------------------
   procedure Teckenloop (A, B : in Character) is
      
   begin
      
      for I in Character range A..B loop

	 Put(" ");
	 Put(I);
	 
      end loop;
      
   end Teckenloop;
   -------------------------------------------------------   
   
   Number_Of_Dice : Integer;
   Tarningssort : Integer := 6;
   Slumptecken_1, Slumptecken_2 : Character;
   X : Float;
   Y : Float;

   GenF : Ada.Numerics.Float_Random.generator;
   GenT : Mitt_Slumptecken.Generator;
   
begin
   
   Put_Line("DEL 1:");
   Put("Mata in antal 6-sidiga tärningar: ");
   
   Get(Number_Of_Dice);
   Skip_Line;
   Slumpheltal(Number_Of_Dice, tarningssort);  --slumpa antal tärningar med tarningssort
   New_Line;
   
   Put_line("Nu slumpas ett tal mellan 0.0 och 100.0.");
   Put("Slumpat flyttal: ");
   Slumpflyt(GenF); --slumpning av flyttal mellan 0 och 100
   New_Line(2);
   
   Put_Line("DEL 2:");
   Put_Line("Nu slumpas två tecken mellan a och z.");
   Put("Slumpade tecken: ");
   Slumptecken(Slumptecken_1, Slumptecken_2, GenT);
   
   --  while Slumptecken_1 = Slumptecken_2 loop  --se till att tecknen inte är samma 
   --     Slumptecken(Slumptecken_1,Slumptecken_2, GenT);
   --end loop;
   
   if Slumptecken_1 > Slumptecken_2 then  --byta plats på tecknen så störst är först.
      Swap(Slumptecken_1,Slumptecken_2);
   end if;
   
   Put(Slumptecken_1);
   Put(" ");
   Put(Slumptecken_2);
   
   New_Line;
   Put("Alla tecken mellan ");
   Put(Slumptecken_1);
   Put(" och ");
   Put(Slumptecken_2);
   Put(":");
   
   Teckenloop(Slumptecken_1,Slumptecken_2);
   New_Line(2);
   
   Put_Line("DEL 3:");
   Put("Mata in tärningssort: ");
   Get(Tarningssort);
   Put("Mata in antal tärningar: ");
   Get(Number_Of_Dice);
   
   Slumpheltal(Number_Of_Dice, Tarningssort);  
   New_Line;
   
   Put("Mata in x: ");
   Get(X);
   Put("Mata in y: ");
   Get(Y);
   Put("Slumpat flyttal: ");
   Crazy_Slumpflyt(X,Y,GenF);

end Slump;
