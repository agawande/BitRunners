#include <stdio.h>

int main(){
	FILE *kill_signal=fopen("_kill", "w");
	fclose(kill_signal);
	return 0;
}
