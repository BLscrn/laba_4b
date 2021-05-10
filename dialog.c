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
		,"3. find element","4. show tree","5. Exite","6. show tree like graf" };
	printf("Choose one of this variants:\n");
	for (int i = 0; i < 6; i++) {
		printf("%s\n", chouse[i]);
	}
	flag = 0;
	do {
		if (flag == 1) {
			printf("\nPlease enter number more than 0 and less than 6:");
		}
		getInt(&ch);
		while (getchar() != '\n');
		flag = 1;
	} while (ch <= 0 || ch >= 7);
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
		printf("Enter number:");
		getInt(what);
		while (getchar() != '\n');
		return 3;
	}
	if (ch == 4) {
		return 4;
	}
	if (ch == 5) {
		return 5;
	}
	if (ch == 6) {
		return 6;
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