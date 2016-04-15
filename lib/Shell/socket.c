#include <sys/types.h> /* Consultez NOTES */ 
#include <sys/socket.h> 

void connects(int ip,int port){
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
if(sock <= 0)
{
    perror("socket()");
    exit(0);
}
int connect(sock,ip);
    
}
int main(){
    connects (20,1);
    return 0;
}