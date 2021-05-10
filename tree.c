#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "tree.h"
#include "dialog.h"




int rasp(int ch, char* key, char* inf1, char* inf2, int what, Knot** help, Knot** knot1, char* key2) {
	if (ch == 1) {
		add_el(knot1, key, inf1, inf2);
		return 0;
	}
	if (ch == 2) {
		del_el(knot1, key);
		//prosh_tree(*knot1);
		return 0;
	}
	if (ch == 3) {
		
		*help = seach(*knot1, key);
		if (*help != NULL) { return 2; }
		else { return 404; }
	}
	if (ch == 4) {
		show_tree(*knot1);
		return 0;
	}
	if (ch == 5) {
		*help = NULL;
		a_bit_more(*knot1, key,help);
		if (*help != NULL) { return 2; }
		else { return 404; }
	}
	if (ch == 6) {
		print_tree(*knot1, 0);
		return 0;
	}
	if (ch == 7) {
		return 7;
	}
}

Knot* rotateLeft(Knot* knot1) {
	Knot* child;
	child = knot1->right;
	knot1->right = child->left;
	child->left = knot1;
	child->color = knot1->color;
	knot1->color = 1;
	return child;
}
Knot* rotateRight(Knot* knot1) {
	Knot* child;
	child = knot1->left;
	knot1->left = child->right;
	child->right = knot1;
	child->color = knot1->color;
	knot1->color = 1;
	return child;
}

void flipColors(Knot* knot1) {
	knot1->color = knot1->color == 0 ?  1:  0;
	knot1->left->color = knot1->left->color == 0 ? 1: 0;
	knot1->right->color = knot1->right->color == 0 ? 1 : 0;
}


Knot* new_knot(char* key, char* inf1, char* inf2) {
	Knot* re;
	re = (Knot*)calloc(1, sizeof(Knot));
	re->color = 1;
	re->info = (Info*)calloc(1, sizeof(Info));
	re->info->inf1 = inf1;
	re->info->inf2 = inf2;
	re->key = key;
	return re;
}

void add_el(Knot** knot1, char* key, char* inf1, char* inf2) {
	*knot1 = insert(*knot1,key,inf1,inf2);
	(*knot1)->color = 0;
}
int isRED(Knot* knot1) {
	if (knot1 == NULL) {
		return 0;
	}
	else if (knot1->color == 0){
		return 0;
	}
	else if (knot1->color == 1) {
		return 1;
	}
	else {
		return 0;
	}
}

Knot* insert(Knot* knot1, char* key, char* inf1, char* inf2) {
	if (knot1 == NULL) {
		return new_knot(key, inf1, inf2);
	}
	int cmp;
	cmp = strcmp(key, (knot1)->key);
	if (cmp == 0) {
		free((knot1)->info->inf1);
		free((knot1)->info->inf2);
		(knot1)->info->inf1 = inf1;
		(knot1)->info->inf2 = inf2;
	}
	else if (cmp < 0) {
		knot1->left = insert((knot1)->left, key, inf1, inf2);
	}
	else if (cmp > 0) {
		knot1->right = insert((knot1)->right, key, inf1, inf2);
	}
	if (isRED((knot1)->right) == 1 && isRED((knot1)->left) == 0) {
		knot1 = rotateLeft(knot1);
	} 
	if (isRED((knot1)->left) == 1 && isRED((knot1)->left->left) == 1) {
		knot1 = rotateRight(knot1);
	}
	if (isRED((knot1)->left) == 1 && isRED((knot1)->right) == 1) {
		flipColors(knot1);
	}	
	return knot1;
}

Knot* moveRedLeft(Knot* knot1) {
	flipColors(knot1);
	if (isRED(knot1->right->left) == 1) {
		knot1->right = rotateRight(knot1->right);
		knot1 = rotateLeft(knot1);
		flipColors(knot1);
	}
	return knot1;
}

Knot* moveRedRight(Knot* knot1) {
	flipColors(knot1);
	if (isRED(knot1->left->left) == 1) {
		knot1 = rotateRight(knot1);
		flipColors(knot1);
	}
	return knot1;
}

void del_el(Knot** knot1, char* key) {
	*knot1 = delete(*knot1, key);
	
	if (*knot1 != NULL) {
		(*knot1)->color = 0;
	}
}

Knot* delete(Knot* knot1, char* key) {
	if (strcmp(key, knot1->key) < 0) {
		if (isRED(knot1->left) == 0 && isRED(knot1->left->left) == 0) {
			knot1 = moveRedLeft(knot1);
		}
		knot1->left = delete(knot1->left, key);
	}
	else {
		if (isRED(knot1->left) == 1) {
			knot1 = rotateRight(knot1);
		}
		if (strcmp(key, knot1->key) == 0 && (knot1->right == NULL)) {
			FREE_knot(knot1);
			return NULL;
		}
		if (isRED(knot1->right) == 0 && isRED(knot1->right->left) == 0) {
			knot1 = moveRedRight(knot1);
		}
		if (strcmp(key, knot1->key) == 0) {
			Knot* min;
			min = min_knot(knot1->right);
			/*knot1->info->inf1 = min->info->inf1;
			knot1->info->inf2 = min->info->inf2;
			knot1->key =  min->key;
			*/
			knot1 = cp_el(knot1, min);
			knot1->right = del_min(knot1->right);
		}
		else {
			knot1->right = delete(knot1->right, key);
		}

	}
	return fixUP(knot1);
}


Knot* min_knot(Knot* knot1) {
	if (knot1->left == NULL) {
		return knot1;
	}
	else {
		return min_knot(knot1->left);
	}
}


Knot* del_min(Knot* knot1) {
	if (knot1->left == NULL) {
		FREE_knot(knot1);
		return NULL;
	}
	if (isRED(knot1->left) == 0 && isRED(knot1->left->left) == 0) {
		knot1 = moveRedLeft(knot1);
	}

	knot1->left = del_min(knot1->left);
	return fixUP(knot1);
}


Knot* fixUP(Knot* knot1) {
	if (isRED(knot1->right) == 1 && isRED(knot1->left) == 0) {
		knot1 = rotateLeft(knot1);
	}
	if (isRED(knot1->left) == 1 && isRED(knot1->left->left) == 1) {
		knot1 = rotateRight(knot1);
	}
	if (isRED(knot1->right) == 1 && isRED(knot1->left) == 1) {
		flipColors(knot1);
	}
	return knot1;
}

void FREE_knot(Knot* knot1) {
	free(knot1->key);
	free(knot1->info->inf1);
	free(knot1->info->inf2);
	free(knot1->info);
	free(knot1);
}

Knot* cp_el(Knot* knot1,Knot* help) {
	free((knot1)->key);
	(knot1)->key = (char*)calloc(strlen(help->key) + 1, sizeof(char));
	strcpy(knot1->key, help->key);
	free(knot1->info->inf1);
	(knot1)->info->inf1 = (char*)calloc(strlen(help->info->inf1) + 1, sizeof(char));
	strcpy(knot1->info->inf1, help->info->inf1);
	free(knot1->info->inf2);
	(knot1)->info->inf2 = (char*)calloc(strlen(help->info->inf2) + 1, sizeof(char));
	strcpy(knot1->info->inf2, help->info->inf2);
	return knot1;
}

Knot* seach(Knot* knot1, char* key) {
	if (knot1 == NULL) {
		return NULL;
	}
	if (strcmp(key, knot1->key) == 0) {
		return knot1;
	}
	if (strcmp(key, knot1->key) < 0) {
		return seach(knot1->left,key);
	}
	if (strcmp(key, knot1->key) > 0) {
		return seach(knot1->right,key);
	}
}


int load(Knot** knot1, char* name) {
	FILE* f = NULL;
	char** inf;
	char** inf_help;
	char* help;
	char* prov;
	int flag;
	inf = (char**)calloc(3, sizeof(char*));
	for (int i = 0; i < 3; i++) {
		inf[i] = (char*)calloc(255, sizeof(char));
	}

	f = fopen(name, "r+b");
	if (f == NULL) {
		return 1;
	}
	flag = 1;
	while (flag == 1) {
		inf_help = (char**)calloc(3, sizeof(char*));
		for (int i = 0; i < 3; i++) {
			inf_help[i] = (char*)calloc(255, sizeof(char));
		}
		for (int i = 0; i < 3; i++) {
			prov = fgets(inf[i], 255, f);
			if (prov == NULL) {
				flag = 0;
				break;
			}
			strncpy(inf_help[i], inf[i], strlen(inf[i]) - 2);
		}

		if (flag == 0) { continue; }
		//from_str_to_fl(inf_help[1], &inf2);
		add_el(knot1, inf_help[0], inf_help[1], inf_help[2]);

	}
	return 0;
}

void a_bit_more(Knot* knot1, char* key,Knot** help) {
	if (knot1 == NULL) {
		return;
	}
	else {
		a_bit_more(knot1->left,key,help);
		if (strcmp(key, knot1->key) < 0 && *help == NULL) {
			*help = knot1;
			return;
		}
		a_bit_more(knot1->right,key,help);
		
	}
}