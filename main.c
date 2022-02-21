#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symtab.h"

typedef enum{UG, PG} studentLevelT;
typedef struct student StudentT;

struct student{
    char *sName;
    studentLevelT level;
    int mark;
};

char getGrade(StudentT student){
    if (student.level == UG){
        if (student.mark >= 87) return 'A';
        else if (student.mark >= 72) return 'B';
        else if (student.mark >= 59) return 'C';
        else if (student.mark >= 50) return 'D';
        else return 'F';
    }
    else{
        if (student.mark >= 90) return 'A';
        else if (student.mark >= 75) return 'B';
        else if (student.mark >= 65) return 'C';
        else return 'F';
    }
    return 'E'; // E for Error
}

void displayStudentNameAndGrade(char* key, StudentT* student){
    printf("%s %s\n%c \n", key, student->sName, getGrade(*student));

}

int main()
{
    FILE *datafile, *correctionfile;
    datafile = fopen("studentData.txt", "r");
    correctionfile = fopen("dataCorrection.txt", "r");
    symtabADT studentlist;
    studentlist = EmptySymbolTable();
    StudentT* temp;
    temp = malloc(sizeof(StudentT));
    int corrkey[101], corrmark[101], count, c;
    char line[100][100], *key;

    count = 0;

    int num = 0;
    while (fgets(line[num], 100, correctionfile) != NULL){
            corrkey[count] = atoi(strtok(line[num], "\n"));
            fgets(line[num], 100, correctionfile);
            corrmark[count] = atoi(strtok(line[num], "\n"));
            count++;
    }
    fclose(correctionfile);
    while (fgets(line[num], 100, datafile) != NULL){
        key = strtok(line[num], "\n");
        num++;
        if ((atoi(key) - 210000) < 0){
            temp->level = PG;
        }
        else{
            temp->level = UG;
        }
        fgets(line[num], 100, datafile);
        temp->sName = strtok(line[num], "\n");
        num++;
        fgets(line[num], 100, datafile);
        temp->mark = atoi(strtok(line[num], "\n"));
        num++;
        for (int i = 0; i <= count; i++){
            if (atoi(key) == corrkey[i]){
                temp->mark = corrmark[i];
            }
        }

        Enter(studentlist, key, temp);
        displayStudentNameAndGrade(key, temp);


    }
    fclose(datafile);
    printf("\n");
    //forEachEntryDo(displayStudentNameAndGrade, studentlist);


    return 0;
}
