#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>
#pragma warning(disable:4996)
#define MAX_MEMBERS 50
#define MAX_STAFF 50

//structure for SCHEDULING MODULE
typedef struct {
    int hour, minute;
    int day, month, year;
}Date;

typedef struct {
    char trainId[6], departureStation[50], arrivalStation[50];
    Date departureTime;
    int availableSeats;
}Train;

typedef struct {
    int seatcancel;
    int seatBooked;
}Seat;

//structure for MEMBER MODULE
struct member {
    char ID[6];
    char name[31];
    char password[16];
    char passwordRecov[21];
    char gender;
    char IC[15];
    char contactNum[13];
};

//structure for BOOKING MODULE

typedef struct {
    char id[11];
    char name[50];
    char DepStation[50];
    char ArrStation[50];
}Customer;

typedef struct {
    int bookingID;
    char customerID[11];
    char customerName[25];
    char paymentMethod[21];
    char trainID[6];
    char departureStation[20];
    Date departureTime;
    int seatsBooked;
}Booking;

//structure for STAFF MODULE
typedef struct {
    char Staff_Id[6];
    char Staff_Name[100];
    char Staff_Pass[21];
    char Staff_PassRec[21];
    char position[100];
}Staff;

//function declaration for MEMBER MODULE (done by: Ooi Jun Kang)
void maskPassword(char*);
unsigned int hashPassword(const char*);
void memberLogin(struct member memberInfo[], int count, int* memberLoggedInIndex);
void viewMemberInfo(struct member memberInfo[], int count);
void enterNewMember(struct member memberInfo[], int* count);
void deleteMember(struct member memberInfo[], int* count);
void updateMemberFile(struct member memberInfo[], int count);
void importMemberList(struct member memberInfo[], int count);
void exportMemberList(struct member memberInfo[], int count);
void editMemberProfile(struct member memberInfo[], int count, int memberLoggedInIndex);
void passwordRecovery(struct member memberInfo[], int count);
void memberPage();
void staffPage();
void logo();

//Function declaration for TICKET SCHEDULING MODULE (done by: Chaw Chun Jia)
void addTrain();
void displayTrain();
void adminSearchTrain();
void modifyTrain();
void deleteTrain();
void backupTrain();

//Function Declaration for TICKET BOOKING MODULE (done by: Goh Chun Wen)
int BuyTicket(struct member memberInfo[], int count, int memberLoggedInIndex);
void ModifyBooking(struct member memberInfo[], int count, int memberLoggedInIndex);
void DisplayAllTrain(struct member memberInfo[], int count, int memberLoggedInIndex);
void SearchTrain(struct member memberInfo[], int count, int memberLoggedInIndex);
void GenerateTicket(struct member memberInfo[], int count, int memberLoggedInIndex);
void CheckBooking(struct member memberInfo[], int count, int memberLoggedInIndex);
void generateReferenceCode(char* refCode, int length);
void printBookingDetails(Booking booking, char referenceCode[]);

//function declaration for STAFF MODULE (done by: Wong Shun Bin)
void editStaffProfile(Staff staffInfo[], int count, int staffLoggedInIndex);
void loginStaff(Staff staffInfo[], int count, int* staffLoggedInIndex);
void updateStaffFile(Staff staffInfo[], int count);
void viewStaffInfo(Staff staffInfo[], int count);
void enterNewStaff(Staff staffInfo[], int* count);
void backupStaff(Staff staffInfo[], int count);
void deleteStaff(Staff staffInfo[], int* count);
void searchStaff(Staff staffInfo[], int count);

void main() {
    do {
        int choice;

        logo();

        printf("\n\n[ 1 ] Login As Member\n");
        printf("[ 2 ] Login As Staff\n");
        printf("[ 3 ] Exit program\n\n");

        do{
            printf(">> ");
            scanf("%d", &choice);
            if (choice != 1 && choice != 2 && choice != 3) {
                printf("Invalid choice\n");
            }
            else {
                break;
            }
        } while (choice != 1 && choice != 2 && choice != 3);

        switch (choice) {
        case 1:
            memberPage();
            break;

        case 2:
            staffPage();
            break;
        case 3:
            exit(-1);
            break;
        }

        system("cls");
    } while (1);
}

void logo() {
    printf("   ___     ___      ___    ___     ___            _  __    _     \n");
    printf("  | _ \\   /   \\    | _ \\  |_ _|   |   \\          | |/ /   | |    \n");
    printf("  |   /   | - |    |  _/   | |    | |) |   ___   | ' <    | |__  \n");
    printf("  |_|_\\   |_|_|   _|_|_   |___|   |___/   |___|  |_|\\_\\   |____| \n");
    printf("_|\"\"\"\"\"|_|\"\"\"\"\"|_| \"\"\"|_|\"\"\"\"\"|_|\"\"\"\"\"|_|\"\"\"\"\"|_|\"\"\"\"\"|_|\"\"\"\"\"| \n");
    printf("\"`-0-0-'\"`-0-0-'\"`-0-0-'\"`-0-0-'\"`-0-0-'\"`-0-0-'\"`-0-0-'\"`-0-0-'\n");
}

void memberPage() {
    struct member memberInfo[MAX_MEMBERS];
    int count = 0;
    int choice;
    char exitChoice;
    int memberLoggedInIndex = -1;

    FILE* memberFile;
    memberFile = fopen("member.txt", "r");

    if (memberFile == NULL) {
        printf("Error opening file.\n");

    }
    while (fscanf(memberFile, "%5[^,],%30[^,],%15[^,],%20[^,],%c,%14[^,],%12[^\n]\n", memberInfo[count].ID, memberInfo[count].name, memberInfo[count].password, memberInfo[count].passwordRecov, &memberInfo[count].gender, memberInfo[count].IC, memberInfo[count].contactNum) != EOF) {
        count++;
    }

    fclose(memberFile);

    memberLogin(memberInfo, count, &memberLoggedInIndex);

    do {
        system("cls");
        printf("=============\n");
        printf("Member Module\n");
        printf("=============\n\n");

        printf("[ 1 ] Edit profile\n");
        printf("[ 2 ] Buy Ticket\n");
        printf("[ 3 ] Modify Booking\n");
        printf("[ 4 ] Search Train\n");
        printf("[ 5 ] Display Available Train\n");
        printf("[ 6 ] Generate Ticket\n");
        printf("[ 7 ] Check Booking\n");
        printf("[ 0 ] Logout\n");
        printf("\n>> ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            system("cls");
            editMemberProfile(memberInfo, count, memberLoggedInIndex);
            break;
        case 2:
            system("cls");
            BuyTicket(memberInfo, count, memberLoggedInIndex);
            break;
        case 3:
            system("cls");
            ModifyBooking(memberInfo, count, memberLoggedInIndex);
            break;
        case 4:
            system("cls");
            SearchTrain(memberInfo, count, memberLoggedInIndex);
            break;
        case 5:
            system("cls");
            DisplayAllTrain(memberInfo, count, memberLoggedInIndex);
            break;
        case 6:
            system("cls");
            GenerateTicket(memberInfo, count, memberLoggedInIndex);
            break;
        case 7:
            system("cls");
            CheckBooking(memberInfo, count, memberLoggedInIndex);
            break;
        case 0:
            system("cls");
            updateMemberFile(memberInfo, count);
            return;
            break;
        default:
            printf("Invalid choice.\n");
            break;
        }
    } while (1);
}

void staffPage() {

    int choice;

    Staff staffInfo[MAX_STAFF];
    char backup;
    int count = 0;
    int staffLoggedInIndex = -1;

    FILE* staffFile;
    staffFile = fopen("staff.txt", "r");

    if (staffFile == NULL) {
        printf("Error opening file.\n");
        return 1;
    }
    while (fscanf(staffFile, "%5[^,],%30[^,],%14[^,],%14[^,],%15s\n",
        staffInfo[count].Staff_Id, staffInfo[count].Staff_Name, staffInfo[count].Staff_Pass, staffInfo[count].Staff_PassRec,
        &staffInfo[count].position) == 5) {
        count++;
    }

    fclose(staffFile);

    loginStaff(staffInfo, count, &staffLoggedInIndex);

    do {
        mainMenu:
        printf("============\n");
        printf("Staff Module\n");
        printf("============\n\n");

        printf("[ 1 ] Staff Control Panel\n");
        printf("[ 2 ] Member Control Panel\n");
        printf("[ 3 ] Train Scheduling Control Panel\n");
        printf("[ 4 ] Logout\n\n");

        printf(">> ");
        scanf("%d", &choice);

        if (choice == 1) {
            do {
                system("cls");
                printf("===================\n");
                printf("Staff Control Panel\n");
                printf("===================\n\n");

                printf("[ 1 ] Add New Staff\n");
                printf("[ 2 ] Search Staff Details\n");
                printf("[ 3 ] View Staff Details\n");
                printf("[ 4 ] Edit Staff Detail\n");
                printf("[ 5 ] Delete Staff Detail\n");
                printf("[ 6 ] Back up Staff Detail\n");
                printf("[ 0 ] Back to menu\n");

                printf("\nEnter your choice: ");
                scanf("%d", &choice);

                switch (choice) {
                case 1:
                    system("cls");
                    enterNewStaff(staffInfo, &count);
                    break;
                case 2:
                    system("cls");
                    searchStaff(staffInfo, count);
                    break;
                case 3:
                    system("cls");
                    viewStaffInfo(staffInfo, count);
                    break;
                case 4:
                    system("cls");
                    editStaffProfile(staffInfo, count, staffLoggedInIndex);
                    updateStaffFile(staffInfo, count); // Update member file after editing profile
                    break;
                case 5:
                    system("cls");
                    deleteStaff(staffInfo, &count);
                    break;
                case 6:
                    system("cls");
                    backupStaff(staffInfo, count);
                    break;
                case 0:
                    system("cls");
                    goto mainMenu;
                    break;
                default:
                    printf("Invalid choice.\n");
                    break;
                }
            } while (1);
        }
        else if (choice == 2) {

            struct member memberInfo[MAX_MEMBERS];
            int count = 0;
            int memberloggedInIndex = -1;

            FILE* memberFile;
            memberFile = fopen("member.txt", "r");

            if (memberFile == NULL) {
                printf("Error opening file.\n");
                return;
            }
            while (fscanf(memberFile, "%5[^,],%30[^,],%15[^,],%20[^,],%c,%14[^,],%12[^\n]\n", memberInfo[count].ID, memberInfo[count].name, memberInfo[count].password, memberInfo[count].passwordRecov, &memberInfo[count].gender, memberInfo[count].IC, memberInfo[count].contactNum) != EOF) {
                count++;
            }

            fclose(memberFile);
            do{
                system("cls");
                printf("====================\n");
                printf("Member Control Panel\n");
                printf("====================\n\n");
                printf("[ 1 ] View all member\n");
                printf("[ 2 ] Import member list\n");
                printf("[ 3 ] Back up member list\n");
                printf("[ 4 ] Enter new member\n");
                printf("[ 5 ] Delete member\n");
                printf("[ 0 ] Back to menu\n");

                printf("\nEnter your choice: ");
                scanf("%d", &choice);

                switch (choice) {
                case 1:
                    system("cls");
                    viewMemberInfo(memberInfo, count);
                    break;
                case 2:
                    system("cls");
                    importMemberList(memberInfo, &count);
                    updateMemberFile(memberInfo, count);
                    break;
                case 3:
                    system("cls");
                    exportMemberList(memberInfo, count);
                    break;
                case 4:
                    system("cls");
                    enterNewMember(memberInfo, &count);
                    break;
                case 5:
                    system("cls");
                    deleteMember(memberInfo, &count);
                    break;
                case 0:
                    system("cls");
                    goto mainMenu;
                default:
                    printf("Invalid choice.\n");
                    break;
                }
            } while (1);
            
    }
        else if (choice == 3) {
            do {
                int choice;

                system("cls");
                printf("==============================\n");
                printf("Train Scheduling Control Panel\n");
                printf("==============================\n\n");

                printf("[ 1 ] Add new train for departure\n");
                printf("[ 2 ] Search available train\n");
                printf("[ 3 ] Modify train information\n");
                printf("[ 4 ] Display all train available\n");
                printf("[ 5 ] Delete Certain Train\n");
                printf("[ 6 ] Backup Train\n");
                printf("[ 0 ] Back To Menu\n");

                printf("\nEnter your choice: ");
                scanf("%d", &choice);

                switch (choice) {
                case 1:
                    addTrain();
                    break;
                case 2:
                    adminSearchTrain();
                    break;
                case 3:
                    modifyTrain();
                    break;
                case 4:
                    displayTrain();
                    break;
                case 5:
                    deleteTrain();
                    break;
                case 6:
                    backupTrain();
                    break;
                case 0:
                    system("cls");
                    goto mainMenu;
                    break;
                default:
                    printf("Invalid choice.\n");
                    break;
                }
            } while (1);
        }
        else if(choice == 4) {
            system("cls");
            main();
        }
        
        system("cls");

    } while (1);

    return ;
}

unsigned int hashPassword(const char* password) {
    unsigned int hash = 0;
    while (*password) {
        hash = hash * 31 + *password++;
    }
    return hash;
}

void maskPassword(char* password) {
    int index = 0;
    char ch;
    while (1) {
        ch = getch(); // Read character without echoing to the screen
        if (ch == '\r' || ch == '\n') {
            password[index] = '\0';
            break;
        }
        else if (ch == 8) { // ASCII of Backspace = 8
            if (index > 0) {
                index--;
                putchar('\b'); // Move cursor back
                putchar(' ');  // Overwrite character with space
                putchar('\b'); // Move cursor back again
            }
        }
        else {
            if (index < 15) { // Maximum password length is 15 characters
                password[index++] = ch;
                putchar('*'); // Print asterisk instead of character
            }
        }
    }
    printf("\n");
}

//MEMBER MODULE (done by: Ooi Jun Kang)

void updateMemberFile(struct member memberInfo[], int count) {
    FILE* memberFile = fopen("member.txt", "w");
    if (memberFile == NULL) {
        printf("Error opening file.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(memberFile, "%s,%s,%s,%s,%c,%s,%s\n", memberInfo[i].ID, memberInfo[i].name, memberInfo[i].password, memberInfo[i].passwordRecov,
            memberInfo[i].gender, memberInfo[i].IC, memberInfo[i].contactNum);
    }

    fclose(memberFile);

    return;
}

void memberLogin(struct member memberInfo[], int count, int* memberLoggedInIndex) {
    char loginID[50], loginPassword[16];
    int loggedIn = 0;

    do {
        printf("Enter ID: ");
        rewind(stdin);
        scanf("%s", loginID);
        printf("Enter password (-1 if forgot password): ");

        // Mask the password input
        maskPassword(loginPassword);

        // unsigned does not allow negative int
        // Compare hashed passwords instead of plain text passwords
        unsigned int hashedPassword = hashPassword(loginPassword);

        for (int i = 0; i < count; i++) {
            if (strcmp(loginID, memberInfo[i].ID) == 0 && hashedPassword == hashPassword(memberInfo[i].password)) {
                loggedIn = 1;
                *memberLoggedInIndex = i;
                break;
            }
        }

        if (loggedIn) {
            system("cls");
            printf("Login successful!\n");
        }
        else {
            if (strcmp(loginPassword, "-1") == 0) {
                system("cls");
                passwordRecovery(memberInfo, count);
            }
            else {
                printf("Invalid username or password. Please try again.\n");
            }
        }

    } while (!loggedIn);
}

void passwordRecovery(struct member memberInfo[], int count) {
    char recoveryID[50], recoveryPw[21];
    char newPassword[16], confirmPassword[16];
    int index;

    printf("=================\n");
    printf("Password Recovery\n");
    printf("=================\n\n");

    printf("Enter ID: ");
    scanf("%s", recoveryID);

    for (int i = 0; i < count; i++) {
        if (strcmp(recoveryID, memberInfo[i].ID) == 0) {
            index = i;
            break;
        }
    }

    printf("Enter password recovery term: ");
    scanf("%s", recoveryPw);

    if (strcmp(recoveryPw, memberInfo[index].passwordRecov) != 0) {
        printf("Password Recovery term does not match.\n");
        return;
    }

    printf("Enter new password: ");
    maskPassword(newPassword);
    printf("Confirm new password: ");
    maskPassword(confirmPassword);

    if (strcmp(newPassword, confirmPassword) != 0) {
        printf("Passwords do not match.\n");
        return;
    }

    strcpy(memberInfo[index].password, newPassword);
    system("cls");
    printf("Password changed successfully.\n");
}

void viewMemberInfo(struct member memberInfo[], int count) {

    int back = 0;

    do {
        printf("=============================================================================================\n");
        printf("%-5s %-15s %-15s %-15s %-6s %-15s %-15s\n", "ID", "Name", "Password", "Password Recov", "Gender", "IC", "Contact Number");
        printf("=============================================================================================\n");
        for (int j = 0; j < count; j++) {
            printf("%-5s %-15s %-15s %-15s %-6c %-15s %-15s\n", memberInfo[j].ID, memberInfo[j].name, memberInfo[j].password, memberInfo[j].passwordRecov, memberInfo[j].gender, memberInfo[j].IC, memberInfo[j].contactNum);
        }

        int choice;

        printf("\n[ 1 ] Return to main menu\n");
        printf("[ 2 ] Add new member\n");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume newline character

        switch (choice) {
        case 1:
            back = 1;
            system("cls");
            return;
            break;
        case 2:
            system("cls");
            enterNewMember(memberInfo, &count);
            break;
        default:
            printf("Invalid choice.\n");
            break;
        }
    } while (back == 0);
}

void enterNewMember(struct member memberInfo[], int* count) {
    char confirm;

    printf("================\n");
    printf("Enter New Member\n");
    printf("================\n");

    do {
        int idExists = 0;
        do {
            printf("Enter ID: ");
            rewind(stdin);
            scanf("%s", memberInfo[*count].ID);

            for (int i = 0; i < *count; i++) {
                if (strcmp(memberInfo[i].ID, memberInfo[*count].ID) == 0) {
                    idExists = 1;
                    printf("ID already exists. Please enter a different ID.\n");
                    break;
                }
                else {
                    idExists = 0;
                    break;
                }
            }
        } while (idExists == 1);
        printf("Enter name: ");
        scanf(" %[^\n]", memberInfo[*count].name);
        printf("Enter password: ");
        scanf("%s", memberInfo[*count].password);
        printf("Enter password recovery: ");
        scanf("%s", memberInfo[*count].passwordRecov);
        do {
            printf("Enter gender (M/F): ");
            scanf(" %c", &memberInfo[*count].gender);
            memberInfo[*count].gender = toupper(memberInfo[*count].gender);
            if (memberInfo[*count].gender != 'M' && memberInfo[*count].gender != 'F') {
                printf("Invalid gender. Please enter 'M' for male or 'F' for female.\n");
            }
        } while (memberInfo[*count].gender != 'M' && memberInfo[*count].gender != 'F');
        printf("Enter IC: ");
        scanf("%s", memberInfo[*count].IC);
        printf("Enter contact number: ");
        scanf("%s", memberInfo[*count].contactNum);

        printf("Confirm the information (Y/N): ");
        scanf(" %c", &confirm);

        if (confirm == 'Y' || confirm == 'y') {
            FILE* filePtr = fopen("member.txt", "a");
            if (filePtr == NULL) {
                printf("Error opening file.\n");
                return;
            }

            fprintf(filePtr, "%s,%s,%s,%s,%c,%s,%s\n", memberInfo[*count].ID, memberInfo[*count].name, memberInfo[*count].password, memberInfo[*count].passwordRecov, memberInfo[*count].gender, memberInfo[*count].IC, memberInfo[*count].contactNum);

            fclose(filePtr);

            printf("Data has been stored in member.txt.\n");
            (*count)++;
        }
        else {
            printf("Data input aborted.\n");
        }

        printf("Enter another member? (Y/N): ");
        scanf(" %c", &confirm);

    } while (confirm == 'Y' || confirm == 'y');
}

void deleteMember(struct member memberInfo[], int* count) {
    char memberIDToDelete[6];
    char confirm;

    printf("=============\n");
    printf("Delete Member\n");
    printf("=============\n");

    printf("Enter the ID of the member to delete: ");
    scanf("%5s", memberIDToDelete);

    int foundIndex = -1;
    for (int i = 0; i < *count; i++) {
        if (strcmp(memberIDToDelete, memberInfo[i].ID) == 0) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex != -1) {
        printf("Member found:\n");
        printf("Name: %s\n", memberInfo[foundIndex].name);
        printf("Gender: %c\n", memberInfo[foundIndex].gender);
        printf("IC: %s\n", memberInfo[foundIndex].IC);
        printf("Contact Number: %s\n", memberInfo[foundIndex].contactNum);

        printf("Are you sure you want to delete this member? (Y/N): ");
        scanf(" %c", &confirm);

        if (confirm == 'Y' || confirm == 'y') {
            memberInfo[foundIndex] = memberInfo[*count - 1];
            (*count)--;
            system("cls");
            printf("Member deleted successfully.\n");
            updateMemberFile(memberInfo, *count);
        }
    }
    else {
        printf("Member with ID %s not found.\n", memberIDToDelete);
    }
    system("pause");
}

void editMemberProfile(struct member memberInfo[], int count, int staffLoggedInIndex) {
    int choice;
    do {
        char newName[31];
        char newPassword[3][16];
        char newIC[15];
        char newContactNum[13];
        char gender;

        printf("===========\n");
        printf("Edit Profile\n");
        printf("===========\n");
        printf("Name           : %s\n", memberInfo[staffLoggedInIndex].name);
        printf("Gender         : %c\n", memberInfo[staffLoggedInIndex].gender);
        printf("IC             : %s\n", memberInfo[staffLoggedInIndex].IC);
        printf("Contact Number : %s\n", memberInfo[staffLoggedInIndex].contactNum);

        printf("\nEdit:\n");
        printf("[ 1 ] Name\n");
        printf("[ 2 ] Password\n");
        printf("[ 3 ] Gender\n");
        printf("[ 4 ] IC\n");
        printf("[ 5 ] Contact Number\n");
        printf("[ 0 ] Exit\n");
        printf(">> ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("Enter new name: ");
            scanf(" %[^\n]", newName);
            system("cls");
            strcpy(memberInfo[staffLoggedInIndex].name, newName);
            break;

        case 2:
            printf("Enter current password: ");
            maskPassword(newPassword[0]);
            printf("Enter new password: ");
            maskPassword(newPassword[1]);
            printf("Confirm new password: ");
            maskPassword(newPassword[2]);
            if (strcmp(newPassword[0], memberInfo[staffLoggedInIndex].password) != 0) {
                printf("Incorrect current password.\n");
                break;
            }
            if (strcmp(newPassword[1], newPassword[2]) != 0) {
                printf("Passwords do not match.\n");
                break;
            }
            strcpy(memberInfo[staffLoggedInIndex].password, newPassword[1]);
            system("cls");
            printf("Password updated successfully.\n");
            break;


        case 3:
            printf("Enter new gender: ");
            scanf(" %c", &gender);
            if (gender != 'M' && gender != 'F') {
                printf("Invalid gender. Please enter 'M' for male or 'F' for female.\n");
                break;
            }

            memberInfo[staffLoggedInIndex].gender = gender;
            system("cls");
            printf("Gender updated successfully.\n");
            break;

        case 4:
            printf("Enter new IC: ");
            scanf("%14s", newIC);
            strcpy(memberInfo[staffLoggedInIndex].IC, newIC);
            system("cls");
            printf("IC updated successfully.\n");
            break;

        case 5:
            printf("Enter new contact number: ");
            scanf("%12s", newContactNum);
            strcpy(memberInfo[staffLoggedInIndex].contactNum, newContactNum);
            system("cls");
            printf("Contact number updated successfully.\n");
            break;

        case 0:
            system("cls");
            break;

        default:
            printf("Invalid choice.\n");
            break;
        }
    } while (choice != 0);
}

void exportMemberList(struct member memberInfo[], int* count) {

    char fileName[50];
    FILE* memberFile;
    FILE* exportFile;
    char line[100];

    printf("Enter file name to export (example: export.txt): ");
    scanf("%s", fileName);

    memberFile = fopen("member.txt", "r");
    if (memberFile == NULL) {
        printf("Error opening member.txt.\n");
        return;
    }

    exportFile = fopen(fileName, "w");
    if (exportFile == NULL) {
        printf("Error creating export file.\n");
        fclose(memberFile);
        return;
    }

    while (fscanf(memberFile, "%99[^\n]%*c", line) == 1) {
        fprintf(exportFile, "%s\n", line);
    }

    fclose(memberFile);
    fclose(exportFile);

    printf("Export completed.\n");
}

void importMemberList(struct member memberInfo[], int* count) {
    char fileName[50];
    FILE* importFile;
    FILE* memberFile;
    char confirm;

    struct member importMembers[MAX_MEMBERS];
    int importCount = 0;

    do {
        printf("Enter file name (example: import.txt): ");
        scanf("%s", fileName);

        importFile = fopen(fileName, "r");
        if (importFile == NULL) {
            printf("Error opening file.\n");
        }
    } while (importFile == NULL);

    printf("=======================================================================================================\n");
    printf("%-5s %-15s %-15s %-15s %-6s %-15s %-15s\n", "ID", "Name", "Password", "Password Recov", "Gender", "IC", "Contact Number");
    printf("=======================================================================================================\n");
    while (fscanf(importFile, "%5[^,],%30[^,],%14[^,],%19[^,],%c,%14[^,],%12[^,]\n",
        importMembers[importCount].ID, importMembers[importCount].name, importMembers[importCount].password, importMembers[importCount].passwordRecov,
        &importMembers[importCount].gender, importMembers[importCount].IC, importMembers[importCount].contactNum) != EOF) {
        printf("%-5s %-15s %-15s %-15s %-6c %-15s %-15s\n", importMembers[importCount].ID, importMembers[importCount].name, importMembers[importCount].password, importMembers[importCount].passwordRecov, importMembers[importCount].gender, importMembers[importCount].IC, importMembers[importCount].contactNum);
        importCount++;
    }

    fclose(importFile);

    printf("Confirm all imported data (Y/N): ");
    scanf(" %c", &confirm);

    if (confirm == 'Y' || confirm == 'y') {
        for (int i = 0; i < importCount; i++) {
            strcpy(memberInfo[*count + i].ID, importMembers[i].ID);
            strcpy(memberInfo[*count + i].name, importMembers[i].name);
            strcpy(memberInfo[*count + i].password, importMembers[i].password);
            strcpy(memberInfo[*count + i].passwordRecov, importMembers[i].passwordRecov);
            memberInfo[*count + i].gender = importMembers[i].gender;
            strcpy(memberInfo[*count + i].IC, importMembers[i].IC);
            strcpy(memberInfo[*count + i].contactNum, importMembers[i].contactNum);
        }

        *count += importCount;

        memberFile = fopen("member.txt", "a");

        for (int i = 0; i < importCount; i++) {
            fprintf(memberFile, "%s,%s,%s,%s,%c,%s,%s,%s\n", importMembers[i].ID, importMembers[i].name, importMembers[i].password, importMembers[i].passwordRecov, importMembers[i].gender, importMembers[i].IC, importMembers[i].contactNum);
        }

        fclose(memberFile);
    }
    else {
        printf("Data import aborted.\n");
    }
}

//SCHEDULING MODULE (done by: Chaw Chun Jia)

void addTrain() {
    int selection, trainFound = 0;
    char confirm, userEnterID[6];

    Train addT;
    do {
        FILE* fptr = fopen("Train.bin", "ab+");
        if (fptr == NULL) {
            printf("Unable to open file.\n");
            return;
        }
    Enter:
        system("cls");
        do {
            trainFound = 0;
            printf("Enter Train ID (eg:T1001)          : ");
            rewind(stdin);
            scanf("%s", userEnterID);

            // Read through the file to check if train ID already exists
            rewind(fptr);
            while (fread(&addT, sizeof(Train), 1, fptr)) {
                if (strcmp(userEnterID, addT.trainId) == 0) { // Train ID exists
                    printf("\nTrain ID already exists. Please enter another ID.\n");
                    trainFound = 1;
                    break;
                }
            }
        } while (trainFound);

        strcpy(addT.trainId, userEnterID);
        printf("Enter Departure Station            : ");
        rewind(stdin);
        scanf("%[^\n]", addT.departureStation);
        printf("Enter Arrival Station              : ");
        rewind(stdin);
        scanf("%[^\n]", addT.arrivalStation);
        printf("Enter Departure Time(eg:23:30)     : ");
        rewind(stdin);
        scanf("%d:%d", &addT.departureTime.hour, &addT.departureTime.minute);
        printf("Enter Departure Date(eg:31-12-2024): ");
        rewind(stdin);
        scanf("%d-%d-%d", &addT.departureTime.day, &addT.departureTime.month, &addT.departureTime.year);
        printf("Enter Available Seats              : ");
        rewind(stdin);
        scanf("%d", &addT.availableSeats);

        system("cls");
        printf("Train ID         : %s\n", addT.trainId);
        printf("Departure Station: %s\n", addT.departureStation);
        printf("Arrival Station  : %s\n", addT.arrivalStation);
        printf("Departure Time   : %02d:%02d\n", addT.departureTime.hour, addT.departureTime.minute);
        printf("Departure Date   : %02d-%02d-%04d\n", addT.departureTime.day, addT.departureTime.month, addT.departureTime.year);
        printf("Available seats  : %d\n", addT.availableSeats);

        printf("\nConfirm Your information are correct:\n");
        printf("[1] Correct\n");
        printf("[2] Incorrect (Re-Enter Again)\n");
        printf("[3] Back To Schedulling Menu without saving\n");
        printf(">>>>>>>>>>>> ");
        scanf("%d", &selection);

        switch (selection) {
        case 1:
            fwrite(&addT, sizeof(Train), 1, fptr);
            printf("\nData Saved\n");
            fclose(fptr);
            printf("\nEnter more Information? (Press 'Y'): ");
            rewind(stdin);
            scanf("%c", &confirm);
            confirm = toupper(confirm);
            break;
        case 2:
            goto Enter;
            break;
        case 3:
            fclose(fptr);
            return;
        }
        fclose(fptr);
    } while (confirm == 'Y');
    system("cls");
}

void displayTrain() {
    char value;
    Train addT;
    int found = 0;

    FILE* fptr = fopen("Train.bin", "rb");
    if (fptr == NULL) {
        printf("Unable to open file.\n");
        exit(-1);
    }

    system("cls");
    printf("%50s\n", "All Train Available");
    printf("%-10s%-20s%-20s%-20s%-20s%s\n", "Train ID", "Departure Station", "Arrival Station", "Departure Time", "Departure Date", "Available Seat");
    while (fread(&addT, sizeof(Train), 1, fptr)) {
        printf("%-10s%-20s%-20s%02d:%02d%18s%02d-%02d-%02d%20d\n", addT.trainId, addT.departureStation, addT.arrivalStation, addT.departureTime.hour, addT.departureTime.minute, "", addT.departureTime.day, addT.departureTime.month, addT.departureTime.year, addT.availableSeats);
        found++;
    }
    fclose(fptr);

    printf("\n%d record found in file.\n", found);

    do {
        printf("\nEnter 'Y' to return menu.\n");
        printf(">>>>>>>>>>");
        rewind(stdin);
        scanf(" %c", &value);
        value = toupper(value);
    } while (value != 'Y');
    return;
}

void adminSearchTrain() {
    int found = 0;
    char userEnterID[6], value;

    Train addT;
    FILE* fptr = fopen("Train.bin", "rb");

    system("cls");
    printf("Enter Train ID you're going to search: ");
    rewind(stdin);
    scanf("%s", userEnterID);
    while (fread(&addT, sizeof(Train), 1, fptr)) {
        if (strcmp(userEnterID, addT.trainId) == 0) {
            system("cls");
            printf("%50s\n", "Train Found");
            printf("%-10s%-20s%-20s%-20s%-20s%s\n", "Train ID", "Departure Station", "Arrival Station", "Departure Time", "Departure Date", "Available Seat");
            printf("%-10s%-20s%-20s%02d:%02d%18s%02d-%02d-%02d%20d\n", addT.trainId, addT.departureStation, addT.arrivalStation, addT.departureTime.hour, addT.departureTime.minute,"", addT.departureTime.day, addT.departureTime.month, addT.departureTime.year, addT.availableSeats);
            found++;
            break;
        }
    }

    if (found == 0)
        printf("No records found.\n");

    do {
        // Prompt the user to return or perform another operation
        printf("\nEnter 'Y' to return to the scheduling menu or 'N' to search another train.\n");
        printf(">>>>>>>>>>");
        rewind(stdin);
        scanf(" %c", &value);
        value = toupper(value);
    } while (value != 'Y' && value != 'N');
    fclose(fptr);
    if (value == 'Y') {
        return;
    }
    else {
        adminSearchTrain(); // Loop back to search another train
    }
}

void modifyTrain() {
    int found = 0, selection, trainFound;
    char userEnterID[6], confirm, value;
    FILE* fptr = fopen("Train.bin", "r+b"); //open file in read-write mode
    Train addT;
    Train edit;

    if (fptr == NULL) {
        printf("Unable to open file.\n");
        return;
    }

    do {
        system("cls");
        printf("Enter Train ID you're going to modify: ");
        rewind(stdin);
        scanf(" %s", userEnterID);
        rewind(fptr); // Reset file pointer to the beginning of the file

        found = 0;
        while (fread(&addT, sizeof(Train), 1, fptr)) {
            if (strcmp(userEnterID, addT.trainId) == 0) {
                found = 1;
                printf("%-10s%-20s%-20s%-20s%-20s%s\n", "Train ID", "Departure Station", "Arrival Station", "Departure Time", "Departure Date", "Available Seat");
                printf("%-10s%-20s%-20s%d:%02d%18s%02d-%02d-%02d%20d\n", addT.trainId, addT.departureStation, addT.arrivalStation, addT.departureTime.hour, addT.departureTime.minute,"", addT.departureTime.day, addT.departureTime.month, addT.departureTime.year, addT.availableSeats);
                break;
            }
        }

        if (found == 0) {
            printf("No records found.\n");
            do {
                // Prompt the user to return or perform another operation
                printf("\nEnter 'Y' to return to the scheduling menu or 'N' to modify another train.\n");
                printf(">>>>>>>>>>");
                rewind(stdin);
                scanf(" %c", &confirm);
                confirm = toupper(confirm);
            } while (confirm != 'Y' && confirm != 'N');

            if (confirm == 'Y') {
                return;
            }
            else {
                modifyTrain(); // Loop back to modify another train
            }
        }
        else {
            do {
                printf("\n");
                printf("[1] Edit Departure Station\n");
                printf("[2] Edit Arrival Station\n");
                printf("[3] Edit Departure Time\n");
                printf("[4] Edit Departure Date\n");
                printf("[5] Edit Available seat\n");
                printf("[6] Return to schedulling menu\n");
                printf(">>>>>>>>>>>>>>>> ");
                rewind(stdin);
                scanf("%d", &selection);
                switch (selection) {
                case 1:
                    printf("Enter new train departure station: ");
                    scanf(" %[^\n]", edit.departureStation);
                    strcpy(addT.departureStation, edit.departureStation);
                    break;

                case 2:
                    printf("Enter new train arrival station: ");
                    scanf(" %[^\n]", edit.arrivalStation);
                    strcpy(addT.arrivalStation, edit.arrivalStation);
                    break;

                case 3:
                    printf("Enter new train departure time (eg: 23:30): ");
                    scanf("%d:%d", &edit.departureTime.hour, &edit.departureTime.minute);
                    addT.departureTime.hour = edit.departureTime.hour;
                    addT.departureTime.minute = edit.departureTime.minute;
                    break;

                case 4:
                    printf("Enter new train departure date (eg: 31-12-2023): ");
                    scanf("%d-%d-%d", &edit.departureTime.day, &edit.departureTime.month, &edit.departureTime.year);
                    addT.departureTime.day = edit.departureTime.day;
                    addT.departureTime.month = edit.departureTime.month;
                    addT.departureTime.year = edit.departureTime.year;
                    break;

                case 5:
                    printf("Edit available seat: ");
                    scanf("%d", &edit.availableSeats);
                    addT.availableSeats = edit.availableSeats;
                    break;

                case 6:
                    fclose(fptr);
                    return;
                    break;

                default:
                    printf("Invalid value. Please Enter again.\n\n");
                }
            } while (selection < 1 || selection > 7);
        }
        // Calculate the current position in the file
        long currentPosition = ftell(fptr);
        // Move the file pointer back to the beginning of the current train record
        fseek(fptr, currentPosition - sizeof(Train), SEEK_SET);
        // Write the modified train information back to the file
        fwrite(&addT, sizeof(Train), 1, fptr);
        // Move the file pointer back to the original position
        fseek(fptr, currentPosition, SEEK_SET);

        printf("%40s\n", "New Train Information");
        printf("%-10s%-20s%-20s%-20s%-20s%s\n", "Train ID", "Departure Station", "Arrival Station", "Departure Time", "Departure Date", "Available Seat");
        printf("%-10s%-20s%-20s%02d:%02d%18s%02d-%02d-%02d%20d\n", addT.trainId, addT.departureStation, addT.arrivalStation, addT.departureTime.hour, addT.departureTime.minute,"", addT.departureTime.day, addT.departureTime.month, addT.departureTime.year, addT.availableSeats);
        do {
            printf("\n\nEnter 'Y' for editing more information.\n");
            printf("Enter 'N' for back to schedulling menu.\n");
            printf(">>>>>>>>>>>>> ");
            scanf(" %c", &confirm);
            confirm = toupper(confirm);
        } while (confirm != 'Y' && confirm != 'N');
    } while (confirm == 'Y');
    fclose(fptr); // Close the file
    return;
}

void backupTrain() {
    int selection, found = 0;
    Train addT;
    Train backupT;
    FILE* fp, * fptr;
    fp = fopen("backupTrain.bin", "r+b");
    if (fp == NULL) {
        fp = fopen("backupTrain.bin", "w+b");
    }
    fptr = fopen("Train.bin", "rb");
    if (fptr == NULL) {
        printf("Error opening Train.bin\n");
        return;
    }
    printf("%50s\n", "All Train Available");
    printf("%-10s%-20s%-20s%-20s%-20s%s\n", "Train ID", "Departure Station", "Arrival Station", "Departure Time", "Departure Date", "Available Seat");
    while (fread(&addT, sizeof(Train), 1, fptr)) {
        printf("%-10s%-20s%-20s%02d:%02d%18s%02d-%02d-%02d%20d\n", addT.trainId, addT.departureStation, addT.arrivalStation, addT.departureTime.hour, addT.departureTime.minute,"", addT.departureTime.day, addT.departureTime.month, addT.departureTime.year, addT.availableSeats);
        found++;
    }
    printf("\n%d record found in file.\n", found);

select:
    printf("\n");
    printf("[ 1 ] Backup Current Train to File\n");
    printf("[ 2 ] Display Current Backup Train\n");
    printf("[ 3 ] Back To Menu\n");
    printf(">> ");
    scanf("%d", &selection);

    switch (selection) {
    case 1:
        system("cls");
        rewind(fptr); // Move file pointer back to the beginning
        while (fread(&addT, sizeof(Train), 1, fptr) == 1) {
            fwrite(&addT, sizeof(Train), 1, fp);
        }
        printf("\nBackup Completed\n");
        break;
    case 2:
        system("cls");
        rewind(fp); // Move file pointer back to the beginning
        printf("%40s\n", "Train Information");
        printf("%-10s%-20s%-20s%-20s%-20s%s\n", "Train ID", "Departure Station", "Arrival Station", "Departure Time", "Departure Date", "Available Seat");
        while (fread(&backupT, sizeof(Train), 1, fp) == 1) {
            printf("%-10s%-20s%-20s%02d:%02d%18s%02d-%02d-%02d%20d\n", backupT.trainId, backupT.departureStation, backupT.arrivalStation, backupT.departureTime.hour, backupT.departureTime.minute,"", backupT.departureTime.day, backupT.departureTime.month, backupT.departureTime.year, backupT.availableSeats);
        }
        break;
    case 3:
        system("cls");
        fclose(fp);
        fclose(fptr);
        return;
    default:
        printf("Invalid Choice\n");
        goto select;
    }
    goto select;
    fclose(fp);
    fclose(fptr);
}

void deleteTrain()
{
    Train train;
    char deleteID[10], confirm;
    int found = 0;

    FILE* fp, * fptemp;

    fp = fopen("Train.bin", "rb");
    if (!fp)
    {
        printf("File error opening");
        exit(-1);
    }

    fptemp = fopen("temp.bin", "wb");
    if (!fptemp)
    {
        printf("File error opening");
        exit(-1);
    }

    system("cls");
    printf("%50s\n", "All Train Available");
    printf("%-10s%-20s%-20s%-20s%-20s%s\n", "Train ID", "Departure Station", "Arrival Station", "Departure Time", "Departure Date", "Available Seat");

    // Read and display all train records
    while (fread(&train, sizeof(Train), 1, fp)) {
        printf("%-10s%-20s%-20s%02d:%02d%18s%02d-%02d-%02d%20d\n", train.trainId, train.departureStation, train.arrivalStation, train.departureTime.hour, train.departureTime.minute,"", train.departureTime.day, train.departureTime.month, train.departureTime.year, train.availableSeats);
    }

    printf("Enter a Train ID to delete: ");
    rewind(stdin);
    gets(deleteID);

    rewind(fp); // Rewind the file pointer to read from the beginning

    while (fread(&train, sizeof(Train), 1, fp))
    {
        if (strcmp(train.trainId, deleteID) == 0)
        {
            found++;
            printf("Deleting the record...\n");
            printf("Record %s deleted successfully\n", deleteID);
            continue; // Skip writing this record to the temp file
        }
        fwrite(&train, sizeof(Train), 1, fptemp);
    }

    fclose(fp);
    fclose(fptemp);

    if (!found)
    {
        printf("Record ID %s not existed \n", deleteID);
        remove("temp.bin");
    }
    else
    {
        remove("Train.bin");
        rename("temp.bin", "Train.bin");
    }

    do {
        // Prompt the user to delete more or return to scheduling menu
        printf("\nEnter 'Y' to delete more or 'N' to return to scheduling menu.\n");
        printf(">>>>>>>>>>");
        rewind(stdin);
        scanf(" %c", &confirm);
        confirm = toupper(confirm);
    } while (confirm != 'Y' && confirm != 'N');

    if (confirm == 'Y') {
        deleteTrain(); // Recursive call to delete more
    }
    else {
        return;
    }
}

//STAFF MODULE (done by: Wong Shun Bin)

void editStaffProfile(Staff staffInfo[], int count, int staffLoggedInIndex) {
    int choice;
    do {
        char newName[31];
        char newPassword[3][16];
        char newPosition[13];

        system("cls");

        printf("============\n");
        printf("Edit Profile\n");
        printf("============\n");
        printf("Name           : %s\n", staffInfo[staffLoggedInIndex].Staff_Name);
        printf("Password       : %s\n", staffInfo[staffLoggedInIndex].Staff_Pass);
        printf("Position       : %s\n", staffInfo[staffLoggedInIndex].position);

        printf("\nEdit:\n");
        printf("[ 1 ] Name\n");
        printf("[ 2 ] Password\n");
        printf("[ 3 ] Position\n");
        printf("[ 0 ] Exit\n");
        printf(">> ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("Enter new name: ");
            scanf(" %[^\n]", newName);
            system("cls");
            strcpy(staffInfo[staffLoggedInIndex].Staff_Name, newName);
            break;

        case 2:
            printf("Enter current password: ");
            maskPassword(newPassword[0]);
            printf("Enter new password: ");
            maskPassword(newPassword[1]);
            printf("Confirm new password: ");
            maskPassword(newPassword[2]);
            if (strcmp(newPassword[0], staffInfo[staffLoggedInIndex].Staff_Pass) != 0) {
                printf("Incorrect current password.\n");
                break;
            }
            if (strcmp(newPassword[1], newPassword[2]) != 0) {
                printf("Passwords do not match.\n");
                break;
            }
            strcpy(staffInfo[staffLoggedInIndex].Staff_Pass, newPassword[1]);
            printf("Password updated successfully.\n");
            break;


        case 3:
            printf("Enter new Position: ");
            scanf(" %[^\n]", newPosition);
            system("cls");
            strcpy(staffInfo[staffLoggedInIndex].position, newPosition);
            break;

        case 0:
            printf("Exiting edit profile.\n");
            break;

        default:
            printf("Invalid choice.\n");
            break;
        }
    } while (choice != 0);
}

void loginStaff(Staff staffInfo[], int count, int* staffLoggedInIndex) {
    char loginID[50], loginPassword[16];
    int loggedIn = 0;

    do {
        printf("Enter ID: ");
        scanf("%s", loginID);

        printf("Enter password: ");

        // Mask the password input
        maskPassword(loginPassword);

        // unsigned does not allow negative int
        // Compare hashed passwords instead of plain text passwords
        unsigned int hashedPassword = hashPassword(loginPassword);

        for (int i = 0; i < count; i++) {
            if (strcmp(loginID, staffInfo[i].Staff_Id) == 0 && hashedPassword == hashPassword(staffInfo[i].Staff_Pass)) {
                loggedIn = 1;
                *staffLoggedInIndex = i;
                break;
            }
        }

        if (loggedIn) {
            system("cls");
            printf("Login successful!\n");
        }
        else {
            printf("Invalid username or password. Please try again.\n");
        }

    } while (!loggedIn);
}

void updateStaffFile(Staff staffInfo[], int count) {
    FILE* filePtr = fopen("staff.txt", "w");
    if (filePtr == NULL) {
        printf("Error opening file.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(filePtr, "%s,%s,%s,%s,%s\n", staffInfo[i].Staff_Id, staffInfo[i].Staff_Name, staffInfo[i].Staff_Pass, staffInfo[i].Staff_PassRec,
            staffInfo[i].position);
    }

    fclose(filePtr);
    printf("Staff information updated.\n");

    return;
}

void viewStaffInfo(Staff staffInfo[], int count) {
    int back = 0;
    int choice;

    do {
        FILE* filePtr = fopen("staff.txt", "r");
        if (filePtr == NULL) {
            printf("Error opening file.\n");
            return;
        }
        printf("======================\n");
        printf("View Staff Information\n");
        printf("======================\n");
        printf("=======================================================================================================\n");
        printf("%-5s %-15s %-15s %-15s %-15s\n", "ID", "Name", "Password", "Password Recov", "Position");
        printf("=======================================================================================================\n");

        while (fscanf(filePtr, "%5[^,],%99[^,],%20[^,],%20[^,],%99[^\n]\n",
            staffInfo[count].Staff_Id, staffInfo[count].Staff_Name, staffInfo[count].Staff_Pass, staffInfo[count].Staff_PassRec,
            &staffInfo[count].position) == 5) {
            printf("%-5s %-15s %-15s %-15s %-15s\n", staffInfo[count].Staff_Id, staffInfo[count].Staff_Name, staffInfo[count].Staff_Pass, staffInfo[count].Staff_PassRec, staffInfo[count].position);
            count++;
        }

        fclose(filePtr);

        printf("\n[ 1 ] Return to main menu\n");
        printf("[ 2 ] Delete a staff\n");
        printf("[ 3 ] Add new staff\n");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
        case 1:
            back = 1;
            system("cls");
            return;
            break;
        case 2:
            system("cls");
            deleteStaff(staffInfo, &count);
            break;
        case 3:
            system("cls");
            enterNewStaff(staffInfo, &count);
            break;
        default:
            printf("Invalid choice.\n");
            break;
        }
    } while (back == 0);
}

void enterNewStaff(Staff staffInfo[], int* count) {
    char confirm;

    printf("===============\n");
    printf("Enter New Staff\n");
    printf("===============\n\n");

    do {
        int idExists = 0;
        do {
            printf("Enter ID: ");
            rewind(stdin);
            scanf("%s", staffInfo[*count].Staff_Id);

            for (int i = 0; i < *count; i++) {
                if (strcmp(staffInfo[i].Staff_Id, staffInfo[*count].Staff_Id) == 0) {
                    idExists = 1;
                    printf("ID already exists. Please enter a different ID.\n");
                    break;
                }
                else {
                    idExists = 0;
                    break;
                }
            }
        } while (idExists == 1);
        printf("Enter name: ");
        scanf(" %[^\n]", staffInfo[*count].Staff_Name);
        printf("Enter password: ");
        scanf("%20s", staffInfo[*count].Staff_Pass);
        printf("Enter password recovery: ");
        scanf("%20s", staffInfo[*count].Staff_PassRec);
        printf("Enter Position: ");
        scanf(" %[^\n]", staffInfo[*count].position);

        printf("Confirm the information (Y/N): ");
        scanf(" %c", &confirm);

        if (confirm == 'Y' || confirm == 'y') {
            FILE* filePtr = fopen("staff.txt", "a");
            if (filePtr == NULL) {
                printf("Error opening file.\n");
                return;
            }

            fprintf(filePtr, "%s,%s,%s,%s,%s\n", staffInfo[*count].Staff_Id, staffInfo[*count].Staff_Name, staffInfo[*count].Staff_Pass, staffInfo[*count].Staff_PassRec, staffInfo[*count].position);

            fclose(filePtr);

            printf("Data has been stored in staff.txt.\n");
            (*count)++;
        }
        else {
            printf("Data input aborted.\n");
        }

        printf("Enter another staff? (Y/N): ");
        scanf(" %c", &confirm);

    } while (confirm == 'Y' || confirm == 'y');
}

void backupStaff(Staff staffInfo[], int count) {
    FILE* filePtr = fopen("backup_Staff.txt", "w");
    if (filePtr == NULL) {
        printf("Unable to open file for writing.\n");
        return;
    }
    char backup;
    printf("=====================\n");
    printf("Back Up Staff Records\n");
    printf("=====================\n\n");
    printf("Do you want to backup staff record (Y/N)?");
    rewind(stdin);
    scanf("%c", &backup);
    if (backup == 'Y' || backup == 'y') {
        for (int i = 0; i < count; i++) {
            fprintf(filePtr, "%s,%s,%s,%s,%s\n", staffInfo[i].Staff_Id, staffInfo[i].Staff_Name, staffInfo[i].Staff_Pass, staffInfo[i].Staff_PassRec, staffInfo[i].position);
        }

        fclose(filePtr);
        printf("Records saved to file successfully.\n");
    }
    else {
        printf("Backup canceled.\n");
    }
}

void deleteStaff(Staff staffInfo[], int* count) {
    char delete_Id[6];
    char confirm;
    printf("========================\n");
    printf("Delete Staff Information\n");
    printf("========================\n\n");
    printf("Enter Staff Id that you want to delete:");
    scanf("%s", &delete_Id);

    int found = -1;
    for (int i = 0; i < *count; i++) {
        if (strcmp(delete_Id, staffInfo[i].Staff_Id) == 0) {
            found = i;
            break;
        }
    }

    if (found != -1) {
        printf("Staff details found:\n");
        printf("Name: %s\n", staffInfo[found].Staff_Name);
        printf("Position: %s\n", staffInfo[found].position);

        printf("Are you sure you want to delete this staff? (Y/N): ");
        scanf(" %c", &confirm);

        if (confirm == 'Y' || confirm == 'y') {
            for (int i = found; i < *count - 1; i++) {
                staffInfo[i] = staffInfo[i + 1];
            }
            (*count)--;
            printf("Staff deleted successfully.\n");
            updateStaffFile(staffInfo, *count);
        }
    }
    else {
        printf("Staff ID %s not found.\n", delete_Id);
    }
    system("pause");
}

void searchStaff(Staff staffInfo[], int count) {
    char search_Id[6];
    FILE* filePtr = fopen("staff.txt", "r");
    if (filePtr == NULL) {
        printf("Error opening file.\n");
        return 0;
    }
    printf("========================\n");
    printf("Search Staff Information\n");
    printf("========================\n\n");
    printf("Enter Staff Id that you want to search:");
    rewind(stdin);
    scanf("%5s", search_Id);

    int found = 0;
    for (int i = 0; i < count; i++) {
        if (strcmp(staffInfo[i].Staff_Id, search_Id) == 0) {
            printf("============================================\n");
            printf("Staff ID: %s\n", staffInfo[i].Staff_Id);
            printf("Staff Name: %s\n", staffInfo[i].Staff_Name);
            printf("Staff Position: %s\n", staffInfo[i].position);
            printf("============================================\n");
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("No record found, please key in the correct ID.\n");
    }
    fclose(filePtr);

    system("pause");

    return;
}

//TRAIN BOOKING MODULE (done by: Goh Chun Wen) 

int BuyTicket(struct member memberInfo[], int count, int memberLoggedInIndex)
{
    system("cls");
    printf("Welcome to Ticket Booking Module!\n\n");
    Train train;
    Booking booking;
    Customer customer;
    Date time;

    FILE* trainFile;
    trainFile = fopen("train.bin", "rb");
    FILE* customerBooking;
    customerBooking = fopen("customerBooking.bin", "a+b");
    FILE* bookingFile = fopen("lastBookingID.bin", "r+b");

    if (trainFile == NULL || customerBooking == NULL || bookingFile == NULL) {
        system("cls");
        printf("Failed to open the file.\n");
        exit(-1);
    }

    char depStat[50];
    char arrStat[50];
    char trainID[6];
    int requestedSeats;
    int ticketSelection;
    int ticketPass = 0;
    char paymentMethod[21];
    char choice;
    int numTrains = 0;

    do {
        rewind(stdin);
        printf("Enter your Departure Station: ");
        scanf("%[^\n]", depStat);
        rewind(stdin);
        printf("Enter your Arrival Station: ");
        scanf(" %[^\n]", arrStat);

        rewind(trainFile);
        int foundMatch = 0; //Variable to indicate if a train is found

        printf("%-10s%-20s%-20s%-20s%-20s%s\n", "Train ID", "Departure Station", "Arrival Station", "Departure Time", "Departure Date", "Available Seat");
        while (fread(&train, sizeof(Train), 1, trainFile) != 0) {
            if (strcmp(depStat, train.departureStation) == 0 && strcmp(arrStat, train.arrivalStation) == 0) {
                foundMatch = 1;
                printf("%-10s%-20s%-20s%02d:%-20d%02d-%02d-%04d%20d\n",
                    train.trainId, train.departureStation, train.arrivalStation, train.departureTime.hour, train.departureTime.minute, train.departureTime.day, train.departureTime.month, train.departureTime.year, train.availableSeats);
                break;
            }
        }

        if (!foundMatch) {
            printf("\nNo train found for the given Departure and Arrival Station!\n");
            printf("Do you want to try again? (Y/N)\n");
            scanf(" %c", &choice);
            if (choice == 'N' || choice == 'n') {
                fclose(trainFile);
                return;
            }
            else if (choice == 'Y' || choice == 'y') {
                rewind(trainFile); // Reset the file pointer to read from the beginning
                numTrains = 0; // Reset numTrains to start from the beginning of the train array
                system("cls");
            }
            else {
                printf("Invalid choice. Exiting.\n");
                fclose(trainFile);
                return -1;
            }
        }
        else {
            break; // Exit the loop if a match is found
        }

    } while (1); // Infinite loop, breaks are used to exit



    printf("Enter Train ID to book: ");
    rewind(stdin);
    scanf("%[^\n]", trainID);
    printf("Enter the number of seats you want: ");
    rewind(stdin);
    scanf("%d", &requestedSeats);

    if (strcmp(trainID, train.trainId) == 0)
    {
        if (train.availableSeats >= requestedSeats)
        { //IF HAVE SEATS
            train.availableSeats -= requestedSeats;

        payment:
            system("cls");
            printf("Total payment will be (RM10 x %d) : RM%.2f\n", requestedSeats, (10.0 * requestedSeats));
            printf("Please Select Your Payment Method:\n");
            printf("[1]Credit Card\n");
            printf("[2]Cash\n");
            printf("[3]Ewallet\n");
            printf("[4]Cancel Booking\n\n");
            scanf("%d", &ticketSelection);

            switch (ticketSelection)
            {
            case 1:
                ticketPass = 1;
                strcpy(paymentMethod, "Credit Card");
                break;
            case 2:
                strcpy(paymentMethod, "Cash");
                ticketPass = 1;
                break;
            case 3:
                strcpy(paymentMethod, "Ewallet");
                ticketPass = 1;
                break;
            case 4: // Corrected case label
                printf("Thanks for your visit!\n");
                return;
                break;
            default:
                printf("Invalid input! Please try again!\n");
                goto payment;
            }


            if (ticketPass == 1)
            {
                system("cls");
                int bookingID;
                fread(&bookingID, sizeof(int), 1, bookingFile);
                bookingID++;
                fseek(bookingFile, 0, SEEK_SET); // Move file pointer to the beginning
                fwrite(&bookingID, sizeof(int), 1, bookingFile);

                printf("Payment Successful. Your booking details are as below:\n");
                printf("Booking ID        : B%d\n", bookingID);
                printf("Customer ID       : %s\n", memberInfo[memberLoggedInIndex].ID);
                printf("Customer Name     : %s\n", memberInfo[memberLoggedInIndex].name);
                printf("Payment Method    : %s\n", paymentMethod);
                printf("Train ID          : %s\n", trainID);
                printf("Departure Station : %s\n", depStat);
                printf("Departure Date    : %02d-%02d-%04d\n", train.departureTime.day, train.departureTime.month, train.departureTime.year);
                printf("Departure Time    : %02d:02%d\n", train.departureTime.hour, train.departureTime.minute);
                printf("Seats Booked      : %d\n", requestedSeats);

                booking.bookingID = bookingID;
                strcpy(booking.customerID, memberInfo[memberLoggedInIndex].ID);
                strcpy(booking.customerName, memberInfo[memberLoggedInIndex].name);
                strcpy(booking.paymentMethod, paymentMethod);
                strcpy(booking.trainID, trainID);
                strcpy(booking.departureStation, depStat);
                booking.departureTime = train.departureTime;
                booking.seatsBooked = requestedSeats;

                fwrite(&booking, sizeof(Booking), 1, customerBooking);
                fclose(customerBooking);
            }
            // Rewind the train file to read from the beginning
            rewind(trainFile);

            // Open a temporary file for writing
            FILE* tempTrainFile = fopen("temp_train.bin", "wb");
            if (tempTrainFile == NULL) {
                printf("Failed to open the temporary file.\n");
                return -1;
            }

            system("pause");

            // Read train records from the original file, update the seats for the specific train, and write back to the temporary file
            while (fread(&train, sizeof(Train), 1, trainFile) != 0) {
                if (strcmp(trainID, train.trainId) == 0) {
                    // Update the seats for the specific train
                    train.availableSeats -= requestedSeats;
                }
                // Write the train record to the temporary file
                fwrite(&train, sizeof(Train), 1, tempTrainFile);
            }

            // Close both the original train file and the temporary file
            fclose(trainFile);
            fclose(tempTrainFile);

            // Delete the original train file
            remove("train.bin");

            // Rename the temporary train file to the original file name
            rename("temp_train.bin", "train.bin");
        }
        else {
            printf("Insufficient seats available.\n\n\n");

            system("pause");
        }
    }
    else {
        printf("Invalid Train ID.\n");
        return -1;
    }

    fclose(bookingFile);
    fclose(trainFile);

    printf("\n\n");
    return;
}

void ModifyBooking(struct member memberInfo[], int count, int memberLoggedInIndex) {
    FILE* fptr;
    FILE* tempFptr;
    FILE* fptr2;
    FILE* tempFptr2;
    Booking booking;
    Train train;

    fptr = fopen("customerBooking.bin", "r+b");
    tempFptr = fopen("temp_customerBooking.bin", "wb");
    fptr2 = fopen("Train.bin", "r+b");
    tempFptr2 = fopen("temp_train.bin", "wb");

    if (fptr == NULL || tempFptr == NULL || fptr2 == NULL || tempFptr2 == NULL) {
        printf("Error opening files.\n");
        return;
    }

    int tempBook;
    int found = 0;

    printf("Your bookings:\n\n");
    printf("================================================================================\n");
    printf("%-13s%-13s%-25s%-15s%-16s\n", "Booking ID", "Customer ID", "Customer Name", "Departure Date", "Departure Time");
    printf("================================================================================\n");

    while (fread(&booking, sizeof(Booking), 1, fptr) != 0) {
        if (strcmp(memberInfo[memberLoggedInIndex].ID, booking.customerID) == 0) {
            printf("B%-12d", booking.bookingID);
            printf("%-13s", booking.customerID);
            printf("%-25s", booking.customerName);
            printf("%02d-%02d-%-9d", booking.departureTime.day, booking.departureTime.month, booking.departureTime.year);
            printf("%02d:%-9d\n", booking.departureTime.hour, booking.departureTime.minute);
            found = 1;
        }
    }

    if (!found) {
        printf("\n\nNo Booking(s) Found!!\n");
        fclose(fptr);
        fclose(tempFptr);
        fclose(fptr2);
        fclose(tempFptr2);
        system("pause");
        remove("temp_customerBooking.bin");
        remove("temp_train.bin");
        return;
    }

    printf("Select booking to be modified (0 to cancel): B");
    scanf("%d", &tempBook);

    if (tempBook != 0) {
        rewind(fptr);
        while (fread(&booking, sizeof(Booking), 1, fptr) != 0) {
            if (tempBook == booking.bookingID && strcmp(memberInfo[memberLoggedInIndex].ID, booking.customerID) == 0) {
                int newSeats;
                printf("Enter new number of seats (0 to delete): ");
                scanf("%d", &newSeats);

                if (newSeats == 0) {
                    // If newSeats is 0, remove the entire booking
                    while (fread(&train, sizeof(Train), 1, fptr2) != 0) {
                        if (strcmp(booking.trainID, train.trainId) == 0 && strcmp(booking.departureStation, train.departureStation) == 0) {
                            train.availableSeats += booking.seatsBooked;
                            fwrite(&train, sizeof(Train), 1, tempFptr2);
                        }
                        else {
                            fwrite(&train, sizeof(Train), 1, tempFptr2);
                        }
                    }
                    printf("Booking deleted successfully.\n");
                    system("pause");
                }
                else {
                    // Calculate the difference between new and old seats
                    int seatDifference = newSeats - booking.seatsBooked;

                    // Update the seats booked for the booking
                    booking.seatsBooked = newSeats;
                    printf("Seats modified successfully.\n");
                    fwrite(&booking, sizeof(Booking), 1, tempFptr);

                    // Update the available seats of the respective train
                    while (fread(&train, sizeof(Train), 1, fptr2) != 0) {
                        if (strcmp(booking.trainID, train.trainId) == 0 && strcmp(booking.departureStation, train.departureStation) == 0) {
                            train.availableSeats -= seatDifference;
                            fwrite(&train, sizeof(Train), 1, tempFptr2);
                        }
                        else {
                            fwrite(&train, sizeof(Train), 1, tempFptr2);
                        }
                    }
                    system("pause");
                }
            }
            else {
                fwrite(&booking, sizeof(Booking), 1, tempFptr);
            }
        }
    }
    else {
        printf("Action Cancelled!\n");
        system("pause");
    }

    fclose(fptr);
    fclose(tempFptr);
    fclose(fptr2);
    fclose(tempFptr2);

    // Reopen files for deletion and renaming
    fptr = fopen("customerBooking.bin", "wb");
    tempFptr = fopen("temp_customerBooking.bin", "r+b");
    fptr2 = fopen("Train.bin", "wb");
    tempFptr2 = fopen("temp_train.bin", "r+b");

    if (fptr == NULL || tempFptr == NULL || fptr2 == NULL || tempFptr2 == NULL) {
        printf("Error reopening files for deletion and renaming.\n");
        return;
    }

    // Copy contents from temporary files to original files
    while (fread(&booking, sizeof(Booking), 1, tempFptr) != 0) {
        fwrite(&booking, sizeof(Booking), 1, fptr);
    }

    while (fread(&train, sizeof(Train), 1, tempFptr2) != 0) {
        fwrite(&train, sizeof(Train), 1, fptr2);
    }

    // Close files and remove temporary files
    fclose(fptr);
    fclose(tempFptr);
    fclose(fptr2);
    fclose(tempFptr2);

    remove("temp_customerBooking.bin");
    remove("temp_train.bin");
}


void SearchTrain(struct member memberInfo[], int count, int memberLoggedInIndex)
{
    system("cls");
    printf("============\n");
    printf("Search Train\n");
    printf("============\n\n");
    Train train;
    Customer customer;
    Date time;

    FILE* trainFile;
    trainFile = fopen("train.bin", "rb");
    FILE* customerBooking;
    customerBooking = fopen("customerBooking.bin", "a+b");

    if (trainFile == NULL || customerBooking == NULL) {
        system("cls");
        printf("Failed to open the file.\n");
        exit(-1);
    }

    char depStat[50];
    char arrStat[50];
    char trainID[6];
    int numTrains;
    char choice;

    do {
        rewind(stdin);
        printf("Enter your Departure Station: ");
        scanf("%[^\n]", depStat);
        rewind(stdin);
        printf("Enter your Arrival Station: ");
        scanf(" %[^\n]", arrStat);

        rewind(trainFile);
        int foundMatch = 0; //Variable to indicate if a train is found

        printf("=========================================================================================================\n");
        printf("%-10s%-20s%-20s%-20s%-20s%s\n", "Train ID", "Departure Station", "Arrival Station", "Departure Time", "Departure Date", "Available Seat");
        printf("=========================================================================================================\n");
        while (fread(&train, sizeof(Train), 1, trainFile) != 0) {
            if (strcmp(depStat, train.departureStation) == 0 && strcmp(arrStat, train.arrivalStation) == 0) {
                foundMatch = 1;
                printf("%-10s%-20s%-20s%02d:%-20d%02d-%02d-%02d%20d\n",
                    train.trainId, train.departureStation, train.arrivalStation, train.departureTime.hour, train.departureTime.minute, train.departureTime.day, train.departureTime.month, train.departureTime.year, train.availableSeats);
                break;
            }
        }

        if (!foundMatch) {
            printf("\nNo train found for the given Departure and Arrival Station!\n");
            printf("Do you want to try again? (Y/N)\n");
            scanf(" %c", &choice);
            if (choice == 'N' || choice == 'n') {
                fclose(trainFile);
                exit(-1);
            }
            else if (choice == 'Y' || choice == 'y') {
                rewind(trainFile); // Reset the file pointer to read from the beginning
                numTrains = 0; // Reset numTrains to start from the beginning of the train array
                system("cls");
            }
            else {
                printf("Invalid choice. Exiting.\n");
                fclose(trainFile);
                return -1;
            }
        }
        else {
            break; // Exit the loop if a match is found
        }

    } while (1);

    system("pause");

    return;
}

void DisplayAllTrain(struct member memberInfo[], int count, int memberLoggedInIndex) {
    system("cls");
    printf("==========\n");
    printf("All Trains\n");
    printf("==========\n\n");

    Train train;
    Booking booking;
    Customer customer;

    FILE* trainFile = fopen("train.bin", "rb");

    int choice;
    int track = 0;

    if (trainFile == NULL) {
        printf("Failed to open the file.\n");
        main();
        return;
    }

    printf("========================================================================================================\n");
    printf("%-10s%-20s%-20s%-20s%-20s%s\n", "Train ID", "Departure Station", "Arrival Station", "Departure Time", "Departure Date", "Available Seat");
    printf("========================================================================================================\n");
    while (fread(&train, sizeof(Train), 1, trainFile)) {

        printf("%-10s%-20s%-20s%02d:%-20d%02d-%02d-%02d%20d\n",
            train.trainId, train.departureStation, train.arrivalStation, train.departureTime.hour, train.departureTime.minute, train.departureTime.day, train.departureTime.month, train.departureTime.year, train.availableSeats);
    }

    fclose(trainFile);

    do {
        printf("Menu:\n");
        printf("[1] Buy Ticket(s)\n");
        printf("[2] Return to Menu\n");
        printf("Enter your choice: ");
        rewind(stdin);
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("Proceeding to Purchase Ticket Menu....\n");
            BuyTicket(memberInfo, count, memberLoggedInIndex);
            track = 1;
            break;
        case 2:
            printf("Exiting to Ticket Booking Menu\n");
            track = 1;
            return;
            break;
        default:
            printf("Invalid Selection\n");

        }
    } while (track != 1);

}

void GenerateTicket(struct member memberInfo[], int count, int memberLoggedInIndex) {
    FILE* fptr;
    fptr = fopen("customerBooking.bin", "rb");
    Booking booking;

    if (fptr == NULL) {
        printf("Error while opening file!!\n");
        return;
    }

    int bookingID;
    int selection;

    do {
        printf("Enter Booking ID to print ticket (0 to exit): B");
        scanf("%d", &bookingID);

        if (bookingID == 0) {
            break; // Exit if 0 is entered
        }

        char referenceCode[9]; // Adjust the length as needed
        generateReferenceCode(referenceCode, sizeof(referenceCode));

        int foundBooking = 0;
        rewind(fptr);
        while (fread(&booking, sizeof(Booking), 1, fptr) != 0) {
            if (bookingID == booking.bookingID) {
                printBookingDetails(booking, referenceCode);
                foundBooking = 1;
                break;
            }
        }

        if (!foundBooking) {
            printf("Booking ID does not exist. Please try again.\n");
        }

    } while (bookingID != 0);

    fclose(fptr);

    do {
        printf("[1] Return to main menu\n");
        printf("[2] Generate another ticket\n");
        printf(">> ");
        scanf("%d", &selection);

        switch (selection) {
        case 1:
            system("cls");
            return;
        case 2:
            break; // Repeats the process
        default:
            printf("Invalid Input. Please enter 1 or 2.\n");
        }
    } while (selection != 1);
}

void printBookingDetails(Booking booking, char referenceCode[]) {
    printf("======================================\n");
    printf("  Booking ID       : B%d\n", booking.bookingID);
    printf("  Customer ID      : %s\n", booking.customerID);
    printf("  Customer Name    : %s\n", booking.customerName);
    printf("  Payment Method   : %s\n", booking.paymentMethod);
    printf("  Train ID         : %s\n", booking.trainID);
    printf("  Departure Station: %s\n", booking.departureStation);
    printf("  Departure Date   : %d-%d-%d\n", booking.departureTime.day, booking.departureTime.month, booking.departureTime.year);
    printf("  Departure Time   : %d:%d\n", booking.departureTime.hour, booking.departureTime.minute);
    printf("  Requested Seats  : %d\n", booking.seatsBooked);
    printf("  Reference Code   : %s\n", referenceCode); // Include the reference code
    printf("=====================================\n");
}

void generateReferenceCode(char* refCode, int length) {
    const char charset[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    srand((unsigned int)time(NULL));
    for (int i = 0; i < length - 1; ++i) {
        refCode[i] = charset[rand() % (sizeof(charset) - 1)];
    }
    refCode[length - 1] = '\0'; // Null-terminate the string
}

void CheckBooking(struct member memberInfo[], int count, int memberLoggedInIndex) {
    system("cls");
    printf("=============\n");
    printf("Check Booking\n");
    printf("=============\n\n");

    Booking booking;
    FILE* customerBooking = fopen("customerBooking.bin", "rb");

    if (customerBooking == NULL) {
        printf("Error while opening file!\n");
        return;
    }

    int tempBookingID;
    int foundBookings = 0;

    printf("Your bookings:\n\n");
    printf("%-13s%-13s%-25s%-15s%-16s\n", "Booking ID", "Customer ID", "Customer Name", "Departure Date", "Departure Time");
    while (fread(&booking, sizeof(Booking), 1, customerBooking) != 0) {
        if (strcmp(memberInfo[memberLoggedInIndex].ID, booking.customerID) == 0) {
            printf("B%-12d%-13s%-25s%d-%d-%-9d%d:%-9d\n", booking.bookingID, booking.customerID, booking.customerName, booking.departureTime.day, booking.departureTime.month, booking.departureTime.year, booking.departureTime.hour, booking.departureTime.minute);
            foundBookings = 1;
        }
    }

    if (!foundBookings) {
        printf("\nNo bookings found for the logged-in member.\n");
        fclose(customerBooking);
        return;
    }

    do {
        printf("\nEnter Booking ID to check details (0 to exit): B");
        scanf("%d", &tempBookingID);

        if (tempBookingID == 0) {
            printf("Exiting check booking...\n");
            fclose(customerBooking);
            return;
        }

        rewind(customerBooking);
        int found = 0;
        while (fread(&booking, sizeof(Booking), 1, customerBooking) != 0) {
            if (tempBookingID == booking.bookingID && strcmp(memberInfo[memberLoggedInIndex].ID, booking.customerID) == 0) {
                printf("===========================================\n");
                printf("    Booking ID          : B%d\n", booking.bookingID);
                printf("    Customer ID         : %s\n", booking.customerID);
                printf("    Customer Name       : %s\n", booking.customerName);
                printf("    Departure Station   : %s\n", booking.departureStation);
                printf("    Departure Date      : %d-%d-%d\n", booking.departureTime.day, booking.departureTime.month, booking.departureTime.year);
                printf("    Departure Time      : %d:%d\n", booking.departureTime.hour, booking.departureTime.minute);
                printf("    Seats Booked        : %d\n", booking.seatsBooked);
                printf("========================================\n");
                found = 1;
                break;
            }
        }

        if (!found) {
            printf("Invalid Booking ID or Booking not found.\n");
        }

    } while (tempBookingID != 0);

    fclose(customerBooking);
}
