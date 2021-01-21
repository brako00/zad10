#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include<stdlib.h>

typedef struct stablo *pozicija;
struct stablo 
{
	char el;
	pozicija desno;
	pozicija lijevo;
};

typedef struct stog* poz;
struct stog
{
	pozicija element;
	poz next;
};

typedef struct stogchar* position;
struct stogchar
{
	char clan;
	position next;
};

char popchar(position);
int pushchar(position, char);
pozicija pop(poz);
int push(poz, pozicija);
int IspisInfix(pozicija, position);
int IspisInfixDatoteka(position);

int main()
{
	char ImeDat[50];
	char* buffer = NULL;
	int broj=0, n=0, duljina=0, brojac=0;
	char znak;
	struct stog head;
	head.next = NULL;
	pozicija root;
	struct stogchar headchar;
	headchar.next = NULL;

	printf("Unesi ime datoteke iz koje citas postfiks izraz\n");
	scanf("%s", ImeDat);

	FILE* Citanjedatoteka = fopen(ImeDat, "r");
	if (!Citanjedatoteka)
		printf("Greska pri otvaranju datoteke!\n");

	buffer = (char*)malloc(1024);
	fgets(buffer, 1024, Citanjedatoteka);
	duljina = strlen(buffer);


	while (brojac<=duljina)
	{
		if (sscanf(buffer, "%d%n", &broj, &n) == 1)
		{
			pozicija temp=(pozicija)malloc(sizeof(struct stablo));
			char brojka = broj + 48;
			temp->el = brojka;
			temp->desno = NULL;
			temp->lijevo = NULL;

			push(&head, temp);
		}
		else if (sscanf(buffer, "%c%n", &znak, &n) == 1)
		{
			if(znak=='+'||znak=='-'||znak=='*'||znak=='/')
			{
				pozicija temp = (pozicija)malloc(sizeof(struct stablo));
				temp->el = znak;
				temp->desno = pop(&head);
				temp->lijevo = pop(&head);

				push(&head, temp);
			}
		}
		brojac += n;
		buffer += n;
	}
	root = pop(&head);

	IspisInfix(root, &headchar);
	IspisInfixDatoteka(&headchar);

	return 0;
}

int IspisInfixDatoteka(position p)
{
	FILE* IspisDatoteka = fopen("ispis", "w");
	p = p->next;
	while (p != NULL)
	{
		fprintf(IspisDatoteka, "%c", p->clan);
		p = p->next;
	}

	return 0;
}

int IspisInfix(pozicija p, position q)
{	
	if (p != NULL)
	{
		IspisInfix(p->lijevo, q);
		printf(" %c", p->el);
		pushchar(q, p->el);
		IspisInfix(p->desno, q);
	}

	return 0;
}

pozicija pop(poz p)
{
	poz q;
	if (p->next != NULL)
	{
		q = p->next;
		p->next = q->next;
		return q->element;
		free(q);
	}
	return 0;
}

int push(poz p, pozicija c)
{
	poz q = (poz)malloc(sizeof(struct stog));
	q->element = c;
	q->next = p->next;
	p->next = q;

	return 0;
}

int pushchar(position p, char c)
{
	position q = (position)malloc(sizeof(struct stogchar));

	q->clan = c;
	q->next = p->next;
	p->next = q;

	return 0;
}

char popchar(position p)
{
	position q;
	if (p->next != NULL)
	{
		q = p->next;
		p->next = q->next;
		return q->clan;
		free(q);
	}
	return 0;
}