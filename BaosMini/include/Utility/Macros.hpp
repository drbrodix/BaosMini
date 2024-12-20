#ifndef MACROS_HPP
#define MACROS_HPP

/// <summary>
/// Macro swapping the bytes of 2byte datatypes, effectively
/// serving as a little-endian - big-endian converter.
/// </summary>
#define swap2(x) (((x << 8) & 0xFF00) | ((x >> 8) & 0x00FF))

/// <summary>
/// Macro swapping the bytes of 4byte datatypes, effectively
/// serving as a little-endian - big-endian converter.
/// </summary>
#define swap4(x) (((x << 24) & 0xFF000000) | ((x << 8) & 0x00FF0000) | ((x >> 8) & 0x0000FF00) | ((x >> 24) & 0x000000FF))

#endif // !MACROS_HPP