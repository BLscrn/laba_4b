#ifndef TREE_H
#define TREE_H


typedef struct Info {
	char* inf1;
	char* inf2;
} Info;

typedef struct Knot {
	char* key;
	struct Knot* right;
	struct Knot* left;
	//struct Knot* next_befor;
	struct Knot* parent;
	struct Info* info;
	int color;  // 0 - black , 1 - red;
}Knot;

Knot* knot1;
Knot* help;
char* key;
char* inf1;
char* inf2;
int ret, ch, what;
char* key2;


int rasp(int ch, char* key, char* inf1, char* inf2, int what, Knot** help, Knot** knot1, char* key2);
Knot* rotateLeft(Knot* knot1);
Knot* rotateRight(Knot* knot1);
void flipColors(Knot* knot1);
Knot* new_knot(char* key, char* inf1, char* inf2);
void add_el(Knot** knot1, char* key, char* inf1, char* inf2);
Knot* insert(Knot* knot1, char* key, char* inf1, char* inf2);
int isRED(Knot* knot1);
Knot* moveRedLeft(Knot* knot1);
Knot* moveRedRight(Knot* knot1);
void del_el(Knot** knot1, char* key);
Knot* delete(Knot* knot1, char* key);
Knot* min_knot(Knot* knot1);
Knot* del_min(Knot* knot1);
Knot* fixUP(Knot* knot1);
void FREE_knot(Knot* knot1);
Knot* cp_el(Knot* knot1, Knot* help);
Knot* seach(Knot* knot1, char* key);
int load(Knot** knot1, char* name);
#endif