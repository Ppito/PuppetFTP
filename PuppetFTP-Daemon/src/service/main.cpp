
#include "puppetftpservice.h"

// -ORBInitRef NameService=corbaloc:iiop:localhost:2809/NameService

int main(int argc, char ** argv)
{
    PuppetFtpService service(argc, argv);
    return service.exec();
}
