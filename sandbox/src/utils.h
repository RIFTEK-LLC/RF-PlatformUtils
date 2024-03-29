#ifndef UTILS_H
#define UTILS_H

/*==============================================================================
 * CONVERT UTILS
 *
 * 1. From STRING to UINT16, UINT32
 * 1.1 uint8_t string_to_uint16 (const char*  string_val, uint16_t* uint16_val);
 * 1.2 uint8_t string_to_uint32 (const char*  string_val, uint32_t* uint32_val);
 *
 * 2.
 */

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

/**
 * @brief string_to_uint16 - Convert char* to UINT16
 * @param string_val Input C string e.g. "1234"
 * @param uint16_val Output UINT32
 * @return TRUE on success, else FALSE
 */
uint8_t string_to_uint16 (const char*  string_val, uint16_t* uint16_val);

/**
 * @brief string_to_uint - Convert char* to UINT32
 * @param string_val Input C string e.g. "1234"
 * @param uint32_val Output UINT32
 * @return TRUE on success, else FALSE
 */
uint8_t string_to_uint32 (const char*  string_val, uint32_t* uint32_val);


/*==============================================================================
 * NETWORK UTILS
 *
 * 1 IP STRING from/to UINT32
 * 1.1 uint8_t ip_string_to_uint32 (const char*  ip_string, uint32_t* ip_addr);
 */


#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>
#else
#include <sys/socket.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#endif

/**
 * @brief ip_string_to_uint - Convert human readable IPv4 address to UINT32
 * @param ip_string Input C string e.g. "192.168.0.1"
 * @param ip_addr Output IP address as UINT32
 * @return TRUE on success, else FALSE
 */
uint8_t ip_string_to_uint32 (const char* ip_string, uint32_t* ip_addr);


/**
 * @brief uint32_to_ip_string - Convert UINT32 IPv4 address to human readable
 * @param ip_addr Input IP address as UINT32
 * @param ip_string Output C string e.g. "192.168.0.1"
 * @return TRUE on success, else FALSE
 */
uint8_t uint32_to_ip_string (uint32_t ip_addr, char** ip_string);


/*==============================================================================
 * THREAD UTILS
 *
 * 1. Errors
 * 1.1 void error_pthread_mutex_unlock(const int unlock_rv);
 * 1.2 void error_pthread_mutex_lock(const int lock_rv);
 * 1.3 void error_pthread_cond_signal(const int signal_rv);
 * 1.4 void error_pthread_setcanceltype(const int setcanceltype_rv);
 * 1.5 void error_pthread_create(const int create_rv);
 * 1.6 void error_pthread_cond_timedwait(const int timed_wait_rv);
 * 1.7 void error_pthread_join(const int join_rv);
 * 1.8 void error_clock_gettime(const int gettime_rv);
 *
 * 2. Examples
 * 2.1 void *worker_thread_example(void *data);
 * 2.2 int main_thread_example();
 */

#include <stdio.h>

#ifdef _WIN32
#include <time.h>
#include <windows.h>
#else
#include <sys/types.h>
#include <asm/errno.h>
#endif

void error_pthread_mutex_unlock(const int unlock_rv);
void error_pthread_mutex_lock(const int lock_rv);
void error_pthread_cond_signal(const int signal_rv);
void error_pthread_setcanceltype(const int setcanceltype_rv);
void error_pthread_create(const int create_rv);
void error_pthread_cond_timedwait(const int timed_wait_rv);
void error_pthread_join(const int join_rv);
void error_clock_gettime(const int gettime_rv);


/*==============================================================================
 * TIME UTILS
 *
 * 1. int get_time_of_day(struct timeval *tv, struct timezone *tz) - This function
 *    can get the time as well as a timezone.
 */

#ifdef _MSC_VER
#define CLOCK_REALTIME 0
struct timezone {
    int tz_minuteswest;     /* minutes west of Greenwich */
    int tz_dsttime;         /* type of DST correction */
};

int get_time_of_day(struct timeval *tv, struct timezone *tz);

LARGE_INTEGER getFILETIMEoffset();
int clock_gettime(int X, struct timespec *tv);
#endif

#endif // UTILS_H
