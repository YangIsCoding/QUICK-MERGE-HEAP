#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void getalpha(){
	srand(time(NULL));
	for(int i=0;i<1000000;i++){
		for(int j=0;j<100;j++){
			printf("%c",rand()%26+'A');
		}
		printf("\n");
	}
}
