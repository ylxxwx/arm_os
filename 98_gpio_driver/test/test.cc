#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h> /* ioctl */

class PortGPIO
{
public:
    enum Mode
    {
        PullDisable = 0,
        PullDown = 1,
        PullUp = 2,
    };
    enum Direction
    {
        Input = 1,
        Output = 2,
    };
    PortGPIO(int file, int port, Direction dir, Mode mode) : file(file), port(port)
    {
        unsigned int params[2] = {port, mode};
        ioctl(file, dir, params);
    }

    int PortRead()
    {
        char buf;
        pread(file, &buf, 1, port);
        int value = (int)buf;
        return value;
    }

    int PortWrite(int value)
    {
        char buf = (char)value;
        pwrite(file, &buf, 1, port);
        return 0;
    }

private:
    int file;
    int port;
};

int main()
{
    int f = open("/dev/mygpio", O_RDWR);

    PortGPIO inPort(f, 20, PortGPIO::Input, PortGPIO::PullDown);
    PortGPIO outPort(f, 21, PortGPIO::Output, PortGPIO::PullDisable);
    while (1)
    {
        int ctl = inPort.PortRead();
        outPort.PortWrite(ctl);
        usleep(500000);
    }
}
