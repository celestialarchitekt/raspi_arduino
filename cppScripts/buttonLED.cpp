
/*
	Button Press -> LED ON / OFF Raspi->Arduino 
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
 tcflush(fd, TCIFLUSH);
  
 while(true){
 
  std::vector<char> response(8);
  int x = read(fd, response.data(), response.size());
  response.resize(x);

  
  // check if data available at serial port
  if(x>0)
  {
    if(response[0]=='1')
    {
     std::cout<<"response: "<<response[0]<<std::endl; 
     write(fd, "on\n", strlen("on\n"));
     std::cout<<"on command sent"<<std::endl;
    }  

    else if(response[0]=='0')
    {
     std::cout<<"response: "<<response[0]<<std::endl;
     write(fd, "off\n", strlen("off\n"));
      std::cout<<"off command sent" << std::endl;
    }
  }

 }


 close(fd);
 return 0;

}


