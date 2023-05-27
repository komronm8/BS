#include <stdio.h>
#include <stdlib.h>

float p = 0.00001;

float heron(float x, float a){
	float a_neu = (a + (x/a))/2;

	printf("Addresse von a_neu ist %p\n", (void*)&a_neu);

	if(a_neu*a_neu - x < p){
		return a_neu;
	}	
	else{
		return heron(x, a_neu);
	}
}

float bs_sqrt(float x){
	return heron(x,1);
}

int main(int argc, char* argv[]){
	if(argc > 1){
		int y = atoi(argv[1]);
		if(y < 0){
			printf("Fehler: Negative Zahl als Parameter angegeben\n");
		}
		else{
			printf("Die Quadratwurzel von %d lautet %.4f\n", y, bs_sqrt(y) );
		}
	}
	else{
		printf("Fehler: Keine Parameter angegeben\n");
	}
	return 0;
}


