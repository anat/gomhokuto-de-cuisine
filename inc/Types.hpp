/* 
 * File:   Types.h
 * Author: cedric.creusot
 *
 * Created on May 13, 2011, 10:05 AM
 */

#ifndef TYPES_HPP_
#define TYPES_HPP_

# ifdef  __unix__
#  include <stdint.h>
# elif   WIN32
#  include <BaseTsd.h>

//typedef UINT8   uint8_t;
//typedef UINT16  uint16_t;
typedef UINT32  uint32_t;
typedef UINT64  uint64_t;
//typedef INT8    int8_t;
//typedef INT16   int16_t;
typedef INT32   int32_t;
typedef INT64   int64_t;


# endif

typedef char    byte_t;

#endif //!TYPES_HPP_


