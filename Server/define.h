/* 
 * File:   define.h
 * Author: Administrator
 *
 * Created on February 1, 2014, 3:08 AM
 */

#ifndef DEFINE_H
#define	DEFINE_H

  struct table{
        char string[128];
        char read[32];
        char write[32];
        int size;
    }table[64];
    
    struct {
        int size;
    }table_s;

#endif	/* DEFINE_H */

