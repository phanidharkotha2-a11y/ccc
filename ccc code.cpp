#include <stdio.h>
#include <string.h>

#define MAX 100

typedef struct {
    int id;
    char name[50];
    float marks;
} Student;

typedef struct {
    char username[20];
    char password[20];
    char role[10];
} User;

Student sList[MAX];
int count = 0;

/* STUDENT FUNCTIONS */
void addStudent() {
    if (count >= MAX) {
        printf("\nList full!\n");
        return;
    }
    printf("\nEnter ID: ");
    scanf("%d", &sList[count].id);
    printf("Enter Name: ");
    scanf("%s", sList[count].name);
    printf("Enter Marks: ");
    scanf("%f", &sList[count].marks);
    count++;
    printf("\nAdded successfully.\n");
}

void display() {
    if (count == 0) {
        printf("\nNo data.\n"); return;
    }
    printf("\nID\tName\tMarks\n");
    for (int i = 0; i < count; i++)
        printf("%d\t%s\t%.2f\n", sList[i].id, sList[i].name, sList[i].marks);
}

int searchIndex(int id) {
    for (int i = 0; i < count; i++)
        if (sList[i].id == id) return i;
    return -1;
}

void searchStudent() {
    int id;
    printf("\nEnter ID: ");
    scanf("%d", &id);
    int idx = searchIndex(id);

    if (idx == -1) printf("\nNot found.\n");
    else {
        printf("\nFOUND:\n");
        printf("ID: %d\nName: %s\nMarks: %.2f\n",
               sList[idx].id, sList[idx].name, sList[idx].marks);
    }
}

void updateStudent() {
    int id;
    printf("\nEnter ID to update: ");
    scanf("%d", &id);
    int idx = searchIndex(id);

    if (idx == -1) {
        printf("\nNot found.\n"); return;
    }
    printf("New Name: ");
    scanf("%s", sList[idx].name);
    printf("New Marks: ");
    scanf("%f", &sList[idx].marks);

    printf("\nUpdated.\n");
}

void deleteStudent() {
    int id;
    printf("\nEnter ID to delete: ");
    scanf("%d", &id);
    int idx = searchIndex(id);

    if (idx == -1) {
        printf("\nNot found.\n"); return;
    }
    for (int i = idx; i < count - 1; i++)
        sList[i] = sList[i + 1];
    count--;
    printf("\nDeleted.\n");
}

/* LOGIN */
int login(User u[], int n, User *in) {
    char un[20], pw[20];
    printf("\nUsername: "); scanf("%s", un);
    printf("Password: "); scanf("%s", pw);

    for (int i = 0; i < n; i++)
        if (!strcmp(un, u[i].username) &&
            !strcmp(pw, u[i].password)) {
            *in = u[i];
            return 1;
        }
    return 0;
}

/* MENUS */
void adminMenu() {
    int c;
    do {
        printf("\n=== ADMIN MENU ===\n");
        printf("1.Add\n2.Display\n3.Search\n4.Update\n5.Delete\n6.Logout\nChoice: ");
        scanf("%d", &c);

        switch (c) {
            case 1: addStudent(); break;
            case 2: display(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
        }
    } while (c != 6);
}

void staffMenu() {
    int c;
    do {
        printf("\n=== STAFF MENU ===\n");
        printf("1.Display\n2.Search\n3.Update\n4.Logout\nChoice: ");
        scanf("%d", &c);

        switch (c) {
            case 1: display(); break;
            case 2: searchStudent(); break;
            case 3: updateStudent(); break;
        }
    } while (c != 4);
}

void userMenu() {
    int c;
    do {
        printf("\n=== USER MENU ===\n");
        printf("1.Display\n2.Search\n3.Logout\nChoice: ");
        scanf("%d", &c);

        switch (c) {
            case 1: display(); break;
            case 2: searchStudent(); break;
        }
    } while (c != 3);
}

void guestMenu() {
    int c;
    do {
        printf("\n=== GUEST MENU ===\n");
        printf("1.Display\n2.Logout\nChoice: ");
        scanf("%d", &c);

        if (c == 1) display();
    } while (c != 2);
}

int main() {
    User u[] = {
        {"admin","admin123","ADMIN"},
        {"staff","staff666","STAFF"},
        {"guest","guest111","GUEST"},
        {"user","user123","USER"}
    };

    User curr;
    while (1) {
        if (!login(u, 4, &curr))
            printf("\nInvalid.\n");
        else {
            printf("\nLogged in as %s (%s)\n", curr.username, curr.role);
            if (!strcmp(curr.role, "ADMIN")) adminMenu();
            else if (!strcmp(curr.role, "STAFF")) staffMenu();
            else if (!strcmp(curr.role, "GUEST")) guestMenu();
            else userMenu();
        }
    }
}