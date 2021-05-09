#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "tree.h"
#include "dialog.h"




int main() {
	
	ret = 0;
	knot1 = NULL;
	//entee_file(&knot1);
	while (ret != 5) {
		ch = dialog(&key, &inf1, &inf2, &what, &key2);
		ret = rasp(ch, key, inf1, inf2, what, &help, &knot1, key2);
		//check_ans(ret, help);
	}
	ret = 1;
	//free_tree(knot1);
	return 0;
}