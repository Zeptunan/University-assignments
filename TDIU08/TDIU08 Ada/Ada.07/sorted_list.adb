with Ada.Text_IO;		  use Ada.Text_IO;
with Ada.Integer_Text_IO;         use Ada.Integer_Text_IO;
with Ada.Unchecked_Deallocation;

package body Sorted_List is
   procedure Free is new Ada.Unchecked_Deallocation(Ptr, List_Type);
   
   function Empty(List : in List_Type)return Boolean is
   begin
      
      return  (List = null); -- returnerar värdet beroende på om listan är tom eller ej
      
   end Empty;
   
   procedure Insert (List : in out List_Type; 
		     I : in Integer) is
      
      Temp : List_Type;   
   begin
      if Empty(List) then
	 List := new Ptr; 
	 List.Data := I;
	 List.Next := null;
	 
      elsif I < List.Data then
	 Temp := List;
	 List := new Ptr;
	 List.Data:=I;
	 List.next := Temp;
	 
      elsif I = List.Data then
      	 return; 
	 
      else
	 Insert(List.next, I);
      end if;
      
   end Insert;
   
   procedure Put(List: in List_type) is
   begin
      if Empty(List) then  
	 null;
      else
	 Put(" ");
	 Put(List.Data, Width => 0);
         
         Put(List.Next);
      end if;
      
   end Put;
  
   function Member(List : in List_Type; 
		   Key : in integer)return Boolean is
   begin
      if Empty(List) then
	 return False;
      elsif List.Data = Key then
	 return True;
      else
	 return Member(List.Next, Key);
      end if;
      
   end Member;
   
   procedure Remove(List : in out List_Type; 
		    Key : in integer) is
      Temp : List_Type;   
   begin
      if Empty(List) then
	 raise No_Such_Element_Error;
      end if;
      
      if List.data = Key then
	 Temp := List;
	 List:= Temp.Next;
	 Free(Temp);
	 return;
      end if;
      Remove(List.Next, Key);

   end Remove;

   procedure Delete (List : in out List_Type) is
      Temp : List_Type;
   begin
      
      Temp := null;
      
      if Empty(List) then
	 return;	 
      else 	 
	 Temp:= List.next;
	 Free(List);
	 List := Temp;
	 Delete(list);
      end if;
      
   end Delete;
   
  
   function Length(List : in List_type) return Integer is
   begin
      
      if Empty(List) then
	 return 0;
      else
	 return 1 + Length(List.Next);
      end if;
      
   end Length;

end Sorted_List;
