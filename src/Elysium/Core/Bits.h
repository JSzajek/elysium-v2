#pragma once

#define BIT(n)			(1 << n)

//https://stackoverflow.com/questions/47981/how-do-you-set-clear-and-toggle-a-single-bit/263738#263738
#define BIT_SET(n,k)	((n) |= (1ULL<<(k)))
#define BIT_CLEAR(n,k)	((n) &= ~(1ULL<<(k)))
#define BIT_CHECK(n,k)	(!!((n) & (1ULL << (k))))
