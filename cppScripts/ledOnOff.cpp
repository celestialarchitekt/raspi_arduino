
/*
	LED ON / OFF Raspi->Arduino 
 */

#include<iostream>
#include<termios.h>
#include<fcntl.h>
#include<unistd.h>
#include<cstring>



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
    
 }
 else if(ch=='2'){
    std::cout<<"pressed OFF"<<std::endl;
    write(fd, "OFF\n", strlen("OFF\n"));
    usleep(500000); // half a second delay
    
 }
 else {
    std::cout<<"wrong choice, enter again"<<std::endl;
    continue;
 }

 }

close(fd);
return 0;
}


