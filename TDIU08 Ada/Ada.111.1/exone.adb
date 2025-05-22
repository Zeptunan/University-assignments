-- Allsh436:
with Ada.Text_IO;         use Ada.Text_IO;
with Ada.Float_Text_IO;   use Ada.Float_Text_IO; 
with Ada.Integer_Text_IO; use Ada.Integer_Text_IO;
with Ada.Numerics.Elementary_Functions; use Ada.Numerics.Elementary_Functions;
with Ada.Numerics;                      use Ada.Numerics;

procedure Exone is
    
   -- Deluppgift 1   
   function Area_Av_Triangel(S : in Float) return Float is 
   

   
   begin  
    
      return S * (S * sqrt(3.0) / 2.0) / 2.0; 
      
   end Area_Av_Triangel;
   
   
   
   -- Deluppgift 2
   procedure Kvoten_Av(Flyt: out Float;					     
   		       Str: in out String;
   		       Kvot: out Integer) is   
     
   begin
      
      Put("Mata in ett flyttal: ");
      Get(Flyt);     
      Put("Mata in en sträng med exakt 3 tecken: ");
      Get(Str); 
      Kvot:= Integer(Float'Ceiling(Flyt / Float'Value(Str)));
        
   end Kvoten_Av;
   
   
   
   -- Deluppgift 3   
   function "/"(Char: in Character; 
   		Int: in Integer) return Float is 
            
   begin
      
      return Float(Character'Pos(Char)-48) / Float(Int);     				             
      
   end "/";
   
         
       S:           Float; 
    Kvot:         Integer;
    Flyt:           Float;
     Str:  String(1 .. 3);
    Char:       Character; 
     Int:         Integer; 
              
begin
   -- Deluppgift 1
   Put("Mata in längden: ");
   Get(S);
   Put("Den beräknade arean blev: ");
   Put(Area_Av_Triangel(S), Fore=>0, Aft=> 1, Exp=>0);
   New_Line(2);
   
 
   -- Deluppgift 2
   Kvoten_Av(Flyt, Str, Kvot);
   Put("Du matade in flyttalet: ");
   Put(Flyt, Fore=>0, Aft=>1, Exp=>0);   
   Put(" och strängen: ");
   Put(Str);
   Put(" och kvoten blev ");
   Put(Kvot);
   New_Line(2);
   
   
   -- Deluppgift 3
   Put("Mata in ett tecken: ");
   Get(Char);
   Put("Mata in ett heltal: ");
   Get(Int); 
   Put("Den beräknade kvoten mellan ");
   Put(Int, Width=>0);
   Put(" och "); 
   Put(Char);
   Put(" blir ");
   Put((Char/Int), Fore=>0, Aft=>1, Exp=>0);
   

   
end Exone;
