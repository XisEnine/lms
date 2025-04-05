
#include "../headerfile/MainHashTable.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define ADMIN_PASSWORD "admin"
#define MAX_INPUT 256

void waitForEnter() {
  printf("\nPress Enter to continue...");
  getchar();
  while (getchar() != '\n')
    ; // Clear input buffer
}

int adminLogin() {
  char password[MAX_INPUT];
  printf("\n[Admin Login] Enter Password: ");
  scanf("%s", password);
  while (getchar() != '\n')
    ; // Clear input buffer

  if (strcmp(password, ADMIN_PASSWORD) == 0) {
    printf("[Access Granted] Welcome, Admin.\n");
    return 1;
  } else {
    printf("[Access Denied] Incorrect password.\n");
    return 0;
  }
}

void adminMenu() {
  int choice;
  char bookID[MAX_INPUT];
  BookDetails *book = NULL;

  do {
    printf("\n--- Admin Menu ---\n");
    printf("1. Add Book\n");
    printf("2. Remove Book\n");
    printf("3. Update Book\n");
    printf("4. Display All Books\n");
    printf("5. View Borrowed Books Report\n");
    printf("6. Back to Main Menu\n");
    printf("7. Exit\n"); // Added Exit option
    printf("Enter choice: ");
    scanf("%d", &choice);
    while (getchar() != '\n')
      ; // Clear input buffer

    switch (choice) {
    case 1:
      book = (BookDetails *)malloc(sizeof(BookDetails));
      if (!book) {
        printf("Memory allocation error.\n");
        waitForEnter();
        break;
      }
      memset(book, 0, sizeof(BookDetails)); // Initialize memory

      printf("Enter Book ID: ");
      scanf("%s", book->BookId);
      while (getchar() != '\n')
        ; // Clear input buffer

      printf("Enter Title: ");
      scanf("%s", book->title);
      while (getchar() != '\n')
        ; // Clear input buffer

      printf("Enter Author: ");
      scanf("%s", book->author);
      while (getchar() != '\n')
        ; // Clear input buffer

      printf("Enter Category: ");
      scanf("%s", book->category);
      while (getchar() != '\n')
        ; // Clear input buffer

      printf("Enter Quantity: ");
      if (scanf("%d", &book->quantity) != 1) {
        printf("Invalid input.\n");
        free(book);
        book = NULL;
        while (getchar() != '\n')
          ; // Clear input buffer
        waitForEnter();
        break;
      }
      while (getchar() != '\n')
        ; // Clear input buffer

      printf("Enter Total Copies: ");
      if (scanf("%d", &book->total_copies) != 1) {
        printf("Invalid input.\n");
        free(book);
        book = NULL;
        while (getchar() != '\n')
          ; // Clear input buffer
        waitForEnter();
        break;
      }
      while (getchar() != '\n')
        ; // Clear input buffer

      book->next = NULL;
      addBook(book);
      waitForEnter();
      break;

    case 2:
      printf("Enter Book ID to remove: ");
      scanf("%s", bookID);
      while (getchar() != '\n')
        ; // Clear input buffer
      removeBook(bookID);
      waitForEnter();
      break;

    case 3:
      printf("Enter Book ID to update: ");
      scanf("%s", bookID);
      while (getchar() != '\n')
        ; // Clear input buffer
      updateBook(bookID);
      waitForEnter();
      break;

    case 4:
      displayAllBooks();
      waitForEnter();
      break;

    case 5:
      viewBorrowedBooksReport();
      waitForEnter();
      break;

    case 6:
      printf("Returning to Main Menu.\n");
      break;

    case 7: // Exit option
      printf("Exiting system.\n");
      break;

    default:
      printf("Invalid choice.\n");
      waitForEnter();
    }
  } while (choice != 6 && choice != 7); // Exit condition updated
}

void guestMenu() {
  int choice;
  char bookID[MAX_INPUT];
  BorrowTransaction *transaction = NULL;
  char tokenID[MAX_INPUT];

  do {
    printf("\n--- Guest Menu ---\n");
    printf("1. View Book Details\n");
    printf("2. Print every Book.\n");
    printf("3. Borrow Book\n");
    printf("4. Return Book\n");
    printf("5. Back to Main Menu\n");
    printf("6. Exit\n"); // Added Exit option
    printf("Enter choice: ");
    scanf("%d", &choice);
    while (getchar() != '\n')
      ; // Clear input buffer

    switch (choice) {
    case 1:
      printf("Enter Book ID: ");
      scanf("%s", bookID);
      while (getchar() != '\n')
        ; // Clear input buffer
      viewBookDetails(bookID);
      waitForEnter();
      break;
    case 2:
      displayAllBooks();
      waitForEnter();
      break;
    case 3: {
      transaction = (BorrowTransaction *)malloc(sizeof(BorrowTransaction));
      if (!transaction) {
        printf("Memory allocation error.\n");
        waitForEnter();
        break;
      }
      memset(transaction, 0,
             sizeof(BorrowTransaction)); // Initialize memory

      time_t now = time(NULL);
      snprintf(transaction->tokenID, sizeof(transaction->tokenID), "T%ld", now);
      printf("Auto-generated Token ID: %s\n", transaction->tokenID);

      printf("Enter Guest Name: ");
      scanf("%s", transaction->guestName);
      while (getchar() != '\n')
        ; // Clear input buffer

      printf("Enter Phone Number: ");
      scanf("%s", transaction->phoneNumber);
      while (getchar() != '\n')
        ; // Clear input buffer

      printf("Enter Book ID to borrow: ");
      scanf("%s", transaction->bookID);
      while (getchar() != '\n')
        ; // Clear input buffer

      printf("Enter Book Title: ");
      scanf("%s", transaction->bookTitle);
      while (getchar() != '\n')
        ; // Clear input buffer

      struct tm *tm_now = localtime(&now);
      strftime(transaction->borrowDate, sizeof(transaction->borrowDate),
               "%Y-%m-%d", tm_now);

      time_t dueTime = now + (7 * 24 * 60 * 60);
      struct tm *tm_due = localtime(&dueTime);
      strftime(transaction->dueDate, sizeof(transaction->dueDate), "%Y-%m-%d",
               tm_due);

      transaction->next = NULL;
      borrowBook(transaction);
      waitForEnter();
      break;
    }

    case 4:
      printf("Enter Token ID to return book: ");
      scanf("%s", tokenID);
      while (getchar() != '\n')
        ; // Clear input buffer
      returnBook(tokenID);
      waitForEnter();
      break;

    case 5:
      printf("Returning to Main Menu.\n");
      break;

    case 6: // Exit option
      printf("Exiting system.\n");
      break;

    default:
      printf("Invalid choice.\n");
      waitForEnter();
    }
  } while (choice != 5 && choice != 6); // Exit condition updated
}

int main() {
  int choice;
  initTables();

  do {
    printf("\n===== Library Management System =====\n");
    printf("1. Admin Login\n");
    printf("2. Guest Access\n");
    printf("3. Exit\n");
    printf("Enter choice: ");
    scanf("%d", &choice);
    while (getchar() != '\n')
      ; // Clear input buffer

    switch (choice) {
    case 1:
      if (adminLogin())
        adminMenu();
      break;
    case 2:
      guestMenu();
      break;
    case 3:
      printf("Exiting system. Goodbye!\n");
      break;
    default:
      printf("Invalid choice.\n");
    }
  } while (choice != 3);

  return 0;
}
