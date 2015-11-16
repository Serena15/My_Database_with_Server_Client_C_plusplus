#include "list.h"
#include <stdio.h>
#include <iostream>
void
list::next()
{
  if(curr && curr->get_next())
    curr = curr->get_next();
}

void
list::prev()
{
  if(curr && curr->get_prev())
    curr = curr->get_prev();
}

void
list::push_begin (list_node *x)
{
  if(!x)
    return;
  if(!head)
    curr = head = tail = x;
  else
    {
      x->set_next(head);
      head->set_prev(x);
      head = x;
    }
}
void
list::push_end (list_node *x)
{
  if(!x)
    return;
  if(!tail)
    {curr = head = tail = x;}
  else
    {
      x->set_prev(tail);
      tail->set_next(x);
      tail = x;
    }
}
void
list::insert_after (list_node *x)
{
  if(!x)
    return;
  if(!curr)
    push_begin(x);
  if(curr->get_next())
    curr->get_next()->set_prev(x);
  x->set_next(curr->get_next());
  x->set_prev(curr);
  curr->set_next(x);
}

void
list::insert_before (list_node *x)
{
  if(!x)
    return;
  if(!curr)
    push_end(x);
  if(curr->get_prev())
    curr->get_prev()->set_next(x);
  x->set_prev(curr->get_prev());
  x->set_next(curr);
  curr->set_prev(x);
}
void
list::delete_begin ()
{
  if(!head)
    return;
  if(head == tail)
    {
      delete head;
      head = tail = curr = 0;
    }
  else
    {
      head->get_next()->set_prev(0);
      list_node *temp = head;
      if(head == curr)
        curr = curr->get_next();
      head = head->get_next();
      delete temp;
    }
}

void
list::delete_end ()
{
  if(!tail)
    return;
  if(head == tail)
    {
      delete tail;
      head = tail = curr = 0;
    }
  else
    {
      tail->get_prev()->set_next(0);
      list_node *temp = tail;
      if(tail == curr)
        curr = curr->get_prev();
      tail = tail->get_prev();
      delete temp;
    }
}

void
list::delete_node(list_node *x)
{
  if(!x)
    return;
  if(x == head)
    delete_begin();
  else if(x == tail)
    delete_end();
  else
    {
      if(x == curr)
        curr = curr->get_next();
      x->get_next()->set_prev(x->get_prev());
      x->get_prev()->set_next(x->get_next());
      delete x;
    }
}

list_node*
list::searh_group (int group_number)
{
  list_node *temp = head;
  while(temp && temp->get_group_number() != group_number)
    temp = temp->get_next();
  if(temp && temp->get_group_number() == group_number)
    return temp;
  return 0;
}
