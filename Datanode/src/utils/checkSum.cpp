//
// Created by lxx18 on 2023/9/10.
//
#include "utils/checkSum.h"

uint32_t checkSum(const unsigned char *buf, size_t len){
    auto ptr = (uintptr_t)buf;
    typedef uint16_t  __attribute__((__may_alias__)) u16_p;
    auto *u16_buf = (const u16_p *) ptr;

    uint32_t sum = 0;
    while(len >= (sizeof(*u16_buf) * 4)){
        sum += u16_buf[0];
        sum += u16_buf[1];
        sum += u16_buf[2];
        sum += u16_buf[3];
        len -= sizeof (*u16_buf) * 4;
        u16_buf += 4;
    }
    while (len >= sizeof(*u16_buf)){
        sum += *u16_buf;
        len -= sizeof (*u16_buf);
        u16_buf += 1;
    }

    if (len == 1){
        sum += *((const uint8_t *)u16_buf);
    }

    return (~sum) + 1;
}
