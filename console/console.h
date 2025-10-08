#ifdef SCORE_CONSOLE

#ifndef SCORE_CONSOLE_H
#define SCORE_CONSOLE_H

/* TODO: SS - Add a _read function that takes a SCore_Buffer_Reader. */

SCORE_BOOL score_console_read_from_stdin(char *buffer, unsigned int buffer_length);

#endif

#endif