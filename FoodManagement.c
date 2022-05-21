#include<stdio.h>
#include<string.h>
#include<stdlib.h>

//creating a structure for details about food items
struct Node
{
	char foodname[50];
	int quantity;
	float price;
	int foodID;
	struct Node *next;
};
typedef struct Node node ;
node *head;

//creating a structure for order details using customer ID
struct OrderNode
{
    int OrderId;
	int customerID;
    float totalAmount;
    int totalItems;
	node *fhead;
	struct OrderNode *next;
};
typedef struct OrderNode onode ;
onode *ohead,*olist;

//Declaring the functions
void DisplayCustomer();
void PrintCustomerName(int);
void foodlist();
void InsertEndOrder(node *fhead, int customerID, int orderId,int totalItems);

void PlaceOrder() 
{
    int customerID, orderId, totalItems, i, foodID, quantity;
    node *temp, *newnode,*flist, *ftemp;
    flist = NULL; //assigned null because it is locally declared
    DisplayCustomer();
    printf("\n\nEnter the customer id : ");
    scanf("%d", &customerID);
    orderId = rand(); //rand() is a function generates random integer included in header stdlib.h itself
    printf("Enter the total number of items  to be ordered by the customer : ");
    scanf("%d", &totalItems);
    if(totalItems <= 0)
    {
        printf("Invalid Total Items. Request you to enter total items properly.");
        getch();
        return;
    }
    for(i=0; i<totalItems;i++) //looping for number of times customer has to place order
    {
        printf("\n\nSelect from the below given Food List for Food Item %d: ", (i+1));
        foodlist();
        printf("\n\nEnter Food Item ID: ");
        scanf("%d", &foodID);
        printf("\nEnter the Quantity : ");
        scanf("%d", &quantity);
        temp = head;
        while(temp != NULL && temp->foodID != foodID)
        {
            temp = temp->next;
        }

        if(temp == NULL)
        {
            printf("Invalid food ID. Request you to enter proper food id. Please re-enter the details");
            i--;
            continue;
        }
        else if(temp->quantity < quantity)
        {
            printf("Insufficient Stock for the given food. Request you to re-enter the details");
            i--;
            continue;
        }
        else
        {
            
            newnode=(node *)malloc(sizeof(node));
            newnode->foodID = foodID;
            newnode->price = temp->price;
            newnode->quantity = quantity;
            strcpy(newnode->foodname,temp->foodname);
            newnode->next = NULL;
            
            if(flist==NULL)
            {               
                flist = newnode;                
            }
            else
            {
                ftemp = flist;
                while(ftemp->next != NULL)
                {
                    ftemp = ftemp->next;
                }
                ftemp->next = newnode;
                
            }
            
            temp->quantity = temp->quantity - quantity;            
        }
    }
    InsertEndOrder(flist, customerID, orderId,totalItems);
}
  
//creating a structure for customer details
struct CustomerNode
{
	char CustomerName[50];    
	int CustomerID;
	struct CustomerNode *next;
};
typedef struct CustomerNode cnode ;
cnode *chead,*clist;

//function for inserting order at the end using singly linked list
void InsertEndOrder(node *fhead, int customerID, int orderId,int totalItems)
{
    onode *temp, *temp1;
	temp=(onode *)malloc(sizeof(onode));
	temp->customerID = customerID;
	temp->OrderId = orderId;
    temp->totalItems = totalItems;
    temp->fhead = fhead;
	temp->next = NULL;
    
	if(ohead==NULL)
    {
		ohead = temp;
	}
	else
    {
        temp1 = ohead;
		while(temp1->next != NULL)
        {
			temp1 = temp1->next;
		}
		temp1->next = temp;
	}
    printf("\nOrder Added at the end Successfully with Order ID : %d", orderId);   
}

//function for displaying order details along with the total amount using TOTAL AMOUNT=Price per item* quantity
void DisplayOrder(int OrderId)
{
    onode *otemp;
    node *temp;
    if(ohead == NULL)
    {
        printf("No data present for the orders");
        return;
    }
    otemp = ohead;
    while(otemp != NULL && otemp->OrderId != OrderId)
    {
        otemp = otemp->next;
    }

    if(otemp == NULL)
    {
        printf("Order No. is not correct. Given Order ID not present in the order list : %d", OrderId);
        return;
    }
    else
    {
        printf("\n\n\nCustomer ID : %d", otemp->customerID);
        printf("\nCustomer Name : ");
        PrintCustomerName(otemp->customerID);
        printf("\nOrder ID : %d", otemp->OrderId);
        printf("\nNo. Of Items : %d", otemp->totalItems);
        printf("\nFood Item Order Details : \n");
        
        printf("\n\t\t"); 
        printf("_______________________________________________________________________________________"); 
        printf("\n\t\t"); 
        printf("|  Food ID.   |          Food Name  |            Price  |   Quantity   |     Amount    |"); 
        printf("\n\t\t"); 
        printf("----------------------------------------------------------------------------------------"); 

        float totalAmount = 0.0;
        temp = otemp->fhead;
        while(temp != NULL)
        {
            printf("\n\t\t"); 
            printf("|%12d |    %15.15s  |    %12.2f   |    %6d    |   %6.1f     |",temp->foodID,temp->foodname, temp->price, temp->quantity, temp->price*temp->quantity);
            printf("\n\t\t"); 
            printf("----------------------------------------------------------------------------------------");
            totalAmount += temp->price*temp->quantity;
            temp = temp->next ;
        }

        printf("\n\nTotal Bill Amount : %f Rs\n\n", totalAmount);

    }
	    
}

//function for inserting food items in the menu at the end using singly linked list
void insertend(int foodID, char foodname[25], int quantity, float price)
{
    node *temp, *list;
	temp=(node *)malloc(sizeof(node));
	temp->foodID = foodID;
	temp->price = price;
	temp-> quantity = quantity;
	strcpy(temp->foodname,foodname);
	temp->next = NULL;
	if(head==NULL)
    {
		head = temp;
	}
	else
    {
        list = head;
		while(list->next != NULL)
        {
			list = list->next;
		}
		list->next = temp;
	}
    printf("\nFood Item Added at the end Successfully");
    
}

//function for maintaining customer by inserting them at the end using singly linked list
void InsertEndCustomer(int CustomerID, char CustomerName[25])
{
    cnode *temp, *ctemp;
	temp=(cnode *)malloc(sizeof(cnode));
	temp->CustomerID = CustomerID;
	strcpy(temp->CustomerName,CustomerName);
	temp->next = NULL;
    ctemp = chead;
	if(chead==NULL)
    {
		chead = temp;		
	}
	else
    {
		while(ctemp->next != NULL)
        {
			ctemp = ctemp->next;
		}
		ctemp->next = temp;
	}
    printf("\nCustomer Added at the end Successfully");
}

//function for clear screen
void cls()
{
	system("cls");
}

//function for deleting a food item from the menu using the logic of deleting a specific node in singly linked list
void deletefood(int serial)
{
	node *temp;
	temp=(node *)malloc(sizeof(node));
	temp = head;
	if(temp->foodID != serial)
	{
		while(temp != NULL && temp->next->foodID != serial)
		{
			temp = temp->next;
		}
		if(temp != NULL && temp->next->foodID == serial)
		{
			temp->next = temp->next->next;
			cls();
			printf("\n\n\n\t\t\tDeleted Successfully \n\n\n"); 
		}
		else
		{
			printf("\n\n\n\n\t\t\tFood Item Not Found\n"); 
		}
		//head = temp ;
	}
	else
	{
		temp = temp->next;
		cls();
		printf("\n\n\n\t\t\tDeleted Successfully \n\n\n"); 
		head = temp ;		
	}
}

//function for updating a food item in the menu
void updatefood(int udata, int uquantity)
{
	node *temp;
	temp = head;
	while(temp!= NULL && temp->foodID!=udata)
	{
		temp = temp->next;
	}
	if(temp!= NULL && temp->foodID == udata)
	{
		temp->quantity = uquantity;
        printf("Food Quantity Updated Successfully...");
        return;
	}
    printf("Invalid Food Product ID. Please check and update again...");
}

//function for keeping a count of total food items present in menu
int countitem()
{
	node *temp;
	temp = head;
	int countitem=0;
	if(temp==NULL)
	{
		countitem = 0;
	}
	else
	{
		countitem = 1;
		while(temp->next != NULL)
		{
			countitem++;
			temp = temp->next;
		}
	}
	return countitem;
}

//creation of food items for maintaining in the menu
void CreateFoodItem()
{
    char foodItem[100];
    int foodID, qty;
    float price;
    cls();
    printf("\n\n\n\t\t\t\t\t\tAdministrator Screen\n\n\n\n\n");
    printf("Enter the Food Item Name : ");
    scanf(" %[^\n]%*c", foodItem);
    printf("Enter Food Item ID : ");
    scanf("%d", &foodID);
    printf("Enter Food Quantity : ");
    scanf("%d", &qty);
    printf("Enter Food Price : ");
    scanf("%f", &price);
    insertend( foodID, foodItem, qty, price);
    printf("\n\nThe Food Item Created Successfully...");
    getch();    
}

//'' for customer
void CreateCustomer()
{
    char CustomerName[100];
    int CustomerID;
    
    cls();
    printf("\n\n\n\t\t\t\t\t\tCustomer Creation Screen\n\n\n\n\n");
    printf("Enter the Customer Name : ");
    scanf(" %[^\n]%*c", CustomerName);
    printf("Enter Customer ID : ");
    scanf("%d", &CustomerID);
    
    InsertEndCustomer(CustomerID, CustomerName);
    printf("\n\nThe Customer Created Successfully...");
    getch();    
}

//to print customer's name while displaying the order details
void PrintCustomerName(int CustomerID)
{
    cnode *temp = chead;
    if(chead == NULL)
    {
        return;
    }
    else
    {
        while(temp!=NULL && temp->CustomerID != CustomerID)
        {
            temp = temp->next;
        }
        if(temp!=NULL)
        {
            printf("%s", temp->CustomerName);
        }
    }
}

//to display the menu
void foodlist()
{
	
	printf("\n\t\t");
     printf("\033[0;31m"); 
	printf("_______________________________________________________________________"); 
	printf("\n\t\t"); 
	printf("|  Food ID.   |          Food Name  |            Price  |   Quantity   |"); 
	printf("\n\t\t"); 
	printf("------------------------------------------------------------------------"); 
    printf("\033[0m"); 

	node *temp;
	temp = head;
	while(temp != NULL)
    {
         printf("\033[0;37m"); 
		printf("\n\t\t"); 
		printf("|%12d |    %15.15s  |    %12.2f   |    %6d    |",temp->foodID,temp->foodname, temp->price, temp->quantity);
		printf("\n\t\t"); 
		printf("------------------------------------------------------------------------");
         printf("\033[0m"); 
		temp = temp->next ;
    }
    
}

void existingmenu()
{
    insertend(120,"lays",1190,150);
    insertend(119,"kitkat",2998,200);
    insertend(118,"twix",1449,74);
    insertend(117,"honeybell",1000,240);
    insertend(116,"waffle",1109,85);
    insertend(115,"chocos",899,50);
    insertend(114,"britannia cake",1439,10);
    insertend(113,"lolipop",299,22);
    insertend(112,"sourcandy",699,55);
    insertend(111,"Brownie",230,170);
    insertend(110,"dairy milk",760,60);
    insertend(109,"Cheetos",700,800);
    insertend(108,"hideNseek",1500,55);
    insertend(107,"maggi",3000,11.09);
    insertend(106,"milano",7000,40);
    insertend(105,"yippee",2255,20);
    insertend(104,"Cookies",1500,15.15);
    insertend(103,"Parle-G",10,1000);
    insertend(102,"pringlees",500,200);
    insertend(101,"mentos",6000,250);
}

void existingcustomer()
{
    InsertEndCustomer(11,"Atharv");
    InsertEndCustomer(22,"Harsh");
    InsertEndCustomer(33,"Niraj");
}
//to display the details of the customer and their order details using their specific orderID
void DisplayCustomer()
{
	
	printf("\n\t\t"); 
	printf("______________________________________"); 
	printf("\n\t\t"); 
	printf("| Customer ID. |      Customer Name  |"); 
	printf("\n\t\t"); 
	printf("--------------------------------------"); 

	cnode *temp;
	temp = chead;
	while(temp != NULL)
    {
		printf("\n\t\t"); 
		printf("|%13d |    %15.15s  |",temp->CustomerID,temp->CustomerName);
		printf("\n\t\t"); 
		printf("--------------------------------------");
		temp = temp->next ;
    }
    
}

//logic for username and masked password to login
int CheckUserPassword()
{
    int x = 0, i, n;
    char  u2[20],  p2[20], ch; 

    char u1[] = {'a','b','c','1','2','3', '\0'};
    char p1[] = {'d','e','f','@','4','5','6','\0'};
    n = strlen(p1);

    printf("\n\nLOGIN");
    printf("\nUsername: ");
    scanf("%s", u2);
    
    if(strcmp(u1,u2) == 0)
    {
        while(x != 5)
        {
            i = 0;
            printf("ATTEMPT %d\nPassword: ", (x+1));
            for(i=0; i<n; i++)
            {
                ch = getch();
                p2[i] = ch;
                ch = '*' ;
                printf("%c", ch);
            }
            p2[i] = '\0';            
            if(strcmp(p1,p2) == 0)
            {
                printf("\nLOGIN SUCCESSFUL.\n\n");
                getch();
                return 1;
            }
            else
            {
                printf("\033[0;31m");
                printf("\nThe entered password is wrong. Please try again.\n");
                printf("\033[0m");
            }
            x++;
        }
    }
    else
    {
        printf("\nThe username entered is wrong. Please try again...\n");
    }
    return 0;
}

//main function for Admin where he/she can update,delete basically make changes in the menu by login in 
void ProcessAdminUser()
{
    
    int option, foodID, quantity;
    char ch;
    if(CheckUserPassword() == 0)
    {
         return;
    }
    do
    {
        cls();
        printf("\033[0;32m");
        printf("\n\n\n\t\t\t\t\t\tAdministrator Screen\n\n\n\n\n");
        printf("\033[0m");
        printf("\033[0;36m");
        printf("Select from the given option : ");
        printf("\n\n1.\tView Food Items");
        printf("\n2.\tEnter Food Item");
        printf("\n3.\tDelete a Food Item");
        printf("\n4.\tUpdate Quantity of a Food Item");
        printf("\n5.\tCount All the Food Items");
        printf("\n6.\tGo Back to Main Menu");
        printf("\033[0m");
        printf("\nYour Option : ");
        scanf("%d", &option);
        switch(option)
        {
            case 1 :
                foodlist();
                getch();
                break;
            case 2 :
                CreateFoodItem();
                break;
            case 3 :
                printf("Enter the Food Product ID to be deleted from the given list : ");
                foodlist();
                printf("\n\nYour Option for Food ID to be deleted :");
                scanf("%d", &foodID);
                deletefood(foodID);
                getch();
                break;
            case 4 :
                printf("Enter the Food Product ID to be Updated from the given list : ");
                foodlist();
                printf("\n\nYour Option for Food ID to be Updated :");
                scanf("%d", &foodID);
                printf("\nEnter the new quantity to be Updated :");
                scanf("%d", &quantity);
                updatefood(foodID, quantity);
                getch();
                break;
            case 5 :
                foodID = countitem();
                printf("The total number of Food Items are : %d", foodID);
                getch();
                break;
            case 6 :                
                break;
            default :
                printf("Invalid Option. Please select the option again.");
                getch();
                
        }
    } while(option != 6);
}

//main function for customer where function calling takes place using menu driven
void ProcessCustomer()
{
    int option, foodID, orderId;
    char ch;
    do
    {
        cls();
        printf("\033[0;32m");
        printf("\n\n\n\t\t\t\t\t\tCustomer Screen\n\n\n");
        printf("\033[0m");
        printf("\033[0;36m");
        printf("Select from the given option : ");
        printf("\n\n1.\tCreate Customer");
        printf("\n2.\tView Customer");
        printf("\n3.\tView Food Product Menu");
        printf("\n4.\tPlace Order");
        printf("\n5.\tView Order Details");
        printf("\n6.\tGo Back to Previous Menu");
        printf("\033[0m");
        printf("\nYour Option : ");
        scanf("%d", &option);
        switch(option)
        {
            case 1 :
                CreateCustomer();
                break;
            case 2 :
                DisplayCustomer();
                getch();
                break;     
            case 3 :
                foodlist();
                getch();
                break;     
            case 4 : 
                PlaceOrder();
                getch();
                break;  
            case 5 :
                printf("\nEnter the Order ID for Displaying Order : ");
                scanf("%d", &orderId);
                DisplayOrder(orderId);
                getch();
                break;
            case 6 :
                printf("\n\n\nThanks for using the Application.");
                getch();
                break;
            default :
                printf("Invalid Option. Please select the option again.");
                getch();                
        }
    } while(option != 6);
}

int main()
{
    int option;
    char ch;
    existingmenu();
    existingcustomer();
    do
    {
        cls();
        printf("\033[0;36m");
        printf("Select from the given option : ");
        printf("\n\n1.\tAdministrator");
        printf("\n2.\tCustomer");
        printf("\n3.\tExit");
        printf("\nYour Option : ");
        printf("\033[0m");
        scanf("%d", &option);
        switch(option)
        {
            case 1 :
                ProcessAdminUser();
                break;
            case 2 :
                ProcessCustomer();
                break;
            case 3 :
                printf("\n\n\nThanks for using the Application.");
                break;
            default :
                printf("Invalid Option. Please select the option again.");
                getch();                
        }
    } while(option != 3);
}