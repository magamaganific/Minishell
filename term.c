#include <term.h>
#include <termios.h>
#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

int main()
{
    struct termios old_term;
    if (tcgetattr(STDIN_FILENO, &old_term) == -1) {
        perror("tcgetattr");
        return 1;
    }
    struct termios new_term = old_term;
    new_term.c_iflag |= ICRNL;
    new_term.c_lflag |= (ICANON | IEXTEN | ECHO);
	new_term.c_cc[VINTR] = '\x04'; //ctrl + D suele ser VEOF, que sale del programa de una
	// new_term.c_cc[VKILL] = '\x03'; KILL borra la linea escrita, pero no hace salto de linea
    new_term.c_cc[VKILL] = '\x03';
    if (tcsetattr(STDIN_FILENO, TCSANOW, &new_term) == -1) {
        perror("tcsetattr");
        return 1;
    }
	char	*prompt;
	while (1)
	{
		prompt = readline("minishell$ ");
		if (!prompt)
			break;
		add_history(prompt);
		free(prompt);
	}
	clear_history();
    if (tcsetattr(STDIN_FILENO, TCSANOW, &old_term) == -1) {
        perror("tcsetattr");
        return 1;
    }
    return 0;
}