package Date_Package is
      
   type Date_Type is private;
   
   
   procedure Get (date : out Date_Type);
   procedure Put (date : in Date_Type);
      
   --Returnerar nästa datum
   function Next_Date (Date : in Date_Type) return Date_type;  
   --Returnerar datumet innan
   function Previous_Date (Date : in Date_Type) return Date_type;    
   
   function "<" (Left, Right : in Date_Type) return Boolean;  
   function ">" (Left, Right : in Date_Type) return Boolean;   
   function "=" (Left, Right : in Date_Type) return Boolean;
   
   
    
   Format_Error : exception;
   Year_Error : exception;
   Month_Error: exception;
   Day_Error : exception;

   
private 
   type Date_Type is record
      Year:Integer;
      Month:Integer;
      Day:Integer;
   end record;
   
end Date_Package;
