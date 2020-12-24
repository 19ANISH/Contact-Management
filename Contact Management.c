#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
void insert_contact();
void edit_contact();
void delete_contact();
void display_contact();

struct contact
{
    char phone[11];
    char NAME[15];
    char surname[15];
};
struct contact c;
void main()
{
    int ch;
    //Ch is choice
    while(ch!=5)
    {
    //printf("\n1. Display Existing Contact");
    printf("\n1.Insert Contact");
    printf("\n2.Edit Contact");
    printf("\n3.Delete Contact");
    printf("\n4.Exit\n");
    scanf("%d",&ch);
    switch(ch)
    {
        /*case 1:
        display_contact();
        break;*/
        case 1:
        insert_contact();
        break;
        case 2:
        edit_contact();
        break;
        case 3:
        delete_contact();
        break;
        case 4: exit(1);
        default:
        printf("\nWrong Input Try Again\n\t:)");
    }
    }
}
//HERE WE WILL INSERET CONTACT//
void insert_contact()
{
    display_contact();

    FILE *filePointer;
    filePointer=fopen("Contact.txt","ab+");
    if(filePointer==NULL)
    {

        printf("\nError: IN OPENING FILE\a");
        return;
    }
    printf("\nEnter Name:\t\a");
    scanf("%s",c.NAME);
    printf("\nEnter Surname:\t\a");
    scanf("%s",c.surname);
    printf("\nEnter Phone number:\t\a");
    scanf("%s",c.phone);
    fwrite(&c,sizeof(c),1,filePointer);
    {
        printf("\nContact Saved\a");
    }
    fclose(filePointer);
}
void display_contact()
{
    FILE *filePointer;
    filePointer=fopen("Contact.txt","rb");
    if(filePointer==NULL)
    {
        printf("\nError In Opening File");
        return;
    }
    printf("\nExisting Contacts In Phonebook");
    printf("\nName\t\t\t Phone Number\n");
    while(fread(&c,sizeof(c),1,filePointer)==1)
    {
        printf("%s %s\t\t\t %s\n",c.NAME,c.surname,c.phone);
    }
    fclose(filePointer);

}
//HERE WE WILL EDIT THE CONTACT//
void edit_contact()
{
    display_contact();
    int flag=0;
    char no[50];
        FILE *filePointer;
        filePointer=fopen("Contact.txt","rb+");
        if(filePointer==NULL)
        {
            printf("\nError in opening file");
            return;
        }
        printf("\nEnter Name:\t\a");
        scanf("%s",no);
        while(fread(&c,sizeof(c),1,filePointer)>0&&flag==0)
        {

            if(strcmp(c.NAME,no)==0)
            {

                    flag=1;
                    printf("\nEdit Contact\n\t\a");
                    fflush(stdin);
                    printf("\nUpdate Name:\t\a");
                    scanf("%s",c.NAME);
                    printf("\nUpdate Surname:\a\t");
                    scanf("%s",c.surname);
                    printf("\nUpdate Number:\t\a");
                    scanf("%s",c.phone);
                    fseek(filePointer,-(long)sizeof(c),1);
                    fwrite(&c,sizeof(c),1,filePointer);
                    printf("\nYour Contact is Updated Successfully");

            }
            if(flag==0)
            {
            printf("There Is No Such Contact In System");
            return;
            }
        }
        fclose(filePointer);

}
//HERE WE DELETE THE CONTACT//
void delete_contact()
{
    display_contact();
     char a[15];
     unsigned flag=0;
     FILE *filePointer, *fileTemp;
     filePointer=fopen("Contact.txt","rb");
     //   fileTemp=fopen("ContactN.txt","ab+");
     if(filePointer==NULL)
     {
         printf("\nError In Opening File");
         return;
     }
     printf("\nEnter Name:\t");
     scanf("%s",a);
     fileTemp=fopen("ContactN.txt","ab+");
     while(fread(&c,sizeof(c),1,filePointer)==1)
     {
         if(strcmp(a,c.NAME)!=0)
         {
             printf(" ");
             fwrite(&c,sizeof(c),1,fileTemp);

         }else
            flag=1;
     }

     if(flag==0)
     {
         printf("\nThere is No Such Contact\a");
     }
     else
     {
         printf("\nContact Deleted Successfully");
     }
     fclose(filePointer);
     fclose(fileTemp);
     remove("Contact.txt");
     rename("ContactN.txt","Contact.txt");
}
