SOCKET sock = socket(AF_INET, SOCK_DGRAM, 0);
if(sock == INVALID_SOCKET)
{
    perror("socket()");
    exit(errno);
}