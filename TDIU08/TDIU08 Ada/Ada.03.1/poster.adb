 -- Allsh436: Arbetat enskilt
with Ada.Text_Io, Ada.Integer_Text_IO;  use Ada.Text_Io, Ada.Integer_Text_IO;
with Ada.Integer_Text_IO;               use Ada.Integer_Text_IO;
with Ada.Float_Text_IO;                 use Ada.Float_Text_IO;


procedure Poster is
   
  -- Datastruktur 1
   type Post_Type1 is
      record
	 W: Character;
	 P: String(1..4);
      end record;

  -- Datastruktur 2  
   type Post_Type2_U is
      record
	 S:Float;
	 Z:String(1..4);	 
      end record;
   
   type Post_Type2 is
      record
	 D,U :Post_Type2_U;
      end record;
   
   
  -- Datastruktur 3  
   type Post_Type3_U is
      record
	 Y,Q:Character;
      end record;
   
   type Post_Type3_U2 is
      record 
	 T:Boolean;
	 L:Character;	 
      end record;
   
   type Post_Type3 is
      record
	 J:Post_Type3_U;
	 B:Post_Type3_U;	 
	 O:Post_Type3_U2;	   
      end record;
   
   procedure Get(Item: out Post_Type1) is
      
      C:Character;   
      
   begin 
      
      Get(Item.W);
      Get(C);
      Get(Item.P);
      
   end Get;
   
   
   procedure Put(Item: in Post_Type1) is
      
   begin
      
      Put(Item.W);
      Put(" ");
      Put(Item.P);
      
   end Put;
   
  
   procedure Get(Item: out Post_Type2_U) is
      
      C:Character; 
      
   begin 
      
      Get(Item.S);
      Get(C);
      Get(Item.Z);
      
   end Get;
      
   procedure Get(Item: out Post_Type2) is
      
      C:Character;
      
   begin 
      
      Get(Item.D);
      Get(C);
      Get(Item.U);
      
   end Get;
   
   
   procedure Put(Item: in Post_Type2_U) is
      
   begin
      
      Put(Item.S, Fore=>1 ,Aft=>3, Exp=>0);
      Put(" ");
      Put(Item.Z);
      
   end Put;
   
   
   procedure Put(Item: in Post_Type2) is
      
   begin
      
      Put(Item.D);
      Put(" ");
      Put(Item.U);
            
   end Put;
   
 
   procedure Get(Item : out Post_Type3_U) is
      
      FT, C:Character; 
      
   begin 
      
      Get(Item.Y);
      Get(C);
      Get(Item.Q);
      
   end Get;
   
   
   procedure Get(Item : out Post_Type3_U2) is
      
      FT, C:Character; 
      
   begin 
      
      Get(FT);
      if FT = 'F' then 
	 Item.T := False;
      else
	 Item.T := True;
      end if;
      
      Get(C);
      Get(Item.L);
      
   end Get;
   
   
   procedure Get(Item : out Post_Type3) is
      
      
      FT, C:Character; 
      
   begin 
      
      Get(Item.J);
      Get(C);
      Get(Item.B);
      Get(C);
      Get(Item.O);
      
      
   end Get;
   
   
   procedure Put(Item: in Post_Type3_U) is
      
   begin 
      Put(Item.Y);
      Put(" ");
      Put(Item.Q);
      
   end Put;
   
   procedure Put(Item: in Post_Type3_U2) is
      
   begin 
      
      if not (Item.T) then
	 Put("False");
	 
      elsif  (Item.T) then
	 Put("True");
      end if;
      Put(" ");
      Put(Item.L);
            
   end Put;
   
   procedure Put(Item: in Post_Type3) is
      
   begin 
      Put(Item.J);
      Put(" ");
      Put(Item.B);
      Put(" ");
      Put(Item.O);
     
   end Put;
      
   DS1:Post_Type1;
   DS2:Post_Type2;
   DS3:Post_Type3;
     
begin

   Put_Line("För DS1:");
   Put("Mata in datamängd: ");
   Get(DS1);
   Skip_Line;
   Put("Inmatad datamängd: ");
   Put(DS1);
   
   New_Line(2);
   Put_line("För DS2:");
   Put("Mata in datamängd: ");
   Get(DS2);
   Skip_Line;
   Put("Inmatad datamängd: ");
   Put(DS2);
   
   New_Line(2);
   Put_Line("För DS3:");
   Put("Mata in datamängd: ");
   Get(DS3);
   Skip_Line;
   Put("Inmatad datamängd: ");
   Put(DS3); 
   
end Poster;
