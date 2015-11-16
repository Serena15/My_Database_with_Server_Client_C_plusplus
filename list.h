#ifndef _LIST
#define _LIST

#include "hash.h"

class list_node;
class list_node: public group
{
private:
  list_node *next, *prev;
  int group_number;
public:
  list_node() : group()
  {	next = 0; prev = 0;}
  list_node(const list_node& x) : group(x)
  {	next = 0; prev = 0;}
  ~list_node()
  {	next = 0; prev = 0;}
  list_node* get_next()const
  {	return next;}
  void set_next(list_node *x)
  {	next = x;}
  list_node* get_prev()const
  {	return prev;}
  void set_prev(list_node *x)
  {	prev = x;}
  int get_group_number()const
  {
    return group_number;
  }
  void set_group_number(int x)
  {
    group_number=x;
  }
  void delete_list(list_node *head);
};

class list
{
private:
  list_node *head, *tail, *curr;
public:
  list()
  {     head = 0; tail = 0; curr = 0;}
  ~list()
  {
      list_node * tmp = head, * next;
      while(tmp)
      {
          next = tmp->get_next ();
          delete tmp;
          tmp = next;
      }
      head = 0; tail = 0; curr = 0;
  }
  list_node* get_head ()
  {     return head;}
  void set_head (list_node *x)
  {     head = x;}
  list_node* get_tail ()
  {     return tail;}
  void set_tail (list_node *x)
  {     tail = x;}
  list_node* get_curr ()
  {     return curr;}
  void set_curr (list_node *x)
  {     curr = x;}
  void next ();
  void prev ();
  void push_begin (list_node *x);
  void push_end (list_node *x);
  void insert_before (list_node *x);
  void insert_after (list_node *x);
  void delete_begin ();
  void delete_end ();
  void delete_node (list_node *x);
  list_node* searh_group (int group_number);
};

#endif
