#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>

int main() {
    const char *port_name = "/dev/pts/2";
    int fd = open(port_name, O_RDWR | O_NOCTTY);

    if (fd == -1) {
        printf("Error: Could not open port. %s\n", strerror(errno));
        return 1;
    }

    struct termios tty;
    tcgetattr(fd, &tty);
    cfsetispeed(&tty, B115200);
    cfsetospeed(&tty, B115200);

    // Configuration for 8N1
    tty.c_cflag &= ~PARENB;
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8;
    tty.c_cflag |= (CLOCAL | CREAD);

    // This part is vital for Receiving:
    // It tells the program to wait up to 20 seconds for data
    tty.c_cc[VTIME] = 200;
    tty.c_cc[VMIN] = 0;

    tcsetattr(fd, TCSANOW, &tty);

    // --- PART 1: TRANSMISSION ---
    const char *msg = "Masooma is testing the RISC-V UART bridge...\n";
    write(fd, msg, strlen(msg));
    tcdrain(fd);
    printf("1. Message sent to the hardware board.\n");

    // --- PART 2: RECEIVING ---
    printf("2. Waiting up to 20 seconds for a reply...\n");

    char buffer[256];
    memset(buffer, 0, sizeof(buffer)); // Clear the buffer

    // This command "listens" to the port
    int bytes_read = read(fd, buffer, sizeof(buffer) - 1);

    if (bytes_read > 0) {
        printf("3. SUCCESS! Received from hardware: %s\n", buffer);
    } else {
        printf("3. No reply received (Timeout).\n");
    }

    close(fd);
    return 0;
}
