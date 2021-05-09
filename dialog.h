#ifndef DIALOG_H
#define DIALOG_H

typedef struct Knot Knot;
typedef struct Info Info;


char* enter_str();
int getInt(int* a);
int dialog(char** key, float* inf1, char** inf2, int* what, char** key2);
void print_tree(Knot* knot1, int i);


#endif