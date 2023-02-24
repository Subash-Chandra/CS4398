#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

void print_info(char* device) {
    // Open the device in read-only mode
    int fd = open(device, O_RDONLY);
    if (fd == -1) {
        printf("Error opening device %s\n", device);
        exit(1);
    }

    // Read from the device
    char buf[1024];
    ssize_t val = read(fd, buf, sizeof(buf));
    if (val == -1) {
        printf("Error reading from device %s\n", device);
        exit(1);
    }

    // Print the read data
    printf("Data read from device %s:\n", device);
    fwrite(buf, sizeof(char), val, stdout);

    // Close the device file descriptor
    close(fd);
}

int main(int argc, char* argv[]) {
    // Check that a command line argument was provided
    if (argc != 2) {
        printf("Usage: %s /dev/<device id>\n", argv[0]);
        exit(1);
    }

    // Check that the argument is in the expected format
    char* device = argv[1];
    if (strncmp(device, "/dev/", 5) != 0) {
        printf("Invalid device ID: %s\n", device);
        exit(1);
    }

    // Call the print_info function
    print_info(device);

    return 0;
}
