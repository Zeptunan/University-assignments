-- Allsh436: Arbetat enskilt 
with Ada.Text_IO;         use Ada.Text_IO;
with Ada.Float_Text_IO;   use Ada.Float_Text_IO; 
with Ada.Integer_Text_IO; use Ada.Integer_Text_IO;

procedure Underprogram is
   --------Operator----------
   function "-"(Int : in Integer;
   		Flyt : in Float) return Float is   


   begin

      return Float(Int) - Flyt;
              

                      
   end "-";
   
   
   procedure Substantiv(Str : in out String; 
   		    Truth : out Boolean) is 
      
      
   begin
      
      if Str(Str'Last) = 'S' or Str(Str'Last) = 's' then
   	 Truth:= True;
	 
      elsif Str(Str'Last) /= 'S' or Str(Str'Last) /= 's' then
   	 Str:= (Str(Str'First .. Str'First + 3) & 's');
   	 Truth:= False;
      end if;           
      
   end Substantiv;
   

   
 
   
   function Truth_Or_False(Char : in Character) return Boolean is 
      
      Truth: Boolean;
      
   begin
      if Char = 'S' or Char = 's' then 
	 Truth:= True;
      elsif Char /= 'S' or Char /= 's' then 
	 Truth:= False;
      end if;
      
      return Truth;  
	 
	
      
   end Truth_Or_False; 
      
   Int: Integer;      
   Flyt: Float;
   Truth:        Boolean;
   Str:   String(1 .. 5);
   Char: Character; 
   
begin
   
   Put("Mata in ett heltal och ett flyttal: ");      
   Get(Int);         
   Get(Flyt);
   Flyt:= Int - Flyt;
   Put("Differensen mellan dem är ");              
   Put(Flyt, Aft=>2, Fore=>0, Exp=>0);
   New_Line(2);

   Put("Skriv in ett 5 tecken långt engelskt substantiv: ");
   Get(Str(1 .. 5));
   
   Substantiv(Str, Truth);
   if Truth = True then 
      Put("Ordet ");
      Put(Str(1 .. 5)); 
      Put(" var troligtvis i plural från början"); 
      
   elsif Truth = False then 
      Put("Ordet ");
      Put(Str(1 .. 5)); 
      Put(" var troligtvis inte i plural från början"); 
   end if;
   New_Line(2);
   
   Put("Mata in ett tecken: ");
   Get(Char);
   
   Truth:= Truth_Or_False(Char);
   if Truth = True then
      Put("Tecknet var sant");
   elsif Truth = False then
      Put("Tecknet var inte sant");
   end if;
   
     
   
       
   
   
     end Underprogram;
