/*
 * Types.h
 *
 *  Created on: Jan 20, 2023
 *      Author: ahmad
 */

#ifndef INC_TYPES_H_
#define INC_TYPES_H_

#define NULL_PTR	(void *)0

typedef unsigned char				u8;
typedef signed char					s8;
typedef unsigned short int			u16;
typedef signed short int			s16;
typedef unsigned int				u32;
typedef signed int					s32;
typedef unsigned long long int		u64;
typedef signed long long int		s64;
typedef float						f32;
typedef double						f64;
typedef long double					f128;

typedef enum {
	FALSE,
	TRUE
} BooleanType;


#endif /* INC_TYPES_H_ */
