#ifndef _RECORD 
#define _RECORD 

#include <string.h>

#define BUFLEN 1234

class record
{
private:
  int group,phone;
  char* name;
public:
  record(const char* iname = 0, int iphone = 0, int igroup = 0);
  record(const record& init);
  ~record();
  record& operator = (const record& rhs);
  int operator < ( record& b);
  int operator > (record& b);
  int operator == (record& b);
  int operator <= (record& b);
  int operator >= (record& b);
  int operator != (record& b);
  int init(const char* iname = 0, int iphone = 0, int igroup = 0);
  int get_phone()const
  {	return phone;}
  int get_group()const
  {	return group;}
  char* get_name()const
  {	return (char*)name;}
  /*char* get_name0()const
  {	return (char*)name[0];}*/
  void set_phone(int iphone)
  {	phone = iphone;}
  void set_group(int igroup)
  {	group = igroup;}
  void set_name(char *iname)
  {	strcpy(name,iname);}
  void print();
};

class list_node_record;
class list_node_record: public record
{
private:
  list_node_record *next;
public:
  list_node_record(const char* iname = 0, int iphone = 0, int igroup = 0) : record(iname, iphone, igroup)
  {	next = 0;}
  list_node_record(const list_node_record& x) : record(x)
  {	next = 0;}
  ~list_node_record()
  {	next = 0;}
  list_node_record& operator = (const list_node_record& rhs)
  {
    *(record*)(this) = rhs;
    next = 0;
    return *this;
  }
  list_node_record* get_next()const
  {	return next;}
  void set_next(list_node_record *x)
  {	next = x;}
 
  void print_record_list(list_node_record * head);
};

 void delete_record_list(list_node_record *head);

#endif
