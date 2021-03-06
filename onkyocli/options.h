
#ifndef OPTIONS_H
#define OPTIONS_H

class Options
{
public:
    const char *cmd;     /* -c option */
    int tmdelay;         /* -t option */

    const char *host;    /* -H option */
    int port;            /* -p option */

    char **inputCmds;
    int    numInputCmds;

    Options();
    int parse_args ( int argc, char *argv[] );
    void display_usage_and_exit( void );

};

#endif // OPTIONS_H
