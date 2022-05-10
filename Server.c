#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include <pthread.h>


// Normal user characterstics
struct Normal_User
{
    int Normal_User_ID;
    char Username[50];
    char Password[20];
    int Account_no;
    float Balance;
    char Acc_Status[20];
};

// Joint user characterstics
struct Joint_User
{
    int Joint_User_ID;
    char Username1[50];
    char Username2[50];
    char Password[20];
    int Account_no;
    float Balance;
    char Acc_Status[20];
};

// Admin characterstics
struct Administrator
{
    int Admin_User_ID;
    char Username[50];
    char Password[20];
};

// returns normal user corresponding to give id
struct Normal_User Get_Normal_User(int id)
{
    id = id - 100;
    struct Normal_User user;
    int fd = open("Normal_Users", O_RDONLY, 0744);

    struct flock lock;
    lock.l_type = F_RDLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = (id) * sizeof(struct Normal_User);
    lock.l_len = sizeof(struct Normal_User);
    lock.l_pid = getpid();

    // Locking
    fcntl(fd, F_SETLKW, &lock);

    lseek(fd, (id) * sizeof(struct Normal_User), SEEK_SET);
    read(fd, &user, sizeof(struct Normal_User));

    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);
    close(fd);

    return user;
}

// returns joint user corresponding to give id
struct Joint_User Get_Joint_User(int id)
{
    id = id - 200;
    struct Joint_User user;
    int fd = open("Joint_Users", O_RDONLY, 0744);

    struct flock lock;
    lock.l_type = F_RDLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = (id) * sizeof(struct Joint_User);
    lock.l_len = sizeof(struct Joint_User);
    lock.l_pid = getpid();

    // Locking
    fcntl(fd, F_SETLKW, &lock);

    lseek(fd, (id) * sizeof(struct Joint_User), SEEK_SET);
    read(fd, &user, sizeof(struct Joint_User));

    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);
    close(fd);

    return user;
}

// returns admin user corresponding to give id
struct Administrator Get_Administrator(int id)
{
    struct Administrator user;
    int fd = open("Admin", O_RDONLY, 0744);

    struct flock lock;
    lock.l_type = F_RDLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = (id) * sizeof(struct Administrator);
    lock.l_len = sizeof(struct Administrator);
    lock.l_pid = getpid();

    // Locking
    fcntl(fd, F_SETLKW, &lock);

    lseek(fd, (id) * sizeof(struct Administrator), SEEK_SET);
    read(fd, &user, sizeof(struct Administrator));

    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);
    close(fd);

    return user;
}

// Check if this particular user is active
bool if_Normal_User(struct Normal_User user)
{
    int positon = user.Normal_User_ID - 100;
    int fd = open("Normal_Users", O_RDONLY, 0744);
    bool if_normal;

    struct flock lock;
    lock.l_type = F_RDLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = (positon) * sizeof(struct Normal_User);
    lock.l_len = sizeof(struct Normal_User);
    lock.l_pid = getpid();

    // Locking
    fcntl(fd, F_SETLKW, &lock);
    struct Normal_User user_real;
    lseek(fd, (positon) * sizeof(struct Normal_User), SEEK_SET);
    read(fd, &user_real, sizeof(struct Normal_User));

    bool check_password = strcmp(user_real.Password, user.Password);
    bool check_About = strcmp(user_real.Acc_Status, "Account is Active");

    if (check_password == 0 && check_About == 0)
    {
        if_normal = true;
    }
    else
    {
        if_normal = false;
    }
    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);
    close(fd);
    return if_normal;
}
// Check if this particular user is active
bool if_Joint_User(struct Joint_User user)
{
    int positon = user.Joint_User_ID - 200;
    int fd = open("Joint_Users", O_RDONLY, 0744);
    bool if_joint;

    struct flock lock;
    lock.l_type = F_RDLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = (positon) * sizeof(struct Joint_User);
    lock.l_len = sizeof(struct Joint_User);
    lock.l_pid = getpid();

    // Locking
    fcntl(fd, F_SETLKW, &lock);
    struct Joint_User user_real;
    lseek(fd, (positon) * sizeof(struct Joint_User), SEEK_SET);
    read(fd, &user_real, sizeof(struct Joint_User));

    bool check_password = strcmp(user_real.Password, user.Password);
    bool check_About = strcmp(user_real.Acc_Status, "Account is Active");
    
    if (check_password == 0 && check_About == 0)
    {
        if_joint = true;
    }
    else
    {
        if_joint = false;
    }
    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);
    close(fd);
    return if_joint;
}
// Check if this admin is active
bool if_Administrator(struct Administrator user)
{
    int positon = user.Admin_User_ID-1;
    int fd = open("Admin", O_RDONLY, 0744);
    bool if_admin;

    struct flock lock;
    lock.l_type = F_RDLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = (positon) * sizeof(struct Administrator);
    lock.l_len = sizeof(struct Administrator);
    lock.l_pid = getpid();

    // Locking
    fcntl(fd, F_SETLKW, &lock);
    struct Administrator user_real;
    lseek(fd, (positon) * sizeof(struct Administrator), SEEK_SET);
    read(fd, &user_real, sizeof(struct Administrator));

    bool check_password = strcmp(user_real.Password, user.Password);
    
    if (check_password == 0)
    {
        if_admin = true;
    }
    else
    {
        if_admin = false;
    }
    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);
    close(fd);
    return if_admin;
}

// Deposit the given Amount to the Account of given id
bool Deposit(int Normal_Joint, int id, float Amount)
{
    if (Normal_Joint == 1)
    {
        id = id - 100;
        int fd = open("Normal_Users", O_RDWR, 0744);
        bool if_deposit;

        struct flock lock;
        lock.l_type = F_WRLCK;
        lock.l_whence = SEEK_SET;
        lock.l_start = (id) * sizeof(struct Normal_User);
        lock.l_len = sizeof(struct Normal_User);
        lock.l_pid = getpid();

        // Locking
        fcntl(fd, F_SETLKW, &lock);
        struct Normal_User user_real;
        lseek(fd, (id) * sizeof(struct Normal_User), SEEK_SET);
        read(fd, &user_real, sizeof(struct Normal_User));

        bool check_About = strcmp(user_real.Acc_Status, "Account is Active");
        if (check_About == 0)
        {
            user_real.Balance += Amount;
            lseek(fd, sizeof(struct Normal_User) * (-1), SEEK_CUR);
            write(fd, &user_real, sizeof(struct Normal_User));
            if_deposit = true;
        }
        else
        {
            if_deposit = false;
        }

        lock.l_type = F_UNLCK;
        fcntl(fd, F_SETLK,  &lock);
        close(fd);
        return if_deposit;
    }
    else if (Normal_Joint == 2)
    {
        id = id - 200;
        int fd = open("Joint_Users", O_RDWR, 0744);
        bool if_deposit;

        struct flock lock;
        lock.l_type = F_WRLCK;
        lock.l_whence = SEEK_SET;
        lock.l_start = (id) * sizeof(struct Joint_User);
        lock.l_len = sizeof(struct Joint_User);
        lock.l_pid = getpid();

        // Locking
        fcntl(fd, F_SETLKW, &lock);
        struct Joint_User user_real;
        lseek(fd, (id) * sizeof(struct Joint_User), SEEK_SET);
        read(fd, &user_real, sizeof(struct Joint_User));

        bool check_About = strcmp(user_real.Acc_Status, "Account is Active");
        if (check_About == 0)
        {
            user_real.Balance += Amount;
            lseek(fd, sizeof(struct Joint_User) * (-1), SEEK_CUR);
            write(fd, &user_real, sizeof(struct Joint_User));
            if_deposit = true;
        }
        else
        {
            if_deposit = false;
        }

        lock.l_type = F_UNLCK;
        fcntl(fd, F_SETLK,  &lock);
        close(fd);
        return if_deposit;
    }
    else
    {
        bool if_deposit = false;
        return if_deposit;
    }
}

// Withdraw the given Amount from the Account of given id
bool Withdraw(int Normal_Joint, int id, float Amount)
{
    if (Normal_Joint == 1)
    {
        id = id - 100;
        int fd = open("Normal_Users", O_RDWR, 0744);
        bool if_withdraw;

        struct flock lock;
        lock.l_type = F_WRLCK;
        lock.l_whence = SEEK_SET;
        lock.l_start = (id) * sizeof(struct Normal_User);
        lock.l_len = sizeof(struct Normal_User);
        lock.l_pid = getpid();

        // Locking
        fcntl(fd, F_SETLKW, &lock);
        struct Normal_User user_real;
        lseek(fd, (id) * sizeof(struct Normal_User), SEEK_SET);
        read(fd, &user_real, sizeof(struct Normal_User));

        bool check_About = strcmp(user_real.Acc_Status, "Account is Active");
       
        if (check_About == 0 && user_real.Balance >= Amount)
        {
            
            user_real.Balance -= Amount;
            lseek(fd, sizeof(struct Normal_User) * (-1), SEEK_CUR);
            write(fd, &user_real, sizeof(struct Normal_User));
            if_withdraw = true;
        }
        else
        {
            if_withdraw = false;
        }

        lock.l_type = F_UNLCK;
        fcntl(fd, F_SETLK, &lock);
        close(fd);
        return if_withdraw;
    }
    else if (Normal_Joint == 2)
    {
        id = id - 200;
        int fd = open("Joint_Users", O_RDWR, 0744);
        bool if_withdraw;

        struct flock lock;
        lock.l_type = F_WRLCK;
        lock.l_whence = SEEK_SET;
        lock.l_start = (id) * sizeof(struct Joint_User);
        lock.l_len = sizeof(struct Joint_User);
        lock.l_pid = getpid();

        // Locking
        fcntl(fd, F_SETLKW, &lock);
        struct Joint_User user_real;
        lseek(fd, (id) * sizeof(struct Joint_User), SEEK_SET);
        read(fd, &user_real, sizeof(struct Joint_User));

        bool check_About = strcmp(user_real.Acc_Status, "Account is Active");
        if (check_About == 0 && user_real.Balance >= Amount)
        {
            user_real.Balance -= Amount;
            lseek(fd, sizeof(struct Joint_User) * (-1), SEEK_CUR);
            write(fd, &user_real, sizeof(struct Joint_User));
            if_withdraw = true;
        }
        else
        {
            if_withdraw = false;
        }

        lock.l_type = F_UNLCK;
        fcntl(fd, F_SETLK,  &lock);
        close(fd);
        return if_withdraw;
    }
    else
    {
        
        bool if_withdraw = false;
        return if_withdraw;
    }
}

// Get Balance of the Account of given id
float Get_Balance(int Normal_Joint, int id)
{
    if (Normal_Joint == 1)
    {
        id = id - 100;
        int fd = open("Normal_Users", O_RDONLY, 0744);

        // int file_lock;
        struct flock lock;
        lock.l_type = F_RDLCK;
        lock.l_whence = SEEK_SET;
        lock.l_start = (id) * sizeof(struct Normal_User);
        lock.l_len = sizeof(struct Normal_User);
        lock.l_pid = getpid();

        // Locking
        fcntl(fd, F_SETLKW, &lock);
        struct Normal_User user_real;
        lseek(fd, (id) * sizeof(struct Normal_User), SEEK_SET);
        read(fd, &user_real, sizeof(struct Normal_User));

        bool check_About = strcmp(user_real.Acc_Status, "Account is Active");
        float balance;
        if (check_About == 0)
        {
            balance = user_real.Balance;
        }
        else
        {
            balance = 0;
        }

        lock.l_type = F_UNLCK;
        fcntl(fd, F_SETLK,  &lock);
        close(fd);
        return balance;
    }
    else if (Normal_Joint == 2)
    {
        id = id - 200;
        int fd = open("Joint_Users", O_RDONLY, 0744);

        struct flock lock;
        lock.l_type = F_RDLCK;
        lock.l_whence = SEEK_SET;
        lock.l_start = (id) * sizeof(struct Joint_User);
        lock.l_len = sizeof(struct Joint_User);
        lock.l_pid = getpid();

        // Locking
        fcntl(fd, F_SETLKW, &lock);
        struct Joint_User user_real;
        lseek(fd, (id) * sizeof(struct Joint_User), SEEK_SET);
        read(fd, &user_real, sizeof(struct Joint_User));

        bool check_About = strcmp(user_real.Acc_Status, "Account is Active");
        float balance;
        if (check_About == 0)
        {
            balance = user_real.Balance;
        }
        else
        {
            balance = 0;
        }

        lock.l_type = F_UNLCK;
        fcntl(fd, F_SETLK,  &lock);
        close(fd);
        return balance;
    }
    else
    {
        return 0;
    }
}
// Change the Password of the given Account
bool Change_Password(int Normal_Joint, int id, char New_Password[20])
{
    if (Normal_Joint == 1)
    {
        id = id - 100;
        int fd = open("Normal_Users", O_RDWR, 0744);
        bool if_change;

        struct flock lock;
        lock.l_type = F_WRLCK;
        lock.l_whence = SEEK_SET;
        lock.l_start = (id) * sizeof(struct Normal_User);
        lock.l_len = sizeof(struct Normal_User);
        lock.l_pid = getpid();

        // Locking
        fcntl(fd, F_SETLKW, &lock);
        struct Normal_User user_real;
        lseek(fd, (id) * sizeof(struct Normal_User), SEEK_SET);
        read(fd, &user_real, sizeof(struct Normal_User));

        bool check_About = strcmp(user_real.Acc_Status, "Account is Active");

        if (check_About == 0)
        {
            strcpy(user_real.Password, New_Password);
            lseek(fd, sizeof(struct Normal_User) * (-1), SEEK_CUR);
            write(fd, &user_real, sizeof(struct Normal_User));
            if_change = true;
        }
        else
        {
            if_change = false;
        }

        lock.l_type = F_UNLCK;
        fcntl(fd, F_SETLK,  &lock);
        close(fd);
        return if_change;
    }
    else if (Normal_Joint == 2)
    {
        id = id - 200;
        int fd = open("Joint_Users", O_RDWR, 0744);
        bool if_change;

        struct flock lock;
        lock.l_type = F_WRLCK;
        lock.l_whence = SEEK_SET;
        lock.l_start = (id) * sizeof(struct Joint_User);
        lock.l_len = sizeof(struct Joint_User);
        lock.l_pid = getpid();

        // Locking
        fcntl(fd, F_SETLKW, &lock);
        struct Joint_User user_real;
        lseek(fd, (id) * sizeof(struct Joint_User), SEEK_SET);
        read(fd, &user_real, sizeof(struct Joint_User));

        bool check_About = strcmp(user_real.Acc_Status, "Account is Active");
        if (check_About == 0)
        {
            strcpy(user_real.Password, New_Password);
            lseek(fd, sizeof(struct Joint_User) * (-1), SEEK_CUR);
            write(fd, &user_real, sizeof(struct Joint_User));
            if_change = true;
        }
        else
        {
            if_change = false;
        }

        lock.l_type = F_UNLCK;
        fcntl(fd, F_SETLK, &lock);
        close(fd);
        return if_change;
    }
    else
    {
        bool if_change = false;
        return if_change;
    }
}

// Add new Normal user
bool Add_Normal_User(struct Normal_User user)
{
    int fd = open("Normal_Users", O_RDWR, 0744);
    bool if_added;

    struct flock lock;
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_END;
    lock.l_start = (-1) * sizeof(struct Normal_User);
    lock.l_len = sizeof(struct Normal_User);
    lock.l_pid = getpid();

    // Locking
    fcntl(fd, F_SETLKW, &lock);

    struct Normal_User user_real; // User after which new user will be created

    lseek(fd, (-1) * sizeof(struct Normal_User), SEEK_END);
    read(fd, &user_real, sizeof(struct Normal_User));

    strcpy(user.Acc_Status, "Account is Active");
    user.Normal_User_ID = user_real.Normal_User_ID + 1;
    user.Account_no = user_real.Account_no + 1;

    int add = write(fd, &user, sizeof(struct Normal_User));
    if (add == 0)
    {
        if_added = false;
    }
    else
    {
        if_added = true;
    }
    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);
    close(fd);
    return if_added;
}

// Add new joint user
bool Add_Joint_User(struct Joint_User user)
{
    int fd = open("Joint_Users", O_RDWR, 0744);
    bool if_added;

    struct flock lock;
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_END;
    lock.l_start = (-1) * sizeof(struct Joint_User);
    lock.l_len = sizeof(struct Joint_User);
    lock.l_pid = getpid();

    // Locking
    fcntl(fd, F_SETLKW, &lock);
    struct Joint_User user_real; // User after which new user will be added
    lseek(fd, (-1) * sizeof(struct Joint_User), SEEK_END);
    read(fd, &user_real, sizeof(struct Joint_User));

    strcpy(user.Acc_Status, "Account is Active");
    user.Joint_User_ID = user_real.Joint_User_ID + 1;
    user.Account_no = user_real.Account_no + 1;

    int add = write(fd, &user, sizeof(struct Joint_User));
    if (add == 0)
    {
        if_added = false;
    }
    else
    {
        if_added = true;
    }
    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);
    close(fd);
    return if_added;
}

// Delete the given normal user
bool Delete_Normal_User(int id)
{
    id = id - 100;
    int fd = open("Normal_Users", O_RDWR, 0744);
    bool if_deleted;

    struct flock lock;
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = (id) * sizeof(struct Normal_User);
    lock.l_len = sizeof(struct Normal_User);
    lock.l_pid = getpid();

    // Locking
    fcntl(fd, F_SETLKW, &lock);

    struct Normal_User user_real; // User after which new user will be created

    lseek(fd, (id) * sizeof(struct Normal_User), SEEK_SET);
    read(fd, &user_real, sizeof(struct Normal_User));

    int check_About = strcmp(user_real.Acc_Status, "Account is Active");
    if (check_About == 0)
    {
        strcpy(user_real.Acc_Status, "Account is Closed");
        user_real.Balance = 0;
        lseek(fd, (-1) * sizeof(struct Normal_User), SEEK_CUR);

        int del = write(fd, &user_real, sizeof(struct Normal_User));
        if (del == 0)
        {
            if_deleted = false;
        }
        else
        {
            if_deleted = true;
        }
    }
    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);
    close(fd);
    return if_deleted;
}

// Delete the given joint user
bool Delete_Joint_User(int id)
{
    id = id - 200;
    int fd = open("Joint_Users", O_RDWR, 0744);
    bool if_deleted;

    struct flock lock;
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = (id) * sizeof(struct Joint_User);
    lock.l_len = sizeof(struct Joint_User);
    lock.l_pid = getpid();

    // Locking
    fcntl(fd, F_SETLKW, &lock);

    struct Joint_User user_real; // User after which new user will be created

    lseek(fd, (id) * sizeof(struct Joint_User), SEEK_SET);
    read(fd, &user_real, sizeof(struct Joint_User));

    int check_About = strcmp(user_real.Acc_Status, "Account is Active");
    if (check_About == 0)
    {
        strcpy(user_real.Acc_Status, "Account is Closed");
        user_real.Balance = 0;
        lseek(fd, (-1) * sizeof(struct Joint_User), SEEK_CUR);

        int del = write(fd, &user_real, sizeof(struct Joint_User));
        if (del == 0)
        {
            if_deleted = false;
        }
        else
        {
            if_deleted = true;
        }
    }
    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);
    close(fd);
    return if_deleted;
}

// Modify the given normal user
bool Modify_Normal_User(struct Normal_User user)
{
    int id = user.Normal_User_ID - 100;
    int fd = open("Normal_Users", O_RDWR, 0744);
    bool if_modified;

    struct flock lock;
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = (id) * sizeof(struct Normal_User);
    lock.l_len = sizeof(struct Normal_User);
    lock.l_pid = getpid();

    // Locking
    fcntl(fd, F_SETLKW, &lock);

    struct Normal_User user_real; // User after which new user will be created

    lseek(fd, (id) * sizeof(struct Normal_User), SEEK_SET);
    read(fd, &user_real, sizeof(struct Normal_User));

    int check_About = strcmp(user_real.Acc_Status, "Account is Active");
    if (check_About == 0 && user.Account_no == user_real.Account_no)
    {
        strcpy(user.Acc_Status, "Account is Active");

        lseek(fd, (-1) * sizeof(struct Normal_User), SEEK_CUR);

        int mod = write(fd, &user, sizeof(struct Normal_User));
        if (mod == 0)
        {
            if_modified = false;
        }
        else
        {
            if_modified = true;
        }
    }
    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);
    close(fd);
    return if_modified;
}
// Modify the given Joint user
bool Modify_Joint_User(struct Joint_User user)
{
    int id = user.Joint_User_ID - 200;
    int fd = open("Normal_Users", O_RDWR, 0744);
    bool if_modified;

    struct flock lock;
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = (id) * sizeof(struct Joint_User);
    lock.l_len = sizeof(struct Joint_User);
    lock.l_pid = getpid();

    // Locking
    fcntl(fd, F_SETLKW, &lock);

    struct Joint_User user_real; // User after which new user will be created

    lseek(fd, (id) * sizeof(struct Joint_User), SEEK_SET);
    read(fd, &user_real, sizeof(struct Joint_User));

    int check_About = strcmp(user_real.Acc_Status, "Account is Active");
    if (check_About == 0 && user.Account_no == user_real.Account_no)
    {
        strcpy(user.Acc_Status, "Account is Active");

        lseek(fd, (-1) * sizeof(struct Joint_User), SEEK_CUR);

        int mod = write(fd, &user, sizeof(struct Joint_User));
        if (mod == 0)
        {
            if_modified = false;
        }
        else
        {
            if_modified = true;
        }
    }
    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);
    close(fd);
    return if_modified;
}

// Operations given by Client
void Client_Q(int socketd)
{
    int Login_as;
    int Normal_Joint;
    int choose;
    int id;
    bool check;
    int type_of_Account;
    while (1)
    {
        read(socketd, &Login_as, sizeof(Login_as));
        printf("You Chose: %d\n", Login_as);
        if (Login_as == 1)
        {
            struct Normal_User user;
            type_of_Account = 1;
            read(socketd, &user, sizeof(struct Normal_User));
            printf("User ID activated: %d\n", user.Normal_User_ID);
            printf("Password: %s\n", user.Password);
            id = user.Normal_User_ID;
            check = if_Normal_User(user);
            
            write(socketd, &check, sizeof(check));
        }
        else if (Login_as == 2)
        {
            struct Joint_User user;
            type_of_Account = 2;
            read(socketd, &user, sizeof(struct Joint_User));
            printf("User ID activated: %d\n", user.Joint_User_ID);
            printf("Password: %s\n", user.Password);
            id = user.Joint_User_ID;
            check = if_Joint_User(user);
            
            write(socketd, &check, sizeof(check));
        }
        else if (Login_as == 3)
        {
            struct Administrator user;
            type_of_Account = 3;
            read(socketd, &user, sizeof(struct Administrator));
            printf("User ID activated: %d\n", user.Admin_User_ID);
            printf("Password: %s\n", user.Password);
            id = user.Admin_User_ID;
            check = if_Administrator(user);
            
            write(socketd, &check, sizeof(check));
        }
        else
        {
            check = false;
            write(socketd, &check, sizeof(check));
        }
        if (check == true)
        {
            break;
        }
    }
    while (1)
    {
        read(socketd, &choose, sizeof(int));
        if (Login_as == 1 || Login_as == 2)
        {
            if (choose == 1)
            {
                float Amount;
                read(socketd, &Amount, sizeof(Amount));
                check = Deposit(type_of_Account, id, Amount);
                write(socketd, &check, sizeof(check));
            }
            else if (choose == 2)
            {
                float Amount;
                read(socketd, &Amount, sizeof(Amount));
                check = Withdraw(type_of_Account, id, Amount);
                write(socketd, &check, sizeof(check));
            }
            else if (choose == 3)
            {
                float Amount;
                Amount = Get_Balance(type_of_Account, id);
                write(socketd, &Amount, sizeof(Amount));
            }
            else if (choose == 4)
            {
                char Password[20];
                read(socketd, Password, sizeof(Password));
                check = Change_Password(type_of_Account, id, Password);
                write(socketd, &check, sizeof(check));
            }
            else if (choose == 5)
            {
                if (Login_as == 1)
                {
                    struct Normal_User user = Get_Normal_User(id);
                    write(socketd, &user, sizeof(user));
                }
                else if (Login_as == 2)
                {
                    struct Joint_User user = Get_Joint_User(id);
                    write(socketd, &user, sizeof(user));
                }
            }
            else if (choose == 6)
            {
                // Thank you... end
                break;
            }
        }
        else if (Login_as == 3)
        {
            read(socketd,&Normal_Joint,sizeof(Normal_Joint));
            if(choose==1){
                if(Normal_Joint==1){
                    struct Normal_User user;
                    read(socketd,&user,sizeof(user));
                    check=Add_Normal_User(user);
                    write(socketd, &check,sizeof(check));
                }
                else if(Normal_Joint==2){
                    struct Joint_User user;
                    read(socketd,&user,sizeof(user));
                    check=Add_Joint_User(user);
                    write(socketd, &check,sizeof(check));
                }
            }
            else if(choose == 2){
                if(Normal_Joint == 1){
                    int del_id;
                    read(socketd,&del_id,sizeof(del_id));
                    check=Delete_Normal_User(del_id);
                    write(socketd, &check,sizeof(check));
                }
                else if(Normal_Joint == 2){
                    int del_id;
                    read(socketd,&del_id,sizeof(del_id));
                    check=Delete_Joint_User(del_id);
                    write(socketd, &check,sizeof(check));
                }
            }
            else if(choose==3){
                if(Normal_Joint == 1)
                {
                    struct Normal_User user;
                    read(socketd,&user, sizeof(user));
                    check=Modify_Normal_User(user);
                    write(socketd, &check,sizeof(check));
                }
                else if(Normal_Joint == 2){
                    struct Joint_User user;
                    read(socketd,&user, sizeof(user));
                    check=Modify_Joint_User(user);
                    write(socketd, &check,sizeof(check));
                }
            }
            else if(choose == 4){
                if(Normal_Joint ==1){
                    struct Normal_User user;
                    int user_id;
                    read(socketd,&user_id, sizeof(user_id));
                    user=Get_Normal_User(user_id);
                    write(socketd, &user,sizeof(user));
                }
                else if(Normal_Joint ==2){
                    struct Joint_User user;
                    int user_id;
                    read(socketd,&user_id, sizeof(user_id));
                    user=Get_Joint_User(user_id);
                    write(socketd, &user,sizeof(user));
                }
            }
            else if(choose==5){
                //end
                break;
            }
        }
    }
    close(socketd);
    write(1,"End of Operations...\n",sizeof("End of Operations...\n"));

}
void *Operation(void *socketd){
    int nsocketd=*(int*)socketd;
    Client_Q(nsocketd);
}
int main(){
    struct sockaddr_in server,client;
    int socketd,c_socketd,size_client;
    pthread_t thread;
    // Creating a socket here
    socketd=socket(AF_INET,SOCK_STREAM,0);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    //Change the port number every time you run the code
    server.sin_port = htons(5543);

    bind(socketd,(struct sockaddr*)&server,sizeof(server));
    listen(socketd,5);
    int fd=1;//STDOUT
    write(fd,"Waiting for the client...\n",sizeof("Waiting for the client...\n"));
    while(1){
        size_client=sizeof(client);
        c_socketd=accept(socketd,(struct sockaddr*)&client,&size_client);
        write(fd,"Got the client...\n",sizeof("Got the client...\n"));
        pthread_create(&thread,NULL,Operation,(void*)&c_socketd);
    }
    pthread_exit(NULL);
    close(socketd);

}
