// book and borrowTransaction structures
#ifndef BOOKSTRUCT_H
#define BOOKSTRUCT_H

typedef struct BookDetails {
    char BookId[20];
    char title[256];
    char author[256];
    char category[256];
    int quantity;
    int total_copies;
    struct BookDetails* next; // For chaining in hash table
} BookDetails;

typedef struct BorrowTransaction {
    char tokenID[20];
    char guestName[100];
    char phoneNumber[15];
    char bookID[20];
    char bookTitle[100];
    char borrowDate[20];  // Can use time.h for real date handling
    char dueDate[20];
    struct BorrowTransaction* next; // For chaining in hash table
} BorrowTransaction;

#endif // BOOKSTRUCT_H
