//This Program is to create normal user, joint account user and administrator.
#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>

// Normal user characterstics
struct Normal_User{
    int Normal_User_ID;
	char Username[50];
	char Password[20];
	int Account_no;
	float Balance;
	char Acc_Status[20];
};

// Joint user characterstics
struct Joint_User{
    int Joint_User_ID;
	char Username1[50];
    char Username2[50];
	char Password[20];
	int Account_no;
	float Balance;
	char Acc_Status[20];
};

// Admin characterstics
struct Administrator{
    int Admin_User_ID;
	char Username[50];
    char Password[20];
};

// Creating Admin ID
int Admin_ID(){
    int fd =open("Admin",O_RDONLY,0744);
	struct Administrator previous_id;
	lseek(fd,-sizeof(struct Administrator),SEEK_END);
	read(fd,&previous_id,sizeof(struct Administrator));
	close(fd);
	return previous_id.Admin_User_ID+1;
}
// Creating Normal user ID
int Normal_User_ID(){
    int fd=open("Normal_Users",O_RDONLY,0744);
	struct Normal_User previous_id;
	lseek(fd,-sizeof(struct Normal_User),SEEK_END);
	read(fd,&previous_id,sizeof(struct Normal_User));
	close(fd);
	return previous_id.Normal_User_ID+1;
}
// Creating Joint user ID
int Joint_User_ID(){
    int fd=open("Joint_Users",O_RDONLY,0744);
	struct Joint_User previous_id;
	lseek(fd,-sizeof(struct Joint_User),SEEK_END);
	read(fd,&previous_id,sizeof(struct Joint_User));
	close(fd);
	return previous_id.Joint_User_ID+1;
}

int main(){

    // Adding the Admins to database
    // "Admin" file will keep the details of admin
    // ID of Admin starts from 1
    int fd = open("Admin",O_RDWR | O_CREAT,0744);
    int Number_Of_Admins;
    printf("Number of Admins to be created: ");
    scanf("%d",&Number_Of_Admins);
    struct Administrator Admin_Details;
    int temp=0;
    while(Number_Of_Admins){
        Number_Of_Admins--;
        printf("Enter the name of Admin: ");
        scanf("%s",Admin_Details.Username);
        printf("Enter the password for this account: ");
        scanf("%s",Admin_Details.Password);
        if(temp==0){
            temp=1;
            Admin_Details.Admin_User_ID=1;
        }
        else{
            Admin_Details.Admin_User_ID = Admin_ID();
        }
        printf("New User ID created: %d\n",Admin_Details.Admin_User_ID);
        write(fd,&Admin_Details,sizeof(struct Administrator));
    }
    close(fd);

    // Adding the Normal users to database
    // "Normal_Users" file will keep the details of Normal users
    // ID of Normal users starts from 100
    // Default balance starts from 0 
    // Account number starts from 1000
    fd = open("Normal_Users",O_RDWR | O_CREAT,0744);
    int Number_Of_Normal_Users;
    printf("Number of Normal Users to be created: ");
    scanf("%d",&Number_Of_Normal_Users);
    struct Normal_User Normal_User_Details;
    temp=0;
    while(Number_Of_Normal_Users){
        Number_Of_Normal_Users--;
        printf("Enter the name of User: ");
        scanf("%s",Normal_User_Details.Username);
        printf("Enter the password for this account: ");
        scanf("%s",Normal_User_Details.Password);
        if(temp==0){
            temp=1;
            Normal_User_Details.Normal_User_ID=100;
            Normal_User_Details.Balance =0;
            Normal_User_Details.Account_no=Normal_User_Details.Normal_User_ID-100+1000;
        }
        else{
            Normal_User_Details.Normal_User_ID = Normal_User_ID();
            Normal_User_Details.Balance =0;
            Normal_User_Details.Account_no=Normal_User_Details.Normal_User_ID-100+1000;
        }
        printf("New User ID created: %d\n",Normal_User_Details.Normal_User_ID);
        strcpy(Normal_User_Details.Acc_Status,"Account is Active");
        write(fd,&Normal_User_Details,sizeof(struct Normal_User));
    }
    close(fd);

    // Adding the Joint users to database
    // "Joint_Users" file will keep the details of Joint users
    // ID of Joint users starts from 200
    // Default balance starts from 0 
    // Account number starts from 2000
    fd = open("Joint_Users",O_RDWR | O_CREAT,0744);
    int Number_Of_Joint_Users;
    printf("Number of Joint Users to be created: ");
    scanf("%d",&Number_Of_Joint_Users);
    struct Joint_User Joint_User_Details;
    temp=0;
    while(Number_Of_Joint_Users){
        Number_Of_Joint_Users--;
        printf("Enter the name of first joint user: ");
        scanf("%s",Joint_User_Details.Username1);
         printf("Enter the name of second joint user: ");
        scanf("%s",Joint_User_Details.Username2);
        printf("Enter the password for this account: ");
        scanf("%s",Joint_User_Details.Password);
        if(temp==0){
            temp=1;
            Joint_User_Details.Joint_User_ID=200;
            Joint_User_Details.Balance =0;
            Joint_User_Details.Account_no=Joint_User_Details.Joint_User_ID-200+2000;
        }
        else{
            Joint_User_Details.Joint_User_ID = Joint_User_ID();
            Joint_User_Details.Balance =0;
            Joint_User_Details.Account_no=Joint_User_Details.Joint_User_ID-200+2000;
        }
        printf("New User ID created: %d\n",Joint_User_Details.Joint_User_ID);
        strcpy(Joint_User_Details.Acc_Status,"Account is Active");
        write(fd,&Joint_User_Details,sizeof(struct Joint_User));
    }
    close(fd);
}