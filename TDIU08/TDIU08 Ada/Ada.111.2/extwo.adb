 -- Allsh436: Arbetat enskilt
with Ada.Text_IO;                       use Ada.Text_IO;
with Ada.Float_Text_IO;                 use Ada.Float_Text_IO; 
with Ada.Integer_Text_IO;               use Ada.Integer_Text_IO;
with Ada.Numerics.Elementary_Functions; use Ada.Numerics.Elementary_Functions;
with Ada.Numerics;                      use Ada.Numerics;

procedure extwo is 
   
   -- Deluppgift 1
   procedure Kvoten_Av(Flyt: in Float;					     
   		       Str: in String;
   		       Kvot: out Integer) is 
      
      F: Float := Float'Value(Str);  
     
   begin
     
      Kvot:= Integer(Float'Value(Str) / Float'Rounding(Flyt)-0.25); 
      
   end Kvoten_Av;
   
   
   
   -- Deluppgift 2
   function Medelvarde(Flyt1: in Float; 
   		       Flyt2: in Float;
   		       Flyt3: in Float) return Integer is
      
      Medel: Integer;
      
   begin
      
      Medel:= (Integer(Flyt1+Flyt2+Flyt3)/3)-1;
      return Medel;
      
   end Medelvarde;
   
   
   
   -- Deluppgift 3
   function  "-"(Char: in Character;
		 Strang: in String) return Float is
      
      F: Float := Float'Value(Strang);
      
   begin
      
      return Float(Character'Pos(Char)-48) - Float'Value(Strang);
                     
   end "-";
   
   -- Deluppgift 1		     
   Flyt: Float; 		     
   Str: String(1 .. 3);	 
   Kvot: Integer;
   
   -- Deluppgift 2
   Flyt1: Float;
   Flyt2: Float; 
   Flyt3: Float;
   Medel: Integer;
   
   --  Deluppgift 3
   Differensen: Float;
   Char: Character;
   Strang: String(1..3);
		     
begin
   
   -- Deluppgift 1
   Put("Mata in en sträng: ");
   Get(Str);
   
   Put("Mata in ett flyttal: ");
   Get(Flyt);
   
   Kvoten_Av(Flyt, Str, Kvot);
   
   Put("Den beräknade Kvoten mellan ");
   Put(Str);
   Put(" och ");
   Put(Flyt, Fore=>0, Aft=>1, Exp=>0);
   Put(" blir ");
   Put(Kvot, Width=>0);
   New_Line(2);
   
   
   -- Deluppgift 2
   Put("Mata in tre flyttal: ");
   Get(Flyt1);
   Get(Flyt2);
   Get(Flyt3);
   
   Medel := Medelvarde(Flyt1, Flyt2, Flyt3);
   
   Put("Medelvärdet av dessa är: ");
   Put(Medel, Width=>0);
   New_Line(2);
   
   
   -- Deluppgift 3
   Put("Mata in ett tecken: ");
   Get(Char);
      
   Put("Mata in en sträng med exakt 3 tecken: ");
   Get(Strang);
   
   Differensen:= Char-Strang;
 
   Put("Du matade in tecknet: ");
   Put(Char);
   Put(" och strängen: ");
   Put(Strang);
   Put(" och differensen blev ");
   Put(Differensen, Fore=> 0);
   
end extwo; 
