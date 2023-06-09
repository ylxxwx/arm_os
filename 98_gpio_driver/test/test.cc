#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h> /* ioctl */

typedef struct tagPortIn
{
    unsigned int port;
    unsigned int dir;
    unsigned int mode;
} PortInit;

// Define custom ioctl commands
#define IOCTL_PORT_INP _IOW(1, 1, PortInit *)
#define IOCTL_PORT_OUT _IOW(2, 2, PortInit *)

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
        PortInit init = {(unsigned int)port, dir, mode};
        printf("Port %d, Dir: %d, mode: %x\n", port, dir, mode);
        if (dir == Direction::Input)
            ioctl(file, IOCTL_PORT_INP, &init);
        else
            ioctl(file, IOCTL_PORT_OUT, &init);
    }

    int PortRead()
    {
        char buf;
        printf("Port Read:%d \n", port);
        pread(file, &buf, 1, port);
        int value = (int)buf;
        printf("Port Read:%d val:%d \n", port, value);
        return value;
    }

    int PortWrite(int value)
    {
        char buf = (char)value;
        printf("Port Write:%d val:%d \n", port, value);
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
