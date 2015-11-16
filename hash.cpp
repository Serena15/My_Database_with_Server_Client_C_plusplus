#include "hash.h"
#include "record.h"
#include "string.h"
#include "stdio.h"
#include <iostream>


int group::Insert(list_node_record *x)
{
    int nom;
    if(x->get_name()!=0 && x->get_name()[0]>='a' && x->get_name()[0]<='z')
		nom=x->get_name()[0]-'a';
    else if(x->get_name()!=0)
		nom=x->get_name()[0]-'A';
    else
		return 1;
    if(hash[nom]==0)
    {	hash[nom]=x;return 0;}
 	else
	{	
		list_node_record *temp=hash[nom];
		temp->set_next(hash[nom]->get_next());		
		while(temp!=0)
		{
			if(strcmp(temp->get_name(),x->get_name())==0 &&	temp->get_phone() == x->get_phone() && temp->get_group() == x->get_group())
			{ return 1;}	
			temp=temp->get_next();
		}
		x->set_next(hash[nom]);
		hash[nom]=x;
	}
	return 0;
}


void group::Delete(list_node_record *x)
{
    int nom;
    if(x->get_name()!=0 && x->get_name()[0]>='a' && x->get_name()[0]<='z')
		nom=x->get_name()[0]-'a';
    else if(x->get_name()!=0)
		nom=x->get_name()[0]-'A';
    else
		{ return;}
    //if(hash[nom]==0)
    //{	delete x; return;}
	list_node_record *temp=hash[nom];
	temp->set_next(hash[nom]->get_next());
	if(temp == x)
	{
		if (temp->get_next()!=0) 
		{
			hash[nom]=temp->get_next();
			hash[nom]->set_next(temp->get_next()->get_next());
		}
		 else hash[nom]=0;	
		 delete temp;return ;
	}
	while(temp && temp->get_next()!=x)
		temp=temp->get_next();
	if(temp==0)
		return;
	list_node_record *tt=temp->get_next();
	temp->set_next(tt->get_next());
	delete tt;
}

list_node_record* group::find_name(const char *name, int &k)
{
    if(name==0)
	return 0;
    list_node_record *r;
    if(name[0]>='a' && name[0]<='z')
	{r=hash[name[0]-'a'];k=name[0]-'a';}
    else if(name[0]>='A' && name[0]<='Z')
	{r=hash[name[0]-'A'];k=name[0]-'A';}
    else
	{k=0;return 0;}
    while(r!=0 && strcmp(name,r->get_name())!=0)
	{r=r->get_next(); }
    if(r!=0)
	return r;
    return 0;	
}
group::~group()
{
    int i;
    for(i=0;i<26;i++)
    {	delete_record_list(hash[i]);}
}

void group:: print_hash()
{
	//list_node_record a;
	for(int i=0;i < 26; i++)
	{
		hash[i]->print_record_list(hash[i]);
		//printf("\n");
	}

}
