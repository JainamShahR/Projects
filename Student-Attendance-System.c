#include<windows.h>
#include<stdio.h>
#include<conio.h>
#include <stdlib.h>
#include<string.h>                  
#include<ctype.h>                   
#include<dos.h>                     
#include<time.h>

void mainmenu();
void teachpass();
void adminpass();
void stddetails();
int getdata();
void deletedatails();
void admin();
void searchstd();
void viewad();
void editdetail();
int getdata();
int checkid(int t);
void adminpass();
void teachpass();
void admin();
void teacher();
void addaten();
int getatt();
int checkatt(char t);
void viewatten();
void searchatten();
void editatten();
void copy();

FILE *fp,*ft,*fs;

int s;
char findbook;

void gotoxy (int x, int y)
{
	COORD coord = {0, 0};
	coord.X = x; coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

struct detail
{
int id;
char ftname[20];
char ltname[20];
int sem;
int sec;
};
struct detail st;

struct atten
{
char date;
char att;
int id;
char ftname[20];
char ltname[20];
int sem;
int sec;
};
struct atten y;

int main()
{
	mainmenu();
	getch();
	return 0;
}

void mainmenu()
{
	system("cls");
	char d[60]={"~~ WELCOME TO STUDENT ATTENDANCE MANAGEMENT SYSTEM ~~"};
	int i,choice,j;
	
	gotoxy(35,4);
	for(j=0;j<60;j++){
		Sleep(50);
		printf("%c",d[j]);
	}
	gotoxy(40,7);
	printf("-> 1. Login as Admin User");
	gotoxy(40,9);
	printf("-> 2. Login as Teacher User");
	gotoxy(40,11);
	printf("-> 3. Exit the program");
	
	gotoxy(40,17);
	printf("Enter your choice : ");
	scanf("%d", &choice);
	
	switch(choice){
		case 1:{
			copy();
			adminpass();
			break;
		}
		case 2:{
			copy();
			teachpass();
			break;
		}
		case 3:
		{	system("cls");
			gotoxy(50,14);
			printf("Ending...");
			Sleep(3000);
			system("cls");
			gotoxy(50,14);
			printf("Ended");
			exit(0);
		}
		default:{
			gotoxy(10,23);
			printf("\aWrong Entry!! Please re-enter correct option");
			if(getch()){
				mainmenu();
			}
		}
	}
}

void stddetails()
{
	system("cls");
	int i,ex;
	
	fp=fopen("Studentdetail.txt","ab+");
	if(getdata()==1){
		fseek(fp,0,SEEK_END);
		fwrite(&st,sizeof(st),1,fp);
		
		fclose(fp);
		copy();
		gotoxy(21,21);
		printf("The Record Is Sucessfully Saved");
		
		gotoxy(21,23);
		printf("Do you want to save more? -> Enter ( 1 ) or -> Enter any number : ");
		scanf("%d", &ex);
		
		if(ex==1){
			stddetails();
		}
		else{
			admin();
		}
	}
	else{
		admin();
	}
}

void deletedatails()
{
	system("cls");
	int d,j;
	int a=1;
	char filename[] = "Studentdetail.txt";
	
	char f[30]={"~~ DELETE STUDENT DETAIL ~~"};
	gotoxy(45,4);
	for(j=0;j<30;j++){
			Sleep(50);
			printf("%c",f[j]);
	}
	
	while(a==1)
	{
		gotoxy(35,7);
		printf("Enter Student Id to Delete : AU");
		scanf("%d",&d);
		fp=fopen("Studentdetail.txt","rb+");
		rewind(fp);
		while(fread(&st,sizeof(st),1,fp)==1)
		{
			if(st.id==d)
			{
			
				gotoxy(35,9);
				printf("Student details are Available");
				gotoxy(35,10);
				printf("Student name is %s %s",st.ftname,st.ltname);
				findbook='t';
			}
		}
		if(findbook!='t')
		{
			gotoxy(35,11);
			printf("Student details is not available");
			if(getch())
			admin();
		}
		if(findbook=='t' )
		{
			gotoxy(25,15);
			printf("Do you want to delete it ?-> ( 1 ) to delete or -> any number to back to Admin Portal");
			scanf("%d",&a);
			if(a==1)
			{
				ft=fopen("test.txt","wb+");
				rewind(fp);
				while(fread(&st,sizeof(st),1,fp)==1)
				{
					if(st.id!=d)
					{
						fseek(ft,0,SEEK_CUR);
						fwrite(&st,sizeof(st),1,ft);
					}                             
				}
				fclose(ft);
				fclose(fp);
				remove(filename);
				rename("test.txt","Studentdetail.txt");
			
				if(findbook=='t')
				{
					gotoxy(35,17);
					printf("Student details are Sucessfully Deleted");
					gotoxy(35,19);
					printf("Delete another record? -> ( 1 ) or -> Enter any number ");
					scanf("%d",&a);
					if(a==1){
						deletedatails();
					}
					else{
						admin();
					}
				}
			}
			else
			admin();
			fflush(stdin);
		}
	}
	admin();
}

void searchstd()
{
	FILE *fp;
	system("cls");
	int d,j,k,n;
	char f[30]={"~~ SEARCH STUDENT DETAILS ~~"};
	
	gotoxy(40,4);
	for(j=0;j<30;j++){
		Sleep(50);
		printf("%c",f[j]);
	}
	
	gotoxy(30,8);
	printf("Enter Student id : AU");
	scanf("%d",&d);
		
		fp=fopen("Studentdetail.txt","rb+");
		rewind(fp);
		while(fread(&st,sizeof(st),1,fp)==1)
		{
			if(st.id==d)
			{
			Sleep(2);
			gotoxy(30,10);
			printf("The Student details are Available");
			gotoxy(32,12);
			printf("Id : %d",st.id);
			gotoxy(32,13);
			printf("Name : %s %s",st.ftname,st.ltname);
			gotoxy(32,14);
			printf("Semester : %d",st.sem);
			gotoxy(32,15);
			printf("Section : %d",st.sec);
			k=0;
		}
	}
	if(k != 0){
		gotoxy(30,15);
		printf("No Student Details Found!!");
	}
	gotoxy(30,18);
	printf("Try another search? -> Enter ( 1 ) or -> Enter any number : ");
	scanf("%d", &n);
	
	if(n==1){
		searchstd();
	}
	else{
		admin();
	}
}

void viewad()
{
	FILE *fp;
	int i=0,j;
	char d[35]={"~~ VIEW ALL STUDENT DETAIL ~~"};
	system("cls");
	
	gotoxy(40,4);
	for(j=0;j<35;j++){
			Sleep(50);
			printf("%c",d[j]);
	}
	gotoxy(26,6);
	printf("   Id          Student name    Semester   Section ");
	
	j=8;
	
	fp=fopen("Studentdetail.txt","r");
	while(fread(&st,sizeof(st),1,fp)==1){
		
		gotoxy(24,j);
		printf("AU%d",st.id);
		
		gotoxy(40,j);
		printf("%s %s",st.ftname,st.ltname);
		
		gotoxy(60,j);
		printf("%d",st.sem);
		
		gotoxy(71,j);
		printf("%d",st.sec);
		
		printf("\n\n");
		j++;
	}
	
	fclose(fp);
	gotoxy(30,23);
	printf("Press any button to Continue . . .");
	getch();
	admin();
	
}

void editdetail()
{
	FILE *fp;
	system("cls");
	int c=0;
	int d,e,j;
	char f[30]={"~~ EDIT STUDENT DETAIL ~~"};
	
	gotoxy(45,4);
	for(j=0;j<30;j++){
		Sleep(50);
		printf("%c",f[j]);
	}
	gotoxy(35,6);
	int a=1;
	while(a==1)
	{
		gotoxy(30,7);
		
		printf("Enter Student Id : AU");
		scanf("%d",&d);
		
		fp=fopen("Studentdetail.txt","rb+");
		rewind(fp);
		while(fread(&st,sizeof(st),1,fp)==1)
		{
			if(st.id==d)
			{
				gotoxy(30,9);
				printf("Student details are Available");
				
				gotoxy(35,11);
				printf("Student Id : AU%d",st.id);
				
				gotoxy(35,12);
				printf("Enter New First Name : ");
				scanf("%s",st.ftname);
				
				gotoxy(35,13);
				printf("Enter New Last Name : ");
				scanf("%s",st.ltname);
				
				gotoxy(35,14);
				printf("Add New Semester:");
				scanf("%d",&st.sem);
				
				gotoxy(35,15);
				printf("Enter New Section:");
				scanf("%d",&st.sec);
				
				gotoxy(35,17);
				printf("The Details are modified");
				fseek(fp,ftell(fp)-sizeof(st),0);
				fwrite(&st,sizeof(st),1,fp);
				fclose(fp);
				c=1;
			}
			if(c==0)
			{	
				gotoxy(30,11);
				printf("No record found");
				
				gotoxy(30,13);
				printf("Press any button to go back");
				
				getch();
				admin();
			}
		}
		gotoxy(25,19);
		printf("Modify another details? -> ( 1 ) or -> any number to go back");
		fflush(stdin);
		scanf("%d", &a);
		if(a==1){
			editdetail();
		}
		else{
			admin();
		}
	}
}

int getdata()
{
	int t;
	char d[30]={"~~ ADD STUDENT DETAIL ~~"};
	int i,choice,j;
	
	gotoxy(45,4);
	for(j=0;j<30;j++){
			Sleep(50);
			printf("%c",d[j]);
	}
	
	gotoxy(30,7);
	printf("Student Id : AU");
	scanf("%d",&t);
	fp=fopen("Studentdetail.txt","rb+");
	rewind(fp);
	while(fread(&st,sizeof(st),1,fp)==1)
		{
		if(st.id==t)
		{
		gotoxy(21,13);
		printf("Student details already exists");
		gotoxy(21,15);
		printf("Press any butten to continue");
		getch();
		return 0;
		}
		}
		
	st.id=t;
	
	gotoxy(30,9);
	printf("Student Firstname : ");
	scanf("%s",st.ftname);
	
	gotoxy(30,11);
	printf("Student Lastname : ");
	scanf("%s",st.ltname);
	
	gotoxy(30,13);
	printf("Semester(in number) : ");
	scanf("%d", &st.sem);

	gotoxy(30,15);
	printf("Section : ");
	scanf("%d",&st.sec);

	return 1;
}

int checkid(int t)
{
	rewind(fp);
	while(fread(&st,sizeof(st),1,fp)==1){
		if(st.id==t){
			return 0;
		}
		return 1;
	}
}

void adminpass()
{
	system("cls");
	
	char teacher_id[10]={"Guest"};
	char password[10]={"guest123"};
	char f[25]="~~ ADMIN PORTAL ~~";
	char ch1,id[10],pass[10],ch2;
	int i=0,j;

	gotoxy(46,4);
	for(j=0;j<20;j++){
		Sleep(50);
		printf("%c",f[j]);
	}
	
	gotoxy(45,7);
	printf("Admin Id : ");
	scanf("%s", id);
	
	gotoxy(45,9);
	printf("Password : ");
	while(ch2!=13){
		ch2=getch();
		
		if(ch2!=13 && ch2!=8){
		putch('*');
		pass[i] = ch2;
		i++;
		}
	}
	pass[i] = '\0';
	
	if(strcmp(pass,password)==0 && strcmp(id,teacher_id)==0){
		admin();
	}
	else{
		gotoxy(20,16);
		printf("Warning!! Incorrect ID or Password, try again");
		getch();
		adminpass();
	}
}

void teachpass()
{
	
	system("cls");
	
	char teacher_id[10]={"Guest"};
	char password[10]={"guest123"};
	char d[25]="~~ TEACHER PORTAL ~~";
	char ch1,id[10],pass[10],ch2;
	int i=0,j;

	gotoxy(46,4);
	for(j=0;j<20;j++){
		Sleep(50);
		printf("%c",d[j]);
	}
	
	gotoxy(45,7);
	printf("Teacher Id : ");
	scanf("%s", id);
	
	gotoxy(45,9);
	printf("Password : ");
	while(ch2!=13){
		ch2=getch();
		
		if(ch2!=13 && ch2!=8){
		putch('*');
		pass[i] = ch2;
		i++;
		}
	}
	pass[i] = '\0';
	
	if(strcmp(pass,password)==0 && strcmp(id,teacher_id)==0){
		teacher();
	}
	else{
		gotoxy(20,16);
		printf("Warning!! Incorrect ID or Password, try again");
		getch();
		teachpass();
	}
}

void admin()
{
	system("cls");
	char d[25]={"~~ ADMIN PORTAL ~~"};
	int i,choice,j;
	
	gotoxy(46,4);
	for(j=0;j<20;j++){
			Sleep(50);
			printf("%c",d[j]);
	}
	gotoxy(35,7);
	printf("-> 1. Add Student Details");
	gotoxy(35,9);
	printf("-> 2. View Student Details");
	gotoxy(35,11);
	printf("-> 3. Search a Student by Id");
	gotoxy(35,13);
	printf("-> 4. Edit Student Details ");
	gotoxy(35,15);
	printf("-> 5. Delete Student Details");
	gotoxy(35,17);
	printf("-> 6. Log Out");
	gotoxy(35,21);
	printf("Enter your choice : ");
	scanf("%d", &choice);
	switch(choice)
	{
		case 1:{
			stddetails();
			break;
		}
		case 2:{
			viewad();
			break;
		}
		case 3:{
			searchstd();
			break;
		}
		case 4:{
			editdetail();
			break;
		}
		case 5:{
			deletedatails();
			break;
		}
		case 6:
		{
			mainmenu();
			break;
		}
		default:
		{
			gotoxy(10,25);
			printf("\aWrong Entry!! Please re-enter correct option");
			if(getch()){
				admin();
			}
		}
	}
}

void teacher()
{
	system("cls");
	char d[25]={"~~ TEACHER PORTAL ~~"};
	int i,choice,j;
	
	gotoxy(46,4);
	for(j=0;j<20;j++){
			Sleep(50);
			printf("%c",d[j]);
	}
	gotoxy(30,7);
	printf("-> 1. Mark Attendance");
	gotoxy(30,9);
	printf("-> 2. View Attendance");
	gotoxy(30,11);
	printf("-> 3. Search a Student Attendance");
	gotoxy(30,13);
	printf("-> 4. Edit Attendance");
	gotoxy(30,15);
	printf("-> 5. Log Out");
	gotoxy(30,21);
	printf("Enter your choice : ");
	scanf("%d", &choice);
	switch(choice)
	{
		case 1:{
			addaten();
			break;
		}
		case 2:{
			viewatten();
			break;
		}
		case 3:{
			searchatten();
			break;
		}
		case 4:{
			editatten();
			break;
		}
		case 5:
		{
			main();
		}
		default:
		{
			gotoxy(10,25);
			printf("\aWrong Entry!! Please re-enter correct option");
			if(getch()){
				teacher();
			}
		}
	}
}

void copy()
{
	
	FILE *fp, *fp1;
	char ch;
	
	fp = fopen("Studentdetail.txt", "rb+");
	fp1 = fopen("StudentAtten.txt", "wb+");
	
		ch = fgetc(fp);
	
		while(ch!=EOF){
			fputc(ch,fp1);	
			ch = fgetc(fp);
		}
	
		fclose(fp);
		fclose(fp1);
}

void addaten()
{
	system("cls");
	int i,ex;

	fp=fopen("StudentAtten.txt","ab+");
	if(getatt()==1){
		fseek(fp,0,SEEK_END);
		fwrite(&y,sizeof(y),1,fp);
		
		fclose(fp);
		
		gotoxy(21,21);
		printf("The Attendance Is Sucessfully Saved");
		
		gotoxy(21,23);
		printf("Do you want to save more? -> Enter ( 1 ) or -> Enter any number : ");
		scanf("%d", &ex);
		
		if(ex==1){
			addaten();
		}
		else{
			teacher();
		}
	}
	else{
		teacher();
	}
}

int getatt()
{
	char t;
	char d[40]={"~~ ADD ATTENDANCE OF STUDENT ~~"};
	int i,choice,j;
	
	gotoxy(45,4);
	for(j=0;j<40;j++){
			Sleep(50);
			printf("%c",d[j]);
	}
	
	gotoxy(30,7);
	printf("Enter Date(dd-mm-yy) : ");
	scanf("%s",&t);
	
	fp=fopen("StudentAtten.txt","rb+");
	rewind(fp);
	while(fread(&y,sizeof(y),1,fp)==1)
		{
		if(y.date==t)
		
		gotoxy(25,13);
		printf("\n\n\t\t\tAttendance already marked");
		gotoxy(25,15);
		printf("Press any butten to continue");
		getch();
		teacher();
	}
	y.date=t;
	while(fread(&y,sizeof(y),1,fp)==1){
		Sleep(2);
		gotoxy(32,12);
		printf("Id : %d",y.id);
		gotoxy(32,13);
		printf("Name : %s %s",y.ftname,y.ltname);
		gotoxy(32,14);
		gotoxy(30,13);
		printf("Attendance( p / a ) : ");
		scanf("%C", &y.att);
	}
	return 1;
}

int checkatt(char t)
{
	rewind(fp);
	while(fread(&y,sizeof(y),1,fp)==1){
		if(y.date==t){
			return 0;
		}
		return 1;
	}
}

void viewatten()
{
	int i=0,j;
	char d[35]={"~~ VIEW STUDENT ATTENDANCE ~~"};
	system("cls");
	
	gotoxy(40,4);
	for(j=0;j<35;j++){
		Sleep(50);
		printf("%c",d[j]);
	}
	gotoxy(35,23);
	printf("Press any key to continue");
	getch();
	teacher();
	j=7;
	fp=fopen("StudentAtten.txt","r");
	while(fread(&y,sizeof(y),1,fp)==1){
		printf("AU%d\n",y.id);
		j++;
		gotoxy(30,j);
		printf("%s %s",y.ftname,y.ltname);
		j++;
		gotoxy(30,j);
		printf("Date : %s",y.date);
		gotoxy(39,j);
		printf("%c",y.att);
		printf("\n\n");
		j++;
	}
	
	fclose(fp);
	gotoxy(35,25);
	printf("Enter any button to continue");
	getch();
	teacher();
}

void searchatten()
{
	FILE *fp;
	system("cls");
	int j,k,n;
	char f[40]={"~~ SEARCH STUDENT ATTENDANCE ~~"};
	int d;
	
	gotoxy(40,4);
	for(j=0;j<40;j++){
		Sleep(50);
		printf("%c",f[j]);
	}
	
	gotoxy(30,8);
	printf("Enter the Student id : ");
	scanf("%d",&d);
	
		fp=fopen("StudentAtten.txt","rb+");
		rewind(fp);
		while(fread(&y,sizeof(y),1,fp)==1)
		{
			if(y.id==d)
			{
			Sleep(2);
			gotoxy(30,10);
			printf("The Student details are Available");
			gotoxy(32,12);
			printf("Id : %d",y.id);
			gotoxy(32,13);
			printf("Name : %s %s",y.ftname,y.ltname);
			gotoxy(32,14);
			printf("Attendance : %c",y.att);
			k=0;
		}
	}
	if(k != 0){
		gotoxy(30,15);
		printf("No Student Attendance Found!!");
	}
	gotoxy(30,18);
	printf("Try another search? -> Enter ( 1 ) or -> Enter any number : ");
	scanf("%d", &n);
	
	if(n==1){
		searchatten();
	}
	else{
		teacher();
	}
}

void editatten()
{
	FILE *fp;
	system("cls");
	int c=0;
	int d,e,j;
	char f[30]={"~~ EDIT STUDENT ATTANDANCE ~~"};
	
	gotoxy(45,4);
	for(j=0;j<30;j++){
		Sleep(50);
		printf("%c",f[j]);
	}
	gotoxy(35,6);
	int a=1;
	while(a==1)
	{
		gotoxy(30,7);
		
		printf("Enter Student Id : AU");
		scanf("%d",&d);
		
		fp=fopen("Studentatten.txt","rb+");
		rewind(fp);
		while(fread(&y,sizeof(y),1,fp)==1)
		{
			if(st.id==d)
			{
				gotoxy(30,9);
				printf("Student details are Available");
				
				gotoxy(35,11);
				printf("Student Id : AU%d",y.id);
				
				gotoxy(35,12);
				printf("Student Name : %d %d",y.ftname,y.ltname);
				
				gotoxy(35,13);
				printf("Enter Attendance( p / a) : ");
				scanf("%c",y.att);

				gotoxy(35,17);
				printf("The Details are modified");
				fseek(fp,ftell(fp)-sizeof(y),0);
				fwrite(&y,sizeof(y),1,fp);
				fclose(fp);
				c=1;
			}
			if(c==0)
			{	
				gotoxy(30,11);
				printf("No record found");
				
				gotoxy(30,13);
				printf("Press any button to go back");
				
				getch();
				teacher();
			}
		}
		gotoxy(25,19);
		printf("Modify another details? -> ( 1 ) or -> any number to go back");
		fflush(stdin);
		scanf("%d", &a);
		if(a==1){
			editatten();
		}
		else{
			teacher();
		}
	}
}











