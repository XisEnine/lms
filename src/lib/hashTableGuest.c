#include "../headerfile/MainHashTable.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Add a borrow transaction
void addTransaction(BorrowTransaction *transaction) {
  unsigned int index = hash(transaction->tokenID);
  transaction->next = transactionTable[index].head;
  transactionTable[index].head = transaction;
  printf("[Guest] Transaction for '%s' added.\n", transaction->guestName);
}

// Find a book by ID
BookDetails *findBook(const char *bookID) {
  unsigned int index = hash(bookID);
  BookDetails *current = bookTable[index].head;

  while (current != NULL) {
    if (strcmp(current->BookId, bookID) == 0) {
      return current; // Found
    }
    current = current->next;
  }
  return NULL; // Not found
}

// Find a transaction by token ID
BorrowTransaction *findTransaction(const char *tokenID) {
  unsigned int index = hash(tokenID);
  BorrowTransaction *current = transactionTable[index].head;

  while (current != NULL) {
    if (strcmp(current->tokenID, tokenID) == 0) {
      return current; // Found
    }
    current = current->next;
  }
  return NULL; // Not found
}

// View book details
void viewBookDetails(const char *bookID) {
  BookDetails *book = findBook(bookID);
  if (book != NULL) {
    printf("\n[Guest] Book Details:\n");
    printf("ID: %s\nTitle: %s\nAuthor: %s\nCategory: %s\nAvailable: %d/%d\n",
           book->BookId, book->title, book->author, book->category,
           book->quantity, book->total_copies);
  } else {
    printf("[Guest] Book '%s' not found.\n", bookID);
  }
}

// Borrow a book
void borrowBook(BorrowTransaction *transaction) {
  BookDetails *book = findBook(transaction->bookID);
  if (book == NULL) {
    printf("[Guest] Book '%s' not available.\n", transaction->bookID);
    return;
  }

  if (book->quantity <= 0) {
    printf("[Guest] Book '%s' is out of stock.\n", book->title);
    return;
  }

  book->quantity -= 1; // Reduce available count
  addTransaction(transaction);
  printf("[Guest] Book '%s' borrowed. Due on %s\n", book->title,
         transaction->dueDate);
}

// Return a book
int returnBook(const char *tokenID) {
  unsigned int index = hash(tokenID);
  BorrowTransaction *current = transactionTable[index].head;
  BorrowTransaction *prev = NULL;

  while (current != NULL) {
    if (strcmp(current->tokenID, tokenID) == 0) {
      // Found transaction
      BookDetails *book = findBook(current->bookID);
      if (book != NULL) {
        book->quantity += 1; // Increase book count
      }

      // Remove transaction from hash table
      if (prev == NULL) {
        transactionTable[index].head = current->next;
      } else {
        prev->next = current->next;
      }
      free(current);
      printf("[Guest] Book returned successfully.\n");
      return 1; // Success
    }
    prev = current;
    current = current->next;
  }

  printf("[Guest] Transaction '%s' not found.\n", tokenID);
  return 0; // Failure
}
