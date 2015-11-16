#ifndef _TREE
#define _TREE

#include "record.h"

class tree_node
{
private:
  int colour;
  tree_node *left, *right, *parent, *next;
  record* key;
public:
  tree_node()
  {	left = right = parent = next = 0; key = 0; colour = -1; }
  tree_node(const tree_node& init)
  {     key->init(init.key->get_name(), init.key->get_phone(), init.key->get_group()); left = right = parent = next = 0; colour = -1;}
  tree_node& operator = (const tree_node& rhs)
  {
    this->~tree_node();
    key->init(rhs.key->get_name(), rhs.key->get_phone(), rhs.key->get_group());
    left = right = parent = next = 0; colour = -1;
    return *this;
  }
  ~tree_node()
  {	left = right = parent = next = 0; colour = -1;key = 0;}
  record* get_key ()
  {     return key;}
  void set_key (record *x)
  {     key = x;}
  int get_colour()
  {	return colour;}
  void set_colour(int icolour)
  {	colour = icolour;}
  tree_node* get_left()
  {	return left;}
  tree_node* get_right()
  {	return right;}
  tree_node* get_parent()
  {	return parent;}
  tree_node* get_next()
  {	return next;}
  void set_left(tree_node *x)
  {	left = x;}
  void set_right(tree_node *x)
  {	right = x;}
  void set_parent(tree_node *x)
  {	parent = x;}
  void set_next(tree_node *x)
  {	next = x;}
  int operator < ( tree_node& b);
  int operator > (tree_node& b);
  int operator == ( tree_node& b);

};

class tree
{
private:
  tree_node *root, *nil;
public:
  tree ();
  ~tree();
  tree_node* search (tree_node *r,int k);
  tree_node* zam (tree_node *z);
  tree_node* minimum (tree_node *z);
  int insert_node (tree_node *z);
  void delete_node (tree_node *z);
  void zam2 (tree_node *y, tree_node *x);
  void insert_f(tree_node *z);
  void delete_f(tree_node *x);
  void left_rotate (tree_node *x);
  void right_rotate (tree_node *x);
  void delete_tree (tree_node *r);
  tree_node* get_root()const
  {	return root;}
  tree_node* get_nil()const
  {	return nil;}
  void set_root(tree_node *x)
  {	root = x;}

};






#endif
