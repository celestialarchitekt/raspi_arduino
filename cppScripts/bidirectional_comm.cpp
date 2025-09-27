
/*
	LED ON / OFF Raspi->Arduin, receive status, process it and print a msg on screeno 
 */

#include<iostream>
#include<termios.h>
#include<fcntl.h>
#include<unistd.h>
#include<cstring>
#include<vector>


int main()
{

 // open the terminal with read,write and the terminal does not control the process
 int fd = open("/dev/ttyACM0", O_RDWR | O_NOCTTY);
 if(fd<0)
 {
  perror("open");
  return 1;
 }

 termios tty{}; // create a struct tty
 tcgetattr(fd, &tty); // get the port and send it to termimal
 cfsetospeed(&tty, B9600); // set output baud rate
 cfsetispeed(&tty, B9600); // set input baud rate
 cfmakeraw(&tty);  // raw serial binary data on the channel
 tcsetattr(fd, TCSANOW, &tty); // take effect now

 while(true){
 char ch;
 std::cout<<"enter a ON/OFF, ON:1, OFF:2"<<std::endl;
 std::cin>>ch;

 if(ch=='1'){
    std::cout<<"pressed ON"<<std::endl;
    write(fd, "ON\n", strlen("ON\n"));
    usleep(500000); // half a second delay
   
    //receive response logic
    std::vector<char> resp1(256);
    int x = read(fd, resp1.data(), resp1.size());
    resp1.resize(x);

    if(x>0)
    {
      std::string s1(resp1.begin(), resp1.end());
      std::cout<<"status:"<<s1<<std::endl;
    }
 }
 else if(ch=='2'){
    std::cout<<"pressed OFF"<<std::endl;
    write(fd, "OFF\n", strlen("OFF\n"));
    usleep(500000); // half a second delay
    
    //receive response logic
    std::vector<char> response(256);
    int s = read(fd, response.data(), response.size());
    response.resize(s);
    if(s>0)
    {
       for(char ch:response)
       {
       	std::cout<<ch;
       }
       std::cout<<std::endl;
    } 
 }
 else {
    std::cout<<"wrong choice, enter again"<<std::endl;
    continue;
 }

 }

close(fd);
return 0;
}


