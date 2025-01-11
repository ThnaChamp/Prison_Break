#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define MAX_Prisoner 800
#define KEY "Prisonbreak" // Key สำหรับการ Sign Up

int n = 0, m = 0, x = 0, f = 0, mlevel = 0;
char datefood[100][80];

typedef struct
{
    int id;
    int day;
    char name[50];
    char surname[50];
    int age;
    float height;
    float weight;
    char hairColor[20];
    char eyeColor[20];
    char nationality[30];
    char crime[100];
    char level[20];
    char lawyerName[50];
    char lawyerContact[20];
    int merit;
    int oldday;
} Prisoner;

typedef struct
{
    char dateStart[100];
    int day;
    char name[100];
    char surname[100];
    float height;
    float weight;
    char hairColor[100];
    char eyeColor[100];
    char nationality[100];
    char crime[500];
    char lawyerName[100];
    char lawyerContact[100];
    int age;
    char level[100];
    int merit;
    int id;
    int oldday;
    char allergy[100];
    char status[100];
} newPrison;

typedef struct
{
    char food[20];
    char ingredient1[20];
    char ingredient2[20];
    char ingredient3[20];
} Food;

Food list[40] = {
    {"Pizza", "Cheese", "Tomato", "Basil"},
    {"Sandwich", "Bread", "Ham", "Lettuce"},
    {"Salad", "Lettuce", "Tomato", "Cucumber"},
    {"Spaghetti", "Pasta", "Tomato", "Garlic"},
    {"Sushi", "Rice", "Seaweed", "Fish"},
    {"Burger", "Bun", "Beef", "Lettuce"},
    {"Soup", "Water", "Carrot", "Potato"},
    {"FriedRice", "Rice", "Egg", "Carrot"},
    {"Pancake", "Flour", "Milk", "Egg"},
    {"Omelette", "Egg", "Cheese", "Onion"},
    {"Steak", "Beef", "Salt", "Pepper"},
    {"Curry", "Chicken", "CoconutMilk", "CurryPowder"},
    {"Tacos", "Tortilla", "Beef", "Lettuce"},
    {"Burrito", "Tortilla", "Rice", "Beans"},
    {"Nachos", "CornChips", "Cheese", "Jalapeno"},
    {"Falafel", "Chickpeas", "Garlic", "Parsley"},
    {"Biryani", "Rice", "Chicken", "Spices"},
    {"Quesadilla", "Tortilla", "Cheese", "Chicken"},
    {"Hotdog", "Sausage", "Bun", "Mustard"},
    {"Lasagna", "Pasta", "Cheese", "TomatoSauce"},
    {"Casserole", "Potato", "Cheese", "Ham"},
    {"SpringRolls", "RicePaper", "Carrot", "Cabbage"},
    {"PadThai", "Noodles", "Tofu", "Peanuts"},
    {"Paella", "Rice", "Seafood", "Saffron"},
    {"Ramen", "Noodles", "Pork", "Egg"},
    {"TunaSandwich", "Bread", "Tuna", "Mayonnaise"},
    {"Chili", "Beef", "Beans", "Tomato"},
    {"FishAndChips", "Fish", "Potato", "Salt"},
    {"StirFry", "Noodles", "Chicken", "Broccoli"},
};

newPrison person[MAX_Prisoner];

#define MAX_USERNAME_LENGTH 500
#define MAX_PASSWORD_LENGTH 12
#define DATA_FILE "user_data.txt" // ไฟล์สำหรับบันทึกข้อมูลเข้าสู่ระบบ

// เพิ่ม prototype ของ function เพื่อแก้ปัญหาการอ้างอิงก่อนประกาศ
void fileUpdate(const char *filename, int prisonerID);
void prisonMapShown(int prisonFloor[50][50]);
int roomCheck(int rows, int cols, int prisonMap[50][50]);
void prisonMapInput(int prisonMap[50][50]);
void changeRoomStatus(int prisonMap[50][50]);
void PrisonMap(int prisonFloor[50][50]);
int loadPrisonMap(int prisonMap[50][50], const char *filename);
int savePrisonMap(int prisonMap[50][50], const char *filename);
void printHeader();
void printFooter();
void menu();
void signUp();
void key();
int newlogin();
void EntryPrisoner();
void printstartDate(char *startDate);
int releaseDate(int day);
void prisonerEntry();
void textFile();
void ReadtextFile();
void meritPoint();
void Decrease();
void Increase();
void textFile1();
void overView();
void seeDetails(int num);
void selectPrisonerforSeedetails();
void seeAllPrisoner();
void seeAllPrisonerMerit();
void calculateStats(int data[], int n, int *sum, float *avg, int *min, int *max);
void rangeAge(int age[]);
void level(char data[][20], int *low, int *moderate, int *high);
void stat();
void search();
void TimeReduct(int id);
void TimeReductMinus(int id);
void allergy();
void getInput();
void WriteFood();
void ReadFood();
void randomFood();
void filter();
void searchfilter(int count, const char *filterType, const char *filterValue, float min_weight, float max_weight, float min_height, float max_height);

int main()
{
    printHeader();
    int choice;
    printf("Sign Up [1]\nLogin   [2]\n");
    while (1)
    {
        printf("Enter your choice: ");
        scanf("%d", &choice);
        if (choice == 1)
        {
            key();
            break;
        }
        else if (choice == 2)
        {
            if (newlogin())
            {
                printf("\033[1;32mLogin successful!\033[0m\n");
                break;
            }
            else
            {
                printf("\033[1;31mLogin failed! Username or password incorrect.\033[0m\n");
            }
        }
        else
        {
            while (getchar() != '\n')
                ;
            printf("\033[1;31mInvalid choice.\033[0m Please enter \033[1;36m1\033[0m or \033[1;36m2\033[0m.\n");
        }
    }
    ReadtextFile();
    int option = 0;
    int prisonFloor[50][50] = {{0, 0, 0, 0, 0, 0, 0, 0, 0},
                               {0, 0, 0, 0, 0, 0, 0, 0, 0},
                               {0, 0, 0, 0, 0, 0, 0, 0, 0},
                               {0, 0, 0, 0, 0, 0, 0, 0, 0},
                               {0, 0, 0, 0, 0, 0, 0, 0, 0},
                               {0, 0, 0, 0, 0, 0, 0, 0, 0},
                               {0, 0, 0, 0, 0, 0, 0, 0, 0},
                               {0, 0, 0, 0, 0, 0, 0, 0, 0},
                               {0, 0, 0, 0, 0, 0, 0, 0, 0},
                               {0, 0, 0, 0, 0, 0, 0, 0, 0}};
    while (1)
    {
        menu();
        scanf("%d", &option);

        if (option == 1) // Entry New Prisoner
        {
            printf("\033[0;35m--------------------------------\033[0m");
            printf("\033[1;35m\n       Entry New Prisoner\n\033[0m");
            printf("\033[0;35m--------------------------------\n\033[0m");
            EntryPrisoner();
        }
        else if (option == 2) // Prisoners Overview
        {
            printf("\033[0;35m--------------------------------\033[0m");
            printf("\033[1;35m\n       Prisoners Overview\n\033[0m");
            printf("\033[0;35m--------------------------------\n\033[0m");
            overView();
        }
        else if (option == 3) // Search Prisoners
        {
            printf("\033[0;35m--------------------------------\033[0m");
            printf("\033[1;35m\n       Search Prisoners\n\033[0m");
            printf("\033[0;35m--------------------------------\n\033[0m");
            search();
        }
        else if (option == 4) // Prison Map Management
        {
            printf("\033[0;35m--------------------------------\033[0m");
            printf("\033[1;35m\n     Prison Map Management\n\033[0m");
            printf("\033[0;35m--------------------------------\n\033[0m");
            PrisonMap(prisonFloor);
        }
        else if (option == 5) // Merit Points
        {
            printf("\033[0;35m--------------------------------\033[0m");
            printf("\033[1;35m\n          Merit Points\n\033[0m");
            printf("\033[0;35m--------------------------------\n\033[0m");
            meritPoint();
        }
        else if (option == 6) // Prisoner Allergy
        {
            printf("\033[0;35m--------------------------------\033[0m");
            printf("\033[1;35m\n       Prisoner Allergy\n\033[0m");
            printf("\033[0;35m--------------------------------\n\033[0m");
            allergy();
        }
        else if (option == 7) // Logout
        {
            printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
            printf("\033[1;32mLogout Success.\033[0m\n");
            while (1)
            {
                if (newlogin())
                {
                    printf("\033[1;32mLogin successful!\033[0m\n");
                    break;
                }
                else
                {
                    printf("\033[1;31mLogin failed! Username or password incorrect.\033[0m\n");
                }
            }
        }
        else if (option == 8) // Exit Program
        {
            printFooter();
            break;
        }
        else
        {
            printf("\033[1;33mInvalid option.1 Please select a number between 1 and 8.\033[0m\n");
        }
    }

    return 0;
}

// Basic function
void printHeader()
{
    // printf("");
    printf("\n\n\033[1;34m================================\033[0m\n");
    printf("\033[1;37m    Prison Management System\033[0m\n");
    printf("\033[1;34m================================\033[0m\n");
}

void printFooter()
{
    printf("\033[1;34m================================\033[0m\n");
    printf("\033[1;37m  Thanks for using the system!\033[0m\n");
    printf("\033[1;34m================================\033[0m\n");
}

void key() // Check Key for Signup
{
    char key[100];
    while (1)
    {
        printf("Enter Key: ");
        scanf("%s", key);
        if (strcmp(key, KEY) == 0)
        {
            signUp();
            break;
        }
        else
        {
            printf("\033[1;31mKey not match!!\033[0m\n");
            continue;
        }
    }
}

// Add up
void signUp()
{
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    char checkPassword[MAX_PASSWORD_LENGTH];
    FILE *file;

    // // Prompt for user input
    printf("Enter a username: ");
    scanf("%s", username);
    while (1)
    {

        printf("Enter a password: ");
        scanf("%s", password);
        printf("Confirm password: ");
        scanf("%s", checkPassword);
        if (strcmp(password, checkPassword) != 0)
        {
            printf("\033[0;33mPasswords do not match. Try again.\033[0m\n");
        }
        else
        {
            break;
        }
    }

    // Open file to append new user data
    file = fopen(DATA_FILE, "a");
    if (file == NULL)
    {
        perror("Error opening file");
        return;
    }

    // Save username and password to file
    fprintf(file, "%s %s\n", username, password);
    fclose(file);

    printf("\033[0;32mSign-up successful! \033[0mYou can now log in.\n");
}

int newlogin()
{
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    char fileUsername[MAX_USERNAME_LENGTH];
    char filePassword[MAX_PASSWORD_LENGTH];
    FILE *file;

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    file = fopen(DATA_FILE, "r");
    if (file == NULL)
    {
        perror("Error opening file");
        return 0;
    }

    int found = 0; // Track if a match is found
    while (fscanf(file, "%s %s", fileUsername, filePassword) != EOF)
    {
        if (strcmp(username, fileUsername) == 0 && strcmp(password, filePassword) == 0)
        {
            found = 1; // Found matching username and password
            break;
        }
    }

    fclose(file);

    if (found)
    {
        return 1; // Login successful
    }
    else
    {
        return 0; // Login failed
    }
}

void menu()
{
    printf("\n\033[1;37m------ Welcome to Program ------\033[0m\n");
    printf("\n\033[1;36mMain Menu:\033[0m\n");
    printf("  Entry New Prisoner  [1]\n");
    printf("  Prisoner Overview   [2]\n");
    printf("  Search Prisoner     [3]\n");
    printf("  Prison Map Manage   [4]\n");
    printf("  Merit Points        [5]\n");
    printf("  Prisoner Allergy    [6]\n");
    printf("  Logout              [7]\n");
    printf("  Exit Program        [8]\n\n");
    printf("Enter the Menu: ");
}

// Prison Map function
void PrisonMap(int prisonFloor[50][50])
{ // รับพารามิเตอร์ prisonFloor
    int modeCheck = 0;

    if (!loadPrisonMap(prisonFloor, "prisonmap.txt"))
    {
        printf("Error: Could not load prison map.\n");
    }

    while (1)
    { // Infinite loop to keep program running until 'EXIT' is entered
        printf("\nMenu:\n");
        printf("  View all rooms      [1]\n");
        printf("  Check specific room [2]\n");
        printf("  Change room status  [3]\n");
        printf("  Back to Main Menu   [4]\n\n");
        printf("Enter the Menu: ");
        scanf("%d", &modeCheck);

        switch (modeCheck)
        {
        case 1:
            prisonMapShown(prisonFloor); // View all rooms
            break;
        case 2:
            prisonMapInput(prisonFloor); // Check specific room
            break;
        case 3:
            changeRoomStatus(prisonFloor); // Change room status
            break;
        case 4:
            savePrisonMap(prisonFloor, "prisonmap.txt"); // Save Map to file "prisonmap.txt"
            printf("\033[0;35m--------------------------------\n\033[0m");
            return;
        default:
            printf("\033[0;33mInvalid option. Please enter 1, 2, 3 or 4.\n\033[0m");
        }
    }
}

int savePrisonMap(int prisonMap[50][50], const char *filename)
{
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        return 0; // Failed to open file
    }

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            fprintf(file, "%d ", prisonMap[i][j]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
    return 1; // Successfully saved map
}

int loadPrisonMap(int prisonMap[50][50], const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        return 0; // Failed to open file
    }

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            fscanf(file, "%d", &prisonMap[i][j]);
        }
    }

    fclose(file);
    return 1; // Successfully loaded map
}

void fileUpdate(const char *filename, int prisonerID)
{
    FILE *inputFile = fopen(filename, "r");
    FILE *tempFile = fopen("temp.txt", "w+");
    char line[256];
    int tempPrisonerID, tempRoomNumber;

    if (inputFile == NULL || tempFile == NULL)
    {
        printf("Error opening file.\n");
        if (inputFile)
            fclose(inputFile);
        if (tempFile)
            fclose(tempFile);
        return;
    }

    // คัดลอกเฉพาะบรรทัดที่ไม่ต้องการลบไปยังไฟล์ชั่วคราว
    while (fgets(line, sizeof(line), inputFile))
    {
        if (sscanf(line, "Room: %d | Prisoner ID: %d", &tempRoomNumber, &tempPrisonerID) == 2)
        {
            if (tempPrisonerID != prisonerID)
            {
                fputs(line, tempFile); // เขียนบรรทัดที่ไม่ต้องการลบลงในไฟล์ชั่วคราว
            }
        }
    }

    fclose(inputFile); // ปิดไฟล์ input ก่อนจะเขียนใหม่

    // เปิดไฟล์เดิมในโหมดเขียนใหม่ แล้วเขียนข้อมูลจากไฟล์ชั่วคราว
    inputFile = fopen(filename, "w");
    if (inputFile == NULL)
    {
        printf("Error opening file for writing.\n");
        fclose(tempFile);
        return;
    }

    // ตั้งตำแหน่งของ tempFile กลับไปที่จุดเริ่มต้น
    fseek(tempFile, 0, SEEK_SET);

    // คัดลอกข้อมูลจาก tempFile กลับไปยัง inputFile
    while (fgets(line, sizeof(line), tempFile))
    {
        fputs(line, inputFile);
    }

    fclose(inputFile);
    fclose(tempFile);
}

void prisonMapShown(int prisonFloor[50][50])
{
    printf("\nDisplaying:\n");
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            printf("%d0%d: %s  ", i, j, prisonFloor[i][j] == 0 ? "\033[1;32mO\033[0m" : "\033[1;31mX\033[0m");
        }
        printf("\n");
    }
}

int roomCheck(int rows, int cols, int prisonMap[50][50])
{
    int roomNumber = rows * 100 + cols;
    FILE *file;
    char buffer[256];
    int found = 0;

    if (prisonMap[rows][cols] == 0)
    {
        printf("Status Room: ");
        printf("\033[1;34mRoom Available\033[0m\n");
        return 0;
    }
    else
    {
        printf("Status Room: ");
        printf("\033[1;31mRoom Full\033[0m\n");

        // Open the occupiedRooms.txt file to find prisoner details for this room
        file = fopen("occupiedRooms.txt", "r");
        if (file == NULL)
        {
            printf("Error: Unable to open file.\n");
            return -1;
        }

        // Search for the specific room number and display the prisoner details
        while (fgets(buffer, sizeof(buffer), file) != NULL)
        {
            int fileRoomNumber;
            int prisonerID;
            char name[50], surname[50], crime[100];

            // Parse the line to get the room number and prisoner details
            if (sscanf(buffer, "Room: %d | Prisoner ID: %d | Name: %s %s | Crime: %s",
                       &fileRoomNumber, &prisonerID, name, surname, crime) == 5)
            {
                if (fileRoomNumber == roomNumber)
                {
                    printf("\n---- Prisoner Details ----\n");
                    printf("Prisoner_ID    : %d\n", prisonerID);
                    printf("Prisoner_Name  : %s %s\n", name, surname);
                    printf("Prisoner_Crime : %s\n\n", crime);
                    found = 1;
                    break;
                }
            }
        }
        fclose(file);

        if (!found)
        {
            printf("No prisoner details found for room %d.\n", roomNumber);
        }

        return 1;
    }
}

void prisonMapInput(int prisonMap[50][50])
{
    int roomNumber, row, col, mode;

    while (1)
    {
        printf("Enter room number (e.g., 504): ");
        scanf("%d", &roomNumber);
        if (roomNumber >= 0 && roomNumber <= 909)
        {
            break;
        }
        else
        {
            printf("\033[0;33mInvalid. Please enter 000 to 909.\n\033[0m");
        }
    }

    row = roomNumber / 100;
    col = roomNumber % 10;

    if (row >= 0 && row < 10 && col >= 0 && col < 10)
    {
        roomCheck(row, col, prisonMap);

        printf("Press 0 to change status\nPress 1 to Exit\n");
        printf("Enter: ");
        scanf("%d", &mode);

        switch (mode)
        {
        case 0:
            changeRoomStatus(prisonMap);
            break;
        case 1:
            return;
        default:
            printf("\033[0;33mInvalid option. Returning to main menu.\n\033[0m");
        }
    }
    else
    {
        printf("Invalid room number, Try again.\n");
    }
}

void changeRoomStatus(int prisonMap[50][50])
{
    int rows, cols, newStatus, roomNumber, prisonerNumber;
    FILE *file, *mapfile;
    Prisoner person[100];
    int n = 0, found = 0;

    while (1)
    {
        printf("Enter room number (e.g., 504): ");
        scanf("%d", &roomNumber);
        if (roomNumber >= 0 && roomNumber <= 909)
        {
            break;
        }
        else
        {
            printf("\033[0;33mInvalid. Please enter 000 to 909.\n\033[0m");
        }
    }

    rows = roomNumber / 100;
    cols = roomNumber % 10;

    // Open the map file to read the current prison map
    mapfile = fopen("prisonmap.txt", "r");
    if (mapfile == NULL)
    {
        printf("Error: Unable to open prison map file.\n");
        return;
    }

    // Read the map data from the file into the prisonMap array
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            fscanf(mapfile, "%d", &prisonMap[i][j]);
        }
    }
    fclose(mapfile);

    int currentStatus = prisonMap[rows][cols];

    while (1)
    {
        printf("Enter new status (0 for Available, 1 for Full): ");
        scanf("%d", &newStatus);
        if (newStatus == 0 || newStatus == 1)
        {
            break;
        }
        else
        {
            printf("\033[0;33mInvalid. Please enter 0 or 1.\n\033[0m");
        }
    }

    if (currentStatus == 0 && newStatus == 1)
    {
        // If the room is available and user wants to make it full
        printf("Enter Prisoner's ID: ");
        scanf("%d", &prisonerNumber);

        // Check if prisoner is already in another room
        FILE *occupiedFile = fopen("occupiedRooms.txt", "r");
        if (occupiedFile == NULL)
        {
            printf("\033[0;31mError opening file.\n\033[0m");
            return;
        }

        int tempRoomNumber, tempPrisonerID;
        int isAlreadyAssigned = 0;
        char line[256];

        while (fgets(line, sizeof(line), occupiedFile) != NULL)
        {
            sscanf(line, "Room: %d | Prisoner ID: %d", &tempRoomNumber, &tempPrisonerID);
            if (tempPrisonerID == prisonerNumber)
            {
                isAlreadyAssigned = 1; // Set flag if prisoner is already in another room
                break;
            }
        }
        fclose(occupiedFile);

        if (isAlreadyAssigned)
        {
            printf("\033[0;31mError: Prisoner ID %d is already assigned to another room.\n\033[0m", prisonerNumber);
            return; // Exit if prisoner is already assigned to another room
        }

        // Check and save prisoner details if ID is valid
        file = fopen("prisonerData.txt", "r");
        if (file == NULL)
        {
            printf("\033[0;31mError opening file.\n\033[0m");
            return;
        }

        while (fscanf(file, "%d %d %d %s %s %d %f %f %s %s %s %s %s %s %s %d", &person[n].id, &person[n].oldday, &person[n].day,
                      person[n].name, person[n].surname, &person[n].age, &person[n].height, &person[n].weight,
                      person[n].hairColor, person[n].eyeColor, person[n].nationality, person[n].crime,
                      person[n].level, person[n].lawyerName, person[n].lawyerContact, &person[n].merit) != EOF)
        {
            if (person[n].id == prisonerNumber)
            {
                found = 1;
                break;
            }
            n++;
        }
        fclose(file);

        if (found)
        {
            file = fopen("occupiedRooms.txt", "a");
            if (file == NULL)
            {
                printf("\033[0;31mError opening file.\n\033[0m");
                return;
            }
            fprintf(file, "Room: %d | Prisoner ID: %d | Name: %s %s | Crime: %s\n", roomNumber, person[n].id,
                    person[n].name, person[n].surname, person[n].crime);
            fclose(file);

            printf("\nPrisoner details saved for room \033[1;36m%d\033[0m.\n", roomNumber);
        }
        else
        {
            printf("\033[0;31mPrisoner ID not found.\n\033[0m");
            return; // Exit if prisoner ID is not found
        }
    }
    else if (currentStatus == 1 && newStatus == 0)
    {
        FILE *occupiedFile = fopen("occupiedRooms.txt", "r");
        char line[256];
        int tempRoomNumber, tempPrisonerID;
        while (fgets(line, sizeof(line), occupiedFile) != NULL)
        {
            sscanf(line, "Room: %d | Prisoner ID: %d", &tempRoomNumber, &tempPrisonerID);
            if (roomNumber == tempRoomNumber)
            {
                fileUpdate("occupiedRooms.txt", tempPrisonerID);
                break;
            }
        }
        // printf("Update Status to available succesfully. ");
    }

    // Update the room status in the in-memory prisonMap array
    prisonMap[rows][cols] = newStatus;

    // Open the prisonmap.txt file in write mode to update the entire prison map
    mapfile = fopen("prisonmap.txt", "w");
    if (mapfile == NULL)
    {
        printf("Error: Unable to open map file for writing.\n");
        return;
    }

    // Write the updated prisonMap array to the file
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            fprintf(mapfile, "%d ", prisonMap[i][j]);
        }
        fprintf(mapfile, "\n");
    }

    fclose(mapfile); // Close the file after writing
    printf("\033[0;32mRoom status updated successfully.\n\033[0m");
}

// Entry New Prisoner function
void EntryPrisoner()
{
    FILE *fentry, *fdata;
    char fname[20];
    int modeCheck = 0;
    while (1)
    {
        printf("\nMenu:\n");
        printf("  Load from File.txt  [1]\n");
        printf("  Enter Manually      [2]\n");
        printf("  Back to Main Menu   [3]\n");
        printf("\nEnter the Menu: ");
        scanf("%d", &modeCheck);

        switch (modeCheck)
        {
        case 1:
            m = n;
            printf("Enter the filename to load data: ");
            scanf("%s", fname);
            fentry = fopen(fname, "r");
            if (fentry == NULL)
            {
                printf("\n\033[1;31mError opening file for reading.\033[0m\n");
                continue;
            }
            while (fscanf(fentry, "%d %s %s %d %f %f %s %s %s %s %s %s %s", &person[n].day,
                          person[n].name, person[n].surname, &person[n].age, &person[n].height, &person[n].weight,
                          person[n].hairColor, person[n].eyeColor, person[n].nationality, person[n].crime, person[n].level,
                          person[n].lawyerName, person[n].lawyerContact) != EOF)
            {
                printstartDate(person[n].dateStart);
                person[n].id = n + 1001;
                person[n].oldday = person[n].day;
                n++;
            }
            fclose(fentry);
            textFile();
            printf("\n\033[1;32mData loaded successfully.\033[0m\n");
            break;
        case 2:
            prisonerEntry();
            textFile();
            printf("\n\033[1;32mData save successfully.\033[0m\n");
            break;
        case 3:
            printf("\033[0;35m--------------------------------\n\033[0m");
            return;
        default:
            printf("\033[0;33mInvalid option. Please enter 1, 2 or 3.\n\033[0m");
        }
    }
}

// สร้างวันเริ่มต้นเข้าคุก
void printstartDate(char *startDate)
{
    time_t currentTime = time(NULL);
    struct tm *localTime = localtime(&currentTime);
    strftime(startDate, 80, "%d/%m/%Y", localTime);
}

// คำนวณวันพ้นโทษ
int releaseDate(int day)
{
    time_t currentTime = time(NULL);
    time_t futureTime = currentTime + (day * 24 * 60 * 60);

    struct tm *futureDate = localtime(&futureTime);
    char releaseDate[80];

    strftime(releaseDate, sizeof(releaseDate), "%d/%m/%Y", futureDate);
    printf("Release date         : %s\n", releaseDate);
}

// สำหรับคนที่อยู่ในคุก ณ ปัจจุบัน
void prisonerEntry()
{
    m = n;
    person[n].id = n + 1001;
    printf("Enter Manually Mode:\n");
    printf("\n------- Prisoner Detail -------\n\n");
    printf("[Prisoner_ID] %d\n", person[n].id);

    printf("Enter Prisoner_Name        : ");
    scanf(" %19s", person[n].name);

    printf("Enter Prisoner_Surname     : ");
    scanf(" %29s", person[n].surname);

    while (1)
    {
        printf("Enter Prisoner_Age (years) : ");
        if (scanf(" %d", &person[n].age) != 1) // เช็กว่าเป็น จำนวนเต็มหรือไม่
        {
            printf("\033[0;33mInvalid input. Please enter a valid age.\n\033[0m");
            while (getchar() != '\n') // Clear Buffer
                ;
            continue;
        }
        if (person[n].age < 18)
        {
            printf("\033[0;33mAge under 18 is not valid for prison.\n\033[0m");
            continue;
        }
        break;
    }

    while (1)
    {
        printf("Enter Prisoner_Height (cm) : ");
        if (scanf(" %f", &person[n].height) != 1)
        {
            while (getchar() != '\n')
                ;
            printf("\033[0;33mInvalid height.\n\033[0m");
            continue;
        }
        break;
    }

    while (1)
    {
        printf("Enter Prisoner_Weight (kg) : ");
        if (scanf(" %f", &person[n].weight) != 1)
        {
            while (getchar() != '\n')
                ;
            printf("\033[0;33mInvalid weight.\n\033[0m");
            continue;
        }
        break;
    }

    printf("Enter Prisoner_HairColor   : ");
    scanf(" %19s", person[n].hairColor);

    printf("Enter Prisoner_EyeColor    : ");
    scanf(" %19s", person[n].eyeColor);

    printf("Enter Prisoner_Nationality : ");
    scanf(" %29s", person[n].nationality);

    // ข้อมูลเกี่ยวกับคดี
    printf("\n-------- Prisoner Case --------\n");
    printstartDate(person[n].dateStart);
    printf("StartDate            : %s\n", person[n].dateStart);

    while (1)
    {
        printf("Enter Day of release (Number of days (ex.365) or Life imprisonment (press 0)): ");
        if (scanf(" %d", &person[n].day) != 1)
        {
            while (getchar() != '\n')
                ;
            printf("\033[0;33mInvalid days.\n\033[0m");
            continue;
        }
        if (person[n].day == 0)
        {
            printf("Life imprisonment.\n");
            person[n].oldday = person[n].day;
        }
        else
        {
            releaseDate(person[n].day);
            person[n].oldday = person[n].day;
        }
        break;
    }

    getchar(); // เคลียร์ newline character ที่ค้างอยู่ในบัฟเฟอร์
    printf("Enter Prisoner_Crime       : ");
    fgets(person[n].crime, sizeof(person[n].crime), stdin);
    // ลบ newline character ออกจาก crime หากมี
    size_t len = strlen(person[n].crime);
    if (len > 0 && person[n].crime[len - 1] == '\n')
    {
        person[n].crime[len - 1] = '\0';
    }

    while (1)
    {
        printf("Enter Prisoner_ThreatLevel (1 - Low, 2 - Moderate, 3 - High): ");
        if (scanf(" %d", &mlevel) != 1)
        {
            while (getchar() != '\n')
                ;
            printf("\033[0;33mInvalid level.\n\033[0m");
            continue;
        }
        switch (mlevel)
        {
        case 1:
            strcpy(person[n].level, "Low-Risk");
            break;
        case 2:
            strcpy(person[n].level, "Moderate-Risk");
            break;
        case 3:
            strcpy(person[n].level, "High-Risk");
            break;
        default:
            printf("\033[0;33mInvalid level.\n\033[0m");
            break;
        }
        if (mlevel != 1 && mlevel != 2 && mlevel != 3)
        {
            continue;
        }
        break;
    }

    getchar();
    printf("Enter Lawyer_Name          : ");
    fgets(person[n].lawyerName, sizeof(person[n].lawyerName), stdin);
    size_t leng = strlen(person[n].lawyerName);
    if (leng > 0 && person[n].lawyerName[leng - 1] == '\n')
    {
        person[n].lawyerName[leng - 1] = '\0';
    }

    printf("Enter Lawyer_Contact(Tel.) : ");
    scanf(" %s", person[n].lawyerContact);

    n++;
}

// ส่งออกข้อมูลไปที่ File
void textFile()
{
    char nfile[20] = "prisonerData.txt";
    FILE *file = fopen(nfile, "a");

    for (int i = 0; i < n; i++)
    {
        if (person[i].merit == '\0')
        {
            person[i].merit = 0;
        }
    }

    if (file == NULL)
    {
        printf("Could not open file %s for writing\n", nfile);
        return;
    }

    for (int i = m; i < n; i++)
    { // เพิ่มช้อมูล เเก้ในส่วนนี้
        fprintf(file, "%d %d %d %s %s %d %.2f %.2f %s %s %s %s %s %s %s %d\n",
                person[i].id, person[i].oldday, person[i].day, person[i].name, person[i].surname, person[i].age,
                person[i].height, person[i].weight, person[i].hairColor,
                person[i].eyeColor, person[i].nationality, person[i].crime,
                person[i].level, person[i].lawyerName, person[i].lawyerContact, person[i].merit);
    }
    fclose(file);
}

void textFile1()
{
    char nfile[30] = "prisonerData.txt";
    FILE *file = fopen(nfile, "w");

    if (file == NULL)
    {
        printf("Could not open file %s for writing\n", nfile);
        return;
    }

    for (int i = 0; i < n; i++)
    { // เพิ่มช้อมูล เเก้ในส่วนนี้
        fprintf(file, "%d %d %d %s %s %d %.2f %.2f %s %s %s %s %s %s %s %d\n",
                person[i].id, person[i].oldday, person[i].day, person[i].name, person[i].surname, person[i].age,
                person[i].height, person[i].weight, person[i].hairColor,
                person[i].eyeColor, person[i].nationality, person[i].crime,
                person[i].level, person[i].lawyerName, person[i].lawyerContact, person[i].merit);
    }
    fclose(file);
}

// รับเข้าข้อมูลเดิม เมื่อ Run ใหม่ //คอปเอาไปด้วย
void ReadtextFile()
{
    char nfile[20] = "prisonerData.txt";
    FILE *file = fopen(nfile, "r");
    if (file == NULL)
    {
        printf("Could not open file %s for writing\n", nfile);
        return;
    }

    while (fscanf(file, "%d %d %d %s %s %d %f %f %s %s %s %s %s %s %s %d", &person[n].id, &person[n].oldday, &person[n].day,
                  person[n].name, person[n].surname, &person[n].age, &person[n].height, &person[n].weight,
                  person[n].hairColor, person[n].eyeColor, person[n].nationality, person[n].crime, person[n].level,
                  person[n].lawyerName, person[n].lawyerContact, &person[n].merit) != EOF)
    {
        printstartDate(person[n].dateStart);
        n++;
    }
    fclose(file);
}

// merit point
void meritPoint()
{
    int modeCheck = 0;
    while (1)
    {
        printf("\nMenu:\n");
        printf("  Increase merit points [1]\n");
        printf("  Decrease merit points [2]\n");
        printf("  Back to Main Menu     [3]\n");
        printf("\nEnter the Menu: ");
        scanf("%d", &modeCheck);

        switch (modeCheck)
        {
        case 1:
            Increase(); // Increase merit points
            break;
        case 2:
            Decrease(); // Decrease merit points
            break;
        case 3:
            printf("\033[0;35m--------------------------------\n\033[0m");
            return;
        default:
            printf("\033[0;33mInvalid option. Please enter 1, 2 or 3.\n\033[0m");
            break;
        }
    }
}

void Increase()
{
    int id, new_merit;
    seeAllPrisonerMerit();
    printf("\n\033[0;32mIncrease \033[0m");
    printf("merit:\n");
    while (1)
    {
        printf("Enter Prisoner ID: ");
        scanf("%d", &id);
        if (id > (n + 1000) || id < 1001) // เช็กว้ามีนักโทษหรือไม่
        {
            printf("\033[0;33mPrisoner ID not found\n\033[0m");
            continue;
        }
        else
        {
            break;
        }
    }
    id = id - 1001;
    printf("Name: ");
    printf("\033[1;34m%s %s.\033[0m\n", person[id].name, person[id].surname);
    printf("Total scores: ");
    printf("\033[0;34m%d\033[0,m\n", person[id].merit);
    printf("\033[0;32mIncrease \033[0m");
    printf("points: +");
    scanf("%d", &new_merit);
    printf("\n\033[1;32mData save successfully.\033[0m\n");
    person[id].merit += new_merit;
    TimeReduct(id); // ลดเวลา
    textFile1();    // บันทึกเข้า file
}

void Decrease()
{
    int id, new_merit;
    seeAllPrisonerMerit();
    printf("\n\033[0;31mDecrease \033[0m");
    printf("merit:\n");
    while (1)
    {
        printf("Enter Prisoner ID: ");
        scanf("%d", &id);
        if (id > (n + 1000) || id < 1001)
        {
            printf("\033[0;33mPrisoner ID not found\n\033[0m");
            continue;
        }
        else
        {
            break;
        }
    }
    id = id - 1001;
    printf("Name: ");
    printf("\033[1;34m%s %s.\033[0m\n", person[id].name, person[id].surname);
    printf("Total scores: ");
    printf("\033[0;34m%d\033[0,m\n", person[id].merit);
    printf("\033[0;31mDecrease \033[0m");
    printf("points: -");
    scanf("%d", &new_merit);
    printf("\n\033[1;32mData save successfully.\033[0m\n");
    person[id].merit -= new_merit;
    TimeReductMinus(id);
    textFile1();
}

// ลดจำนวนวัน
void TimeReduct(int id)
{
    if (person[id].merit >= 100) // คะแนน 100 ขึ้นไปถึงจะลดจำนวนวัน
    {
        person[id].day = person[id].oldday - (person[id].merit / 10);
    }
    else
    {
        return;
    }
}

// เพิ่มจำนวนวัน
void TimeReductMinus(int id)
{
    person[id].day = person[id].oldday - (person[id].merit / 10);
}

// overview
void overView()
{
    int modeCheck = 0;
    while (1)
    {
        printf("\nMenu:\n");
        printf("  Prisoner Statistics [1]\n");
        printf("  See All Prisoners   [2]\n");
        printf("  Back to Main Menu   [3]\n");
        printf("\nEnter the Menu: ");
        scanf("%d", &modeCheck);

        switch (modeCheck)
        {
        case 1:
            printf("Prisoner Statistics: ");
            if (n == 0)
            {
                printf("\033[0;31m\nNo Prisoners entered.\n\033[0m");
            }
            else
            {
                stat();
            }
            break;
        case 2:
            seeAllPrisoner();
            selectPrisonerforSeedetails();
            break;
        case 3:
            printf("\033[0;35m--------------------------------\n\033[0m");
            return;
        default:
            printf("\033[0;33mInvalid option. Please enter 1, 2 or 3\n\033[0m");
        }
    }
}

// ดูรายละเอียดนักโทษ
void seeDetails(int num)
{
    printf("\033[0;34m\n ------- Prisoner Detail -------\n\n\033[0m");
    printf("  Prisoner_ID          : %d\n", person[num].id);
    printf("  Prisoner_Name        : %s\n", person[num].name);
    printf("  Prisoner_Surname     : %s\n", person[num].surname);
    printf("  Prisoner_Age         : %d years\n", person[num].age);
    printf("  Prisoner_Height      : %.2f cm\n", person[num].height);
    printf("  Prisoner_Weight      : %.2f kg\n", person[num].weight);
    printf("  Prisoner_HairColor   : %s\n", person[num].hairColor);
    printf("  Prisoner_EyeColor    : %s\n", person[num].eyeColor);
    printf("  Prisoner_Nationality : %s\n", person[num].nationality);

    printf("\033[0;34m\n -------- Prisoner Case --------\n\n\033[0m");
    printf("  Prisoner_Merit       : %d\n", person[num].merit);
    printf("  Prisoner_Crime       : %s\n", person[num].crime);
    printf("  Prisoner_ThreatLevel : %s\n", person[num].level);
    printf("  Lawyer_Name          : %s\n", person[num].lawyerName);
    printf("  Lawyer_Contact       : %s\n", person[num].lawyerContact);
    printf("  Start Date           : %s\n", person[num].dateStart);
    printf("  Release Days         : ");
    if (person[num].day == 0)
    {
        printf("Life imprisonment\n");
    }
    else
    {
        printf("%d days\n", person[num].day);
        printf("  ");
        releaseDate(person[num].day);
    }
}

// เลือกนักโทษคนที่ num
void selectPrisonerforSeedetails()
{
    int num;
    if (n != 0)
    {
        while (1)
        {
            printf("\nEnter the prisoner ID: ");
            scanf("%d", &num);
            if (num > (n + 1000) || num < 1001)
            {
                printf("\033[0;33mPrisoner ID not found\033[0m");
                continue;
            }
            else
            {
                break;
            }
        }
        int id = num - 1001;
        seeDetails(id);// เรียกใช้ฟังก์ชั่น seeDetails
    }
    else{
        printf("\033[0;31m\nNo Prisoners entered.\n\033[0m");
    }
}

// ดูข้อมูลนักโทษทุกคน
void seeAllPrisoner()
{
    if (n == 0)
    {
        printf("\033[0;31mNo Prisoners entered.\n\033[0m");
        return;
    }

    printf("\nSee All Prisoners:\n");
    for (int i = 0; i < n; i++)
    {
        printf("  Prisoner_ID : \033[0;35m%d\033[0m - %s %s\n", person[i].id, person[i].name, person[i].surname);
    }
}

// ดูข้อมูลนักโทษทุกคน และคะแนน
void seeAllPrisonerMerit()
{
    if (n == 0)
    {
        printf("\033[0;31mNo Prisoners entered.\n\033[0m");
        return;
    }

    printf("\nSee All Prisoners:\n");
    for (int i = 0; i < n; i++)
    {
        printf("  Prisoner_ID : \033[0;35m%d\033[0m - %s %s | Merit Point : \033[0;34m%d\033[0m\n", person[i].id, person[i].name, person[i].surname, person[i].merit);
    }
}

void calculateStats(int data[], int b, int *sum, float *avg, int *min, int *max)
{
    *sum = 0;
    *min = data[0];
    *max = data[0];

    for (int i = 0; i < b; i++)
    {
        *sum += data[i];
        if (data[i] < *min)
        {
            *min = data[i];
        }
        if (data[i] > *max)
        {
            *max = data[i];
        }
    }

    *avg = *sum / b;
}

void rangeAge(int age[])

{
    int a = 0, b = 0, c = 0, d = 0, e = 0;
    for (int i = 0; i < n; i++)
    {
        if (age[i] >= 18 && age[i] <= 25)
        {
            a++;
        }
        else if (age[i] >= 26 && age[i] <= 35)
        {
            b++;
        }
        else if (age[i] >= 36 && age[i] <= 45)
        {
            c++;
        }
        else if (age[i] >= 46 && age[i] <= 55)
        {
            d++;
        }
        else
        {
            e++;
        }
    }
    printf("  Age Group(18-25)     : %d\n", a);
    printf("  Age Group(26-35)     : %d\n", b);
    printf("  Age Group(36-45)     : %d\n", c);
    printf("  Age Group(46-55)     : %d\n", d);
    printf("  Age Group(56+)       : %d\n\n", e);
}

// แยก Level นักโทษ
void level(char data[][20], int *low, int *moderate, int *high)
{
    *low = 0;
    *moderate = 0;
    *high = 0;

    for (int i = 0; i < n; i++)
    {
        if (strcmp(data[i], "Low-Risk") == 0)
        {
            (*low)++;
        }
        else if (strcmp(data[i], "Moderate-Risk") == 0)
        {
            (*moderate)++;
        }
        else if (strcmp(data[i], "High-Risk") == 0)
        {
            (*high)++;
        }
    }
}

void stat()
{
    int ages[MAX_Prisoner];
    int meritPoints[MAX_Prisoner];
    int timeServed[MAX_Prisoner];
    char danger[MAX_Prisoner][20];

    for (int i = 0; i <= n; i++) // ใช้กับ function
    {
        ages[i] = person[i].age;
        meritPoints[i] = person[i].merit;
        timeServed[i] = person[i].day;
        strcpy(danger[i], person[i].level);
    }

    int sum, min, max;
    float avg;
    printf("\n\n  Total Number of Prisoners: %d\n\n", n);
    calculateStats(ages, n, &sum, &avg, &min, &max);
    printf("\033[1;35m  Age\033[0m\n");
    printf("  Average Age          : %.2f years\n", avg);
    printf("  Age Min              : %d years\n", min);
    printf("  Age Max              : %d years\n", max);
    rangeAge(ages);

    int low, moderate, high;
    level(danger, &low, &moderate, &high);
    printf("\033[1;35m  Danger Level\033[0m\n");
    printf("  Danger Level(Low)      : %d\n", low);
    printf("  Danger Level(Moderate) : %d\n", moderate);
    printf("  Danger Level(High)     : %d\n", high);

    // คำนวณสถิติคะแนนความประพฤติ
    calculateStats(meritPoints, n, &sum, &avg, &min, &max);
    printf("\n\033[1;35m  Merit Points\033[0m\n");
    printf("  Average Merit Points : %.2f pts.\n", avg);
    printf("  Merit Points Min     : %d pts.\n", min);
    printf("  Merit Points Max     : %d pts.\n", max);

    // คำนวณสถิติระยะเวลารับโทษ
    calculateStats(timeServed, n, &sum, &avg, &min, &max);
    printf("\n\033[1;35m  Time Served\033[0m\n");
    printf("  Average Time Served  : %.2f days\n", avg);
    printf("  Time Served Min      : %d days\n", min);
    printf("  Time Served Max      : %d days\n", max);
}

void search()
{
    int modeCheck = 0;
    while (1)
    {
        printf("\nMenu:\n");
        printf("  See Prisoner Detail [1]\n");
        printf("  See All Prisoners   [2]\n");
        printf("  Focus Data Filter   [3]\n");
        printf("  Back to Main Menu   [4]\n");
        printf("\nEnter the Menu: ");
        scanf("%d", &modeCheck);

        switch (modeCheck)
        {
        case 1:
            selectPrisonerforSeedetails();
            break;
        case 2:
            seeAllPrisoner();
            break;
        case 3:
            filter();
            break;
        case 4:
            printf("\033[0;35m--------------------------------\n\033[0m");
            return;
        default:
            printf("\033[0;33mInvalid option. Please enter 1, 2, 3 or 4.\n\033[0m");
        }
    }
}

void allergy()
{
    ReadFood();
    int modeCheck = 0;
    while (1)
    {
        printf("\nMenu:\n");
        printf("  Update Allergy Data  [1]\n");
        printf("  Check Daily Menu     [2]\n");
        printf("  Back to Main Menu    [3]\n");
        printf("\nEnter the Menu: ");
        scanf("%d", &modeCheck);

        switch (modeCheck)
        {
        case 1:
            if (x == n) // เข้ามาใน function แล้วข้อมูลเท่าเดิม
            {
                printf("\033[0;34mNo new Prisoner data to update.\n\033[0m");
            }
            else // เข้ามาใน function แล้วมีนักโทษเพิ่มขึ้น
            {
                getInput();  // รับข้อมูลอาหารที่แพ้
                WriteFood(); // บันทึกข้อมูลลง file
            }
            break;
        case 2:
            randomFood();
            break;
        case 3:
            printf("\033[0;35m--------------------------------\n\033[0m");
            return;
        default:
            printf("\033[0;33mInvalid option. Please enter 1, 2 or 3.\n\033[0m");
            break;
        }
    }
}

void getInput()
{
    int i = 0;
    if (x == n)
    {
        printf("\033[0;34mNo new Prisoner data.\n\033[0m");
    }
    else if (x < n)
    {
        for (i = x; i < n; i++)
        {
            printf("Enter allergy information for ID %d: ", person[i].id);
            scanf(" %s", person[i].allergy);
        }
        printf("\033[0;32mSave Data successfully.\n\033[0m");
    }
    x = i;
}

void WriteFood()
{
    char filename[20] = "food.txt";
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    for (int i = 0; i < n; i++)
    {
        fprintf(file, "%d %s\n", person[i].id, person[i].allergy);
    }

    fclose(file);
}

void ReadFood()
{
    char filename[20] = "food.txt";
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }
    while (fscanf(file, "%d %s", &person[f].id, person[f].allergy) != EOF)
    {
        f++;
    }
    x = f;
    fclose(file);
}

void randomFood()
{
    srand(time(0));
    int randomIndex;
    bool foundSafeFood = false;
    int j = 0;

    while (!foundSafeFood)
    {
        randomIndex = rand() % 30; // เปลี่ยนค่าจำนวนเมนูตามความเหมาะสม

        for (int i = 0; i < n; i++) // ตรวจสอบการแพ้อาหาร
        {
            if (strstr(person[i].allergy, list[randomIndex].ingredient1) != NULL ||
                strstr(person[i].allergy, list[randomIndex].ingredient2) != NULL ||
                strstr(person[i].allergy, list[randomIndex].ingredient3) != NULL)
            {
                foundSafeFood = false;
                break;
            }
            foundSafeFood = true;
        }
    }

    // แสดงข้อมูลเมนูที่ถูกเลือก
    printstartDate(datefood[j]);
    printf("Daily Menu for %s: %s\n", datefood[j], list[randomIndex].food);
    printf("Ingredients: %s, %s, %s\n", list[randomIndex].ingredient1, list[randomIndex].ingredient2, list[randomIndex].ingredient3);
}

// filter data
void filter()
{
    int choice;
    char filterValue[30];
    char filterType[20];
    float min_weight = 0, max_weight = 0, min_height = 0, max_height = 0;

    while (1)
    {
        printf("\nType of filter:\n");
        printf("  Eye Color    [1]\n");
        printf("  Hair Color   [2]\n");
        printf("  Nationality  [3]\n");
        printf("  Weight       [4]\n");
        printf("  Height       [5]\n");
        printf("  Back to Menu [6]\n");
        printf("\nEnter type data: ");
        scanf("%d", &choice);

        // กำหนดประเภทการค้นหาตามที่เลือก
        switch (choice)
        {
        case 1:
            strcpy(filterType, "eyeColor");
            break;
        case 2:
            strcpy(filterType, "hairColor");
            break;
        case 3:
            strcpy(filterType, "nationality");
            break;
        case 4:
            strcpy(filterType, "weight");
            while (1)
            {
                printf("Enter weight range (min max): ");
                if (scanf("%f %f", &min_weight, &max_weight) != 2)
                {
                    while (getchar() != '\n')
                        ;
                    printf("\033[0;33mInvalid input for weight range.\033[0m\n");
                    continue;
                }
                break;
            }
            break;
        case 5:
            strcpy(filterType, "height");
            while (1)
            {
                printf("Enter height range (min max): ");
                if (scanf("%f %f", &min_height, &max_height) != 2)
                {
                    while (getchar() != '\n')
                        ;
                    printf("\033[0;33mInvalid input for height range.\033[0m\n");
                    continue;
                }
                break;
            }
            break;
        case 6:
            return;
        default:
            printf("\033[0;31mDon't have that filter.\033[0m\n");
            break;
        }
        if (choice >= 1 && choice <= 5)
        {
            if (choice != 4 && choice != 5)
            {
                printf("Enter %s: ", filterType);
                scanf("%s", filterValue);
            }

            // เรียกฟังก์ชัน search เพื่อค้นหาตามประเภทและค่าที่กรอก
            searchfilter(n, filterType, filterValue, min_weight, max_weight, min_height, max_height);
        }
    }
}

void searchfilter(int count, const char *filterType, const char *filterValue, float min_weight, float max_weight, float min_height, float max_height)
{
    int found = 0;

    // แสดงหัวข้อการค้นหาขึ้นอยู่กับ filterType
    if (strcmp(filterType, "weight") == 0)
    {
        printf("\nFind prisoner with \033[0;36m%s\033[0m between \033[0;34m%.2f\033[0m and \033[0;34m%.2f\033[0m\n", filterType, min_weight, max_weight);
    }
    else if (strcmp(filterType, "height") == 0)
    {
        printf("\nFind prisoner with \033[0;36m%s\033[0m between \033[0;34m%.2f\033[0m and \033[0;34m%.2f\033[0m\n", filterType, min_height, max_height);
    }
    else
    {
        printf("\nFind prisoner with \033[0;36m%s\033[0m = \033[0;34m%s\033[0m\n", filterType, filterValue);
    }

    for (int i = 0; i < count; i++)
    {
        if (strcmp(filterType, "eyeColor") == 0 && strcmp(person[i].eyeColor, filterValue) == 0)
        {
            printf("Prisoner ID: \033[0;35m%d\033[0m, Name: %s, Eye Color: \033[0;34m%s\033[0m\n", person[i].id, person[i].name, person[i].eyeColor);
            found = 1;
        }
        else if (strcmp(filterType, "hairColor") == 0 && strcmp(person[i].hairColor, filterValue) == 0)
        {
            printf("Prisoner ID: \033[0;35m%d\033[0m, Name: %s, Hair Color: \033[0;34m%s\033[0m\n", person[i].id, person[i].name, person[i].hairColor);
            found = 1;
        }
        else if (strcmp(filterType, "nationality") == 0 && strcmp(person[i].nationality, filterValue) == 0)
        {
            printf("Prisoner ID: \033[0;35m%d\033[0m, Name: %s, Nationality: \033[0;34m%s\033[0m\n", person[i].id, person[i].name, person[i].nationality);
            found = 1;
        }
        else if (strcmp(filterType, "weight") == 0 && person[i].weight >= min_weight && person[i].weight <= max_weight)
        {
            printf("Prisoner ID: \033[0;35m%d\033[0m, Name: %s, Weight: \033[0;34m%.2f\033[0m\n", person[i].id, person[i].name, person[i].weight);
            found = 1;
        }
        else if (strcmp(filterType, "height") == 0 && person[i].height >= min_height && person[i].height <= max_height)
        {
            printf("Prisoner ID: \033[0;35m%d\033[0m, Name: %s, Height: \033[0;34m%.2f\033[0m\n", person[i].id, person[i].name, person[i].height);
            found = 1;
        }
    }

    if (!found)
    {
        printf("\033[0;31mNo prisoner information found.\033[0m\n");
    }
}
