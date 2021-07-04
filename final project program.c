#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
void create(FILE *fptr);
void display(FILE *fptr);
int search(FILE *fptr, char *name);
void del(FILE *fptr);
void update(FILE *fptr);
struct contct
{
	char name[30];
	char phone[100];
	char mail[40];
	char add[50];
}obb;
int main()
{
	int choice,i;
	char name[80];
	FILE *fptr;
	fptr=fopen("contact.txt","rb+");
	if(fptr==NULL)
	{
	fptr=fopen("contact.txt","wb+");
	if(fptr==NULL)	
	{
		printf("Unable to create file.\n");
		exit(1);
	}
	}
	else
    {
    printf("\n\t\t\t\t'      Welcome to The Contact Management System.'\t\t\t");
    printf("\t\t\t\t      ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\t\t\n\n");
    printf("\t\t\t\t\t please kindly select the menu buttom?\n");
    printf("\t\t\t\t ______________________ ______________________\t\t\n\n");
    printf("\n \t 1. Add a contact. \n\t 2. List all contacts. \n \t 3. Search a contact. \n \t 4. Edit a contact. \n\t 5. Delete a contact.\n\t 6. Exit");    
	printf("\n\n\tEnter the choices from above.\n");
	scanf("%d",&choice);
	switch(choice)
	{
   
    case 1:            //to add a new contact
        printf("Your choice is to 'ADD A NEW CONTACT'.\n");
        create(fptr);
        break;
    case 2:           //for displaying all the saved contacts
        printf("Your choice is to 'LIST ALL CONTACTS'.\n\n");
        display(fptr);
        break;
     case 3:         //for searching the contact
        printf("Your choice is to 'SEARCH FOR A CONTACT'.\n\n");
        printf("Enter the name of the Person to be searched:  ");
        scanf("%s",&name);
        if(search(fptr,name)==1)
        {
        printf("\tName    :%s\n",obb.name);
        printf("\tPhone   :%s\n",obb.phone); 
        printf("\tAddress :%s\n",obb.add); 
        printf("\tE-mail  :%s\n\n",obb.mail);
        }
        break;
    case 4:      //for editing or modifying the contact
        printf("Your choice is to 'UPDATE A CONTACT'.\n\n");
        printf("Enter the name of the person to be edited.");
        scanf("%s",name);
        update(fptr);
        break;
    case 5:  //for deleting a contact 
        printf("Your choice is to 'DELETE A CONTACT'.\n\n");
        del(fptr);
        printf("Enter 1 to return to main menu 0 to exit.");
        scanf("%d",&choice);
         if(choice==1)
            main();
        else
            exit(1);
        break;
         case 6:                 //to exit the program
        printf("Are you sure you want to exit?");
        printf("\nEnter 1 to confirm.");
        scanf("%d",&choice);
        if(choice==1)
            exit(1);
            break;
    default:  //for default
        printf("Please select only from the number that is available in the options.\n\n\n");
        
	}
    } 
	
}
void create( FILE *fptr)
{
    int choice,i=1;
    printf("\n\nEnter the Name of the contact.\t");
    scanf("%s",&obb.name);
    while(i=1)
    {
    printf("\nEnter the Phone Number of the contact.+977 ");
    scanf("%s",&obb.phone);
    if(strlen(obb.phone)>10)
    printf("No are greater than 10\n");
    else if(strlen(obb.phone)<10)
     printf("No are less than 10\n");
    else
    break;
    }
    
  
	printf("\nEnter the Address of the contact.\t");
    scanf("%s",&obb.add);
    
	printf("\nEnter the E-mail of the contact.\t");
    scanf("%s",&obb.mail);
   
    fwrite(&obb,sizeof(obb),1,fptr) ;
    fclose(fptr);
   
    printf("\nContact created and saved successfully. :) \n");
    printf("\n\n\n");
    printf("Would you like to add more contacts?\n Enter 1 for adding more contacts 0 for main menu.");
    scanf("%d",&choice);
    if(choice==1)
    {
        create(fptr);
    } else if(choice==0)
    {
        main();
    }else
    {
        printf("You entered wrong choice.");
    }
    
}

void display(FILE *fptr)
{
    
    int choice;
   while(fread(&obb,sizeof(obb),1,fptr)==1)
   {
   
    printf("\tName   :%s\n",obb.name);
    printf("\tPhone  :+977 %s\n",obb.phone); 
    printf("\tAddress:%s\n",obb.add); 
    printf("\tE-mail :%s\n",obb.mail);
    printf("==================================\n");
}
    printf("\n");
       while(fread(&obb,sizeof(obb),1,fptr)==1)
        {
        printf("This is all your stored data.\n\n");
        printf("Press 1 to add a new contact and 0 to return to main menu.\n");
        scanf("%d",&choice);
        if(choice==1)
        {
		
            create(fptr);
        }
        else if(choice==0)
        
            main();
        else
            printf("Wrong choice");
    }
    fclose(fptr);
}
    

int search(FILE *fptr, char *name)
{
    int i=0;
    rewind(fptr);
    while(fread(&obb,sizeof(obb),1,fptr)==1)
    {
        if(strcmp(obb.name,name)==0)
        {
        printf("Contact name  :%s",obb.name);
        printf("contact number:%s",obb.phone);
        i=1;
        }
    }
    return i;
}


  void update(FILE *fptr)
{

   char name[15];
   long size= sizeof(obb);

   scanf("%s",name);
   if(search(fptr,name)==1)
   {
       printf("Enter new data to be stored.\n");
       printf("Enter the name to save.");
       scanf("%s",obb.name);
       printf("Enter the updated phone number.");
       scanf("%s",obb.phone);
       printf("Enter the updated Address.");
       scanf("%s",obb.add);
       printf("Enter the updated E-mail address.");
       scanf("%s",obb.mail);
       fseek(fptr,0,1);
       fwrite(&obb,sizeof(obb),1,fptr);
       printf("\n Contact updated successfully.");
   }
}

    



void del(FILE *fptr)
{
   FILE *fptrD;
   char name[15],cn[20];
   printf("Enter the name of the person to be deleted.");
    scanf("%s",name);
    if(search(fptr,name)==1)
    {
    fptrD=fopen("details.txt","wb");
    rewind(fptr);
    printf("Enter Phone no to be deleted:");
    scanf("%s",&cn);
    while(fread(&obb,sizeof(obb),1,fptr)==1)
        {
            if(strcmp(cn,obb.name)!=0)
        		fwrite(&obb,sizeof(obb),1,fptrD);
        }
        fclose(fptr);
        fclose(fptrD);
        remove("contact.txt");
        rename("details.txt","contact.txt");
        printf("Contact deleted successfully. :) ");
        fptr=fopen("contact.txt","rb+");
    }
    else
        printf("Contact Name not found");
      
} 

