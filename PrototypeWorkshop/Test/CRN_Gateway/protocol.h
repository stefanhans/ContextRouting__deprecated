/*

      Excerpts from RFC draft:


    Figure shows the structure of CIP's header data.

   0                   1                   2                   3
   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |   request (1) |  profile (1)  |  version (1)  |  channel (1)  | |
   |                                                               | |
   |                            UUID (16)                          | |
   |                                                               | |
   |                                                               | fix
   |                          IP address (4)                       | |
   |            IP port (2)        |                               | |
   |                            time (8)                           | |
   |                               |   type (1)   |    size (1)    |---
   | ............................................................  | |
   | .............. additional data up to 255 bytes .............  | dyn
   | ............................................................  | |
   +---------------------------------------------------------------+


    Figure shows the structure of CIP's contextinformation.

   0                   1                   2                   3
   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |   type (1)    |         root-CIC (2)          |   size (1)    | fix
   | ............................................................  | |
   | .............. additional data up to 510 bytes .............  | dyn
   | .............. i.e. up to 255 CIC-Bricks  ..................  | |
   | ............................................................  | |
   +---------------------------------------------------------------+


    Figure shows the structure of CIP's application data.

   0                   1                   2                   3
   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |   type (1)    |   size (1)    | ............................  | fix
   | ............................................................  | |
   | .......... additional data up to 255 bytes (size) ..........  | dyn
   | ............................................................  | |
   +---------------------------------------------------------------+


                          General Errors

    +------------------+----------+-----------------------------------+
    | Category         | Priority | Error Enumeration (Error Number)  |
    +------------------+----------+-----------------------------------+
    | CIP_FORMAT_ERROR | NOTICE   | CIP_FORMAT_ERROR_OUT_OF_RANGE (1) |
    |                  |          |                                   |
    | CIP_FORMAT_ERROR | NOTICE   | CIP_FORMAT_ERROR_INCONSISTENT (2) |
    +------------------+----------+-----------------------------------+


                           UDP Errors

        +----------+----------+----------------------------------+
        | Category | Priority | Error Enumeration (Error Number) |
        +----------+----------+----------------------------------+
        |          |          |                                  |
        +----------+----------+----------------------------------+


                           TCP Errors

   +------------------+----------+-------------------------------------+
   | Category         | Priority | Error Enumeration (Error Number)    |
   +------------------+----------+-------------------------------------+
   | CIP_FORMAT_ERROR | NOTICE   | CIP_FORMAT_ERROR_WRONG_PROTOCOL (3) |
   +------------------+----------+-------------------------------------+


 */

#ifndef SRC_PROTOCOL_H_
#define SRC_PROTOCOL_H_

#define VERSION 1

#define HEADER_ADDITIONAL_SIZE 255

#define BRICKS_ADDITIONAL_SIZE 255

#define DATA_ADDITIONAL_SIZE 255

/**
 * enumeration definitions
 */
enum SERVICE { SERVICE_RZV=0, SERVICE_HEARTBEAT=1, SERVICE_OFFER_REQUEST=2, SERVICE_REPLY=3, SERVICE_DEFAULT_MIN=3 };
enum CHANNEL { CHANNEL_RZV=0, CHANNEL_CI_MATCHING=1, CHANNEL_DEFAULT_MIN=2 };
enum HEADER_TYPE { HEADER_TYPE_RZV=0, HEADER_TYPE_OK=0, HEADER_TYPE_ERROR=1, HEADER_TYPE_DEFAULT_MIN=2 };
enum CI_TYPE { CI_TYPE_RZV=0, CI_TYPE_SIMPLE_MATCH=1, CI_TYPE_DEFAULT_MIN=2 };
enum APP_TYPE { APP_TYPE_RZV=0, APP_TYPE_TEXT=1, APP_TYPE_URL=2, APP_TYPE_DEFAULT_MIN=3 };

enum PORT { PORT_TCP_DEFAULT=22365, PORT_UDP_DEFAULT=22366 };


enum ERROR_CATEGORY { ERROR_CATEGORY_NONE=0, CIP_FORMAT_ERROR=1 };
enum ERROR_PRIORITY { ERROR_PRIORITY_NONE=0, ERROR_PRIORITY_DEBUG=1, ERROR_PRIORITY_INFO=2, ERROR_PRIORITY_NOTICE=3, ERROR_PRIORITY_CRITICAL=4, ERROR_PRIORITY_ALERT=5, ERROR_PRIORITY_EMERGENCY=6 };
enum CIP_FORMAT_ERROR_ENUM { CIP_FORMAT_ERROR_NONE=0, CIP_FORMAT_ERROR_OUT_OF_RANGE=1, CIP_FORMAT_ERROR_INCONSISTENT=2, CIP_FORMAT_ERROR_WRONG_PROTOCOL=3 };


#endif /* SRC_PROTOCOL_H_ */
