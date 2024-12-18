package Date_Package is
   
   type Date_Type is private;
   
   procedure Get (datum : out Date_Type);
   procedure Put (datum : in Date_Type);
   
   --Returnerar nästa datum
   function Next_Date (datum : in Date_Type) return Date_Type;
   --Returnerar datumet innan
   function Previous_Date (datum : in Date_Type) return Date_Type;

   function ">" (Left, Right : in Date_Type) return Boolean;
   function "<" (Left, Right : in Date_Type) return Boolean;
   function "=" (Left, Right : in Date_Type) return Boolean;

   Format_Error : exception;
   Year_Error   : exception;
   Month_Error  : exception;
   Day_Error    : exception;
   
private
   type Date_Type is record
      Year, Month, Day : Integer;
   end record;
   
end Date_Package;
