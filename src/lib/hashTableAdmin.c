#include "../headerfile/MainHashTable.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

BookBucket bookTable[TABLE_SIZE];
TransactionBucket transactionTable[TABLE_SIZE];

// Initialize hash tables
void initTables() {
  for (int i = 0; i < TABLE_SIZE; i++) {
    bookTable[i].head = NULL;
    transactionTable[i].head = NULL;
  }
  printf("[System] Tables initialized.\n");
}

// Add a book to the book table
void addBook(BookDetails *book) {
  unsigned int index = hash(book->BookId);
  book->next = bookTable[index].head;
  bookTable[index].head = book;
  printf("[Admin] Book '%s' added.\n", book->title);
}

// Remove a book from the book table
int removeBook(const char *bookID) {
  unsigned int index = hash(bookID);
  BookDetails *current = bookTable[index].head;
  BookDetails *prev = NULL;

  while (current != NULL) {
    if (strcmp(current->BookId, bookID) == 0) {
      if (prev == NULL) {
        bookTable[index].head = current->next;
      } else {
        prev->next = current->next;
      }
      printf("[Admin] Book '%s' removed.\n", bookID);
      free(current);
      return 1;
    }
    prev = current;
    current = current->next;
  }

  printf("[Admin] Book '%s' not found.\n", bookID);
  return 0;
}

// Update book details
int updateBook(const char *bookID) {
  unsigned int index = hash(bookID);
  BookDetails *current = bookTable[index].head;

  while (current != NULL) {
    if (strcmp(current->BookId, bookID) == 0) {
      printf("Updating book: %s\n", bookID);

      printf("Title: ");
      scanf(" %[^\n]", current->title);

      printf("Author: ");
      scanf(" %[^\n]", current->author);

      printf("Category: ");
      scanf(" %[^\n]", current->category);

      printf("Quantity: ");
      scanf("%d", &current->quantity);

      printf("Total Copies: ");
      scanf("%d", &current->total_copies);

      printf("Book updated.\n");
      return 1;
    }
    current = current->next;
  }

  printf("Book not found.\n");
  return 0;
}

// Display all books in the book table
void displayAllBooks() {
  printf("\n[Admin] All Books:\n");
  for (int i = 0; i < TABLE_SIZE; i++) {
    BookDetails *current = bookTable[i].head;
    while (current != NULL) {
      printf("ID: %s | Title: %s | Author: %s | Qty: %d\n", current->BookId,
             current->title, current->author, current->quantity);
      current = current->next;
    }
  }
}

// View the borrowed books report
void viewBorrowedBooksReport() {
  printf("\n[Admin] Borrowed Books:\n");
  for (int i = 0; i < TABLE_SIZE; i++) {
    BorrowTransaction *current = transactionTable[i].head;
    while (current != NULL) {
      printf("Token: %s | Guest: %s | Book ID: %s | Due: %s\n",
             current->tokenID, current->guestName, current->bookID,
             current->dueDate);
      current = current->next;
    }
  }
}

// Alias for addBook
int insertBook(BookDetails *book) {
  addBook(book);
  return 1; // Always returns success for now
}

// Alias for removeBook
int deleteBook(const char *bookID) { return removeBook(bookID); }

// Search for a book by ID
BookDetails *searchBook(const char *bookID) {
  unsigned int index = hash(bookID);
  BookDetails *current = bookTable[index].head;

  while (current != NULL) {
    if (strcmp(current->BookId, bookID) == 0) {
      return current;
    }
    current = current->next;
  }
  return NULL; // Not found
}

// Traverse the book hash table
void traverseHashTable() {
  printf("\n[Admin] Traversing Hash Table:\n");
  for (int i = 0; i < TABLE_SIZE; i++) {
    BookDetails *current = bookTable[i].head;
    if (current != NULL) {
      printf("Index %d:\n", i);
      while (current != NULL) {
        printf("  -> ID: %s | Title: %s | Qty: %d\n", current->BookId,
               current->title, current->quantity);
        current = current->next;
      }
    }
  }
}

// Initialize only the book hash table
void initHashTable() {
  for (int i = 0; i < TABLE_SIZE; i++) {
    bookTable[i].head = NULL;
  }
  printf("[System] Book hash table initialized.\n");
}

// Alias for viewBorrowedBooksReport
void generateBorrowReport() {
  viewBorrowedBooksReport(); // Same as viewing borrowed books
}
