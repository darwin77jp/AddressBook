#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

  int sockfd ;
  int len ;
  struct sockaddr_in address ;
  int result ;
  char input[1028] = {0};
  const char *no_input;
  char message[1024] = {0};

  /*
  data input to server and quit processing
  @param all input data
  @return input to server or quit
  */
void input_section(){
  memset(input,'\0',sizeof(input));
  fgets(input,sizeof(input),stdin);
  if (strchr(input, '\n') != NULL) {
    input[strlen(input) - 1] = '\0';
  }
  if(!(strlen(input))){
    no_input="no_input";
    write(sockfd, no_input, strlen(no_input));
  }
  else {
    write(sockfd, input, strlen(input));
  }
  if (strcmp(input,"!quit")==0){
    close(sockfd);
    exit(0);
  }
  }
/*
read data from server
@param
@return appear server data
*/
void read_section(){
  memset(message,'\0',sizeof(message));
  read(sockfd, message, sizeof(message));
  std::cout<<message;
}

/*
main client
@param input and read data
@return all personal data
*/
int main(void)
{
  sockfd = socket(AF_INET,SOCK_STREAM,0);
  address.sin_family = AF_INET ;
  address.sin_addr.s_addr = inet_addr("192.168.7.12");
  address.sin_port = 9734 ;
  len = sizeof(address);
  result = connect(sockfd , (struct sockaddr *)&address , len);
  if ( result == -1 ) {
    perror("oops: client2");
    exit(1);
  }
  while(1){
    read_section();
    input_section();
  }
  close(sockfd);
  exit(0);
}

