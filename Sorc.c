#define _CRT_SECURE_NO_WARNINGS

/*
* Napisati program koji prvo procita koliko redaka ima datoteka,
* tj.koliko ima studenata zapisanih u
* datoteci.Nakon toga potrebno je dinamicki alocirati prostor za niz
* struktura
* studenata(ime, prezime, bodovi) i ucitati iz datoteke sve zapise.
* Na ekran ispisati ime, prezime, apsolutni i relativni broj bodova.
* Napomena: Svaki redak datoteke sadrzi ime i prezime studenta,
* te broj bodova na kolokviju.
*/

#include <stdio.h>
#include <stdlib.h>

//tu definiramo txt iz koje cemo citati podatke  studentima
#define studentsFile "student.txt"

typedef struct stud {
	char ime[20];
	char prezime[20];
	int bodovi;
}STUDENT;


int ReadLine();
int ReadFromFile(STUDENT*);
int PrintOnScreen(STUDENT*, int);
float RelativeScore(int, int);
int MaxScore(STUDENT*, int);

int main()
{
	int brojStud = 0;
	STUDENT* pStudent = NULL;


	brojStud = ReadLine();
	if (brojStud > 0)
	{
		printf("broj ucitanih studenata : %d \n", brojStud);

		pStudent = (STUDENT*)malloc(brojStud * sizeof(STUDENT));
		if (ReadFromFile(pStudent) > 0)
		{
			printf("Uspjesno ste ucitali studente iz datoteke \n\n");
			PrintOnScreen(pStudent, brojStud);
			printf("\n Kraj \n");
		}
	}
	free(pStudent);

	system("pause");
	return 0;
}

int ReadLine()
{
	/*
	* vracamo broj linija sto predstavlja broj studenata
	*/
	FILE* fp = fopen("student.txt", "r");
	char buff[1024] = { 0 };
	int brojac = 0;



	if (!fp)
		printf("Neuspjesno otvaranje\n");
	else
	{
		while (!feof(fp))
		{
			fgets(buff, 1024, fp);
			brojac++;
		}
		fclose(fp);
	}
	return brojac;
}
int ReadFromFile(STUDENT* pstud)
{
	int br = 0;
	FILE* fp = NULL;
	fp = fopen("student.txt", "r");

	if (fp == NULL)
	{
		printf("Neuspjesno otvaranje\n");
		return -1;
	}
	else
	{
		while (!feof(fp))
		{
			fscanf(fp, "%s %s %d", pstud[br].ime, pstud[br].prezime, &pstud[br].bodovi);
			br++;
		}
		fclose(fp);
		return 1;
	}

}
int PrintOnScreen(STUDENT* pstud, int br)
{
	int i;
	float relativeScore = 0;
	int maxBodovi = MaxScore(pstud, br);
	for (i = 0; i < br; i++)
	{
		relativeScore = RelativeScore(pstud[i].bodovi, maxBodovi);
		printf("%s %s \n broj bodova: %d \n relativni broj bodova: %.2f \n",
			pstud[i].ime, pstud[i].prezime, pstud[i].bodovi, relativeScore);
	}
	return 1;
}
int MaxScore(STUDENT* pstud, int br)
{

	int i;
	int max = pstud[0].bodovi;
	for (i = 1; i < br; i++)
	{
		if (pstud[i].bodovi > max)
		{
			max = pstud[i].bodovi;
		}
	}
	return max;
}
float RelativeScore(int bodovi, int max)
{

	return (((float)bodovi / max) * 100);
}
