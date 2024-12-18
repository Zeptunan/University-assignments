--Allan Shamseddin (allsh436), Axel Axelsson (axeax512)

with ada.Text_IO;               use Ada.Text_IO; 
with Ada.Integer_Text_IO;       use Ada.Integer_Text_IO;
with Ada.Float_Text_IO;         use Ada.Float_Text_IO;


procedure Inochutmatning is
   I: Integer; 
   C: Character;
   F: Float;
   S: String(1..5);
   
begin
   Put("Skriv in ett heltal: ");
   Get(I);
   Put("Du skrev in talet: ");
   Put(I,Width=>0); 
   New_Line;
   New_Line;
   Skip_Line;
   
   Put("Skriv in fem heltal: ");
   Get(I);
   Put("Du skrev in talen: ");
   Put(I,Width=>0);
   Put(" ");
   Get(I);
   Put(I,Width=>0);
   Put(" ");
   Get(I);
   Put(I,Width=>0);
   Put(" ");
   Get(I);
   Put(I,Width=>0);
   Put(" ");
   Get(I);
   Put(I,Width=>0);
   New_Line;
   New_Line;
   Skip_Line;
   
   Put("Skriv in ett flyttal: ");
   Get(F);
   Put("Du skrev in flyttalet: ");
   Put(F,0,3,0);
   New_Line;
   New_Line;
   Skip_Line;
   
   Put("Skriv in ett heltal och ett flyttal: ");
   Get(I);
   Get(F);
   Put("Du skrev in heltalet: ");
   Put(I,Width=>9);
   New_Line;
   Put("Du skrev in flyttalet:");
   Put(F,Fore=>4,Aft=>4,Exp=>0);
   New_Line;
   New_Line;
   Skip_Line;
   
   Put("Skriv in ett tecken: ");
   Get(C);
   Put("Du skrev in tecknet: ");
   Put(C);
   New_Line;
   New_Line;
   Skip_Line;
   
   Put("Skriv in en sträng med 5 tecken: ");
   Get(S);
   Put("Du skrev in strängen: ");
   Put(S);
   Skip_Line;
   New_Line;
   New_Line;
   
   Put("Skriv in en sträng med 3 tecken: ");
   Get(S(1..3));
   Put("Du skrev in strängen: ");
   Put(S(1..3));
   Skip_Line; 
   New_Line;
   New_Line;
   
   Put("Skriv in ett heltal och en sträng med 5 tecken: ");
   Get(I);
   Get(C);
   Get(S);
   Put("Du skrev in talet |"); 
   Put(I,Width=>0);
   Put("| och strängen |");   
   Put(S);  
   Put("|.");
   New_Line;
   New_Line;
   Skip_Line;
   
   Put("Skriv in en sträng med 3 tecken och ett flyttal: ");
   Get(S(1..3));
   Get(F);
   Put("Du skrev in """);
   Put(F,fore=>2,Aft=>3,Exp=>0);
   Put(""" och """);
   Put(S(1..3));
   Put(""".");
   New_Line;
   New_Line;
   
   Skip_Line;
   Put("Skriv in en sträng som är maximalt 5 tecken: ");
   Get_Line(S,I);
   Put("Du skrev in strängen: ");
   Put(S(1..I));
   if I=5 then 
      Skip_Line;
   end if;
   New_Line;
   New_Line;
   
   Put("Skriv in en sträng som är maximalt 5 tecken: ");
   Get_Line(S,I);
   Put("Du skrev in strängen: ");
   Put(S(1..I));
   
end Inochutmatning;
