#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int getnum(){
	srand(time(NULL));
	for(int i=0;i<1000000;i++){
		printf("%d\n",rand());
	}
}

