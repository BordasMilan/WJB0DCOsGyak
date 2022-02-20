#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *fp;
    fp = fopen("bordas.txt","w");
    fprintf(fp,"%s","Bordas Milan Programtervezo informatikus WJB0DC");
    fclose(fp);
    fp = fopen("bordas.txt","r");
    fclose(fp);
    return 0;
}
