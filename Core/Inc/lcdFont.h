/*
 * font.h
 *
 *  Created on: May 6, 2025
 *      Author: 26448
 */

#ifndef INC_LCDFONT_H_
#define INC_LCDFONT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

    /*---------------------------------------- 常用颜色 ------------------------------------------------------

 1. 这里为了方便用户使用，定义的是24位 RGB888颜色，然后再通过代码自动转换成 16位 RGB565 的颜色
 2. 24位的颜色中，从高位到低位分别对应 R、G、B  3个颜色通道
 3. 用户可以在电脑用调色板获取24位RGB颜色，再将颜色输入LCD_SetColor()或LCD_SetBackColor()就可以显示出相应的颜色
 */
#define LCD_WHITE 0xFFFFFF // 纯白色
#define LCD_BLACK 0x000000 // 纯黑色

#define LCD_BLUE 0x0000FF    //	纯蓝色
#define LCD_GREEN 0x00FF00   //	纯绿色
#define LCD_RED 0xFF0000     //	纯红色
#define LCD_CYAN 0x00FFFF    //	蓝绿色
#define LCD_MAGENTA 0xFF00FF //	紫红色
#define LCD_YELLOW 0xFFFF00  //	黄色
#define LCD_GREY 0x2C2C2C    //	灰色

#define LIGHT_BLUE 0x8080FF    //	亮蓝色
#define LIGHT_GREEN 0x80FF80   //	亮绿色
#define LIGHT_RED 0xFF8080     //	亮红色
#define LIGHT_CYAN 0x80FFFF    //	亮蓝绿色
#define LIGHT_MAGENTA 0xFF80FF //	亮紫红色
#define LIGHT_YELLOW 0xFFFF80  //	亮黄色
#define LIGHT_GREY 0xA3A3A3    //	亮灰色

#define DARK_BLUE 0x000080    //	暗蓝色
#define DARK_GREEN 0x008000   //	暗绿色
#define DARK_RED 0x800000     //	暗红色
#define DARK_CYAN 0x008080    //	暗蓝绿色
#define DARK_MAGENTA 0x800080 //	暗紫红色
#define DARK_YELLOW 0x808000  //	暗黄色
#define DARK_GREY 0x404040    //	暗灰色

    // 字体相关结构定义
    typedef struct _pFont
    {
        const uint8_t* pTable; //	字模数组地址
        uint16_t Width;        //	单个字符的字模宽度
        uint16_t Height;       //	单个字符的字模长度
        uint16_t Sizes;        //	单个字符的字模数据个数
        uint16_t Table_Rows;   // 该参数只有汉字字模用到，表示二维数组的行大小
    } pFONT;

    /*------------------------------------ 中文字体 ---------------------------------------------*/

    extern pFONT CH_Font12; //	1212字体
    extern pFONT CH_Font16; //	1616字体
    extern pFONT CH_Font20; //	2020字体
    extern pFONT CH_Font24; //	2424字体
    extern pFONT CH_Font32; //	3232字体

    /*------------------------------------ ASCII字体 ---------------------------------------------*/

    extern pFONT ASCII_Font32; // 3216 字体
    extern pFONT ASCII_Font24; // 2412 字体
    extern pFONT ASCII_Font20; // 2010 字体
    extern pFONT ASCII_Font16; // 1608 字体
    extern pFONT ASCII_Font12; // 1206 字体

#ifdef __cplusplus
}
#endif

#endif /* INC_LCDFONT_H_ */
