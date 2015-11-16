#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "com.h"

database::database() : head(0)
{
}
database::~database ()
{
	
}

void
database::insert_record (list_node_record *rec)
{
  if(!rec)
    return;
  list_node * c_group = list_of_groups.searh_group(rec->get_group());
  if(!c_group)
  {
      c_group = new list_node;
      c_group->set_group_number (rec->get_group());
      list_of_groups.push_end(c_group);
  }
  if (c_group->Insert(rec))
    {
      delete rec;
      return;
    }
  tree_node * rec2;
  int incr=0;
  rec2 = new tree_node;
  rec2->set_key(((record*)rec));
  tree_of_records.insert_node(rec2);
	//delete c_group;
	//delete rec2;
  //printf("phone = %s \n",tree_of_records.get_root()->get_key()->get_name());
}

int
database::read_database_from_file (const char *filename)
{
  FILE *fin;
  if(!(fin = fopen(filename,"r")))
    return -1;
  char name[BUFLEN];
  int phone;
  int group;
  list_node_record * temp;
  while(fscanf(fin,"%s%d%d", name, &phone, &group) == 3)
    {
      temp = new list_node_record;
      if(temp->init (name, phone, group))
      {
        delete temp;
        fclose(fin);
        return -1;
      }
      insert_record(temp);
    }
  if(!feof(fin))
  {
      fclose(fin);
      return -2;
  }
  fclose(fin);
  return 0;
}

void database::create()
{
list_node_record * temp, *a1, *a2 ;	
	for ( int i=0; i < 10; i++)
	{
		temp = new list_node_record;
		temp->init("a", 1, 2);
		a1 = new list_node_record;
		a1->init("a", 3, 2);		
		insert_record(temp);
		insert_record(a1);
		print_database();		
		delete_rec_tree(temp);
		delete_rec_tree(a1);
		
	        	
	}
return;

}

void
database::print_database ()
{
   print_database2 (tree_of_records.get_root(), 0);
	print_database3 (list_of_groups.get_head());
}

void database::print_database3(list_node * head)
{
   list_node *tmp = head;
	//int i = 0;
	printf("\n");
    while(tmp)
    {
        tmp->print_hash();
       // printf("\n");
	//i++;
        tmp = tmp->get_next ();
    }
}

void database::print_database2(tree_node *x,int h)
{
   if (x == 0 || h > 5)
    return ;
  for(int i = 0; i < h; i++)
    printf("  ");
      printf("(");
      //((record*)x)->print();
  printf("  %s  %d %d ",x->get_key()->get_name(), x->get_key()->get_phone(),x->get_key()->get_group());
  print_database2(x->get_left (), h+1);
  print_database2(x->get_right (), h+1);
  
}


list_node_record *
database::com(int *nom, char *s)
{
    char *temp;
    char s1[BUFLEN];
    int i, ph, gr;
    printf("%s\n",s);
    sscanf(s, "%s", s1);
    if(strcmp(s1, "insert") == 0)
    {
        int len = strlen(s);
        for(i = 0; i < len; i++)
        {
            if(s[i] == ',')
                s[i] = ' ';
        }
        temp = strstr(s, "insert") + 7;
        char nm[BUFLEN];
        sscanf(temp, "(%s %d %d)", nm, &ph, &gr);
        list_node_record * tmp;
        tmp = new list_node_record;
        if(tmp->init (nm, ph, gr))
        {
          delete tmp;
          return 0;
        }
        insert_record(tmp);
        return 0;
    }
    else if(strcmp(s1, "delete") == 0)
    {
        int len = strlen(s);
        for(i = 0; i < len; i++)
        {
            if(s[i] == ';')
                s[i] = ' ';
        }
        temp = strstr(s, "delete") + 6;
        sscanf(temp, "%s", s1);
        if(strcmp(s1, "where") == 0)
        {
            temp = strstr(temp, "where") + 5;
            sscanf(temp, "%s", s1);
            if(strcmp(s1, "name") == 0)
            {
                temp = strstr(temp, "name") + 4;
                sscanf(temp, "%s", s1);
                if(strcmp(s1 ,"=") == 0)
                {
                    temp = strstr(temp, "=") + 1;
                    char nm[BUFLEN];
                    sscanf(temp, "%s", nm);
                    temp = strstr(temp ,nm) + strlen(nm);
                    sscanf(temp, "%s", s1);
                    if(strcmp(s1, "and") == 0)
                    {
                        temp = strstr(temp,"and") + 3;
                        sscanf(temp, "%s", s1);
                        if(strcmp(s1, "phone") == 0)
                        {
                            temp = strstr(temp, "phone") + 5;
                            sscanf(temp, "%s", s1);
                            if(strcmp(s1, "=") == 0)
                            {
                                temp = strstr(temp, "=") + 1;
                                sscanf(temp, "%d", &ph);
                                select_name(tree_of_records.get_root(), nm, 0, ph);
                                delete_(1);
                                delete_record_list(head);
                                head = 0;
                                return 0;
                            }
                            else { return 0;}
                        }
                        else if(strcmp(s1, "group") == 0)
                        {
                            temp = strstr(temp, "group") + 5;
                            sscanf(temp, "%s", s1);
                            if(strcmp(s1, "=") == 0)
                            {
                                temp = strstr(temp, "=") + 1;
                                sscanf(temp, "%d", &gr);
                                select_name(tree_of_records.get_root(), nm, 1, gr);
                                delete_(1);
                                delete_record_list(head);
                                head = 0;
                                return 0;
                            }
                            else {return 0;}
                        }
                        else
                        {	return 0;}
                    }
                    else
                    {
                        select_name(tree_of_records.get_root(), nm, -1, -1);
                        delete_(1);
                        delete_record_list(head);
                        head = 0;
                        return 0;
                    }
                }
                else {return 0;}
            }
            else if(strcmp(s1,"phone") == 0)
            {

                temp = strstr(temp, "phone") + 5;
                sscanf(temp, "%s", s1);
                if(strcmp(s1, "=") == 0)
                {
                    temp = strstr(temp, "=") + 1;
                    sscanf(temp, "%d", &ph);
                    select(tree_of_records.get_root(), 0, ph);
                    delete_(1);
                    delete_record_list(head);
                    head = 0;
                    return 0;
                }
                else {return 0;}
            }
            else if(strcmp(s1, "group") == 0)
            {
                temp = strstr(temp, "group") + 5;
                sscanf(temp, "%s", s1);
                if(strcmp(s1, "=") == 0)
                {
                    temp = strstr(temp, "=") + 1;
                    sscanf(temp, "%d", &gr);		    			
                    select(tree_of_records.get_root(), 1, gr);		    		    
                    delete_(0);	
		    delete_group_h (gr);	    
                    delete_record_list(head);
		    head = 0;		    			                    
                    return 0;
                }
                else {return 0;}
            }
            else {return 0;}
        }
        else {return 0;}
    }
    else if(strcmp(s1, "select") == 0)
    {
        int len = strlen(s);
        for(i = 0; i < len; i++)
        {
            if(s[i] == ';')
                s[i] = ' ';
        }
        temp = strstr(s, "select") + 6;
        sscanf(temp, "%s", s1);
        if(strcmp(s1, "*") == 0)
        {
            temp = strstr(temp, "*") + 1;
            sscanf(temp, "%s", s1);
            if(strcmp(s1, "where") == 0)
            {
                temp = strstr(temp, "where") + 5;
                sscanf(temp, "%s", s1);
                if(strcmp(s1, "name") == 0)
                {
                    temp = strstr(temp, "name") + 4;
                    sscanf(temp, "%s", s1);
                    if(strcmp(s1, "=") == 0)
                    {
                        temp = strstr(temp, "=") + 1;
                        char nm[BUFLEN];
                        sscanf(temp, "%s", nm);
                        temp = strstr(temp, nm) + strlen(nm);
                        sscanf(temp, "%s", s1);
                        if(strcmp(s1, "and") == 0)
                        {
                            temp = strstr(temp, "and") + 3;
                            sscanf(temp, "%s", s1);
                            if(strcmp(s1, "phone") == 0)
                            {
                                temp = strstr(temp, "phone") + 5;
                                sscanf(temp, "%s", s1);
                                if(strcmp(s1, "=") == 0)
                                {
                                    temp = strstr(temp, "=") + 1;
                                    sscanf(temp, "%d", &ph);
                                    select_name(tree_of_records.get_root(), nm, 0, ph);
                                    return head;
                                }
                                else {return 0;}
                            }
                            else if(strcmp(s1, "group") == 0)
                            {
                                temp = strstr(temp, "group") + 5;
                                sscanf(temp, "%s", s1);
                                if(strcmp(s1, "=") == 0)
                                {
                                    temp = strstr(temp, "=") + 1;
                                    sscanf(temp, "%d", &gr);
                                    select_group(1,gr,nm);
                        		return 0;
                                }
                                else {return 0;}
                            }
                            else
                            {	return 0;}
                        }
                        else
                        {
                            select_name(tree_of_records.get_root(), nm, -1, -1);
                            return head;
                        }
                    }
                    else {return 0;}
                }
                else if(strcmp(s1, "phone") == 0)
                {
                    temp = strstr(temp, "phone") + 5;
                    sscanf(temp, "%s", s1);
                    if(strcmp(s1, "=") == 0)
                    {
                        temp = strstr(temp, "=") + 1;
                        sscanf(temp, "%d", &ph);
                     select(tree_of_records.get_root(), 0, ph);
                        return head;
                    }
                    else {return 0;}
                }
                else if(strcmp(s1, "group") == 0)
                {
                    temp = strstr(temp, "group") + 5;
                    sscanf(temp, "%s", s1);
                    if(strcmp(s1, "=") == 0)
                    {
                        temp = strstr(temp, "=") + 1;
                        sscanf(temp, "%d", &gr);
			// select(tree_of_records.get_root(), 1, gr);
                        //return head;
                      select_group(0,gr,0);
                        return 0;
                    }
                    else {return 0;}
                }
                else
                {	return 0;}
            }
            else
            {	return 0;}
        }
        else
        {	return 0;}
    }
    else if(strcmp(s1, "quit;") == 0)
    {	*nom = 1;return 0;}
    else if(strcmp(s1,"print;") == 0)
    {
	print_database ();
	printf("\n");
	return 0;
	}
    else
    {	return 0;}
    return 0;
}


void database::select_name(tree_node *x,char *nm,int n,int p)
{
	if(x == tree_of_records.get_nil ())
        return;
    select_name(x->get_left (), nm, n, p);
    select_name(x->get_right (), nm, n, p);
    select_name(x->get_next (), nm, n, p);
	if(strcmp(x->get_key()->get_name(),nm)==0 && ((n==0 && x->get_key()->get_phone()==p) || (n==1 && x->get_key()->get_group()==p) || n == -1))
    {
        if(head == 0)
        {
            head = new list_node_record;
            head->init(x->get_key()->get_name(),x->get_key()->get_phone(),x->get_key()->get_group());
        }
        else
        {
            list_node_record *tmp;
            tmp = new list_node_record;
            tmp->init(x->get_key()->get_name(),x->get_key()->get_phone(),x->get_key()->get_group());
            tmp->set_next(head->get_next());
            head->set_next(tmp);
        }
    } 
}
void database::select(tree_node *x,int n,int p)
{
   if(x == tree_of_records.get_nil ())
        return;
    select(x->get_left (), n, p);
    select(x->get_right (), n, p);
    select(x->get_next (), n, p);
   if( (n==0 && x->get_key()->get_phone()==p) || (n==1 && x->get_key()->get_group()==p))
    {
        if(head == 0)
        {
            head = new list_node_record;
            head->init(x->get_key()->get_name(),x->get_key()->get_phone(),x->get_key()->get_group());
        }
        else
        {
            list_node_record *tmp;
            tmp = new list_node_record;
            tmp->init(x->get_key()->get_name(),x->get_key()->get_phone(),x->get_key()->get_group());
            tmp->set_next(head->get_next());
            head->set_next(tmp);
        }
    }

}

void database::select_group(int n,int g,char * nm)
{
    list_node * gr;
    list_node_record * tmp2, *t;
    int k = 0;
    gr = list_of_groups.searh_group (g);
    if( n == 0 && gr!=0){ gr->print_hash();}
    else if(n == 1 && gr!=0)
    {
	tmp2 = gr->find_name(nm,k);
	print_hash(gr->hash[k],nm);
    }
    else return;
}
void
database::print_hash(list_node_record * head, char * nm)
{
    list_node_record *tmp = head;
    while(tmp)
    {
       if(strcmp(tmp->get_name(),nm)==0){ tmp->print ();
        printf("\n");}
        tmp = tmp->get_next ();
    }
}
void
database ::delete_ (int n)
{
    list_node_record * tmp = head;
	printf("pspspss\n");
    while(tmp)
    {
        delete_rec_tree(tmp);
	if(n==1) delete_rec_hash(tmp);
        tmp = tmp->get_next ();
    }
}

void
database::delete_rec_tree (record *rec)
{
	tree_node * tmp, * next;
    tmp = tree_of_records.search (tree_of_records.get_root (), rec->get_phone ());
    while(tmp != tree_of_records.get_nil ())
    {
        next = tmp->get_next ();
        if(!strcmp(tmp->get_key()->get_name (), rec->get_name ()) && tmp->get_key ()->get_phone () == rec->get_phone () && tmp->get_key ()->get_group () == rec->get_group ())
        {
            tree_of_records.delete_node (tmp);
        }
        tmp = next;
    }
}

void
database::delete_rec_hash (record *rec)
{
 list_node * gr;
    list_node_record * tmp2, *t;
	int k = 0;
    gr = list_of_groups.searh_group (rec->get_group ());
    tmp2 = gr->find_name(rec->get_name(),k);
    //printf("kadabra k = %d  %s group= %d, phone= %d\n", k,tmp2->get_name(), tmp2->get_group(), tmp2->get_phone());
	while(tmp2!=0)
	{
		//printf("sdf\n");
		if(tmp2->get_phone () == rec->get_phone ())
		{gr->Delete(tmp2); return;}	
		else tmp2=tmp2->get_next();
	}
	

}

void
database::delete_group_h (int g)
{
   list_node * gr;
  // int k = 0;
   gr = list_of_groups.searh_group (g);
   list_of_groups.delete_node(gr);
}

void database::command()
{
    int nom = 0;
    char *s;
    s = (char*)malloc(BUFLEN * sizeof(char));
    while(true)
    {
        fgets(s, BUFLEN, stdin);
        this->com(&nom, s);
        if(nom == 1){
		free(s);
            return;
        }
	else
        {
            if(head)
                head->print_record_list(head);
            delete_record_list(head);
            head = 0;
        }
    }
    free(s);
}
