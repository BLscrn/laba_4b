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
float inf1;
char* inf2;
int ret, ch, what;
char* key2;


int rasp(int ch, char* key, float inf1, char* inf2, int what, Knot** help, Knot** knot1, char* key2);
Knot* rotateLeft(Knot* knot1);
Knot* rotateRight(Knot* knot1);
void flipColors(Knot* knot1);
Knot* new_knot(char* key, char* inf1, char* inf2);
void add_el(Knot* knot1, char* key, char* inf1, char* inf2);
Knot* insert(Knot* knot1, char* key, char* inf1, char* inf2);
int isRED(Knot* knot1);
#endif