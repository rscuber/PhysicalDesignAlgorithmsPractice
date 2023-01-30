/*************************************************************************
	> File Name: macro.h
	> Author: 宫局仁的供橘人
	> Motto: Barefoot makes wheels
	> Created Time: Thu Dec  8 20:19:26 2022
 ************************************************************************/

#ifndef _MACRO_H
#define _MACRO_H

#include "color.h"

#ifdef DEBUG
#define DBG(fmt, args...) { \
    printf(L_GREEN "[%s : %s : %d] ", __FILE__, __func__, __LINE__); \
    printf(fmt, ##args); \
    printf("\n"); \
}
#else
#define DBG(fmt, args...)
#endif

#define GETSETVAR(type, name) \
        private: \
            type name##_; \
        public: \
            const type &name() const { \
                return name##_; \
            } \
            void set_##name(const type &value) { \
                name##_ = value; \
            }

#endif
