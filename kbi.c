#include <stdio.h>
#include <unistd.h>   // STDIN_FILENO, isatty(), ttyname()
#include <stdlib.h>   // exit()
#include <termios.h>

int main() {
    struct termios tty_opts_backup, tty_opts_raw;

    if (!isatty(STDIN_FILENO)) {
      printf("Error: stdin is not a TTY\n");
      exit(1);
    }
    printf("stdin is %s\n", ttyname(STDIN_FILENO));

    // Back up current TTY settings
    tcgetattr(STDIN_FILENO, &tty_opts_backup);

    // Change TTY settings to raw mode
    cfmakeraw(&tty_opts_raw);
    tcsetattr(STDIN_FILENO, TCSANOW, &tty_opts_raw);

    // Read and print characters from stdin
    int c, i = 1;
    for (c = getchar(); c != 3; c = getchar()) {
        printf("%d. 0x%02x (0%02o)\r\n", i++, c, c);
    }
    printf("You typed 0x03 (003). Exiting.\r\n");

    // Restore previous TTY settings
    tcsetattr(STDIN_FILENO, TCSANOW, &tty_opts_backup);
}
