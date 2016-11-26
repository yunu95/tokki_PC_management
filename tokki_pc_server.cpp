#include "tokki_pc_socket.h"
// server
using namespace std;

int main(int argc,char *argv[])
{
	Socket sock(argc,argv[1]);//create socket
	sock.Start();//socket start - execute command
return 0;
}
