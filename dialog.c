#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
#include "time.h"

char* enter_str() {
	int q = 1, size = 10;;
	char vsp_str[11];
	int n = 1;
	char* osn_str;
	osn_str = (char*)calloc(1, sizeof(char));
	while (1) {

		n = scanf("%10[^\n]s", &vsp_str);
		if (n == 0) { return osn_str; }
		osn_str = (char*)realloc(osn_str, (size + q) * sizeof(char));
		strcpy((osn_str)+(q - 1), vsp_str);

		q += 10;

	}
}

int getInt(int* a) {
	int n;
	do {
		n = scanf("%d", a, sizeof(int));
		if (n < 0)
			return 0;
		if (n == 0) {
			printf("%s\n", "Error, try again:");
			scanf("%*s", 0);
		}
	} while (n == 0);
	return 1;
}

int dialog(char** key, char** inf1, char** inf2, int* what, char** key2) {
	int flag, ch;
	char* chouse[] = { "1. Enter new element", "2. delete element"
		,"3. find element","4. show tree","5. a bit more key","6. show tree like graf","7. Exite","8. Timing" };
	printf("Choose one of this variants:\n");
	for (int i = 0; i < 8; i++) {
		printf("%s\n", chouse[i]);
	}
	flag = 0;
	do {
		if (flag == 1) {
			printf("\nPlease enter number more than 0 and less than 7:");
		}
		getInt(&ch);
		while (getchar() != '\n');
		flag = 1;
	} while (ch <= 0 || ch >= 9);
	if (ch == 1) {
		printf("Enter key:");
		*key = enter_str();
		while (getchar() != '\n');
		printf("Enter the first inf:");
		*inf1 = enter_str();
		while (getchar() != '\n');
		printf("Enter the second inf:");
		*inf2 = enter_str();
		while (getchar() != '\n');
		return 1;
	}
	if (ch == 2) {
		printf("Enter key:");
		*key = enter_str();
		while (getchar() != '\n');
		return 2;
	}
	if (ch == 3) {
		printf("Enter key:");
		*key = enter_str();
		while (getchar() != '\n');
		return 3;
	}
	if (ch == 4) {
		return 4;
	}
	if (ch == 5) {
		printf("Enter key:");
		*key = enter_str();
		while (getchar() != '\n');
		return 5;
	}
	if (ch == 6) {
		return 6;
	}
	if (ch == 7) {
		return 7;
	}if (ch == 8) {
		return 8;
	}
}


void print_tree(Knot* knot1, int i) {
	if (knot1 == NULL) { return; }
	print_tree(knot1->right, i + 1);
	for (int j = 0; j < i; j++) {
		printf("\t");
	}
	printf("%s  %d\n", knot1->key,knot1->color);
	print_tree(knot1->left, i + 1);
}

void check_ans(int res, Knot* help) {
	if (res == 2 || res == 301) {
		printf("<show element>\n ");
		printf("\n\n%s\n%s\n%s\n", help->key, help->info->inf1, help->info->inf2);
	}
	if (res == 3) {
		printf("<show element>\n ");
		printf("\n\n%s\n%s\n%s\n", help->key, help->info->inf1, help->info->inf2);
		FREE_knot(help);
		help = NULL;
	}
	if (res == 404) {
		printf("There are no such element in the tree\n");
	}

}

void entee_file(Knot** knot1) {
	char* name;
	char qwer;
	int re = 1;
	printf("Do you want to use file?y/n ");
	scanf("%c", &qwer);
	while (getchar() != '\n');
	if (qwer == 'y') {
		do {
			printf("Enter name of the file: ");
			name = enter_str();
			while (getchar() != '\n');
			re = load(knot1, name);
			free(name);
		} while (re == 1);
	}
}


void obhod_deep(Knot* knot1) {
	if (knot1 == NULL) {
		return;
	}
	else {
		obhod_deep(knot1->left);
		obhod_deep(knot1->right);
		printf("\nkey: %s\nfirst inf: %s\nsecond inf: %s\n", knot1->key, knot1->info->inf1, knot1->info->inf2);
	}
}
void show_tree(Knot* knot1) {
	printf("<--show  tree-->\n ");
	obhod_deep(knot1);
}



int D_Timing() {
	Knot* knot1 = NULL;
	//Node *root = &EList;
	int n = 10, key[10000], k, cnt = 10000, i, m;
	Knot* help_1;
	clock_t first, last;
	srand(time(NULL));
	char* key_node = (char*)calloc(255, sizeof(char));
	while (n-- > 0) {
		for (i = 0; i < 10000; ++i)
			key[i] = rand() * rand();
		for (i = 0; i < cnt; ) {
			k = rand() * rand();
			itoa(k, key_node, 9);
			//new_node = createNode(key_node, NULL, 0, 0, key_node);
			/*if (!insert(&knot1))*/
			char* key_node_h = (char*)calloc(strlen(key_node) + 1, sizeof(char));
			strcpy(key_node_h, key_node);
			help_1 = add_el(&knot1, key_node_h, NULL, NULL);
			if (help_1 != NULL) {
				FREE_knot(help_1);
				help_1 = NULL;
			}
			++i;
			//free(new_node);
			//new_node = NULL;
		}
		m = 0;
		first = clock();
		Knot* help;
		for (i = 0; i < 10000; ++i) {
			help = NULL;
			itoa(key[i], key_node, 10);
			help = seach(knot1, key_node);
			if (help != NULL) {
				++m;
			}
		}
		last = clock();
		printf("%d items was found\n", m);
		printf("test #%d, number of nodes = %d, time = %d\n", 10 - n, (10 - n) * cnt, last - first);
	}
	free_tree(knot1);
	return 1;
}