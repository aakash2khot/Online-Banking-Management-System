#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdbool.h>

// Normal user characterstics
struct Normal_User{
    int Normal_User_ID;
	char Username[50];
	char Password[20];
	int Account_no;
	float Balance;
	char Acc_Status[20];
};
//Joint User Characterstics
struct Joint_User{
    int Joint_User_ID;
	char Username1[50];
    char Username2[50];
	char Password[20];
	int Account_no;
	float Balance;
	char Acc_Status[20];
};
// Admin Characterstics
struct Administrator{
    int Admin_User_ID;
	char Username[50];
    char Password[20];
};
int fd=1; //STDOUT 
void Login(int socketd);
int Login_as;
void Normal_User_Login(int socketd);
void Joint_User_Login(int socketd);
void Admin_User_Login(int socketd);
int ID;
void Menu(int socketd);
void Add_Account(int socketd);
void Delete_Account(int socketd);
void Modify_Account(int socketd);
void Search_for_Account(int socketd);
void Deposit(int socketd);
void Withdraw(int socketd);
void Balance_Enquiry(int socketd);
void Change_Password(int socketd);
void View_Details(int socketd);

// Login as Normal, Joint or Admin user
void Login(int socketd){

    write(fd,"If you want to Login as a Normal user, choose 1\n",sizeof("If you want to Login as a Normal user, choose 1\n"));
    write(fd,"If you want to Login as a Joint user, choose 2\n",sizeof("If you want to Login as a Joint user, choose 2\n"));
    write(fd,"If you want to Login as an Administrator, choose 3\n",sizeof("If you want to Login as an Administrator, choose 3\n"));

    write(fd,"Login as: ",sizeof("Login as: "));
    scanf("%d",&Login_as);
    if(Login_as==1){
        Normal_User_Login(socketd);
    }
    else if(Login_as==2){
        Joint_User_Login(socketd);
    }
    else if(Login_as==3){
        Admin_User_Login(socketd);
    }
    else{
        write(fd,"\nPlease try again.\n",sizeof("\nPlease try again.\n"));
        Login(socketd);
    }
}

// All operations are taken care of in Menu
void Menu(int socketd){

    // For Administrator, We can perform these operations
    if(Login_as==3){
        write(fd,"\nTo Add account, choose 1\n",sizeof("To Add account, choose 1\n"));
        write(fd,"To Delete account, choose 2\n",sizeof("To Delete account, choose 2\n"));
        write(fd,"To Modify account, choose 3\n",sizeof("To Modify account, choose 3\n"));
        write(fd,"To Search for account, choose 4\n",sizeof("To Search for account, choose 4\n"));
        write(fd,"To Exit, choose 5\n",sizeof("To Exit, choose 5\n"));

        int choose;
        write(fd,"What do you want to do ? : ",sizeof("What do you want to do ? :"));
        scanf("%d",&choose);
        if(choose == 1){
            Add_Account(socketd);
        }
        else if(choose == 2){
            Delete_Account(socketd);
        }
        else if(choose == 3){
            Modify_Account(socketd);
            
        }
        else if(choose == 4){
            Search_for_Account(socketd);
            
        }
        else if(choose == 5){
            // Exit from talk
            write(socketd,&choose,sizeof(int));
            write(fd,"Thank you, have a nice day!\n",sizeof("Thank you, have a nice day!\n"));
            exit(0);
        }
        else{
            write(fd,"\nPlease try again.\n",sizeof("\nPlease try again.\n"));
            Menu(socketd);
        
        }

    }
    else{
        // These operations are for Normal and Joint user
        write(fd,"\nTo Deposit, choose 1\n",sizeof("To Deposit, choose 1\n"));
        write(fd,"To Withdraw, choose 2\n",sizeof("To Withdraw, choose 2\n"));
        write(fd,"For Balance Enquiry, choose 3\n",sizeof("For Balance Enquiry, choose 3\n"));
        write(fd,"To Change Password, choose 4\n",sizeof("To Change Password, choose 4\n"));
        write(fd,"To View details, choose 5\n",sizeof("To View details, choose 5\n"));
        write(fd,"To Exit, choose 6\n",sizeof("To Exit, choose 6\n"));

        int choose;
        write(fd,"What do you want to do ? : ",sizeof("What do you want to do ? :"));
        scanf("%d",&choose);
        if(choose==1){
            Deposit(socketd);
           
        }
        else if(choose==2){
            Withdraw(socketd);
           
        }
        else if(choose ==3){
            Balance_Enquiry(socketd);
            
        }
        else if(choose ==4){
            Change_Password(socketd);
           
        }
        else if(choose ==5){
            View_Details(socketd);
           
        }
        else if(choose ==6){
            // Exit from talk
            write(socketd,&choose,sizeof(int));
            write(fd,"Thank you, have a nice day!\n",sizeof("Thank you, have a nice day!\n"));
            exit(0);
        }
        else{
            write(fd,"\nPlease try again.\n",sizeof("\nPlease try again.\n"));
            Menu(socketd);
           
        }
    }
}

// Login for Normal user
void Normal_User_Login(int socketd){
    bool login ;
    struct Normal_User user;
    write(fd,"Your User ID: ",sizeof("Your User ID: "));
    scanf("%d",&user.Normal_User_ID);
    ID=user.Normal_User_ID;
    write(fd,"Your Passowrd: ",sizeof("Your Passowrd: "));
    scanf("%s",user.Password);

    // Checking to the server
    write(socketd,&Login_as,sizeof(int));
    write(socketd,&user,sizeof(struct Normal_User));
    // Reading from the server
    read(socketd,&login,sizeof(bool));
    if(login){
        write(fd,"You are successfully Logged in...\n",sizeof("You are successfully Logged in...\n"));
    }
    else{
        write(fd,"\nPlease try again.\n",sizeof("\nPlease try again.\n"));
        Login(socketd);
    }
}
// Login for Joint user
void Joint_User_Login(int socketd){
    bool login ;
    struct Joint_User user;
    write(fd,"Your User ID: ",sizeof("Your User ID: "));
    scanf("%d",&user.Joint_User_ID);
    ID=user.Joint_User_ID;
    write(fd,"Your Passowrd: ",sizeof("Your Passowrd: "));
    scanf("%s",user.Password);

    // Checking to the server
    write(socketd,&Login_as,sizeof(int));
    write(socketd,&user,sizeof(struct Joint_User));
    // Reading from the server
    read(socketd,&login,sizeof(bool));
    if(login){
        write(fd,"You are successfully Logged in...\n",sizeof("You are successfully Logged in...\n"));
    }
    else{
        write(fd,"\nPlease try again.\n",sizeof("\nPlease try again.\n"));
        Login(socketd);
    }
}

// Login for Admin
void Admin_User_Login(int socketd){
    bool login ;
    struct Administrator user;
    write(fd,"Your User ID: ",sizeof("Your User ID: "));
    scanf("%d",&user.Admin_User_ID);
    ID=user.Admin_User_ID;
    write(fd,"Your Passowrd: ",sizeof("Your Passowrd: "));
    scanf("%s",user.Password);

    // Checking to the server
    write(socketd,&Login_as,sizeof(int));
    write(socketd,&user,sizeof(struct Administrator));
    // Reading from the server
    read(socketd,&login,sizeof(bool));
    if(login){
        write(fd,"You are successfully Logged in...\n",sizeof("You are successfully Logged in...\n"));
    }
    else{
        write(fd,"\nPlease try again.\n",sizeof("\nPlease try again.\n"));
        Login(socketd);
    }
}

// To Deposit money to one particula account
// This is for Normal and Joint user
void Deposit(int socketd){
    float Amount_to_be_Deposited;
    bool deposit;

    write(fd,"Amount to be Deposted: ₹",sizeof("Amount to be Deposted: ₹"));
    // Amount should be greater than ₹0 here
    scanf("%f",&Amount_to_be_Deposited);

    // Checking to the server
    int choose=1; // Deposit maps to option 1
    write(socketd,&choose,sizeof(int));
    write(socketd,&Amount_to_be_Deposited,sizeof(float));
    // Reading from the server
    read(socketd,&deposit,sizeof(bool));

    if(deposit){
        write(fd,"Amount is successfully deposited...\n",sizeof("Amount is successfully deposited...\n"));
    }
    else{
        write(fd,"\nPlease try again.\n",sizeof("\nPlease try again.\n"));
    }    
    Menu(socketd);
}
// To Withdraw money from one particula account
// This is for Normal and Joint user
void Withdraw(int socketd){
    float Amount_to_be_Withdrew;
    bool withdraw;

    write(fd,"Amount to be Withdrew: ₹",sizeof("Amount to be Withdrew: ₹"));
    // Amount should be greater than ₹0 here
    scanf("%f",&Amount_to_be_Withdrew);
    
    // Checking to the server
    int choose=2; // Withdraw maps to option 2
    write(socketd,&choose,sizeof(int));
    write(socketd,&Amount_to_be_Withdrew,sizeof(float));
    // Reading from the server
    read(socketd,&withdraw,sizeof(bool));

    if(withdraw){
        write(fd,"Amount is successfully Withdrew...\n",sizeof("Amount is successfully Withdrew...\n"));
    }
    else{
        write(fd,"\nPlease try again.\n",sizeof("\nPlease try again.\n"));
    }    
    Menu(socketd);
}

// To check Balance of one particula account
// This is for Normal and Joint user
void Balance_Enquiry(int socketd){
    float Amount_Details;

    // Checking to the server
    int choose=3; // Balance Enquiry maps to option 3
    write(socketd,&choose,sizeof(int));
    // Reading from the server
    read(socketd,&Amount_Details,sizeof(float));

    write(fd,"Balance Available in your Account: ₹",sizeof("Balance Available in your Account: ₹"));
    printf("%f\n",Amount_Details);

    Menu(socketd);
}

// To Change Password of one particula account
// This is for Normal and Joint user
void Change_Password(int socketd){
    char Pw[20];
    bool change_Pw;

    
    write(fd,"Enter the New Password: ",sizeof("Enter the New Password: "));
    scanf("%s",Pw);

    // Checking to the server
    int choose=4; // Change Password maps to option 4
    write(socketd,&choose,sizeof(int));
    write(socketd,Pw,sizeof(Pw));
    // Reading from the server
    read(socketd,&change_Pw,sizeof(bool));

    if(change_Pw){
        write(fd,"Password is changed Successfully...\n",sizeof("Password is changed Successfully...\n"));
    }
    else{
        write(fd,"\nPlease try again.\n",sizeof("\nPlease try again.\n"));
    }    
    Menu(socketd);
}

// To view all the details stored of one particula account
// This is for Normal and Joint user
void View_Details(int socketd){
    // Checking to the server
    int choose=5; // View Details maps to option 5
    write(socketd,&choose,sizeof(int));

    if(Login_as==1){
        // As Normal User
        struct Normal_User user;
        // Reading from the server
        read(socketd,&user,sizeof(struct Normal_User));
        printf("Username: %s\n",user.Username);
        printf("User ID: %d\n",user.Normal_User_ID);
        printf("Account Number: %d\n",user.Account_no);
        printf("Balance Available: ₹%f\n",user.Balance);
        printf("About Account: %s\n",user.Acc_Status);
    }
    else{
        // As Joint User
        struct Joint_User user;
        // Reading from the server
        read(socketd,&user,sizeof(struct Joint_User));
        printf("Usernam 1: %s\n",user.Username1);
        printf("Username 2: %s\n",user.Username2);
        printf("Account Number: %d\n",user.Account_no);
        printf("Balance Available: ₹%f\n",user.Balance);
        printf("About Account: %s\n",user.Acc_Status);
    }
    Menu(socketd);
}

// To Add an account to database
// This is done by Administrator
void Add_Account(int socketd){
    // Checking to the server
    int choose = 1; // Add Account maps to 1
    write(socketd,&choose,sizeof(int));
    int Normal_Joint;
    write(fd,"Account type (Choose 1 for Normal Account and Choose 2 for joint Account): ",sizeof("Account type (Choose 1 for Normal Account and Choose 2 for joint Account): "));
    scanf("%d",&Normal_Joint);
    write(socketd,&Normal_Joint,sizeof(int));
    if(Normal_Joint==1){
        // Normal user
        struct Normal_User user;
        write(fd,"Username: ",sizeof("Username: "));
        scanf("%s",user.Username);
        write(fd,"Password: ",sizeof("Password: "));
        scanf("%s",user.Password);
        write(fd,"Amount to be Deposited: ₹",sizeof("Amount to be Deposited: ₹"));
        scanf("%f",&user.Balance);
        write(socketd,&user,sizeof(struct Normal_User));
    }
    else{
        // Joint user
        struct Joint_User user;
        write(fd,"Username 1: ",sizeof("Username 1: "));
        scanf("%s",user.Username1);
        write(fd,"Username 2: ",sizeof("Username 2: "));
        scanf("%s",user.Username2);
        write(fd,"Password: ",sizeof("Password: "));
        scanf("%s",user.Password);
        write(fd,"Amount to be Deposited: ₹",sizeof("Amount to be Deposited: ₹"));
        scanf("%f",&user.Balance);
        write(socketd,&user,sizeof(struct Joint_User));
    }

    // Reading from the server
    bool add;
    read(socketd,&add,sizeof(bool));

    if(add){
        write(fd,"New Account has been added...\n",sizeof("New Account has been added...\n"));
    }
    else{
        write(fd,"\nPlease try again.\n",sizeof("\nPlease try again.\n"));
    }    
    Menu(socketd);
    
}

// To Delete an account from database
// This is done by Administrator
void Delete_Account(int socketd){
    // Checking to the server
    int choose = 2; // Delete Account maps to 2
    write(socketd,&choose,sizeof(int));
    int Normal_Joint;
    write(fd,"Account type (Choose 1 for Normal Account and Choose 2 for joint Account): ",sizeof("Account type (Choose 1 for Normal Account and Choose 2 for joint Account): "));
    scanf("%d",&Normal_Joint);
    write(socketd,&Normal_Joint,sizeof(int));

    int UserdID_to_be_deleted;
    write(fd,"Enter User ID: ",sizeof("Enter User ID: "));
    scanf("%d",&UserdID_to_be_deleted);
    write(socketd,&UserdID_to_be_deleted,sizeof(int));

    // Reading from the server
    bool del;
    read(socketd,&del,sizeof(bool));

    if(del){
        write(fd,"This Account has been deleted...\n",sizeof("This Account has been deleted...\n"));
    }
    else{
        write(fd,"\nPlease try again.\n",sizeof("\nPlease try again.\n"));
    }    
    Menu(socketd);
}

// To modify an account from database
// This is done by Administrator
void Modify_Account(int socketd){
    // Checking to the server
    int choose = 3; // Modify Account maps to 3
    write(socketd,&choose,sizeof(int));
    int Normal_Joint;
    write(fd,"Account type (Choose 1 for Normal Account and Choose 2 for joint Account): ",sizeof("Account type (Choose 1 for Normal Account and Choose 2 for joint Account): "));
    scanf("%d",&Normal_Joint);
    write(socketd,&Normal_Joint,sizeof(int));

    if(Normal_Joint==1){
        // Normal user
        struct Normal_User user;
        write(fd,"Enter User ID: ",sizeof("Enter User ID: "));
        scanf("%d",&user.Normal_User_ID);
        write(fd,"Enter Account Number: ",sizeof("Enter Account Number: "));
        scanf("%d",&user.Account_no);
        write(fd,"New Password: ",sizeof("New Password: "));
        scanf("%s",user.Password);
        write(fd,"New Username: ",sizeof("New Username: "));
        scanf("%s",user.Username);
        write(fd,"New Balance: ₹",sizeof("New Balance: ₹"));
        scanf("%f",&user.Balance);
        write(socketd,&user,sizeof(struct Normal_User));
    }
    else{
        // Joint user
        struct Joint_User user;
        write(fd,"Enter User ID: ",sizeof("Enter User ID: "));
        scanf("%d",&user.Joint_User_ID);
        write(fd,"Enter Account Number: ",sizeof("Enter Account Number: "));
        scanf("%d",&user.Account_no);
        write(fd,"New Username 1: ",sizeof("New Username 1: "));
        scanf("%s",user.Username1);
        write(fd,"New Username 2: ",sizeof("New Username 2: "));
        scanf("%s",user.Username2);
        write(fd,"New Password: ",sizeof("New Password: "));
        scanf("%s",user.Password);
        write(fd,"New Balance: ₹",sizeof("New Balance: ₹"));
        scanf("%f",&user.Balance);
        write(socketd,&user,sizeof(struct Joint_User));
    }

    // Reading from the server
    bool add;
    read(socketd,&add,sizeof(bool));

    if(add){
        write(fd,"Account has been modified...\n",sizeof("Account has been modified...\n"));
    }
    else{
        write(fd,"\nPlease try again.\n",sizeof("\nPlease try again.\n"));
    }    
    Menu(socketd);
}

// To Search an account from database
// This is done by Administrator
void Search_for_Account(int socketd){
    // Checking to the server
    int choose = 4 ;// Search Account maps to 4
    write(socketd,&choose,sizeof(int));
    int Normal_Joint;
    write(fd,"Account type (Choose 1 for Normal Account and Choose 2 for joint Account): ",sizeof("Account type (Choose 1 for Normal Account and Choose 2 for joint Account): "));
    scanf("%d",&Normal_Joint);
    write(socketd,&Normal_Joint,sizeof(int));

    if(Normal_Joint==1){
        // Normal user
        struct Normal_User user;
        int id;
        write(fd,"Enter User ID: ",sizeof("Enter User ID: "));
        scanf("%d",&id);
        write(socketd,&id,sizeof(int));

        // Read from the server
        int r=read(socketd,&user,sizeof(struct Normal_User));
        if(r){
            printf("User ID: %d\n",user.Normal_User_ID);
            printf("Username: %s\n",user.Username);
            printf("Account Number: %d\n",user.Account_no);
            printf("Balance: ₹%f\n",user.Balance);
            printf("About Account: %s\n",user.Acc_Status);
        }
        else{
            write(fd,"\nPlease try again.\n",sizeof("\nPlease try again.\n"));
        }
    }
    else if(Normal_Joint==2){
        // Joint user
        struct Joint_User user;
        int id;
        write(fd,"Enter User ID: ",sizeof("Enter User ID: "));
        scanf("%d",&id);
        write(socketd,&id,sizeof(int));

        // Read from the server
        int r=read(socketd,&user,sizeof(struct Joint_User));
        if(r){
            printf("User ID: %d\n",user.Joint_User_ID);
            printf("Username 1: %s\n",user.Username1);
            printf("Username 2: %s\n",user.Username2);
            printf("Account Number: %d\n",user.Account_no);
            printf("Balance: ₹%f\n",user.Balance);
            printf("About Account: %s\n",user.Acc_Status);
        }
        else{
            write(fd,"\nPlease try again.\n",sizeof("\nPlease try again.\n"));
        }
    }
    Menu(socketd);
}

int main(){
    struct sockaddr_in server;
    int socketd;
    // Creating socket here
    socketd=socket(AF_INET,SOCK_STREAM,0);
    server.sin_family=AF_INET;
    server.sin_addr.s_addr=INADDR_ANY;
    //server.sin_addr.s_addr=inet_addr("127.0.0.1");

    //Change the port number every time you run the code
    server.sin_port=htons(5543);
    connect(socketd,(struct sockaddr *)&server,sizeof(struct sockaddr_in));

    // Login as Normal user, Joint user or Admin
    Login(socketd);
    // All operations are taken care of in Menu
    Menu(socketd);
    close(socketd);
}