//ab main.cpp

#include <ctype.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "ab.h"
#include <iostream>
#include <string>
#include <string.h>
#include <list>
#include <fstream>
#include <regex.h>

list<Person> addlist;

using namespace std;
unsigned char ch;
int menu_num;
const char *message;
char input[1028] = {0};

string str;
string name_str;
int value;
int remove_num;
int search_num;

int server_sockfd , client_sockfd ;
socklen_t server_len , client_len ;
struct sockaddr_in server_address ;
struct sockaddr_in client_address ;

/* 
file reader when start program
@param iterator1 list num
@param name data in file
@param mobile data in file
@param address data in file
@return personal data in list
*/

void Person::file_read(){
    Person *pp = new Person();
    std::ifstream ifs;
    string gomi;
    ifs.open( "address_data.txt" );
    printf("reading...\n");
    while(ifs){
        ifs  >> gomi;
        ifs  >> pp->name;
        ifs  >> gomi;
        ifs  >> pp->mobile;
        ifs  >> gomi;
        ifs  >> pp->address;
        if(ifs.eof())break;
    addlist.push_back(*pp);
    }
    ifs.close();
}

/* 
person data reading from list
@param iterator1 list num
@return all personal data 
*/
void Person::reading(){
    file_read();
    list<Person>::iterator it = addlist.begin();
    for(it=addlist.begin();it!=addlist.end();it++){
        cout << "name    " << (*it).name << endl;
        cout << "mobile  " << (*it).mobile << endl;
        cout << "address " << (*it).address << endl;
    }
}

/* 
file writer when quit program
@param iterator1 list num
@param name data in list
@param mobile data in list
@param address data in list
@return address_data.txt 
*/
void Person::file_write(){
    list<Person>::iterator it = addlist.begin();
    std::ofstream ofs;
    ofs.open( "address_data.txt" );
    printf("writing...\n");
    message="writing...\n";
    write(client_sockfd, message, strlen(message));
    for(it=addlist.begin();it!=addlist.end();it++){
         ofs  << "name    " << (*it).name << endl;
         ofs  << "mobile  " << (*it).mobile << endl;
         ofs  << "address " << (*it).address << endl;
     }
     ofs.close();
}

/* 
the process of adding data to list
@param iterator1 list num
@param name data by user
@param mobile data by user
@param address data by user
@return personal data list
*/
void Person::adding(void){
    Person *pp = new Person();
    message="name:";
    write(client_sockfd, message, strlen(message));
    memset(input,'\0',sizeof(input));
    read(client_sockfd, input, sizeof(input));
    str = input;
    pp->name = str;
    message="mobile:";
    write(client_sockfd, message, strlen(message));
    memset(input,'\0',sizeof(input));
    read(client_sockfd, input, sizeof(input));
    str = input;
    pp->mobile = str;
    message="address:";
    write(client_sockfd, message, strlen(message));
    memset(input,'\0',sizeof(input));
    read(client_sockfd, input, sizeof(input));
    str = input;
    pp->address = str;
    addlist.push_back(*pp);
    printf("address entry added\n");
    message="address entry added\nab>";
    write(client_sockfd, message, strlen(message));
}
/* 
number converter to english
@param counted number i
@return english number
*/
void count(int num){
    if(num == 0){
    printf(" Zero address entries deleted\n");
    message=" Zero address entries deleted\n ab>";
    write(client_sockfd, message, strlen(message));
        return;
    }
    char buf[256];
    const char *onesWord
    [] = {"", "one","two", "three","four", "five", "six","seven", "eight","nine"};
    const char *tensWord
    [] = {"", "ten","twenty", "thirty","fourty", "fifty","sixty", "seventy","eighty", "ninety"};

    int hundreds = num/ 100;
    int tens = (num /10) % 10;
    int ones = num %10;
    if(hundreds > 0){
        cout << onesWord [hundreds] << "hundred ";
        sprintf(buf, "%s%s", onesWord [hundreds], " address entries deleted\nab>");
        write(client_sockfd, buf, strlen(buf));
    }
    if(tens > 0){
        cout << tensWord[tens] << " ";
        sprintf(buf, "%s%s", tensWord[tens], " address entries deleted\nab>");
        write(client_sockfd, buf, strlen(buf));
    }
    if(ones > 0){
        cout << onesWord[ones];
        sprintf(buf, "%s%s", onesWord[ones], " address entries deleted\nab>");
        write(client_sockfd, buf, strlen(buf));
    }
    printf(" address entries deleted\n");
}

/*
the process of removing from list
@param iterator1 list num

@param selected number for name
@param selected number for mobile
@param selected number for address

@param name data in list
@param mobile data in list
@param address data in list
@return removing data from list
*/
void Person::remove(){
    string str;
    int i=0;
    list<Person>::iterator it = addlist.begin();
    switch(remove_num){
        regex_t reg;
case 1:
        message=" remove by name\n";
        write(client_sockfd, message, strlen(message));
        memset(input,'\0',sizeof(input));
        read(client_sockfd, input, sizeof(input));

        regcomp(&reg, input, REG_EXTENDED|REG_NOSUB);
        while( it != addlist.end() ){
          const char *buf=((*it).name).c_str();
         if(regexec(&reg,buf, 0, NULL, 0) != REG_NOMATCH){
            it = addlist.erase(it);
              i++;
              it--;
            }
            it++;
         }
         count(i);
         break;
case 2:
         message=" remove by mobile\n";
         write(client_sockfd, message, strlen(message));
         memset(input,'\0',sizeof(input));
         read(client_sockfd, input, sizeof(input));

         regcomp(&reg, input, REG_EXTENDED|REG_NOSUB);
         while( it != addlist.end() ){
            const char *buf=((*it).mobile).c_str();
            if(regexec(&reg,buf, 0, NULL, 0) != REG_NOMATCH){
                it = addlist.erase(it);
                i++;
                it--;
             }
             it++;
         }
         count(i);
         break;
case 3:
         message=" remove by address\n";
         write(client_sockfd, message, strlen(message));
         memset(input,'\0',sizeof(input));
         read(client_sockfd, input, sizeof(input));

         regcomp(&reg, input, REG_EXTENDED|REG_NOSUB);
         while( it != addlist.end() ){
             const char *buf=((*it).address).c_str();
             if(regexec(&reg,buf, 0, NULL, 0) != REG_NOMATCH){
                 it = addlist.erase(it);
                 i++;
                 it--;
             }
             it++;
         }
         count(i);
         break;
default:
        break;
    }
}
/*
the process of searching from list
@param iterator1 list num

@param selected number for name
@param selected number for mobile
@param selected number for address

@param name data in list
@param mobile data in list
@param address data in list
@return searched data from list
*/

void Person::search() {
    list<Person>::iterator it = addlist.begin();
    switch(search_num){
        const char *buf1;
        const char *buf2;
        const char *buf3;
        char buf_all[256];
        regex_t reg;
        memset(buf_all,'\0',sizeof(buf_all));
case 1:
        message=" ";
        write(client_sockfd, message, strlen(message));
        memset(input,'\0',sizeof(input));
        memset(buf_all,'\0',sizeof(buf_all));
        read(client_sockfd, input, sizeof(input));
        regcomp(&reg, input, REG_EXTENDED|REG_NOSUB);
        while( it != addlist.end() ){
           const char *buf=((*it).name).c_str();
           if(regexec(&reg,buf, 0, NULL, 0) != REG_NOMATCH){
               buf1=(*it).name.c_str();
               buf2=(*it).mobile.c_str();
               buf3=(*it).address.c_str();
               sprintf(buf_all, "%s \n%s %s %s", buf_all, buf1, buf2, buf3);
           }
           it++;
        }
        sprintf(buf_all, "%s \nab>", buf_all);
        printf("searched\n");
        write(client_sockfd, buf_all, strlen(buf_all));
        break;
case 2:
        message=" ";
        write(client_sockfd, message, strlen(message));
        memset(input,'\0',sizeof(input));
        memset(buf_all,'\0',sizeof(buf_all));
        read(client_sockfd, input, sizeof(input));
        regcomp(&reg, input, REG_EXTENDED|REG_NOSUB);
        while( it != addlist.end() ){
           const char *buf=((*it).mobile).c_str();
           if(regexec(&reg,buf, 0, NULL, 0) != REG_NOMATCH){
               buf1=(*it).name.c_str();
               buf2=(*it).mobile.c_str();
               buf3=(*it).address.c_str();
               sprintf(buf_all, "%s %s %s %s\n", buf_all, buf1, buf2, buf3);
           }
           it++;
        }
        sprintf(buf_all, "%s \nab>", buf_all);
        printf("searched\n");
        write(client_sockfd, buf_all, strlen(buf_all));
        break;
case 3:
        message=" ";
        write(client_sockfd, message, strlen(message));
        memset(input,'\0',sizeof(input));
        memset(buf_all,'\0',sizeof(buf_all));
        read(client_sockfd, input, sizeof(input));
        regcomp(&reg, input, REG_EXTENDED|REG_NOSUB);
        while( it != addlist.end() ){
            const char *buf=((*it).address).c_str();
            if(regexec(&reg,buf, 0, NULL, 0) != REG_NOMATCH){
                buf1=(*it).name.c_str();
                buf2=(*it).mobile.c_str();
                buf3=(*it).address.c_str();
                sprintf(buf_all, "%s %s %s %s\n", buf_all, buf1, buf2, buf3);
            }
            it++;
        }
        sprintf(buf_all, "%s \nab>", buf_all);
        printf("searched\n");
        write(client_sockfd, buf_all, strlen(buf_all));
        break;
default:
    break;
    }
}

/*
menu
@param selected number for name
@param selected number for mobile
@param selected number for address
@return proceed to each process
*/
void Person::menu(){
    using namespace std;

    string strAA = "name";
    string strBB = "mobile"; 
    string strCC = "address";
    string str;
    Person tmp;
    Person *psn;
    psn = &tmp;
    switch(menu_num){
case 1:
        Person::adding();
        break;
case 2:
        message=" by (name|mobile|address)";
        write(client_sockfd, message, strlen(message));
        memset(input,'\0',sizeof(input));
        read(client_sockfd, input, sizeof(input));
        str=input;
        if (str.compare(strAA) == 0){
            remove_num = 1;
            psn->remove();
        }
        if (str.compare(strBB) == 0){
            remove_num = 2;
            psn->remove();
        }
        if (str.compare(strCC) == 0){
            remove_num = 3;
             psn->remove();
        }
        else if ((str.compare(strAA) && str.compare(strBB) && str.compare(strCC))!=0||str.size()==0){
            message="ab>";
            write(client_sockfd, message, strlen(message));
            break;
        }
        break;
case 3:
        message=" by (name|mobile|address)";
        write(client_sockfd, message, strlen(message));
        memset(input,'\0',sizeof(input));
        read(client_sockfd, input, sizeof(input));
        str = input;
        if (str.compare(strAA) == 0){
            search_num = 1;
            psn->search();
        }
        if (str.compare(strBB) == 0){
            search_num = 2;
            psn->search();
        }
        if (str.compare(strCC) == 0){
            search_num = 3;
            psn->search();
        }
        else if ((str.compare(strAA) && str.compare(strBB) && str.compare(strCC))!=0||str.size()==0){
            message="ab>";
            write(client_sockfd, message, strlen(message));
            break;
        }
        break;
case 4:
        message="******help******\n add\n remove\n search\n !help\n !quit\nab>";
        printf("help\n");
        write(client_sockfd, message, strlen(message));
        break;
case 5:
        Person::file_write();
        exit(0);
        break;
    }
}
char input_buf[1024];
/*
main
@param selected number for feature
@return proceed to each process via menu
*/
int main(void){

    Person::reading();
    string strA = "add";
    string strB = "remove"; 
    string strC = "search"; 
    string strD = "!help";
    string strE = "!quit";
    
    server_sockfd = socket(AF_INET,SOCK_STREAM,0);
    server_address.sin_family = AF_INET ;
    server_address.sin_addr.s_addr = inet_addr("192.168.7.12");
    server_address.sin_port = 9734 ;

    server_len = sizeof(server_address);
    bind(server_sockfd , (struct sockaddr *)&server_address , server_len);
    listen(server_sockfd , 5);
    client_sockfd = accept(server_sockfd ,(struct sockaddr*)&client_address, &client_len);
    message="ab>";

    write(client_sockfd, message, strlen(message));
        while(1){
            memset(input,'\0',sizeof(input));
            read(client_sockfd, input, sizeof(input));
            menu_num=0;
            string str = input;
            Person *psn = new Person();
            if (((str.compare(strA) && str.compare(strB) && str.compare(strC) && str.compare(strD) && str.compare(strE))) !=0){
                menu_num = 4;
                psn->menu();
            }
            else if (str.compare(strA) == 0){
                menu_num = 1;
                psn->menu();
            }
            else if (str.compare(strB) == 0){
                menu_num = 2;
                psn->menu();
            }
            else if (str.compare(strC) == 0){
                menu_num = 3;
                psn->menu();
            }
            else if (str.compare(strD) == 0){
                menu_num = 4;
                psn->menu();
            }
            else if (str.compare(strE) == 0){
                menu_num = 5;
                psn->menu();
            }
     }
     close(client_sockfd);
     return 0;
}
