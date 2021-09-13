#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<ctype.h>
#define MAX 16

struct book_info
{
    char name[50];
    char author[50];
    int price;
};
typedef struct book_info Book;
char user(char x);
void authority();
void customer();
void userPassword();
void storeBook();
void viewBook();
void editBook();
Book takeInput();
void deleteBook();
void searchBook();

void update(Book b, int index,FILE*fp)
{
    fseek(fp,(index)*sizeof(Book),SEEK_SET);
    fwrite(&b,sizeof(Book),1,fp);
}

int main()
{
    int x , prefer;
    printf("               |====================================|\n");
    printf("               |                                    |\n");
    printf("               |             WELCOME TO             |\n");
    printf("               |          ONLINE BOOK STORE         |\n");
    printf("               |                                    |\n");
    printf("               |====================================|\n\n\n\n");
    prefer=user(x);
    switch(prefer)
    {
    case 'C':case 'c':
        {
        system("cls");
        customer();
        break;
        }
    case 'A': case 'a':
        {
        system("cls");
        userPassword();
        break;
        }
    default:
        {
        printf("You pressed wrong key.\n");
        }
    }
    return 0;
}
char user(char x)
{
    printf("\tyou are entering :\n");
    printf("\t\t1. As a customer.\n");
    printf("\t\t2. As authority.\n\n");
    printf("Please select your choice(C/A):");
    scanf("%c",&x);
    return x;
}
void userPassword()
{
    char buffer[256] = {0};
    char password[] = "12345";
    char c;
    int pos = 0;
    int pass = 0;
    printf("\n\n                      *****PASSWORD PROTECTED*****\n\n\n");
    printf("%s", "                    PLEASE ENTER PASSWORD:   ");
    do {
        c = getch();

        if( isprint(c) )
        {
            buffer[ pos++ ] = c;
            printf("%c", '*');
        }
        else if( c == 8 && pos )
        {
            buffer[ pos-- ] = '\0';
            printf("%s", "\b \b");
        }
    } while( c != 13 );

    if( !strcmp(buffer, password) )
        {
        printf("\n%s\n", "\n\n                         Have A Good Day :)");
        pass = 1;
        }
    else
        printf("\n%s\n", "\n\n                         Invalid Password!");
    if(pass)
    {
        printf ("\n LET'S START \n");
        authority();
    }

}
 void authority()
{
     int n;
     printf("1. Storage books.\n2. View book\n3. Search a book\n4. Delete a book\n5. Edit a book\n6. Exit\n\n");
     printf("Enter your choice:");
     scanf("%d",&n);
     switch(n)
     {
     case 1:
        system("cls");
        storeBook();
        break;
     case 2:
        system("cls");
        viewBook();
        break;
     case 3:
        system("cls");
        searchBook();
        break;
     case 4:
        system("cls");
        deleteBook();
        break;
     case 5:
        system("cls");
        editBook();
        break;
    case 6:
        break;
     default:
        printf("Sorry, you pressed wrong key.\n");
     }

}
void storeBook()
{
    FILE*fp=fopen("books.txt","ab");
    Book b=takeInput();
    fwrite(&b,sizeof(Book),1,fp);
    fclose(fp);
}
Book takeInput()
{
    Book b[MAX];
    fflush;
    printf("Enter name of book: ");
    scanf("%s", b[MAX].name);
    //gets(b[MAX].name);
    printf("Enter author of book: ");
    scanf("%s", b[MAX].author);
   // gets(b[MAX].author);
    printf("Enter price: ");
    scanf("%d", &b[MAX].price);
    system("cls");
}
void printBook(Book b)
{
    printf("Title: %s\tAuthor: %s\tPrice: %d\n",b.name,b.author,b.price);
}
void viewBook()
{
    Book b[MAX];
    FILE *fp = fopen("books.txt", "rb");
    int i=0;
    while(fread(&b[i],sizeof(Book),1,fp)!=0)
    {
        printBook(b[i]);
        i++;
    }
    fclose(fp) ;
}

void deleteBook()
{
    char name[20];
    int found=0;
    printf("Enter a name to delete:");
    scanf("%s",name);
    Book b[MAX];
    FILE*fp=fopen("books.txt","rb+");
    FILE*temp=fopen("temp.txt","wb");
    int i=0;
    while(fread(&b[i].name,sizeof(Book),1,fp)!=0)
    {
        if(strcmp(b[i].name,name)==0)
        {
            printf("The record has been deleted.\n\n");
            break;
        }
        else
        {
            fwrite(&b[i].name,sizeof(Book),1,temp);
        }
        i++;
    }
    fclose(fp);
    fclose(temp);
    if(found==0)
    {
        printf("No record(s) found\n");
        remove("temp.txt");
    }
    else
    {
        remove("books.txt");
        rename("temp.txt","books.txt");
    }
}
void searchBook()
{
    int found=0,i=0,index;
    char name[100];
    FILE*fp=fopen("books.txt","rb");
    printf("Enter a name to search:");
    getchar();
    gets(name);
    Book b[MAX];
    while(fread(&b[i],sizeof(Book),1,fp)!=0)
    {
        if(strcmp(b[i].name,name)==0)
        {
            index=i;
            found=1;
            break;
        }
        i++;
    }
    if(found==1)
    {
        printBook(b[index]);
    }
    else
    {
        printf("Not found.");
    }
    fclose(fp);
}
void editBook()
{
    int id,i=0,found=0,index;
    char title[60];
    Book b[MAX];
    FILE*fp=fopen("books.txt","rb");
    printf("Enter name to edit:");
    gets(title);
    while(fread(&b[i],sizeof(Book),1,fp)!=0)
    {
        if(strcmp(b[i].name,title)==0)
        {
            found=1;
            index=i;
            break;
        }
        i++;
    }
    if(found==0)
    {
        printf("Not found.");
    }
    else
    {
        Book b_new=takeInput();
        update(b_new,index,fp);
    }
    fclose(fp);
}

void customer()
{
    char title[20],writer[20];
    int copy,i=0,found=0,index;
    FILE*fp=fopen("books.txt","rb");
    fflush;
    printf("\tSearch the book you want to buy \n");
    printf("Enter name of book:");
    scanf("%s", title);
    //gets(title);
    printf("Enter the author name:");
    scanf("%s",writer);
   // gets(writer);
    Book b[MAX];
    while(fread(&b[i],sizeof(Book),1,fp)!=0)
    {
        if(strcmp(b[i].name,title)==0 && strcmp(b[i].author,writer)==0)
        {
            index=i;
            found=1;
            break;
        }
        i++;
    }
    if(found==1)
    {
        printf("Enter the copies:");
        scanf("%d",&copy);
        printf("Book name : %s\tAuthor: %s\tcopy : %d\tTotal price: %d",title,writer,copy,b[i].price*copy);
        customer();
    }
    else
    {
        printf("Not found.");
    }
    fclose(fp);
}

