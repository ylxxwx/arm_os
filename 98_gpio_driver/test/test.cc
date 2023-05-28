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
        Output = 1,
        Input = 2,
    };
    PortGPIO(int file, int port, Direction dir, Mode mode) : file(file), port(port)
    {
        unsigned int params[2] = {port, mode};
        ioctl(file, dir, params);
    }

    int PortRead()
    {
        char buf[1024];
        sprintf(buf, "%d", port);
        read(file, buf, 8);
        int value = 0;
        sscanf(buf, "%d", &value);
        return value;
    }

    int PortWrite(int value)
    {
        char buf[16];
        sprintf(buf, "%d-%d", port, value);
        write(file, buf, 16);
        return 0;
    }

private:
    int file;
    int port;
};

int main()
{
    int f = open("/proc/my-gpio", O_RDWR);

    PortGPIO inPort(f, 20, PortGPIO::Input, PortGPIO::PullDown);
    PortGPIO outPort(f, 21, PortGPIO::Output, PortGPIO::PullDisable);
    while (1)
    {
        int ctl = inPort.PortRead();
        outPort.PortWrite(ctl);
        usleep(500000);
    }
}
