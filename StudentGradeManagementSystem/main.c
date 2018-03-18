#include <stdio.h>
#include <string.h>

struct studentData {
	unsigned int ID;
	char name[20];
	char surname[20];
	float grade;
}st;
// function prototypes
unsigned int enterChoice(void);
void newRegister(FILE *fPtr);
void searchbyNum(FILE *fPtr);
void searchbyName(FILE *fPtr);
void updateRegister(FILE *readPtr);
void deleteRegister(FILE *readPtr);
void listsRegister(FILE *readPtr);

int main(void) {

	FILE *cPtr;

	if ((cPtr = fopen("deneme.txt", "ab+")) == NULL) {
		puts("File could not be opened.");
	}
	else {
		unsigned int choice;

		while ((choice = enterChoice()) != 7) {
			switch (choice) {

			case 1:
				newRegister(cPtr);
				break;


			case 2:
				searchbyNum(cPtr);
				break;

			case 3:
				searchbyName(cPtr);
				break;

			case 4:
				updateRegister(cPtr);
				break;

			case 5:
				deleteRegister(cPtr);
				break;

			case 6:
				listsRegister(cPtr);
				break;

			default:
				puts("  Your choice is wrong.\n  Please try again.");
				break;

			}
		}

		fclose(cPtr);
	}

}

//**********************************************************
unsigned int enterChoice(void) {

	printf("\n");
	printf("\n");
	printf("  -----------------------------      \n");
	printf("  *                           *      \n");
	printf("  *      Student Grade        *      \n");
	printf("  *    Management System      *      \n");
	printf("  *                           *      \n");
	printf("  *                           *      \n");
	printf("  *   1.New Register          *      \n");
	printf("  *   2.Search by ID number   *      \n");
	printf("  *   3.Search by Name        *      \n");
	printf("  *   4.Update a Register     *      \n");
	printf("  *   5.Delete a Register     *      \n");
	printf("  *   6.Lists Register        *      \n");
	printf("  *   7.Exit                  *      \n");
	printf("  *                           *      \n");
	printf("  -----------------------------      \n\n");

	unsigned int menuChoice;
	printf("  Please choose one process : ");
	scanf("%d", &menuChoice);
	return menuChoice;
}

//**********************************************************

void newRegister(FILE *fPtr) {

	if ((fPtr = fopen("deneme.txt", "a")) == NULL) {
		puts("File could not be opened.");
	}
	else {

		struct studentData st = { 0,"","",0.0 };

		printf("\n  ID Number(max 15 characters) : ");
		scanf("%u", &st.ID);
		printf("  Name(max 15 characters) : ");
		scanf("%s", st.name);
		printf("  Surname(max 20 characters) : ");
		scanf("%s", st.surname);
		printf("  Grade(max 10 characters) : ");
		scanf("%f", &st.grade);

		fwrite(&st, sizeof(struct studentData), 1, fPtr);


		fclose(fPtr);
	}
}

//**********************************************************

void searchbyNum(FILE *fPtr) {

	int findnum;
	int flag = 0;

	fPtr = fopen("deneme.txt", "rb");

	printf("  Please enter a number you want to find : ");
	scanf("%u", &findnum);

	while (fread(&st, sizeof(struct studentData), 1, fPtr)) {

		if (findnum == st.ID) { //check if the number which user entered and the number in the list same or not
			printf("\n  %-10u%16s%21s\t\t%.2f\n", st.ID, st.name, st.surname, st.grade);
			flag = 1;
		}
	}
	if (flag == 0) {
		printf("  No record found!");
	}

	fclose(fPtr);
}

//**********************************************************

void searchbyName(FILE *fPtr) {

	int flag = 0;
	char findname[20];

	fPtr = fopen("deneme.txt", "r");

	printf("  Please enter a name you want to search : ");
	scanf("%s", findname);

	while (fread(&st, sizeof(struct studentData), 1, fPtr)) {

		if (!strcmp(findname, st.name)) { //check if the name which user entered and the name in the list same or not
			printf("\n  %-10u%16s%21s\t\t%.2f\n", st.ID, st.name, st.surname, st.grade);
			flag = 1;
		} // end if

	} // end while

	if (flag == 0) {
		printf("  No record found!");
	}

	fclose(fPtr);
}


//**********************************************************

void updateRegister(FILE *readPtr) {

	readPtr = fopen("deneme.txt", "rb+");
	int i = 0;
	int num;
	int flag = 0;
	int change;

	printf("  Please enter the number you want to update : ");
	scanf("%d", &num);

	while (fread(&st, sizeof(struct studentData), 1, readPtr)) {
		i++;

		if (num == st.ID) {
			flag = 1;
			break;
		}//end if
	}// end while
	if (flag == 0) {
		printf("  No record found!");
	}
	else {

		fseek(readPtr, (i - 1) * sizeof(struct studentData), SEEK_SET);

		printf("\n  %-10u%16s%21s\t\t%.2f\n", st.ID, st.name, st.surname, st.grade);

		printf("\n  Which part of record do you want to change ?(1/2/3/4) : ");
		scanf("%d", &change);

		switch (change) {

		case 1:
			fseek(readPtr, (i - 1) * sizeof(struct studentData), SEEK_SET); //pointer goes to the beginning of the record
			fseek(readPtr, 0, SEEK_SET); //pointer goes to beginning of the number in the structure
			printf("\n  ID Number(max 15 characters) : ");
			scanf("%u", &st.ID);
			fseek(readPtr, (i - 1) * sizeof(struct studentData), SEEK_SET);
			fwrite(&st, sizeof(struct studentData), 1, readPtr); //write new ID number
			printf("  The record is updated.\n");
			printf("  %-10u%16s%21s\t\t%.2f\n", st.ID, st.name, st.surname, st.grade);
			break;

		case 2:
			fseek(readPtr, (i - 1) * sizeof(struct studentData), SEEK_SET); //pointer goes to the beginning of the record
			fseek(readPtr, 16, SEEK_SET); //pointer goes to beginning of the name in the structure
			printf("\n  Name(max 15 characters) : ");
			scanf("%s", st.name);
			fseek(readPtr, (i - 1) * sizeof(struct studentData), SEEK_SET);
			fwrite(&st, sizeof(struct studentData), 1, readPtr); //write new name
			printf("  The record is updated.\n");
			printf("  %-10u%16s%21s\t\t%.2f\n", st.ID, st.name, st.surname, st.grade);
			break;

		case 3:
			fseek(readPtr, (i - 1) * sizeof(struct studentData), SEEK_SET);//pointer goes to the beginning of the record
			fseek(readPtr, 32, SEEK_SET); //pointer goes to beginning of the surname in the structure
			printf("\n  Surname(max 20 characters) : ");
			scanf("%s", st.surname);
			fseek(readPtr, (i - 1) * sizeof(struct studentData), SEEK_SET);
			fwrite(&st, sizeof(struct studentData), 1, readPtr); //write new surname
			printf("  The record is updated.\n");
			printf("  %-10u%16s%21s\t\t%.2f\n", st.ID, st.name, st.surname, st.grade);
			break;

		case 4:
			fseek(readPtr, (i - 1) * sizeof(struct studentData), SEEK_SET);//pointer goes to the beginning of the record
			fseek(readPtr, 53, SEEK_SET);//pointer goes to beginning of the grade in the structure
			printf("\n  Grade(max 10 characters) : ");
			scanf("%f", &st.grade);
			fseek(readPtr, (i - 1) * sizeof(struct studentData), SEEK_SET);
			fwrite(&st, sizeof(struct studentData), 1, readPtr); //write new grade
			printf("  The record is updated.\n");
			printf("  %-10u%16s%21s\t\t%.2f\n", st.ID, st.name, st.surname, st.grade);
			break;

		}

	}

	fclose(readPtr);
}

//**********************************************************

void deleteRegister(FILE *readPtr) {

	readPtr = fopen("deneme.txt", "rb+");
	int i = 0;
	int flag = 0;
	int num;

	printf("  Please enter the number you want to delete : ");
	scanf("%d", &num);

	while (fread(&st, sizeof(struct studentData), 1, readPtr)) {
		i++;  //to find the record place

		if (num == st.ID) {
			flag = 1;
			break;
		} //end if
	}// end while

	if (flag == 0) {
		printf("  No record found !");
	}
	else {

		fseek(readPtr, (i - 1) * sizeof(struct studentData), SEEK_SET);

		struct studentData null = { 0,"","",0.0 }; //change the all data with zeros

		fwrite(&null, sizeof(struct studentData), 1, readPtr);

		printf("\n  The record is deleted.");
	}


	fclose(readPtr);
}

//**********************************************************

void listsRegister(FILE *readPtr) {

	readPtr = fopen("deneme.txt", "rb");

	printf("  %-10s%16s%21s\t\t%s\n", "ID Number", "Name", "Surname", "Grade");
	printf("  %-10s%16s%21s\t\t%s\n", "---------", "-----", "-------", "------");

	while (fread(&st, sizeof(struct studentData), 1, readPtr)) {
		if (st.ID != 0) { //if the record is zero then it doesn't print the record on the list
			printf("  %-10u%16s%21s\t\t%.2f\n", st.ID, st.name, st.surname, st.grade);
		}
	}
	fclose(readPtr);

}


