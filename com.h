#include "list.h"
#include "tree.h"

#define MAX_DEPTH_TREE_FOR_PRINT 3

class database
{
private:
  list  list_of_groups;
  tree  tree_of_records;
public:
  database();
  ~database();
  void insert_record (list_node_record *rec);
  void delete_rec_tree(record *rec);
  void delete_rec_hash (record *rec);
  int read_database_from_file (const char * filename);
  void print_database ();
  void print_database2 (tree_node * r, int h);
  void select (tree_node * r, int n, int p);
  void select_name (tree_node * r, char *nm, int n, int p);
  list_node_record * com (int *nom, char *s);
  void delete_ (int n);
  void command ();
 // void select_group(int g);
  //void select_phone (AVL_tree_node * r, int p);
  list_node_record * head;
  void print_database3(list_node * head);
  void select_group(int n,int g,char * nm);
  void delete_group_h (int g);
  void create();
  void print_hash(list_node_record * head, char * nm);
};
