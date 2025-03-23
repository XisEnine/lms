#ifndef HASHTABLEBOOK_H
#define HASHTABLEBOOK_H

#include "bookStruct.h"

#define TABLE_SIZE 100

typedef struct BookBucket {
  BookDetails *head;
} BookBucket;

typedef struct TransactionBucket {
  BorrowTransaction *head;
} TransactionBucket;

// we use extern keyword to make it a global variable accross the other files in
// the same folder
extern BookBucket bookTable[TABLE_SIZE];
extern TransactionBucket transactionTable[TABLE_SIZE];

// hashkey generator.
static inline unsigned int hash(const char *key) {
  unsigned long hash = 5381;
  int c;
  while ((c = *key++)) {
    hash = ((hash << 5) + hash) + c; // hash * 33 + c
  }
  return hash % TABLE_SIZE;
}

// Admin Functions
void initTables();
void addBook(BookDetails *book);
int removeBook(const char *bookID);
int updateBook(const char *bookID);
void displayAllBooks();
void viewBorrowedBooksReport();

// Guest Functions
void addTransaction(BorrowTransaction *transaction);
BookDetails *findBook(const char *bookID);
BorrowTransaction *findTransaction(const char *tokenID);
void viewBookDetails(const char *bookID);
void borrowBook(BorrowTransaction *transaction);
int returnBook(const char *tokenID);
#endif
