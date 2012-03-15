#include "options.h"

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>

Options::Options()
    : host(0/*"192.168.1.11"*/), // my default onky
      port(60128),
      cmd(0),
      tmdelay(-1)
{
}

void Options::display_usage_and_exit( void )
{
    puts( "Onkyo receiver control client (eISCP) over IP" );
    puts( "Options:\n"
          " -H, --onkyo-host\t onkyo ip address\n"
          " -p, --onkyo-port\t onkyo ip port\n"
          " -c, --command\t ISCP command\n"
          " -t, --tmdelay\t delay for waiting messages, ms\n"
          " -h, --help\t this help."
         );
    exit( EXIT_FAILURE );
}


static const char *optString = "H:p:c:t:h?";
static const struct option longOpts[] = {
    { "onkyo-host", required_argument, NULL, 'H' },
    { "onkyo-port", required_argument, NULL, 'p' },
    { "command", required_argument, NULL, 'c' },
    { "tmdelay", required_argument, NULL, 't' },
    { "help", no_argument, NULL, 'h' },
    { NULL, no_argument, NULL, 0 }
};

int Options::parse_args(int argc, char *argv[])
{
    int longIndex = 0;
    int opt = getopt_long( argc, argv, optString, longOpts, &longIndex );
    while( opt != -1 ) {
        switch( opt ) {
        case 'H':
            host = optarg;
            break;
        case 'p':
            port = atoi(optarg);
            break;
        case 'c':
            cmd = optarg;
            break;
        case 't':
            tmdelay = atoi(optarg);
            break;
        case 'h':   /* fall-through is intentional */
        case '?':
            display_usage_and_exit();
            break;
        default:
            break;
        }
        opt = getopt_long( argc, argv, optString, longOpts, &longIndex );
    }
    return 0;
}
