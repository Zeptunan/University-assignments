package Sorted_List is
   
   No_Such_Element_Error : exception;
   
   type List_Type is private;
   
   function Empty (List : in List_Type)return Boolean;
   
   procedure Insert (List : in out List_Type; I : in Integer);
   
   procedure Put(List : in List_type);
   
   function Member(List : in List_Type; Key : in integer) return Boolean;
   
   procedure Remove(List : in out List_Type; Key : in integer);
   
   procedure Delete(List : in out List_type);
   
   function Length(List : in List_type) return integer;  
   
private
   
   type Ptr;
   
   type List_Type is
     access Ptr;
   
   type Ptr is
      record
	 Data : Integer;
	 next : List_type;
      end record;
   
end Sorted_list;
