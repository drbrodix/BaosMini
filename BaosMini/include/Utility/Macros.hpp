#ifndef MACROS_HPP
#define MACROS_HPP

// Byte swapper macros for endianness
#ifndef swap2
#define swap2(x) (((x << 8) & 0xFF00) | ((x >> 8) & 0x00FF))
#endif // !swap2

#ifndef swap4
#define swap4(x) (((x << 24) & 0xFF000000) | ((x << 8) & 0x00FF0000) | ((x >> 8) & 0x0000FF00) | ((x >> 24) & 0x000000FF))
#endif // !swap4

#endif // !MACROS_HPP