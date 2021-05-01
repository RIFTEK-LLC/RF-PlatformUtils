﻿#ifndef NETWORK_PLATFORM_H
#define NETWORK_PLATFORM_H
#include "platform_types.h"



#define RF_SOCKET_ERROR -1 /* Socket error  */

/** @brief The modbusHtoN_long_t function converts a u_long from host to TCP/IP
 *         network byte order (which is big-endian).
 *
 * @param hostlong - A 32-bit number in host byte order.
 * @return: The modbusHtoN_long_t function returns the value in TCP/IP's network
 *          byte order.
 */
typedef rfUint32 (*hton_long_t) (rfUint32 hostlong);

/** @brief The modbusHtoN_long_t function converts a u_long from TCP/IP network
 * order to host byte order (which is little-endian on rfIntel processors).
 *
 * @param netlong - A 32-bit number in TCP/IP network byte order.
 * @return: The modbusNtoH_long_t function returns the value supplied in the netlong parameter with the byte order reversed.
 */
typedef rfUint32 (*ntoh_long_t) (rfUint32 netlong);

/** @brief The modbusHtoN_short_t function converts a u_short from host to TCP/IP network byte order (which is big-endian).
 *
 * @param hostlong - A 16-bit number in host byte order.
 * @return: The modbusHtoN_short_t function returns the value in TCP/IP's network byte order.
 */
typedef rfUint16 (*hton_short_t)(rfUint16 hostshort);

/** @brief The modbusHtoN_short_t function converts a u_short from TCP/IP network byte order to host byte order
 *
 * @param netshort - A 16-bit number in TCP/IP network byte order.
 * @return: The modbusNtoH_short_t function returns the value in host byte order.
 */
typedef rfUint16 (*ntoh_short_t)(rfUint16 netshort);

/** @brief Pointer to TCP socket creation function
 *
 * @param af - The address family specification.
 * @param type - The type specification for the new socket.
 * @param protocol - The protocol to be used.
 * @return
 * - On success: If no error occurs, modbusCreateTcpSocket_t returns a descriptor referencing the new socket
 * - On error: NULL
 */
typedef void* (*create_udp_socket_t)();

/** @brief Pointer to the function that sets a socket option.
 *
 * @param socket - A descriptor that identifies a socket.
 * @param level - The level at which the option is defined.
 * @param optname - The socket option for which the value is to be set.
 * @param optval - A pointer to the buffer in which the value for the requested option is specified.
 * @param optlen - The size, in bytes, of the buffer pointed to by the optval parameter.
 *  @return
 * - On success: If no error occurs, modbusSetSocketOption_t returns zero
 * - On error: -1
 */
typedef rfInt8 (*set_broadcast_socket_option_t)(void* socket);

/** @brief Pointer to the function that sets a socket option.
 *
 * @param socket - A descriptor that identifies a socket.
 * @param level - The level at which the option is defined.
 * @param optname - The socket option for which the value is to be set.
 * @param optval - A pointer to the buffer in which the value for the requested option is specified.
 * @param optlen - The size, in bytes, of the buffer pointed to by the optval parameter.
 *  @return
 * - On success: If no error occurs, modbusSetSocketOption_t returns zero
 * - On error: -1
 */
typedef rfInt8 (*set_reuseaddr_socket_option_t)(void* socket);

/** @brief Pointer to the function that sets a socket option.
 *
 * @param socket - A descriptor that identifies a socket.
 * @param level - The level at which the option is defined.
 * @param optname - The socket option for which the value is to be set.
 * @param optval - A pointer to the buffer in which the value for the requested option is specified.
 * @param optlen - The size, in bytes, of the buffer pointed to by the optval parameter.
 *  @return
 * - On success: If no error occurs, modbusSetSocketOption_t returns zero
 * - On error: -1
 */
typedef rfInt8 (*set_socket_option_t)(
        void* socket, rfInt32 level, rfInt32 optname,
        const rfChar* optval, rfInt32 optlen);

/** @brief Pointer to the function that sets a timeout for socket receive.
 *
 * @param socket - A descriptor that identifies a socket.
 * @param msec - The timeout in millisec.
 *  @return
 * - On success: If no error occurs, returns zero
 * - On error: -1
 */
typedef rfInt8 (*set_socket_recv_timeout_t)(void* socket, rfInt32 msec);

/** @brief Pointer to the function that establishes a connection to a specified socket
 *
 * @param socket - A descriptor identifying an unconnected socket.
 * @param name - A pointer to the SockAddr structure to which the connection should be established.
 * @param namelen - The length, in bytes, of the SockAddr structure pointed to by the name parameter.
 * @return
 * - On success: If no error occurs, modbusSocketConnect_t returns zero
 * - On error: -1
 */
typedef rfUint8 (*socket_connect_t)(
        void* socket, rfUint32 dst_ip_addr, rfUint16 dst_port);

/** @brief Pointer to the function that associates a local address with a socket.
 *
 * @param socket - A descriptor identifying an unconnected socket.
 * @param name - A pointer to the SockAddr structure to which the connection should be established.
 * @param namelen - The length, in bytes, of the SockAddr structure pointed to by the name parameter.
 * @return
 * - On success: If no error occurs, modbusSocketBind_t returns zero
 * - On error: -1
 */
typedef rfInt (*socket_bind_t)(
        void* socket, rfUint32 ip_addr, rfUint16 port);

/** @brief Pointer to the function that places a socket in a state in which it is listening for an incoming connection.
 *
 * @param socket - A descriptor identifying a bound, unconnected socket.
 * @param backlog - The maximum length of the queue of pending connections.
 * @return
 * - On success: If no error occurs, modbusSocketListen_t returns zero
 * - On error: -1
 */
typedef rfUint8 (*socket_listen_t)(
        void* socket, rfInt32 backlog);

/** @brief Pointer to the function that permits an incoming connection attempt on a socket.
 *
 * @param socket - A descriptor that identifies a socket that has been placed in a listening
 * 				  state with the modbusSocketListen_t function. The connection is actually
 * 				  made with the socket that is returned by accept.
 * @param name - An optional pointer to a buffer that receives the address of the connecting
 * 				entity, as known to the communications layer. The exact format of the addr
 * 				parameter is determined by the address family that was established when
 * 				the socket from the SockAddr structure was created.
 * @param addrlen - An optional pointer to an rfInteger that contains the length of structure
 * 				   pointed to by the addr parameter.
 * @return
 * - On success: If no error occurs, modbusSocketAccept_t returns value is a handle for the
 * 				socket on which the actual connection is made
 * - On error  : NULL
 */
typedef void* (*socket_accept_t)(
        void* socket, rfUint32* srs_ip_addr, rfUint16* srs_port);

/** @brief Pointer to the function that closes an existing socket.
 *
 * @param socket - A descriptor identifying the socket to close.
 * @return
 * - On success: If no error occurs, modbusCloseTcpSocket_t returns zero.
 * - On error: -1
 */
typedef rfUint8 (*close_socket_t)(void* socket);

/** @brief Pointer to the send function that sends data on a TCP connected socket
 *
 * @param socket - A descriptor identifying a connected socket.
 * @param buf - A pointer to a buffer containing the data to be transmitted.
 * @param len - The length, in bytes, of the data in buffer pointed to by the buf parameter.
 * @return
 * - On success: If no error occurs, send returns the total number of bytes sent, which can be less
 * 				than the number requested to be sent in the len parameter
 * - On error: -1
 */
typedef rfInt (*send_tcp_data_t)(void* socket, const void *buf, rfSize len);

/** @brief Pointer to the send function that sends data on a UDP socket
 *
 * @param socket - A descriptor identifying a socket.
 * @param buf - A pointer to a buffer containing the message to be sent.
 * @param len - The size of the message in bytes.
 * @param dest_addr - Points to a sockaddr_in structure containing the destination address.
 * @param addrlen - Specifies the length of the sockaddr_in structure pointed to by the dest_addr argument.
 * @return
 * - On success: If no error occurs, send returns the total number of bytes sent, which can be less
 * 				than the number requested to be sent in the len parameter
 * - On error: -1
 */
typedef rfInt (*send_udp_data_t)(
        void* socket, const void *data, rfSize len,
        rfUint32 dest_ip_addr, rfUint16 dest_port);

/**
 * @brief Pointer to the function that receive message from socket and capture address of sender.
 * @param sockfd - Specifies a socket descriptor from which data should be received.
 * @param buf - Specifies the buffer in which to place the message.
 * @param len - Specifies the length of the buffer area.
 * @param src_addr - Specifies a socket address structure to record the address of the message sender.
 * @param addrlen - Specifies the length of the sender's address.
 * @return If successful - the number of bytes received. On failure, it returns a value of -1
 */
typedef rfInt (*recv_data_from_t)(
        void* sockfd, void *buf, rfSize len,
        rfUint32* srs_ip_addr, rfUint16* srs_port);

/**
 * @brief Pointer to the function that receive message from socket and capture address of sender.
 * @param sockfd - Specifies a socket descriptor from which data should be received.
 * @param buf - Specifies the buffer in which to place the message.
 * @param len - Specifies the length of the buffer area.
 * @return If successful - the number of bytes received. On failure, it returns a value of -1
 */
typedef rfInt (*recv_data_t)(void* socket, void *buf, rfSize len);

/** @brief Structure with user-provided platform-specific methods
 */
typedef struct
{
    hton_long_t hton_long;
    ntoh_long_t ntoh_long;
    hton_short_t hton_short;
    ntoh_short_t ntoh_short;

    create_udp_socket_t create_udp_socket;
    set_broadcast_socket_option_t set_broadcast_socket_option;
    set_reuseaddr_socket_option_t set_reuseaddr_socket_option;
    set_socket_option_t set_socket_option;
    set_socket_recv_timeout_t set_socket_recv_timeout;
    socket_connect_t socket_connect;
    socket_bind_t socket_bind;
    socket_listen_t socket_listen;
    socket_accept_t  socket_accept;
    close_socket_t close_socket;

    send_tcp_data_t send_tcp_data;
    send_udp_data_t send_udp_data;

    recv_data_from_t recv_data_from;
    recv_data_t recv_data;

}network_platform_dependent_methods_t;

/** @brief Structure with user-provided platform-specific methods
 */
typedef struct
{
    rfUint32 host_ip_addr;
    rfUint32 host_mask;

}network_platform_dependent_settings_t;

/** @brief Structure with user-provided platform-specific settings
 */
typedef struct
{
    network_platform_dependent_methods_t network_methods;
    network_platform_dependent_settings_t network_settings;
}network_platform_t;

extern network_platform_t network_platform;

/**
 * @brief init_network_platform - function for init network
 * @param methods
 */
void init_network_platform(network_platform_dependent_methods_t* methods);

/**
 * @brief set_adapter_settings - adapter settings for init network
 * @param settings
 */
void set_adapter_settings(rfUint32 host_mask, rfUint32 host_ip_addr);

#endif // NETWORK_PLATFORM_H
