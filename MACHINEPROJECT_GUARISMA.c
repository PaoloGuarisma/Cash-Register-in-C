#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

#define MAX_LENGTH 201
#define MAX_ITEMS 500

#define FILENAME "addedItems.txt"

typedef struct
{
	char itemName[MAX_LENGTH];
	double dPrice;
	int quantitysold;
} item;

typedef struct
{
	item items[MAX_ITEMS];
	int quantity[MAX_ITEMS];
}cart;

void addItem(item itemList[MAX_ITEMS], int *itemCount)
{
	item temporaryItem;
	
	system ("cls"); 
	fflush (stdin); 
	
	printf ("Enter new item name: ");
	scanf (" %s", temporaryItem.itemName);
	
	printf ("Enter price: ");
	scanf ("%lf", &temporaryItem.dPrice);
	
	itemList[*itemCount] = temporaryItem;
	itemList[*itemCount].quantitysold=0;
	
	*itemCount = *itemCount + 1;
	
	printf ("\n");
	printf ("New item added successfully.\n");
	system ("pause");
}

void viewItems(item itemList[MAX_ITEMS], int itemCount)
{
	int i;
	
	system("cls");
	
	for (i=0; i<itemCount; i++)
	{
		printf ("Item #%d:\n", i+1);
		printf ("Item name: %s\n", itemList[i].itemName);
		printf ("Price: %.2lf\n", itemList[i].dPrice);
		printf ("\n");
	}
	
	system ("pause");
}

void deleteItems (item itemList[MAX_ITEMS], int *itemCount)
{
	int index = 0, i; 
	char chIn;
	int bReturn = 0;
	
	do
	{
		if (*itemCount <= 0)
		{
			printf ("No items in the database.\n\n");
			system ("pause");
			return;
		}
		
		do
		{
			system ("cls");
			
			printf ("Delete which item?");
			printf ("\n\n");
			printf ("Item: %s\n", itemList[index].itemName);
			printf ("Price: %.2lf\n", itemList[index].dPrice);
			printf ("\n");
			printf ("[N]ext [P]rev [D]elete [R]eturn\n\n");
			chIn = getch(); 
		} while (chIn != 'n' && chIn != 'N' && chIn != 'p' && chIn != 'P' && chIn != 'd' && chIn != 'D' && chIn != 'r' && chIn != 'R');
		
		//Next 
		if (chIn == 'n' || chIn == 'N')
		{
			index++;
			if (index == *itemCount)
				index = 0;
		}
		//Prev
		else if (chIn == 'p' || chIn == 'P')
		{
			index--;
			if (index == -1)
				index = *itemCount - 1;
		}
		//Delete
		else if (chIn == 'd' || chIn == 'D')
		{
			printf ("\n");
			printf ("Are you sure? Y for yes, anything else for no: ");
			chIn = getch();
			
			if (chIn == 'Y' || chIn == 'y') //Delete Proper
			{
				for (i = index; i+1 < *itemCount; i++)
					itemList[i] = itemList[i + 1];
				*itemCount = *itemCount - 1;
					
				printf ("\n");
				printf ("Item deleted successfully!\n");
				getch ();
				
				if (index >= *itemCount)
					index = *itemCount - 1;
				
			}
		}
		//Return
		else if (chIn == 'r' || chIn == 'R')
			bReturn = 1;
	} while (!bReturn);
		
}

void saveContents(item itemList[MAX_ITEMS], int itemCount)
{
	/* Textfile format
		<Number of items>
		<Item Name 1>
		<Price of Item 1>
		...
		<Item Name N>
		<Price of Item N>
	*/
	
	FILE *pOut;
	
	int i;
	
	pOut = fopen (FILENAME, "wt");
	
	if (pOut != NULL)
	{
		fprintf (pOut, "%d\n", itemCount);
		for (i=0; i<itemCount; i++)
		{
			fprintf (pOut, "%s\n", itemList[i].itemName);
			fprintf (pOut, "%.2lf\n", itemList[i].dPrice);
		}
		fclose (pOut);
	}
	
	else 
		printf ("ERROR GENERATING %s. Please contact admin.\n", FILENAME);
}

void loadContents(item itemList[MAX_ITEMS], int *itemCount)
{
	FILE *pList;
	char strLine[MAX_LENGTH];
	int i;
	
	pList = fopen (FILENAME, "rt");
	
	if (pList != NULL) //There is a file
	{
		fgets(strLine, sizeof(strLine), pList);
		sscanf (strLine, "%d", &(*itemCount));
		
		for (i=0; i< *itemCount; i++)
		{
			//Item
			fgets (strLine, sizeof(strLine), pList);
			strLine[strlen(strLine)-1] = '\0';
			
			strcpy(itemList[i].itemName, strLine);
			
			
			//Cost
			fgets (strLine, sizeof(strLine), pList);
			sscanf(strLine, "%lf", &itemList[i].dPrice);
			itemList[i].quantitysold=0;
		}
	}
}

void purchaseItem (item itemList[MAX_ITEMS], int itemCount, int *i, cart *scart)
{
	int quantity;
	printf("Purchase which item: ");
	scanf("%d",&*i);
	if (*i<=itemCount && i>0)
	{
		printf ("Item name: %s\n", itemList[*i-1].itemName);
		printf ("Price: %.2lf\n", itemList[*i-1].dPrice);
		do {
			printf("How many: ");
			scanf("%d",&quantity);
			printf("Item added to cart!\n\n");
			system("pause");
		} while (quantity < 0);

		strcpy((*scart).items[*i-1].itemName, itemList[*i-1].itemName);
		scart->quantity[*i-1] = scart->quantity[*i-1] + quantity;
	}
	//cart
}

int main ()
{
	item itemList[MAX_ITEMS]; 
	int i, itemCount = 0, nInput, bExit = 0,itemNum;
	float total ,cash;
	float change;
	loadContents(itemList, &itemCount); 
	
	do
	{
		do
		{
			system("cls"); 
			printf ("Number of items in the database: %d\n", itemCount);
			printf ("\n");
			printf ("[1] - New Transaction\n\n\n");
			printf("*Admin Functions*\n\n");
			printf ("[2] - Generate report\n");
			printf ("[3] - Add Item\n");
			printf ("[4] - View Items\n");
			printf ("[5] - Delete Items\n");
			printf ("[6] - Exit\n\n"); 
			scanf ("%d", &nInput);
		} while (nInput > 6 || nInput < 1);
			if (nInput == 1)
			{
				cart scart;
				int option;
				
				for (i=0; i < MAX_ITEMS; i++)
					scart.quantity[i]=0;
				total=0;
				do {
				viewItems(itemList, itemCount);
				printf("[1] Purchase Item\n");
				printf("[2] Checkout\n");
				printf("[3] Cancel\n");
				printf("Choose an Option: ");
				scanf("%d",&option);
				if (option == 1)
				do {
					purchaseItem (itemList,itemCount,&itemNum, &scart);
					} while(itemNum < 0 || itemNum > itemCount);
				else if (option == 2)
				{
					system("cls");
					printf("Checkout\n");
					for (i=0;i<itemCount;i++)
					
					if (scart.quantity[i] > 0)
					{
						printf("Bought: %s\tQuantity: %d\tAmount: %.2lf\n",scart.items[i].itemName,scart.quantity[i],scart.quantity[i]*itemList[i].dPrice);
						total = scart.quantity[i]*itemList[i].dPrice + total;
						itemList[i].quantitysold = scart.quantity[i] + itemList[i].quantitysold;
					}
					
					printf("Total : %.2f\n",total);
					do{
					printf("Cash rendered: ");
					scanf("%f",&cash);
					if (cash < total)
						printf("Invalid! Please enter bigger amount\n");
					}while (cash < total);
					change=cash-total;
					system("cls");
					printf("Cash rendered: %.2f\n",cash);
					printf("Change: %.2f\n",change);
					printf("Thank you for shopping!!!\n\n");
					system("pause");
					option=3;		
				}
				else if  (option == 3)
				{
					printf("Cancel\n");	
				}
				}while (option != 3);
			}
		else if (nInput == 2)
		{
			char strPassword[strlen("Handsome")+1];
			strcpy(strPassword, "Handsome");

			char pass[20];
			printf("Enter password: ");
			scanf("%s", pass);
			if (strcmp (strPassword ,pass)==0 )
			{
				printf("\n");
				printf("Generate Report\n");
				
				for(i=0;i<itemCount;i++)
				if(itemList[i].quantitysold>0)
				{
					printf("Bought: %s\tQuantity: %d\tAmount: %.2lf\n",itemList[i].itemName,itemList[i].quantitysold,itemList[i].quantitysold*itemList[i].dPrice);
					system("pause");
				}
			}
			else
			{
				printf("Incorrect Password!\n\n");
				system("pause");
			}
		}
		
		else if (nInput == 3){
			char strPassword[strlen("Handsome")+1];
			strcpy(strPassword, "Handsome");

			char pass[20];
			printf("Enter password: ");
			scanf("%s", pass);
			if (strcmp (strPassword ,pass)==0 )
				addItem(itemList, &itemCount);
			else
			{
				printf("Incorrect Password!\n\n");
				system("pause");
			}
		}
		
		else if (nInput == 4)
		{
			char strPassword[strlen("Handsome")+1];
			strcpy(strPassword, "Handsome");

			char pass[20];
			printf("Enter password: ");
			scanf("%s", pass);
			if (strcmp (strPassword ,pass)==0 )
				viewItems(itemList, itemCount);
			else
			{
				printf("Incorrect Password!\n\n");
				system("pause");
			}
		}

		else if (nInput == 5){
			char strPassword[strlen("Handsome")+1];
			strcpy(strPassword, "Handsome");

			char pass[20];
			printf("Enter password: ");
			scanf("%s", pass);
			if (strcmp (strPassword ,pass)==0 )
				deleteItems(itemList,&itemCount);
			else
				printf("incorrect password\n\n");
				system("pause");
			
		}
		
		else if (nInput == 6)
		{
		
			system("cls");
			printf("Thank you for using the machine :)\n");
			printf("Have a good day ahead of you!\n");
			printf("\n\n");
			bExit = 1;
		}
		
	} while (!bExit);
	
	saveContents(itemList, itemCount);
	
	return 0;
}

