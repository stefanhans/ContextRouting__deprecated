/*
 *
 *      Excerpts from RFC draft:
 *
 *      The following figure shows the header of the Context Datagram
 *
 *     0                   1                   2                   3 3
 *     0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 *     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *     |  service (1)  |  version (1)  |  channel (1)  | opt. size (1) |
 *     +-------------------------------+-------------------------------+
 *     |                                                               |
 *     |                            UUID (16)                          |
 *     |                                                               |
 *     |                                                               |
 *     +---------------------------------------------------------------+
 *     |                         IP address (4)                        |
 *     +---------------------------------------------------------------+
 *     |       port number (2)         | optional (1)  | optional (1)  |
 *     |  ......... optional additional data up to 255 bytes .......  |
 *     +---------------------------------------------------------------+
 *
 *     It will be part of any kind of context structure.
 *
 *
 *     The following figure shows the list of Context Bricks of the Context
 *     Datagram.  A Context Brick consists of two bytes: content und mask.
 *
 *     0                   1                   2                   3 3
 *     0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 *     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *     |   type (1)    |  content (1)  |   mask (1)    | list size (1) |
 *     +-------------------------------+-------------------------------+
 *     |  content (1)  |   mask (1)    |  content (1)  |   mask (1)    |
 *     |  ......... optional additional data up to 512 bytes ........  |
 *     +---------------------------------------------------------------+
 *
 *     It will be part of the context structures Offer and Request.
 *
 *
 *     The following figure shows the data part of the Context Datagram
 *
 *     0                   1                   2                   3 3
 *     0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 *     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *     |   type (1)    |  data (140) ................................  |
 *     |  ...........................................................  |
 *     |  ...........................................................  |
 *     |  ...........................................................  |
 *     |  ...........................................................  |
 *     +---------------------------------------------------------------+
 *     | opt. size (1) | optional (1)  | optional (1)  | optional (1)  |
 *     |  ......... optional additional data upt to 255 bytes .......  |
 *     +---------------------------------------------------------------+
 *
 *     It will be part of the context structures Offer and Answer.
 *
 */

#ifndef SRC_PROTOCOL_H_
#define SRC_PROTOCOL_H_

#define VERSION 0

#define HEADER_ADDITIONAL_SIZE 255

#define BRICKS_ADDITIONAL_SIZE 255

#define DATA_ADDITIONAL_SIZE 255

/**
 * enumeration definitions
 */
enum service_e { SERVICE_RZV=0, SERVICE_OFFER=1, SERVICE_REQUEST=8, SERVICE_ANSWER=64, SERVICE_INFO=128, SERVICE_TEST=UCHAR_MAX-1 };
enum channel_e { CHANNEL_DEFAULT=0, CHANNEL_OFFER=1, CHANNEL_REQUEST=8, CHANNEL_META=64, CHANNEL_TEST=UCHAR_MAX-1 };

enum port_e { PORT_DEFAULT=22365, PORT_TCP_CONTEXT=22365, PORT_UDP_CONTEXT=22366, PORT_TCP_META=22367, PORT_UDP_META=22368 };

enum context_type_e { CONTEXT_TYPE_DEFAULT=0, CONTEXT_TYPE_TEST=UCHAR_MAX-1 };
enum data_type_e { DATA_TYPE_DEFAULT=0, DATA_TYPE_TEXT=0, DATA_TYPE_URL=8, DATA_TYPE_TEST=UCHAR_MAX-1 };

#endif /* SRC_PROTOCOL_H_ */
