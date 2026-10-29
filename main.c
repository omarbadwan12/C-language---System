//Name:Omar Ibrahim Badwan
//ID:1251487
//lab:14 lecture:7:ربى عوض الله
#include<stdio.h>
#include<string.h>
struct Student{
    int studentID;
    char name[50];
    int age;
    double gpa;
};
struct Student students[100];
int studentCount = 0;
void menu ();
void add_std(struct Student students[100], int *count);
void delete_std(struct Student students[100], int *count);
void search_std(struct Student students[100], int *count);
void displayAllStudents(struct Student students[100], int *count);
void initializeStudentRecords();
void saveStudentRecords();


int main(){


    initializeStudentRecords();
    int check;
    do{
         menu ();
        printf("Enter your choice (1-5):");
        scanf("%d",&check);
        if(check<1||check>5){
        printf("Invalid choice. Please enter 1-5");
    }else if (check==1){
        add_std(students,&studentCount);
    }else if(check==2){
        delete_std(students,&studentCount);
    }else if(check==3){
        search_std(students,&studentCount);
    }else if(check==4){
        displayAllStudents(students,&studentCount);
    }
    }
    while (check!=5);

    saveStudentRecords();


    return 0;



}
void menu (){

    printf("\n=== STUDENT RECORD MANAGEMENT SYSTEM === \n");
    printf("Please Select an Operation (1-5): \n");
    printf("1- Add New Student \n");
    printf("2- Remove Student \n");
    printf("3- Search for Student \n");
    printf("4- Display All Students\n");
    printf("5- Exit System\n");


}
void add_std(struct Student students[100], int *count){

    printf("\n=== ADD NEW STUDENT === \n");
    if(*count >= 100){
    printf("System is full.\n");
    return;
}
    int test_the_repeat;
    int ID;

do {//صممت هذا الجزء عشان ما يرجعني على القائمة الرئيسية اذا في غلط بالمعرف الخاص بالطاب بل يرجعك لهذا الفانكشين

    test_the_repeat = 0;
    printf("Enter 4-digit Student ID (1000-9999): ");
    scanf("%d", &ID);
    if(ID < 1000 || ID > 9999){
        printf("Invalid ID. It should be 4 digits.\n");
        continue;
    }
    for(int i = 0; i < *count; i++){

        if(students[i].studentID == ID){
            test_the_repeat = 1;
            printf("ID already exists\n");
        }

    }

} while(ID<1000||ID>9999||test_the_repeat==1);

char STD_NAME[50];
getchar();
do {
    printf("Enter Student name: ");
    fgets(STD_NAME, 50, stdin);
    int j = 0;
    while(STD_NAME[j] != '\0'){//لحذف \n
        if(STD_NAME[j] == '\n'){
            STD_NAME[j] = '\0';
            break;
        }
        j++;
    }
    if(strlen(STD_NAME) <= 0){
        printf("Invalid name\n");
    }
} while(strlen(STD_NAME) <= 0);
    int AGE;

    do{
    printf("Enter Student Age: ");
    scanf("%d",&AGE);

    if(AGE<6||AGE>50){
    printf("Invalid age\n");
    continue;

    }
    }
    while(AGE<6||AGE>50);
    double GPA;
    do{
    printf("Enter GPA: ");
    scanf("%lf",&GPA);
    if(GPA<0||GPA>4){
    printf("Invalid GPA\n");
    continue;
    }

}
while(GPA<0||GPA>4);

    students[*count].studentID=ID;
    strcpy(students[*count].name,STD_NAME);
    students[*count].age=AGE;
    students[*count].gpa=GPA;
    (*count)++;

    printf("Student added successfully!\n");


}
void delete_std(struct Student students[100], int *count){
    printf("\n=== REMOVE STUDENT === \n");
    int found_the_id;
    found_the_id=-1;//نعرفها -1 لانه لا يمكن وجود طالب بهذه القيمة
     if(*count==0){//تم تكرار الكود في اغلب الفانكشنات المطلوبة اذا لا يوجد طلاب يعود الى قائمة البداية

        printf("No students in the system.\n");
        return;
    }

    int ID;
    do{
    printf("Enter Student ID to remove: ");
    scanf("%d",&ID);


    found_the_id=-1;

    for (int i=0;i<*count;i++){

            if(students[i].studentID==ID){

                found_the_id=i;

            }

    }

    if(found_the_id==-1){
        printf("Error: Student ID not found.\n");
        continue;
    }
}
while(found_the_id==-1);
 printf("Removing Student: %s (ID: %d)\n",students[found_the_id].name, students[found_the_id].studentID);



    for(int i=found_the_id;i<*count-1;i++){//هذا الكود لنقل عنصر مصفوفة لمكان المحذوف عن طريق اخذ رقمه

   students[i] = students[i+1];

    }

    (*count)--;

    printf("Student removed successfully!\n");




}
void initializeStudentRecords(){

    FILE *fp;

    fp=fopen("students.bin","rb");

    if(fp == NULL){

        printf("No existing records found. Starting with empty system.\n");

        return;
    }

    studentCount = fread(students,sizeof(struct Student),100,fp);

    printf("%d student record(s) loaded from students.bin.\n",
           studentCount);

    fclose(fp);
}
void search_std(struct Student students[100], int *count){

    printf("\n=== SEARCH STUDENT === \n");
    if(*count==0){

        printf("No students in the system.\n");
        return;
    }

    printf("Enter Student ID to search: ");
    int ID;
    scanf("%d",&ID);

    int found_the_id;
    found_the_id=-1;

    for(int i=0;i<*count;i++){

        if(students[i].studentID==ID){
            found_the_id=i;
            break;
        }

    }
    if(found_the_id==-1){
        printf("Student not found.");
        return;
    }
    printf("Student ID: %d\n",students[found_the_id].studentID);
    printf("Student Name:%s\n",students[found_the_id].name);
    printf("Student Age:%d\n",students[found_the_id].age);
    printf("GPA:%.2f\n",students[found_the_id].gpa);



}
void displayAllStudents(struct Student students[100], int *count){

    printf("\n=== ALL STUDENTS ===\n ");
    if(*count==0){

        printf("No students in the system.\n");
        return;
    }
    double sum=0;
    printf("\nID\tName\t\tAge\tGPA\n");
printf("------------------------------------------------\n");

    for (int i=0;i<*count;i++){

        printf("%d\t%s\t%d\t%.2lf\n",students[i].studentID,students[i].name,students[i].age,students[i].gpa);

        sum=sum+students[i].gpa;

    }
    printf("------------------------------------------------\n");

    int num_of_std=*count;
    printf("Total Students: %d\n",num_of_std);


    double avg_of_gpa=sum/ *count;

        printf("Average GPA:%0.2f\n",avg_of_gpa);


}
void saveStudentRecords(){

    FILE *fp;

    fp=fopen("students.bin","wb");

    if(fp == NULL){

        printf("Error: Could not save records.\n");

        return;
    }

    fwrite(students,sizeof(struct Student),studentCount,fp);

    printf("%d student record(s) saved to students.bin.\n",studentCount);

    fclose(fp);
}


