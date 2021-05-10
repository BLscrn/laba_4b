#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

char* enter_str() {
	int q = 0, size = 0;;
	char vsp_str[11];
	int n = 1;
	char* osn_str;
	osn_str = (char*)malloc(1 * sizeof(char));
	while (1) {

		n = scanf("%10[^\n]s", &vsp_str);
		if (n == 0) { return osn_str; }
		size += 10;
		osn_str = (char*)realloc(osn_str, size * sizeof(char));
		strcpy((osn_str)+q, vsp_str);

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
		,"3. find element","4. show tree","5. Obhod in deep","6. show tree like graf","7. Exite" };
	printf("Choose one of this variants:\n");
	for (int i = 0; i < 7; i++) {
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
	} while (ch <= 0 || ch >= 8);
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