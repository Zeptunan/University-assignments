-- allsh436: Arbetat enskilt 

with Ada.Text_IO, Ada.Integer_Text_IO;  use Ada.Text_IO, Ada.Integer_Text_IO;
with Ada.Integer_Text_IO;               use Ada.Integer_Text_IO;
with Ada.Float_Text_IO;                 use Ada.Float_Text_IO;
with Ada.Numerics.Elementary_Functions; use Ada.Numerics.Elementary_Functions;
with Ada.Numerics;                      use Ada.Numerics;

procedure io4 is
   
  
   
   
   --Menu_selection:
   
   procedure Menu_Selection(Selection : out Integer) is
       
   begin
                  

      Put_Line("=== HUVUDMENY ===");      
      Put_Line("1. Beräkna hypotenusa");            
      Put_Line("2. Beräkna triangelvinklar");            
      Put_Line("3. Beräkna N-fakultet");            
      Put_Line("4. Avsluta programmet");
 
      loop
	 
	 Put("Val: ");
	 Get(Selection);	 	
	 
	 if(Selection > 0) and (Selection < 5) then 
	    exit;
	 end if;
	 
	 Put_Line("Felaktigt val!");
	 	  
      end loop;
      
             	    	      
   end Menu_Selection;     
   
   
      --Calculate_Hypothenuse:
   
   function Calculate_Hypothenuse(A, B : in Integer) return Float is  
      
      Hypothenuse: Float;
      
   begin
      
      Hypothenuse:= Sqrt(Float(A**2 + B**2));
      return Hypothenuse;
      
   end Calculate_Hypothenuse;
   
   
   
   --Hypothenuse_Program:
   
   procedure Hypothenuse_Program is
      
      A, B: Integer;
      Hypothenuse: Float;
      
   begin
      
      Put("Mata in kateternas längder: ");
      Get(A);
      Get(B);
      
      Hypothenuse:= Calculate_Hypothenuse(A,B);
      
      Put("Hypotenusan är ");
      Put(Hypothenuse, Fore=>0, Aft=>2, Exp=>0);
      
   end Hypothenuse_Program;
   
    
   
   --Calculate_Angles:
   
   procedure Calculate_Angles(Hc, Sa: in Float; 
			      Va, Vb, Vc: out Float) is
	 
   begin
	 
	 Va:= Arcsin(Sa/Hc)*(180.0/Pi); 
	 Vb:= Arccos(Sa/Hc)*(180.0/Pi);
	 Vc:= 180.0-Va-Vb;
	   

	 	 
   end Calculate_Angles;   
     
                              
   
   
   --Angle_Program:
   
   Procedure Angle_Program is
      Va: Float;
      Vb: Float;
      Vc: Float;
      Hc: Float;
      Sa: Float;

   begin
      
      Put("Mata in hypotenusans längd: ");
      Get(Hc);
      
      Put("Mata in vertikala katetens längd: ");
      Get(Sa);
      
      Calculate_Angles(Hc, Sa, Va, Vb, Vc);
      
      Put("Va: ");
      Put(Va, Fore=>0, Aft=>1, Exp=>0);
      Put_Line(" grader");
      
      Put("Vb: ");
      Put(Vb, Fore=>0, Aft=>1, Exp=>0);
      Put_Line(" grader");
      
      Put("Vc: ");
      Put(Vc, Fore=>0, Aft=>1, Exp=>0);
      Put(" grader");
      
      
      
   end Angle_Program;
       
   
   
   --Calculate Factorial
   
   function Calculate_Factorial(N: in Integer) return Integer is
      
      Result: Integer;
      
   begin
      
      Result := N;
      for I in 1 .. (N-1) loop
	 Result:= Result * I;
      end loop;
      
      if Result < 1 then Result := 1;
      end if;
	 
      return Result;
      
      
   end Calculate_Factorial;  
   
   --Factorial Program:
   procedure Factorial_Program is
      
      N: Integer;
      Result: Integer; 
      
   begin

      Put("Mata in N: ");
      Get(N);
      
      Result:= Calculate_Factorial(N);
      
      Put(N, Width => 0);
      Put("-fakultet = ");
      Put(Result, Width => 0);
      
   end Factorial_Program;
       
     	 	 	 	 	 	                
   Selection:  Integer;
   
begin
   
   Put("Välkommen till miniräknaren!");
   New_Line;
   
   loop
      Menu_Selection(Selection);
      if Selection = 1 then 
	 Hypothenuse_Program;
      elsif Selection = 2 then 
	 Angle_Program;
      elsif Selection = 3 then 
	 Factorial_Program;
      elsif Selection = 4 then 
	 Put("Ha en bra dag!"); 
	 exit;
      end if;
      New_Line(2);
      
   end loop;
             
   
end Io4;


	 



  
