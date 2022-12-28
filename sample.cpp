// LIBRARY MANAGEMENT

#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include<stdbool.h> 


#define maxlenghth 1000 
struct date {
    int day;
    int month;
    int year;

}borrow, giveback, distance;

struct book {
    int ID_book;
    char name_book[100];
    float prices;
    date import;
    char location[30];
    int amount;
 
};
 struct person {
     int ID_person;
     char name_person[30];
 }p;

 void menu();
 // big function
 void headMessage();
 void EXPORT_lIST_BOOK_FROM_FILE();
 void GET_NEW_IN4_BOOK();
 void EDIT_IN4_BOOK();
 void DELETE_IN4_BOOK();
 void MAXnMIN_PRICES(book* ls, int n);
 void SEARCH_IN4_BOOK(int n, book* ls);
 void BORROW_GIVEBACK_BOOK(); 
 void SAVING(book list[maxlenghth], int current);


 // small function
 int create_array_book(book list[maxlenghth], int current);
 void strcline(char source[], char dest[], int len);
 void show_list_book(book* ls, int n);
 int search_ID_book(book* ls, int n, int ID);
 void insert_list_book(book* ls, int n, int pos);
 int delete_ID_book(book* ls, int n, int pos);
 void distanceofday();

 // smaller function;
 int append_list_book(book* ls, int n, book A);
 book get_a_book_in4();
 void show_a_in4(book A);
 bool leapyear(int year);
 void amount_of_book(book* ls, int n, book a);
 

 int main() {
     headMessage();
     menu();
     
    

 }


void menu() { // sử dụng switch case.
    int choice = 0;
    do
    {

        printf("\n\n\n\t\t\t MENU:");
        printf("\n\t\t\t1.EXPORT LIST BOOK FROM FILE");
        printf("\n\t\t\t2.GET NEW INFORMATION OF BOOK");
        printf("\n\t\t\t3.EDIT INFORMATION OF BOOK");
        printf("\n\t\t\t4.DELETE INFORMATION OF BOOK");
        printf("\n\t\t\t5.MAX AND MIN PRICES");
        printf("\n\t\t\t6.SEARCH IN4 BOOK ");
        printf("\n\t\t\t7.BORROW AND GIVEBACK BOOK");
        printf("\n\t\t\t0.Exit");
        printf("\n\n\n\t\t\tEnter choice => ");
        scanf_s("%d", &choice);
        book list[maxlenghth]; int current = 0;
        current = create_array_book(list, current);
        
        switch (choice)
        {
        case 1:
            printf("\n1.EXPORT LIST BOOK FROM FILE\n\n");
            EXPORT_lIST_BOOK_FROM_FILE();
            break;
        case 2:
            printf("\n2.GET NEW INFORMATION OF BOOK\n\n");;
            GET_NEW_IN4_BOOK();
            
            break;
        case 3:
            printf("\n3.EDIT INFORMATION OF BOOK\n\n");
            EDIT_IN4_BOOK();
         
            break;
        case 4:
            printf("\n4.DELETE INFORMATION OF BOOK\n\n");
            DELETE_IN4_BOOK();
           
            break;
        case 5:
            printf("\n5.MAX AND MIN PRICES\n\n");
            MAXnMIN_PRICES(list, current);
            
            break;
        case 6:
            printf("\n6.SEARCH IN4 BOOK\n");
            SEARCH_IN4_BOOK(current, list);
           
            break;
        case 7:
            printf("\n7.BORROW AND GIVEBACK BOOK\n");
            BORROW_GIVEBACK_BOOK();
            
            break;
         
        case 0:
            printf("\n\n\n\t\t\t\tThank you!!!\n\n\n\n\n");
            exit(1);
            break;
        default:
            printf("\n\n\n\t\t\tINVALID INPUT!!! Try again...");
        }
    } while (choice != 0);
}

// big function 

void headMessage()
{

    printf("\t\t\t###########################################################################");
    printf("\n\t\t\t############                                                   ############");
    printf("\n\t\t\t############      Library management System Project in C       ############");
    printf("\n\t\t\t############                                                   ############");
    printf("\n\t\t\t###########################################################################");
    printf("\n\t\t\t---------------------------------------------------------------------------\n");

}
void EXPORT_lIST_BOOK_FROM_FILE() {

    printf(" ***LIST BOOK IN FILE***\n");

    book list[maxlenghth]; int current = 0;

    current = create_array_book(list, current);
   
    show_list_book(list, current);// show dsach book trong file
}// function trong menu
void GET_NEW_IN4_BOOK() {
    book list[maxlenghth]; int current = 0;
    current = create_array_book(list, current);


    // inserting new book


    int req; // req là request

    printf("\nNumber of book you want insert :"); scanf_s("%d", &req);
    for (int i = 0; i < req; i++) {

        book a = get_a_book_in4();


        current = append_list_book(list, current, a);    
    }


    printf("\n\n");
    show_list_book(list, current); 


    printf("\nDo you want to save(y/n) ?");
    char flag[10];
    getchar();
    scanf_s("%s", flag,10);
    if (*flag == 'y') {
        SAVING(list, current);

    }

   
}
void EDIT_IN4_BOOK() {
    book list[maxlenghth]; int current = 0;
    current = create_array_book(list, current);
 

    printf("\nInsert ID Book you want to change :");

    int add_ID; scanf_s("%d", &add_ID);



    int pos = search_ID_book(list, current, add_ID); //pos=position

    if (pos >= 0)
    {
        insert_list_book(list, current, pos);
    }
    // show list after editing list book



    printf("\nINSERTED BOOKS:\n");
    show_list_book(list, current);


    printf("\nDo you want to save(y/n) ?");
    char flag[10];
    getchar();
    scanf_s("%s", flag, 10);
    if (*flag == 'y') {
        SAVING(list, current);

    }

}
void DELETE_IN4_BOOK() {
    book list[maxlenghth]; int current = 0;
    current = create_array_book(list, current);
    // delete in4 of a book
    printf("\nInsert ID Book you want to change :");
    int ID; scanf_s("%d", &ID);
    int position = search_ID_book(list, current, ID);

    if (position >= 0) {

        current = delete_ID_book(list, current, ID);
    }
    // show list after editing list book



    printf("INSERTED BOOKS:\n");
    show_list_book(list, current);


    printf("\nDo you want to save(y/n) ?");
    char flag[10];
    getchar();
    scanf_s("%s", flag, 10);
    if (*flag == 'y') {
        SAVING(list, current);

    }

    
}
void MAXnMIN_PRICES(book* ls, int n) {
    book list[maxlenghth]; int current = 0;
    current = create_array_book(list, current);
    
    float max = 0;
    
    for (int i = 0; i < n; i++) {
        if (max< ls[i].prices) {

            max = ls[i].prices;
        }
    }
    float min = ls[0].prices;
    for (int i = 0; i < n; i++) {
        
        if (min > ls[i].prices) {

            min = ls[i].prices;

        }
    }
   
    printf("\nTHE HIGHEST PRICES OF BOOK : %f", max);
    printf("\nTHE CHEAPEST PRICES OF BOOK : %f", min);
}
void SEARCH_IN4_BOOK(int n, book* ls) {
    book list[maxlenghth]; int current = 0;
    current = create_array_book(list, current);
    printf("\Insert the ID book you want more information:");

    int ID;  scanf_s("%d", &ID);


    for (int i = 0; i < n; i++) {
        if (ls[i].ID_book == ID)
        {
            show_a_in4(ls[i]);
        }
    }





}
void BORROW_GIVEBACK_BOOK() {
    book list[maxlenghth]; int current = 0;
    current = create_array_book(list, current);

    book a;
    printf("What your name?"), getchar(); scanf_s("%s", &p.name_person,30);
    printf("What your ID?"), scanf_s("%d", &p.ID_person);

    printf("What ID book you want to borrow?"), scanf_s("%d", &a.ID_book);

    
    distanceofday();


    amount_of_book(list, current,a);


    printf("\nDo you want to save(y/n) ?");
    char flag[10];
    getchar();
    scanf_s("%s", flag, 10);
    if (*flag == 'y') {
        SAVING(list, current);

    }
    


}
void SAVING(book list[maxlenghth],int current) {
   
    
   
    FILE* f;
    errno_t err;
    
    char filename[] = "finalexam.txt";
    err = fopen_s(&f,filename, "w");


    
    if (!err) {

        fprintf(f, "%d\n", current);
        
        for ( int i=0; i < current; i++) {
            // save elements
            fprintf(f, "%d\n", list[i].ID_book);
            fprintf(f, "%s\n", list[i].name_book);
            fprintf(f, "%f\n", list[i].prices);
            fprintf(f, "%d\n", list[i].import.day);
            fprintf(f, "%d\n", list[i].import.month);
            fprintf(f, "%d\n", list[i].import.year);
            fprintf(f, "%s\n", list[i].location);
            fprintf(f, "%d\n", list[i].amount);
        }


    }
    fclose(f);
   
}




// small function

int create_array_book(book list[maxlenghth], int current) {
    FILE* f;
    errno_t err;
    char filename[] = "finalexam.txt"; 


    err = fopen_s(&f, filename, "r");

    if (!err) { 

        char str[256];
        fgets(str, 256, f);
        int num_book = atoi(str);

        for (int i = 0; i < num_book; i++) {
            book exist;
            char line[256];
            fgets(line, 256, f);exist.ID_book = atoi(line);


            fgets(line, 256, f);char name_book[100];
            int len = strlen(line);
            strcline(line, name_book, len - 1);
            strcpy_s(exist.name_book, name_book);


            fgets(line, 256, f); exist.prices = atof(line);
            fgets(line, 256, f); exist.import.day = atoi(line);
            fgets(line, 256, f); exist.import.month = atoi(line);
            fgets(line, 256, f); exist.import.year = atoi(line);
            fgets(line, 256, f); char bookshelf[30];
            int len2 = strlen(line);
            strcline(line, bookshelf, len2 - 1);
            strcpy_s(exist.location, bookshelf);

            fgets(line, 256, f); exist.amount = atoi(line);

            current = append_list_book(list, current, exist); /// 
           
        }
    }
    fclose(f);
    return(current);
}
void strcline(char source[], char dest[], int len)
{
    int i = 0;
    for (i = 0; i < len; i++)
        dest[i] = source[i];
    dest[i] = '\0';
}
void show_list_book(book* ls, int n) {

    printf("\n****SHOW EXISTING LIST OF BOOK IN LIBRARY****");


    for (int i = 0; i < n; i++) { 
        printf("\n\nBook number %d:", i + 1);


        show_a_in4(ls[i]);
    }

}
int search_ID_book(book* ls, int n, int ID) {
    for (int i = 0; i < n; i++) {

        if (ls[i].ID_book == ID)
        {
            return i;
        }
    }
    return -1;// return -1 when no book has reqired ID
}
void insert_list_book(book* ls, int n, int pos) {
    if (pos < maxlenghth) {
        printf(" \nCurrent information of book %d \n", n);

        show_a_in4(ls[pos]);

        printf("\nInsert updated information \n ");

        book a = get_a_book_in4();
        ls[pos] = a;
    }
}
int delete_ID_book(book* ls, int n, int pos) {
    if (pos < n) {
        for (int i = pos; i < n; i++)
            ls[i] = ls[i + 1];
    }
    n--;
    return n;
}
void distanceofday() {

    
  
    printf("Day of borrowing: "); fflush(stdin); scanf_s("%d %d %d", &borrow.day, &borrow.month, &borrow.year); fflush(stdin);
    printf("Day of giveback: "); fflush(stdin); scanf_s("%d %d %d", &giveback.day, &giveback.month, &giveback.year); fflush(stdin);
    distance.day = distance.month = distance.year = 0;


    int i;

    /* Tinh khoang cach so ngay giua 2 nam */
    for (i = borrow.year; i < giveback.year; i++)
        if (leapyear(i) == true) {
            distance.year += 366;
        } //////
        else
        {
            distance.year += 365;
        }


    /* Tinh khoang cach so ngay giua 2 thang */
    int dayofmonth[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
    if (leapyear(giveback.year) == true)
    {
        dayofmonth[1] = 29;
    }         
    if (borrow.month > giveback.month)
    {
        for (i =giveback.month; i < borrow.month; i++)
            distance.month -= dayofmonth[i - 1];
    }
    else
    {
        for (i = borrow.month; i < giveback.month; i++)
            distance.month += dayofmonth[i - 1];
    }


    
    distance.day = giveback.day - borrow.day + 1;       
    int  result = distance.year + distance.day + distance.month;

    printf("Number of day from borrowing-day to giveback-day: %d", result);


  
}



// smaller function
int append_list_book(book* ls, int n, book A) {
    if (n < maxlenghth) {
        
        ls[n] = A;
        
        n++;

    }
    else {

        printf("The number of book is over than maximun");

    }
    return n;
}

book get_a_book_in4() {
    book a;

    printf("\n*************GET NEW BOOK INFORMATION************\n");
    printf("ID_BOOK:  "); fflush(stdin); scanf_s("%d", &a.ID_book);
    printf("NAME BOOK:  "); fflush(stdin); getchar(); scanf_s("%s", &a.name_book, 30);
    printf("PRICES:  "); fflush(stdin); scanf_s("%f", &a.prices);
    printf("PUBLIC DAY: "); fflush(stdin); scanf_s("%d %d %d", &a.import.day, &a.import.month, &a.import.year);
    printf("LOCATION:  "); fflush(stdin); getchar(); scanf_s("%s", &a.location, 30);
    printf("AMOUNT: "); scanf_s("%d", &a.amount);
    return a;

}

void show_a_in4(book A) {


    printf("\n%-20s %-20s %-20s %-20s %-20s %-20s\n", " ID_BOOK", "NAME_BOOK", "PRICES OF BOOK", "LOCATION", "PUCLIC DAY", "AMOUNT");
    printf("%-20d %-20s %-20f %-20s %-d/%d/%d %15d", A.ID_book, A.name_book, A.prices,A.location ,A.import.day, A.import.month, A.import.year, A.amount);

}

bool leapyear(int year) {
   
    if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0))
    {
        return true;
    }
    else
        return false;
}

void amount_of_book(book* ls, int n, book a) {
    for (int i = 0; i < n; i++) {

        if (ls[i].ID_book == a.ID_book) {

            printf("\nNow, library has %d book ",ls[i].amount);
            
            ls[i].amount = ls[i].amount - 1;
            
            printf("\nAfter, you borrow a book, library has %d", ls[i].amount);

            book a = {ls[i].ID_book,*ls[i].name_book,ls[i].import.day, ls[i].import.month, ls[i].import.year,*ls[i].location,ls[i].amount};
            
            show_a_in4(ls[i]);
           


             
           
        }
    }
}




