# Project Details:

- **Name:** Library Management System
- **Team Members:**
    - Nauman Hasan
    - Swastik
    - Yuvraj Singh
    - Chandan 
- **Deadline:** 07/04/2025

## File Structure:

- **Makefile**
    - Contains the build instructions for compiling the project, managing dependencies, and creating the executable.

- **README.md**
    - Provides an overview of the project, installation instructions, usage guidelines, and any other relevant information for users and developers.

- **src/**
    - The main source directory containing all the code files.

    - **headerfile/**
        - **MainHashTable.h**
            - Header file that declares the functions and structures used for managing the hash table, including the hashing algorithm and functions for adding, removing, and searching for books.
        - **bookStruct.h**
            - Header file that defines the data structures used to represent books and transactions, including the `BookDetails` and `BorrowTransaction` structures.

    - **lib/**
        - **hashTableAdmin.c**
            - Contains the implementation of functions related to administrative tasks, such as adding, removing, and updating books in the library system.
        - **hashTableGuest.c**
            - Contains the implementation of functions related to guest interactions, such as borrowing and returning books, viewing book details, and generating reports.

    - **main/**
        - **main.c**
            - The entry point of the application. It contains the main function and implements the user interface, including the switch-case structure for navigating between admin and guest menus, handling user input, and invoking the appropriate functions from the library.

## Tree Structure:

```
.
├── Makefile
├── README.md
└── src
    ├── headerfile
    │   ├── MainHashTable.h
    │   └── bookStruct.h
    ├── lib
    │   ├── hashTableAdmin.c
    │   └── hashTableGuest.c
    └── main
        └── main.c
```

### Additional Notes:

- **Functionality Overview:**
    - The Library Management System will allow users to manage a collection of books, including adding new books, removing existing ones, updating book details, and tracking borrowed books. The system will have two user roles: admin and guest, each with specific functionalities.

- **Data Structures:**
    - The `BookDetails` structure will store information about each book, such as its ID, title, author, category, quantity, and total copies.
    - The `BorrowTransaction` structure will manage information related to borrowing transactions, including the token ID, guest name, book ID, borrow date, and due date.

- **Hashing Mechanism:**
    - The system will implement a hash table to efficiently store and retrieve book information, ensuring quick access and management of the library's collection.
---
