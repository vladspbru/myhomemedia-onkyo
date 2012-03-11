#ifndef OPTIONS_H
#define OPTIONS_H

class Options
{
public:
    const char *host;    /* -H option */
    int port;            /* -p option */
    const char *cmd;     /* -c option */
    int spy;             /* -s option */
    int tmdelay;         /* -t option */


    Options();
    int parse_args (int argc, char *argv[]);
    void display_usage_and_exit( void );

};

#endif // OPTIONS_H
