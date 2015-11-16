#ifndef _HASH
#define _HASH

#include "record.h"

class group
{
public:
	list_node_record *hash[26];
	int group_number;
	group()
	{
		int i;
		for(i=0;i<26;i++)
			hash[i]=0;
		group_number=0;
	}
	~group();
	int Insert(list_node_record *x);
	void Delete(list_node_record *x);
	//list_node_record* find_phone(int phone);
	void print_hash();
	int readfile (const char *filename);	
	list_node_record* find_name(const char *name, int &k);
};
int main();

#endif
