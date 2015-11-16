#include <string.h>
#include <stdio.h>
#include <iostream>

#include "record.h"


int
record::init(const char *iname, int iphone, int igroup)
{
  if(iname)
    {
      if(!(name = new char[strlen(iname) + 1]))
        return -1;
      strcpy(name, iname);
    }
  else
    name = 0;
  phone = iphone;
  group = igroup;
  return 0;
}
record::record(const char *iname, int iphone, int igroup)
{
#ifdef DEBUG
  printf("record::record %s %d\n",(iname) ? iname : "no name", iphone);
#endif
  init(iname, iphone, igroup);
 // std:: cout << "11" << std::endl;
}

record::record(const record &init)
{
#ifdef DEBUG
  printf("record::record %s %d\n",(iname) ? iname : "no name", iphone);
#endif
  this->init(init.name, init.phone, init.group);
//std:: cout << "1" << std::endl;
}



record::~record()
{
#ifdef DEBUG
  printf("record::~record %s %d\n",(name) ? name : "no name", phone);
#endif
  if(name)
    delete []name;
  name = 0;phone = 0;group = 0;
//std:: cout << "22" << std::endl;
}
void
record::print()
{
  printf("%s %d %d",name, phone, group);
}

record&
record::operator = (const record& rhs)
{
  this->~record();
  init(rhs.name, rhs.phone, rhs.group);
  return *this;
}
int
record::operator < ( record &b)
{
  return phone < b.phone;
}
int
record::operator > (record& b)
{
  return b < (*this);
}
int
record::operator == (record &b)
{
  return phone == b.phone;
}
int
record::operator != (record& b)
{
  return !( (*this) == b);
}
int
record::operator <= (record& b)
{
  return !(b > (*this));
}
int
record::operator >= (record& b)
{
  return !(b < (*this));
}

void delete_record_list(list_node_record *head)
{
  list_node_record *cur = head, *n;
  while(cur != 0)
    {
      n = cur->get_next();
      delete cur;
      cur = n;
    }
}
void
list_node_record::print_record_list(list_node_record * head)
{
    list_node_record *tmp = head;
    while(tmp)
    {
        tmp->print ();
        printf("\n");
        tmp = tmp->get_next ();
    }
}
