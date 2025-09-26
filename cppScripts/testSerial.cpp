#include <iostream>
#include <termios.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>  // for strlen
#include <csignal>

volatile sig_atomic_t stopFlag = 0;

void handleSigint(int signum)
{
 stopFlag=1;
}


int main() {
  
    std::signal(SIGINT,handleSigint); // catch ctlr-c	
  	
    int fd = open("/dev/ttyACM0", O_RDWR | O_NOCTTY);
    if (fd < 0) { perror("open"); return 1; }

    termios tty{};
    tcgetattr(fd, &tty);
    cfsetospeed(&tty, B9600);
    cfsetispeed(&tty, B9600);
    cfmakeraw(&tty);
    tcsetattr(fd, TCSANOW, &tty);

    while (true) {
        char ch;
        std::cout << "1: send | 2: read | q: quit\n";
        std::cout << "Enter choice: ";
        std::cin >> ch;

        switch (ch) {
		case '1': std::cout<<"in send mode, ctrl-c to stop"<<std::endl;
                try{
	       	 while(true)			  
			{
			if(stopFlag)
			{
			throw std::runtime_error("ctrl-c pressed");
			}

               	 	write(fd, "Hi from Raspi\n", strlen("Hi from Raspi\n"));
                       	std::cout << "Data sent"<<std::endl;
                        
		        usleep(500000); // 0.5seconds	
		  
			}
		} catch(const std::exception &e)
			  {
			    std::cout<<e.what();
			    stopFlag=0;
			  }break;


		case '2': std::cout<<"in listening mode, ctrl-c to stop"<<std::endl;
	       
	        try{		  
		while(true) {
                char buf[128];
                int n = read(fd, buf, sizeof(buf)-1);
                if (n > 0) {
                    buf[n] = '\0';
		    std::cout<<buf;
		}
	        if(stopFlag){
		 throw std::runtime_error("ctrl-pressed");
                }
		
                }}
		catch(const std::exception &e){
	         std::cout<<e.what();
		 stopFlag=0;
		}break;

            case 'q':
                std::cout << "Quitting.\n";
                close(fd);
                return 0;

            default:
                std::cout << "Wrong choice.\n";
                break;
        }
    }

    close(fd);
    return 0;
}

