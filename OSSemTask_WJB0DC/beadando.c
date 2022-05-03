#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
void feltolt(int* tomb, int length); //feltoltjuk az 1000 elemu tombot
int maxkeres(int* tomb, int length); //maxkereses 100 es 10 re
int main()
{
    int db = 1000;
    int processDb = 10;
    int array[db];
    feltolt(array, db);
    int i;
    char str[4]; //pipeba ezen keresztul mennek az adatok
    int p[2]; //pipe amibol a gyerekek olvasnak
    int p2[2]; //pipe amibol a szulo olvas (1-el is lehet mukodik)
    if(pipe(p)<0)
    {
        exit(1);
    }
    if(pipe(p2)<0) //pipeok letrehozasa, ha nem sikerul kilep
    {
	exit(1);
    }
    for(i = 0; i< db; i++)
    {
        sprintf(str,"%d",array[i]); //pipeba stringkent toltjuk az elemeket, majd konvertaljuk
        write(p[1],str,4);
    }
    close(p[1]);
    for(i = 0; i < processDb; i++)
    {
        if(fork() == 0) //itt letrehozunk egy gyereket ciklusonkent, majd annak megadjuk a feladatot
        {
            int szamok[100];
	    int j;
	    char be[4]; //1. pipebol ide jonnek a szamok
	    char vissza[4]; //2. pipeba innen irunk
            for(j = 0;j<100;j++)
            {
                read(p[0],be,4);
                szamok[j] = atoi(be); //konvertaljuk a stringet intbe
            }
            close(p[0]);
            int max = maxkeres(szamok,100);
	    sprintf(vissza,"%d",max);
	    write(p2[1],vissza,4); //visszaadjuk a 2.pipeba a maximumat a darabolt tombnek
	    close(p2[1]);
            exit(0); //kilepunk a gyerekbol, tehat csak a fork() == 0-tol idaigi reszt hajtja vegre
            }
    }
    for(i = 0; i < processDb; i++)
    {
        wait(NULL); //megvarunk minden processt
    }
    int maxok[processDb];
    for(i = 0; i< processDb;i++)
    {
        read(p2[0],str,4);
        maxok[i] = atoi(str); //stringkent jottek a maxok is
    }
    printf("A tomb max erteke: %d\n",maxkeres(maxok,processDb));
    return 0;
}
//fuggvenyek deklaracioi
void feltolt(int* tomb, int length)
{
    srand(time(0));
    int i;
    for(i = 0; i < length; i++)
    {
        tomb[i] = rand()%9900+1;
    }
}
int maxkeres(int* tomb, int length)
{
    int i;
    int max = tomb[0];
    for(i = 0; i< length; i++)
    {
        if(max<tomb[i])
        {
            max = tomb[i];
        }
    }
    return max;
}
