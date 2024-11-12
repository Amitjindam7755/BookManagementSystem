#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BOOKS 100
#define MAX_NAME_LENGTH 50
#define MAX_AUTHOR_LENGTH 50
#define MAX_CATEGORY_LENGTH 50

// Structure to represent a book
struct Book {
    int id;
    char name[MAX_NAME_LENGTH];
    char author[MAX_AUTHOR_LENGTH];
    float price;
    int rating;
    char category[MAX_CATEGORY_LENGTH];
};

struct Book books[MAX_BOOKS]; // Global array to store books
int numBooks = 0; // Variable to keep track of the number of books in the system

// Function prototypes
void addBook();
void removeBook(int bookID);
void searchBookByID(int bookID);
void searchBookByName(char *bookName);
void showAuthorsBooks(char *authorName);
void showCategoryBooks(char *category);
void updateBookData(int bookID);
void displaySortedBooksByPrice();
void displaySortedBooksByRating();
void displayAllBooks();

int main() {
    // Main menu
    int choice;
    do {
        printf("\nBook Management System\n");
        printf("1. Add Book\n");
        printf("2. Remove Book\n");
        printf("3. Search Book by ID\n");
        printf("4. Search Book by Name\n");
        printf("5. Show Author's Books\n");
        printf("6. Show Category's Books\n");
        printf("7. Update Book Data\n");
        printf("8. Display Sorted Books by Price\n");
        printf("9. Display Sorted Books by Rating\n");
        printf("10. Display All Books\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume newline character

        switch (choice) {
            case 1:
                addBook();
                break;
            case 2: {
                int id;
                printf("Enter Book ID to remove: ");
                scanf("%d", &id);
                removeBook(id);
                break;
            }
            case 3: {
                int id;
                printf("Enter Book ID to search: ");
                scanf("%d", &id);
                searchBookByID(id);
                break;
            }
            case 4: {
                char name[MAX_NAME_LENGTH];
                printf("Enter Book Name to search: ");
                fgets(name, MAX_NAME_LENGTH, stdin);
                name[strcspn(name, "\n")] = 0; // Remove trailing newline
                searchBookByName(name);
                break;
            }
            case 5: {
                char author[MAX_AUTHOR_LENGTH];
                printf("Enter Author Name: ");
                fgets(author, MAX_AUTHOR_LENGTH, stdin);
                author[strcspn(author, "\n")] = 0; // Remove trailing newline
                showAuthorsBooks(author);
                break;
            }
            case 6: {
                char category[MAX_CATEGORY_LENGTH];
                printf("Enter Category: ");
                fgets(category, MAX_CATEGORY_LENGTH, stdin);
                category[strcspn(category, "\n")] = 0; // Remove trailing newline
                showCategoryBooks(category);
                break;
            }
            case 7: {
                int id;
                printf("Enter Book ID to update: ");
                scanf("%d", &id);
                updateBookData(id);
                break;
            }
            case 8:
                displaySortedBooksByPrice();
                break;
            case 9:
                displaySortedBooksByRating();
                break;
            case 10:
                displayAllBooks();
                break;
            case 0:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 0);

    return 0;
}

// Function to add a new book
void addBook() {
    if (numBooks >= MAX_BOOKS) {
        printf("Cannot add more books. Database is full.\n");
        return;
    }

    struct Book newBook;

    printf("Enter Book ID: ");
    scanf("%d", &newBook.id);
    getchar(); // Consume newline character

    printf("Enter Book Name: ");
    fgets(newBook.name, MAX_NAME_LENGTH, stdin);
    newBook.name[strcspn(newBook.name, "\n")] = 0; // Remove trailing newline

    printf("Enter Author Name: ");
    fgets(newBook.author, MAX_AUTHOR_LENGTH, stdin);
    newBook.author[strcspn(newBook.author, "\n")] = 0; // Remove trailing newline

    printf("Enter Price: ");
    scanf("%f", &newBook.price);

    printf("Enter Rating: ");
    scanf("%d", &newBook.rating);
    fflush(stdin);
    printf("Enter Category: ");
    fgets(newBook.category, MAX_CATEGORY_LENGTH, stdin);
    newBook.category[strcspn(newBook.category, "\n")] = 0; // Remove trailing newline

    books[numBooks++] = newBook;
    printf("Book added successfully.\n");
}

// Function to remove a book by its ID
void removeBook(int bookID) {
    int found = 0;
    for (int i = 0; i < numBooks; i++) {
        if (books[i].id == bookID) {
            found = 1;
            for (int j = i; j < numBooks - 1; j++) {
                books[j] = books[j + 1];
            }
            numBooks--;
            printf("Book removed successfully.\n");
            break;
        }
    }
    if (!found) {
        printf("Book not found.\n");
    }
}

// Function to search for a book by its ID
void searchBookByID(int bookID) {
    int found = 0;
    for (int i = 0; i < numBooks; i++) {
        if (books[i].id == bookID) {
            found = 1;
            printf("Book found:\n");
            printf("ID: %d\n", books[i].id);
            printf("Name: %s\n", books[i].name);
            printf("Author: %s\n", books[i].author);
            printf("Price: %.2f\n", books[i].price);
            printf("Rating: %d\n", books[i].rating);
            printf("Category: %s\n", books[i].category);
            break;
        }
    }
    if (!found) {
        printf("Book not found.\n");
    }
}

// Function to search for a book by its name
void searchBookByName(char *bookName) {
    int found = 0;
    for (int i = 0; i < numBooks; i++) {
        if (strcmp(books[i].name, bookName) == 0) {
            found = 1;
            printf("Book found:\n");
            printf("ID: %d\n", books[i].id);
            printf("Name: %s\n", books[i].name);
            printf("Author: %s\n", books[i].author);
            printf("Price: %.2f\n", books[i].price);
            printf("Rating: %d\n", books[i].rating);
            printf("Category: %s\n", books[i].category);
            break;
        }
    }
    if (!found) {
        printf("Book not found.\n");
    }
}

// Function to show books written by a specific author
void showAuthorsBooks(char *authorName) {
    printf("Books by %s:\n", authorName);
    int found = 0;
    for (int i = 0; i < numBooks; i++) {
        if (strcmp(books[i].author, authorName) == 0) {
            found = 1;
            printf("ID: %d, Name: %s\n", books[i].id, books[i].name);
        }
    }
    if (!found) {
        printf("No books found for this author.\n");
    }
}

// Function to show books of a specified category
void showCategoryBooks(char *category) {
    printf("Books in category %s:\n", category);
    int found = 0;
    for (int i = 0; i < numBooks; i++) {
        if (strcmp(books[i].category, category) == 0) {
            found = 1;
            printf("ID: %d, Name: %s\n", books[i].id, books[i].name);
        }
    }
    if (!found) {
        printf("No books found in this category.\n");
    }
}

// Function to update book data (price and rating) by its ID
void updateBookData(int bookID) {
    int found = 0;
    for (int i = 0; i < numBooks; i++) {
        if (books[i].id == bookID) {
            found = 1;
            printf("Enter new Price: ");
            scanf("%f", &books[i].price);
            printf("Enter new Rating: ");
            scanf("%d", &books[i].rating);
            printf("Book data updated successfully.\n");
            break;
        }
    }
    if (!found) {
        printf("Book not found.\n");
    }
}

// Comparator function for sorting books by price
int compareByPrice(const void *a, const void *b) {
    struct Book *bookA = (struct Book *)a;
    struct Book *bookB = (struct Book *)b;
    return (int)(bookA->price - bookB->price);
}

// Comparator function for sorting books by rating
int compareByRating(const void *a, const void *b) {
    struct Book *bookA = (struct Book *)a;
    struct Book *bookB = (struct Book *)b;
    return bookB->rating - bookA->rating;
}

// Function to display sorted books by price
void displaySortedBooksByPrice() {
    if (numBooks == 0) {
        printf("No books in the database.\n");
        return;
    }
    struct Book sortedBooks[MAX_BOOKS];
    memcpy(sortedBooks, books, sizeof(struct Book) * numBooks);
    qsort(sortedBooks, numBooks, sizeof(struct Book), compareByPrice);
    printf("Books sorted by price:\n");
    for (int i = 0; i < numBooks; i++) {
        printf("Name: %s, Price: %.2f\n", sortedBooks[i].name, sortedBooks[i].price);
    }
}

// Function to display sorted books by rating
void displaySortedBooksByRating() {
    if (numBooks == 0) {
        printf("No books in the database.\n");
        return;
    }
    struct Book sortedBooks[MAX_BOOKS];
    memcpy(sortedBooks, books, sizeof(struct Book) * numBooks);
    qsort(sortedBooks, numBooks, sizeof(struct Book), compareByRating);
    printf("Books sorted by rating:\n");
    for (int i = 0; i < numBooks; i++) {
        printf("Name: %s, Rating: %d\n", sortedBooks[i].name, sortedBooks[i].rating);
    }
}

// Function to display details of all the books in the database
void displayAllBooks() {
    if (numBooks == 0) {
        printf("No books in the database.\n");
        return;
    }
    printf("All Books:\n");
    for (int i = 0; i < numBooks; i++) {
        printf("ID: %d, Name: %s, Author: %s, Price: %.2f, Rating: %d, Category: %s\n", 
               books[i].id, books[i].name, books[i].author, books[i].price, 
               books[i].rating, books[i].category);
    }
}
