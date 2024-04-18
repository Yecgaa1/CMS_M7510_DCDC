#ifndef _BASE_TYPE_H
#define _BASE_TYPE_H

#define JOIN_EX2(a, b) a##b
#define JOIN_EX3(a, b, c) a##b##c
#define JOIN_EX4(a, b, c, d) a##b##c##d
#define JOIN_EX5(a, b, c, d, e) a##b##c##d##e

#define JOIN2(a, b) JOIN_EX2(a, b)
#define JOIN3(a, b, c) JOIN_EX3(a, b, c)
#define JOIN4(a, b, c, d) JOIN_EX4(a, b, c, d)
#define JOIN5(a, b, c, d, e) JOIN_EX5(a, b, c, d, e)

#endif