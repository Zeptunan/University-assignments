#include <stdlib.h>
#include "pagedir.h"
#include "thread.h"
#include <stdint.h>

/* verfy_*_lenght are intended to be used in a system call that accept
 * parameters containing suspisious (user mode) adresses. The
 * operating system (executng the system call in kernel mode) must not
 * be fooled into using (reading or writing) addresses not available
 * to the user mode process performing the system call.
 *
 * In pagedir.h you can find some supporting functions that will help
 * you dermining if a logic address can be translated into a physical
 * addrerss using the process pagetable. A single translation is
 * costly. Work out a way to perform as few translations as
 * possible.
 *
 * Recommended compilation command:
 *
 *  gcc -Wall -Wextra -std=gnu99 -pedantic -m32 -g pagedir.o verify_adr.c
 */

/* Verify all addresses from and including 'start' up to but excluding
 * (start+length). */
bool verify_fix_length(void* start, unsigned length)
{
  char *ptr = (char *) start; 
  char *end = ptr + length; 
  char *page_addr = pg_round_down(ptr); 
  for(;page_addr < end; page_addr +=PGSIZE){
    if(pagedir_get_page(thread_current()->pagedir, page_addr) == NULL){
      return false;  
    } 
  }
  return true; 
}

/* Verify all addresses from and including 'start' up to and including
 * the address first containg a null-character ('\0'). (The way
 * C-strings are stored.)
 */
bool verify_variable_length(char* start)
{
  if(start == NULL || pagedir_get_page(thread_current()->pagedir, pg_round_down(start)) == NULL)
    return false; 

  unsigned last_page = pg_no(start);

  while (true) {
    if (pg_no(start) != last_page) {
      if (pagedir_get_page(thread_current()->pagedir, pg_round_down(start)) == NULL)
        return false;
      last_page = pg_no(start);
    }

    if (is_end_of_string(start))
      return true;

    ++start;
  }
}


/* Definition of test cases. */
struct test_case_t
{
  void* start;
  unsigned length;
};

#define TEST_CASE_COUNT 7

const struct test_case_t test_case[TEST_CASE_COUNT] =
{
  {(void*)100, 200}, /* one full page */
  {(void*)100, 100},
  {(void*)199, 102},
  {(void*)101, 98},
  {(void*)250, 190},
  {(void*)250, 200},
  {(void*)250, 210}
};

/* This main program will evalutate your solution. */
int main(int argc, char* argv[])
{
  int i;
  bool result;

  if ( argc == 2 )
  {
    simulator_set_pagefault_time( atoi(argv[1]) );
  }
  thread_init();

  /* Test the algorithm with a given intervall (a buffer). */
  for (i = 0; i < TEST_CASE_COUNT; ++i)
  {
    start_evaluate_algorithm(test_case[i].start, test_case[i].length);
    result = verify_fix_length(test_case[i].start, test_case[i].length);
    evaluate(result);
    end_evaluate_algorithm();
  }

  /* Test the algorithm with a C-string (start address with
   * terminating null-character).
   */
  for (i = 0; i < TEST_CASE_COUNT; ++i)
  {
    start_evaluate_algorithm(test_case[i].start, test_case[i].length);
    result = verify_variable_length(test_case[i].start);
    evaluate(result);
    end_evaluate_algorithm();
  }
  return 0;
}
