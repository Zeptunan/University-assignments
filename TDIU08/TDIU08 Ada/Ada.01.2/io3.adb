--allsh436 Allan Shamseddin

with Ada.Float_Text_IO; use Ada.Float_Text_IO;
with Ada.Text_IO;       use Ada.Text_IO;
with Ada.Integer_Text_IO;    use Ada.Integer_Text_IO;

procedure io3 is 
   Fm: Float; -- momsprocent
   Fp: Float; -- första 
   Sp: Float; -- sista pris
   S: Float; -- steg
   Steps: Integer; 
   P: Float;
begin
   loop 
   Put("Första pris: ");
   Get(Fp);
     if(Fp >  0.0) then exit; 
     end if;
     Put("Felaktigt värde!");
     New_Line;
   end loop;  
   
   loop
   Put("Sista pris: ");
   Get(Sp);
     if(Sp >= Fp) then exit;
     end if;
     Put("Felaktigt värde!");
     New_Line;
   end loop;
   
   loop
   Put("Steg: ");
   Get(S);
    if(S > 0.0) then exit;
    end if;
    Put("Felaktigt värde!");
    New_Line;
   end loop;
   
   loop
      Put("Momsprocent: ");
      Get(Fm);
      if(Fm >= 0.0) and(Fm <= 100.0) then exit;
      end if;
      Put("Felaktigt värde!");
      New_Line;
      
   end loop;
   
   New_Line;      
   Put("============ Momstabell ============");
   New_Line;
   Put("Pris utan moms  Moms   Pris med moms");
   New_Line; 
   
   Steps:= Integer(-0.5+(Sp-Fp)/S);
   if Steps < 0 then Steps:= 0;
   end if;
     
   for I in 0..Steps loop
      P:= Fp+S*Float(I);
      Put(P, Fore=>6, Aft=>2, Exp=>0);
      Put((P*Fm/100.0), fore => 8, aft=>2, exp=>0);
      Put(P*(Fm/100.0)+P, fore => 9, Aft => 2, Exp => 0);
      New_Line;          
	  
   end loop;
   

      
    
   
end Io3;
