#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
 
/*Władisław Czebotarew*/

struct node
{
	int element;
	node *left;
	node *right;
	int height;
};
 
 typedef struct node *nodeptr;
 

		void insert(int,nodeptr &);
		void del(int, nodeptr &);
		int deletemin(nodeptr &);
		void find(int,nodeptr &);
		nodeptr findmin(nodeptr);
		nodeptr findmax(nodeptr);
		void makeempty(nodeptr &);
		void copy(nodeptr &,nodeptr &);
		nodeptr nodecopy(nodeptr &);
		void preorder(nodeptr);
		void inorder(nodeptr);
		void postorder(nodeptr);
		int bsheight(nodeptr);
		nodeptr srl(nodeptr &);
		nodeptr drl(nodeptr &);
		nodeptr srr(nodeptr &);
		nodeptr drr(nodeptr &);
		int max(int,int);
		int nonodes(nodeptr);



void insert(int x,nodeptr &p)
{
	if (p == NULL)
	{
		p = new node;
		p->element = x;
		p->left=NULL;
		p->right = NULL;
		p->height=0;
		if (p==NULL)
		{
			printf("Out of Space\n");
		}
	}
	else
	{
		if (x<p->element)
		{
			insert(x,p->left);
			if ((bsheight(p->left) - bsheight(p->right))==2)
			{
				if (x < p->left->element)
				{
					p=srl(p);
				}
				else
				{
					p = drl(p);
				}
			}
		}
		else if (x>p->element)
		{
			insert(x,p->right);
			if ((bsheight(p->right) - bsheight(p->left))==2)
			{
				if (x > p->right->element)
				{
					p=srr(p);
				}
				else
				{
					p = drr(p);
				}
			}
		}
		else
		{
			printf("Element istnieje\n");
		}
}
	int m,n,d;
	m=bsheight(p->left);
	n=bsheight(p->right);
	d=max(m,n);
	p->height = d + 1;
}

nodeptr findmin(nodeptr p)
{
	if (p==NULL)
	{
		printf("Drzewo nie ma elementow\n");
		return p;
	}
	else
	{
		while(p->left !=NULL)
		{
			p=p->left;
			
		}
		return p;
	}
}

nodeptr findmax(nodeptr p)
{
	if (p==NULL)
	{
		printf("Drzewo nie ma elementow\n");
		return p;
	}
	else
	{
		while(p->right !=NULL)
		{
			p=p->right;
			
		}
		return p;
	}
}

void find(int x,nodeptr &p)
{
	if (p==NULL)
	{
		printf("Przepraszam, taki element nie istnieje\n");
	}
	else
	{
		if (x < p->element)
		{
			find(x,p->left);
		}
		else
		{
			if (x>p->element)
			{
				find(x,p->right);
			}
			else
			{
				printf("Element, ktory byl poszukiwany istnieje!\n");
			}
		}
	}
}

void copy(nodeptr &p,nodeptr &p1)
{
	makeempty(p1);
	p1 = nodecopy(p);
}

void makeempty(nodeptr &p)
{
	nodeptr d;
	if (p != NULL)
	{
		makeempty(p->left);
		makeempty(p->right);
		d=p;
		free(d);
		p=NULL;
	}
}

nodeptr nodecopy(nodeptr &p)
{
	nodeptr temp;
	if (p==NULL)
	{
		return p;
	}
	else
	{
		temp = new node;
		temp->element = p->element;
		temp->left = nodecopy(p->left);
		temp->right = nodecopy(p->right);
		return temp;
	}
}
 

void del(int x,nodeptr &p)
{
	nodeptr d;
	if (p==NULL)
	{
		printf("Przepraszam, taki element nie istnieje\n");
	}
	else if ( x < p->element)
	{
		del(x,p->left);
	}
	else if (x > p->element)
	{
		del(x,p->right);
	}
	else if ((p->left == NULL) && (p->right == NULL))
	{
		d=p;
		free(d);
		p=NULL;
		printf("Element zostal usuniety\n");
	}
	else if (p->left == NULL)
	{
		d=p;
		free(d);
		p=p->right;
		printf("Element zostal usuniety\n");
	}
	else if (p->right == NULL)
	{
		d=p;
		p=p->left;
		free(d);
		printf("Element zostal usuniety\n");
	}
	else
	{
		p->element = deletemin(p->right);
	}
}
 
int deletemin(nodeptr &p)
{
	int c;
	printf("Zostanie usuniety element minimalny\n");
	if (p->left == NULL)
	{
		c=p->element;
		p=p->right;
		return c;
	}
	else
	{
		c=deletemin(p->left);
		return c;
	}
}
void preorder(nodeptr p)
{
	if (p!=NULL)
	{
		printf("%d ", p->element);
		preorder(p->left);
		preorder(p->right);
	}
}
 

void inorder(nodeptr p)
{
	if (p!=NULL)
	{
		inorder(p->left);
		printf("%d ", p->element);
		inorder(p->right);
	}
}
 

void postorder(nodeptr p)
{
	if (p!=NULL)
	{
		postorder(p->left);
		postorder(p->right);
		printf("%d ", p->element);
	}
}
 
int max(int value1, int value2)
{
	return ((value1 > value2) ? value1 : value2);
}

int bsheight(nodeptr p)
{
	int t;
	if (p == NULL)
	{
		return 0;
	}
	else
	{
		t = p->height;
		return t;
	}
}
 
nodeptr srl(nodeptr &p1)
{
	nodeptr p2;
	p2 = p1->left;
	p1->left = p2->right;
	p2->right = p1;
	p1->height = max(bsheight(p1->left),bsheight(p1->right)) + 1;
	p2->height = max(bsheight(p2->left),p1->height) + 1;
	return p2;
}

nodeptr srr(nodeptr &p1)
{
	nodeptr p2;
	p2 = p1->right;
	p1->right = p2->left;
	p2->left = p1;
	p1->height = max(bsheight(p1->left),bsheight(p1->right)) + 1;
	p2->height = max(p1->height,bsheight(p2->right)) + 1;
	return p2;
}

nodeptr drl(nodeptr &p1)
{
	p1->left=srr(p1->left);
	return srl(p1);
}

nodeptr drr(nodeptr &p1)
{
	p1->right = srl(p1->right);
	return srr(p1);
}
 
int nonodes(nodeptr p)
{
	int count=0;
	if (p!=NULL)
	{
		nonodes(p->left);
		nonodes(p->right);
		count++;
	}
	return count;
}
 
int main()
{
		//clrscr();
	nodeptr root, root1, min, max;
	int a,choice,findele,delele;
		
 
	//system("clear");
	root = NULL;
	root1=NULL;
	printf("\tAVL Drzewo\n\n");
	
	
	do
	{
		
		printf("-> 1  Dodac nowy wezel\n");
		printf("-> 2  Znalezc element minimalny\n");
		printf("-> 3  Znalezc element maksymalny \n");
		printf("-> 4  Sprawdzic istnienie elementu\n");
		printf("-> 5  Usunac element\n");
		printf("-> 6  Sposob przejscia PRE-order\n");
		printf("-> 7  Sposob przejscia IN-order\n");
		printf("-> 8  Sposob przejscia POST-order\n");
		printf("-> 9  Pokazac wysokosc drzewa\n");
		printf("-> 0  Wyjscie\n");
		printf("\n(UWAGA PROGRAM DZIALA TYLKO Z LICZBAMI CALKOWITYMI)\n");
		
		printf("\nProsze wybrac jedno dzialanie z listy i nacisnac Enter: ");
		scanf("%d", &choice);
		
		switch(choice)
		{
			case 1:
				printf("\nDodanie nowego wezla");
				printf("\n");
				printf("Prosze wprowadzic element: ");
				scanf("%d", &a);
				insert(a,root);
				printf("\nNowy element zostal dodany\n");
				break;
			case 2:
				if (root !=NULL)
				{
					min=findmin(root);
					printf("\nElement minimalny drzewa: %d\n\n", min->element);
				}
				else
				printf("Drzewo jesze nie posiada zadnego elementu\n");
				break;
			case 3:
				if (root !=NULL)
				{
					max=findmax(root);
					printf("\nElement maksymalny drzewa: %d\n\n", max->element);
				}
				break;
			case 4:
				printf("\nProsze wprowadzic element, ktory trzeba sprawdzic: ");
				scanf("%d", &findele);
				if (root != NULL)
				{
					find(findele,root);
				}
				break;
			case 5:
				printf("\nProsze wprowadzic element, ktory trzeba usunac: ");
				scanf("%d", &delele);
				del(delele,root);
				inorder(root);
				printf("\n");
				break;
			case 6:
				printf("\nSposob przejscia PRE-order: ");
				preorder(root);
				printf("\n");
				break;
			case 7:
				printf("\nSposob przejscia IN-order: ");
				inorder(root);
				printf("\n");
				break;
			case 8:
				printf("\nSposob przejscia POST-order: ");	
				postorder(root);
				printf("\n");
				break;
			case 9:
				printf("\nWysokosc drzewa: %d\n" ,bsheight(root));
				break;
			case 0:
				printf("\nDziekuje za korzystanie z programu\n");
				break;
			default:
				printf("Blad! Prosze wybrac jeszcze raz\n");
				break;
		}
		system("pause");
		system("cls");
	}while(choice != 0);
	return 0;
}