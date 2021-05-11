#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "tree.h"
#include "dialog.h"


#define __CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW

int main() {
	//_crtBreakAlloc = 134;
	ret = 0;
	knot1 = NULL;
	entee_file(&knot1);
	while (ret != 7) {
		ch = dialog(&key, &inf1, &inf2, &what, &key2);
		ret = rasp(ch, key, inf1, inf2, what, &help, &knot1, key2);
		check_ans(ret, help);
	}
	ret = 1;
	free_tree(knot1);
	_CrtDumpMemoryLeaks();
	return 0;
}