-- Allsh436: Samarbetat med Saiah135, Said Ali Ahemd, samma program
with Ada.Text_IO;           use Ada.Text_IO;
with Ada.Integer_Text_IO;   use Ada.Integer_Text_IO;

procedure Ada06 is
   
   function Fib (N : in Integer) return Positive is
      
   begin
      if N=1 or N=2 then
	 return 1;
      else 
	 return Fib(N-1) + Fib(N-2);
      end if;
   end Fib;
   
   
   function Leca (I : in Integer) return Integer is
      
   begin
      if I=1 then
	 return 0;
      elsif I=2 then 
	 return 1;
      else
	 return ((I*2)-3)*(I-1)+Leca(I-1);
	 
      end if;
      
   end Leca;
   
   
   
   X, Y : Integer;
   
begin
   
   Put("Mata in N och HH: ");
   Get(X);
   Get(Y);
   
   Put("Fibonacci-tal nummer ");
   Put(X, Width=>0);
   Put(" är ");
   Put(Fib(X), Width=>0);
   Put(".");
   New_Line;
   Put("Det behövs ");
   Put(Leca(Y), Width=>0);
   Put(" stenar för att bygga trappan.");
   
end Ada06;
