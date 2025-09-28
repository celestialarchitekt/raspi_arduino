#include<iostream>
#include<termios.h> // terminal
#include<fcntl.h>   // open
#include<unistd.h> // close
#include<cstring> // string
#include<vector> 
#include<chrono> // time

int main()
{

 //std::cout << std::ctime(&t);

 // open the terminal with read,write and the terminal does not control the process
 int fd = open("/dev/ttyACM1", O_RDWR | O_NOCTTY);
 if(fd<0)
 {
  perror("open");
  return 1;
 }

 /*Terminal Settings*/
 termios tty{}; // create a struct tty
 tcgetattr(fd, &tty); // get the port and send it to termimal
 cfsetospeed(&tty, B9600); // set output baud rate
 cfsetispeed(&tty, B9600); // set input baud rate
 cfmakeraw(&tty);  // raw serial binary data on the channel
 tcsetattr(fd, TCSANOW, &tty); // take effect now

 auto lastTime = std::chrono::steady_clock::now();;

 std::string line;

 while(true)
 {
    auto now = std::chrono::steady_clock::now(); // does not return a printable value
    //std::time_t t = std::chrono::system_clock::to_time_t(now); // makes it printable using std::cout
    std::vector<char> buffer(256);
    int len = read(fd, buffer.data(), buffer.size());
    buffer.resize(len);
    for(char ch:buffer)
    {
      if(ch=='\n')
      {
        std::cout<<line<<std::endl;
       	line.clear();
      }
      else if(ch!='\r')
      {
        line+=ch;
      }
    }
    
  // now is a point in time, we type cast the diff into seconds and use count() to return a numeric, else an obj.  
  if(std::chrono::duration_cast<std::chrono::seconds>(now-lastTime).count()>10)
  {
   write(fd, "reset\n", strlen("reset\n"));
   lastTime=now;
   std::cout<<"reset command sent"<<std::endl;
  }
 } 

return 0;
}
