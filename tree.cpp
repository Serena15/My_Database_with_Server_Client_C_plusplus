#include <stdio.h>
#include <string.h>

#include "tree.h"


tree::tree ()
{	nil = new tree_node; nil->set_colour(1); root = nil;}

tree::~tree ()
{
  delete_tree (root);
  delete nil;
}

void
tree::left_rotate (tree_node *x)
{
  tree_node *y = x->get_right();
  x->set_right (y->get_left ());
  if (y->get_left () != nil)
    y->get_left ()->set_parent (x);
  y->set_parent (x->get_parent ());
  if (x->get_parent () == nil)
    root = y;
  else if (x == x->get_parent ()->get_left ())
    x->get_parent ()->set_left (y);
  else
    x->get_parent ()->set_right (y);
  y->set_left (x);
  x->set_parent (y);
}
void
tree::right_rotate(tree_node *x)
{
  tree_node *y = x->get_left ();
  x->set_left(y->get_right ());
  if (y->get_right () != nil)
    y->get_right ()->set_parent (x);
  y->set_parent (x->get_parent ());
  if (x->get_parent () == nil)
    root = y;
  else if (x == x->get_parent ()->get_left ())
    x->get_parent ()->set_left (y);
  else
    x->get_parent ()->set_right (y);
  y->set_right (x);
  x->set_parent (y);
}
int
tree::insert_node (tree_node *z)
{
  tree_node *r = root,*p = nil;
  while (r != nil)
    {
      p = r;
      if ( *z < *r )
        r = r->get_left ();
      else if (*z > *r )
        r = r->get_right ();
      else
        {
          if ( !strcmp (z->get_key()->get_name (), r->get_key()->get_name () ) && z->get_key()->get_phone() == r->get_key()->get_phone() && z->get_key()->get_group () == r->get_key()->get_group () )
            return -1;
          tree_node *temp = r;
          while (temp->get_next () != nil && !( !strcmp(z->get_key()->get_name (), temp->get_next ()->get_key()->get_name ()) && z->get_key()->get_phone () == temp->get_next ()->get_key()->get_phone () && z->get_key()->get_group () == temp->get_next ()->get_key()->get_group () ) )
            temp = temp->get_next ();
          if (temp->get_next () != nil)
            return -1;
          z->set_next (nil);
          temp->set_next (z);
          z->set_left (nil);
          z->set_right (nil);
          z->set_next (nil);
          return 0;
        }
    }
  z->set_parent (p);
  if (p == nil)
    root = z;
  else if ( *z < *p )
    p->set_left (z);
  else
    p->set_right (z);
  z->set_left (nil);
  z->set_right (nil);
  z->set_next (nil);
  z->set_colour (0);
  insert_f (z);
  return 0;
}
void
tree::insert_f (tree_node *z)
{
  while (z->get_parent ()->get_colour () == 0)
    {
      if (z->get_parent () == z->get_parent ()->get_parent ()->get_left () )
        {
          tree_node *y = z->get_parent ()->get_parent ()->get_right ();
          if (y->get_colour () == 0)
            {
              z->get_parent ()->set_colour (1);
              y->set_colour (1);
              z->get_parent ()->get_parent ()->set_colour (0);
              z=z->get_parent ()->get_parent ();
            }
          else
            {
              if (z == z->get_parent ()->get_right ())
                {
                  z = z->get_parent ();
                  left_rotate (z);
                }
              z->get_parent ()->set_colour (1);
              z->get_parent ()->get_parent ()->set_colour (0);
              right_rotate (z->get_parent ()->get_parent ());
            }
        }
      else
        {
          tree_node *y = z->get_parent ()->get_parent ()->get_left ();
          if (y->get_colour () == 0)
            {
              z->get_parent ()->set_colour (1);
              y->set_colour (1);
              z->get_parent ()->get_parent ()->set_colour (0);
              z=z->get_parent ()->get_parent ();
            }
          else
            {
              if (z == z->get_parent ()->get_left ())
                {
                  z = z->get_parent ();
                  right_rotate (z);
                }
              z->get_parent ()->set_colour (1);
              z->get_parent ()->get_parent ()->set_colour (0);
              left_rotate (z->get_parent ()->get_parent ());
            }
        }
    }
  root->set_colour (1);
}

tree_node*
tree::search(tree_node *r, int k)
{
  while (r != nil && r->get_key()->get_phone () != k)
    {
      if (k < r->get_key()->get_phone ())
        r = r->get_left ();
      else
        r = r->get_right ();
    }
  return r;
}

tree_node*
tree::zam(tree_node *z)
{
  if (z->get_right () == nil)
    return z;
  return minimum(z->get_right ());
}
tree_node*
tree::minimum(tree_node *z)
{
  tree_node *r = z;
  while (r != nil && r->get_left () != nil)
    r = r->get_left ();
  return r;
}

void
tree::zam2(tree_node *y, tree_node *x)
{
  if (x->get_parent () != nil)
    {
      if (x == x->get_parent ()->get_left ())
        x->get_parent ()->set_left(y);
      else
        x->get_parent ()->set_right(y);
    }
  else
    root = y;
  if (x->get_left () != nil)
    x->get_left ()->set_parent (y);
  if (x->get_right () != nil)
    x->get_right ()->set_parent(y);
  y->set_left(x->get_left ());
  y->set_right(x->get_right ());
  y->set_parent(x->get_parent ());
  y->set_colour(x->get_colour ());
}
void
tree::delete_node (tree_node *z)
{
  if (z == nil)
    return;
  if (!z->get_parent ())
    {
      tree_node *x;
      x = search(root, z->get_key()->get_phone ());
      while (x->get_next () && x->get_next () != z)
        x = x->get_next ();
      x->set_next(z->get_next ());
      delete z;
      return;
    }
  else if (z->get_next () != nil)
    {
      zam2(z->get_next (), z);
      delete z;
      return;
    }
  tree_node *y,*x;
  if (z->get_left () == nil || z->get_right () == nil)
    y = z;
  else
    y = zam (z);
  if (y != z)
    {
      tree_node *temp;
      temp = new tree_node;
      zam2(temp, y);
      zam2(y, z);
      zam2(z, temp);
      delete temp;
    }

  if (z->get_left () != nil)
    x = z->get_left ();
  else
    x = z->get_right ();
  x->set_parent(z->get_parent ());
  if (z->get_parent () == nil)
    root = x;
  else if (z->get_parent ()->get_left () == z)
    z->get_parent ()->set_left(x);
  else
    z->get_parent ()->set_right(x);
  if (z->get_colour () == 1)
    delete_f(x);
  delete z;
}

void
tree::delete_f(tree_node *x)
{
  while (x != root && x->get_colour () == 1)
    {
      if (x == x->get_parent ()->get_left ())
        {
          tree_node *w = x->get_parent ()->get_right ();
          if (w->get_colour () == 0)
            {
              w->set_colour(1);
              x->get_parent ()->set_colour(0);
              left_rotate(x->get_parent ());
              w = x->get_parent ()->get_right ();
            }
          if (w->get_left ()->get_colour () == 1 && w->get_right ()->get_colour () == 1)
            {
              w->set_colour (0);
              x = x->get_parent ();
            }
          else
            {
              if (w->get_right ()->get_colour () == 1)
                {
                  w->get_left ()->set_colour(1);
                  w->set_colour(0);
                  right_rotate(w);
                  w = x->get_parent ()->get_right ();
                }
              w->set_colour(x->get_parent ()->get_colour ());
              x->get_parent ()->set_colour(1);
              w->get_right ()->set_colour(1);
              left_rotate(x->get_parent ());
              x = root;
            }
        }
      else
        {
          tree_node *w = x->get_parent ()->get_left ();
          if (w->get_colour () == 0)
            {
              w->set_colour(1);
              x->get_parent ()->set_colour(0);
              right_rotate(x->get_parent ());
              w = x->get_parent ()->get_left ();
            }
          if (w->get_right ()->get_colour () == 1 && w->get_left ()->get_colour () == 1)
            {
              w->set_colour(0);
              x = x->get_parent ();
            }
          else
            {
              if (w->get_left ()->get_colour () == 1)
                {
                  w->get_right ()->set_colour(1);
                  w->set_colour(0);
                  left_rotate(w);
                  w = x->get_parent ()->get_left ();
                }
              w->set_colour(x->get_parent ()->get_colour ());
              x->get_parent ()->set_colour(1);
              w->get_left ()->set_colour(1);
              right_rotate(x->get_parent ());
              x = root;
            }
        }
    }
  x->set_colour(1);
}

void
tree::delete_tree(tree_node *r)
{
  if (r == nil)
    return ;
  delete_tree (r->get_left ());
  delete_tree (r->get_right ());
  delete_tree (r->get_next ());
  delete r;
}

int
tree_node::operator < ( tree_node &b)
{
  return key->get_phone() < b.key->get_phone();
}
int
tree_node::operator > (tree_node& b)
{
  return b < (*this);
}
int
tree_node::operator == (tree_node &b)
{
  return key->get_phone() == b.key->get_phone();
}
