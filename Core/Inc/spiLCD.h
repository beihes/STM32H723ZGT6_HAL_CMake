/*
 * spiLCD.h
 *
 *  Created on: May 6, 2025
 *      Author: 26448
 */

#ifndef INC_SPILCD_H_
#define INC_SPILCD_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdarg.h>
#include "spi.h"
#include "lcdFont.h"

#define SPI6_LCD 1
#if SPI6_LCD
#define LCD_Width 240  // LCD的像素长度
#define LCD_Height 240 // LCD的像素宽度
    // 显示方向参数
// 使用示例：LCD_DisplayDirection(Direction_H) 设置屏幕横屏显示
#define Direction_H 0      // LCD横屏显示
#define Direction_H_Flip 1 // LCD横屏显示,上下翻转
#define Direction_V 2      // LCD竖屏显示
#define Direction_V_Flip 3 // LCD竖屏显示,上下翻转

// 设置变量显示时多余位补0还是补空格
// 只有 LCD_DisplayNumber() 显示整数 和 LCD_DisplayDecimals()显示小数 这两个函数用到
// 使用示例： LCD_ShowNumMode(Fill_Zero) 设置多余位填充0，例如 123 可以显示为 000123
#define Fill_Zero 0  // 填充0
#define Fill_Space 1 // 填充空格

#define RADIAN(angle) ((angle == 0) ? 0 : (3.14159 * angle / 180)) // 角度转换
#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define MIN(x, y) ((x) < (y) ? (x) : (y))
#define SWAP(x, y)   \
    (y) = (x) + (y); \
    (x) = (y) - (x); \
    (y) = (y) - (x);
#define ABS(X) ((X) > 0 ? (X) : -(X)) // 计算输入数值的绝对值

#define LCD_Backlight_PIN GPIO_PIN_12                              // 背光  引脚
#define LCD_Backlight_PORT GPIOG                                   // 背光 GPIO端口
#define GPIO_LDC_Backlight_CLK_ENABLE __HAL_RCC_GPIOG_CLK_ENABLE() // 背光 GPIO时钟

#define LCD_Backlight_OFF HAL_GPIO_WritePin(LCD_Backlight_PORT, LCD_Backlight_PIN, GPIO_PIN_RESET); // 低电平，关闭背光
#define LCD_Backlight_ON HAL_GPIO_WritePin(LCD_Backlight_PORT, LCD_Backlight_PIN, GPIO_PIN_SET);    // 高电平，开启背光

#define LCD_DC_PIN GPIO_PIN_15                              // 数据指令选择  引脚
#define LCD_DC_PORT GPIOG                                   // 数据指令选择  GPIO端口
#define GPIO_LDC_DC_CLK_ENABLE __HAL_RCC_GPIOG_CLK_ENABLE() // 数据指令选择  GPIO时钟

#define LCD_DC_Command HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_RESET); // 低电平，指令传输
#define LCD_DC_Data HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_SET);      // 高电平，数据传输

    // 二维坐标结构体，包含横坐标 x 和纵坐标 y
    typedef struct COORDINATE
    {
        int x; // 横坐标
        int y; // 纵坐标
    } TypeXY;

    // 旋转结构体，包含旋转中心 center、旋转角度 angle 和旋转方向 direct
    typedef struct ROATE
    {
        TypeXY center; // 旋转中心坐标
        float angle;   // 旋转角度
        int direct;    // 旋转方向
    } TypeRoate;

#define LCD_BUFFER_LENGTH 1024
    typedef struct SPILCDData
    {
        SPI_HandleTypeDef* hspi;
        uint32_t Color;       //	LCD当前画笔颜色
        uint32_t BackColor;   //	背景色
        uint8_t ShowNum_Mode; // 数字显示模式
        uint8_t Direction;    //	显示方向
        uint16_t Width;       // 屏幕像素长度
        uint16_t Height;      // 屏幕像素宽度
        uint8_t X_Offset;     // X坐标偏移，用于设置屏幕控制器的显存写入方式
        uint8_t Y_Offset;     // Y坐标偏移，用于设置屏幕控制器的显存写入方式
        pFONT* asciiFonts;      // 英文字体，ASCII字符集
        pFONT* cnFonts;         // 中文字体（同时也包含英文字体）
        uint16_t buffer[LCD_BUFFER_LENGTH]; // LCD缓冲区，16位宽（每个像素点占2字节）
    }SPILCDData;
    extern SPILCDData spiLCDData;

    /*------------------------------------------------ 函数声明 ----------------------------------------------*/

    void SPI_LCD_Init(void);                                                     // 液晶屏以及SPI初始化
    void LCD_Clear(void);                                                        // 清屏函数
    void LCD_ClearRect(uint16_t x, uint16_t y, uint16_t width, uint16_t height); // 局部清屏函数

    void LCD_SetAddress(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2); // 设置坐标
    void LCD_SetColor(uint32_t Color);                                       //	设置画笔颜色
    void LCD_SetBackColor(uint32_t Color);                                   //	设置背景颜色
    void LCD_SetDirection(uint8_t direction);                                //	设置显示方向

    //>>>>>	显示ASCII字符
    void LCD_SetAsciiFont(pFONT* fonts);                     //	设置ASCII字体
    void LCD_DisplayChar(uint16_t x, uint16_t y, uint8_t c); //	显示单个ASCII字符
    void LCD_DisplayString(uint16_t x, uint16_t y, char* p); //	显示ASCII字符串

    //>>>>>	显示中文字符，包括ASCII码
    void LCD_SetTextFont(pFONT* fonts);                           // 设置文本字体，包括中文和ASCII字体
    void LCD_DisplayChinese(uint16_t x, uint16_t y, char* pText); // 显示单个汉字
    void LCD_DisplayText(uint16_t x, uint16_t y, char* pText);    // 显示字符串，包括中文和ASCII字符

    //>>>>>	显示整数或小数
    void LCD_ShowNumMode(uint8_t mode);                                                         // 设置变量显示模式，多余位填充空格还是填充0
    void LCD_DisplayNumber(uint16_t x, uint16_t y, int32_t number, uint8_t len);                // 显示整数
    void LCD_DisplayDecimals(uint16_t x, uint16_t y, double number, uint8_t len, uint8_t decs); // 显示小数

    //>>>>>	2D图形函数
    void LCD_DrawPoint(uint16_t x, uint16_t y, uint32_t color); // 画点

    void LCD_DrawLine_V(uint16_t x, uint16_t y, uint16_t height);          // 画垂直线
    void LCD_DrawLine_H(uint16_t x, uint16_t y, uint16_t width);           // 画水平线
    void LCD_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2); // 两点之间画线

    void LCD_DrawRect(uint16_t x, uint16_t y, uint16_t width, uint16_t height); // 画矩形
    void LCD_DrawCircle(uint16_t x, uint16_t y, uint16_t r);                    // 画圆
    void LCD_DrawEllipse(int x, int y, int r1, int r2);                         // 画椭圆

    //>>>>>	区域填充函数
    void LCD_FillRect(uint16_t x, uint16_t y, uint16_t width, uint16_t height); // 填充矩形
    void LCD_FillCircle(uint16_t x, uint16_t y, uint16_t r);                    // 填充圆

    //>>>>>	绘制单色图片
    void LCD_DrawImage(uint16_t x, uint16_t y, uint16_t width, uint16_t height, const uint8_t* pImage);

    //>>>>>	批量复制函数，直接将数据复制到屏幕的显存
    void LCD_CopyBuffer(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t* DataBuff);

    void MoveTo(int x, int y);                                  // 移动到指定坐标
    void LineTo(int x, int y);                                  // 画线到指定坐标
    void SetRotateValue(int x, int y, float angle, int direct); // 设置旋转值

    TypeXY GetXY(void);                                                       // 获取当前坐标
    void SetRotateCenter(int x0, int y0);                                     // 设置旋转中心
    void SetAngleDir(int direction);                                          // 设置旋转方向
    void SetAngle(float angle);                                               // 设置旋转角度
    float mySqrt(float x);                                                    // 计算平方根
    void Rotate(int x0, int y0, int* x, int* y, double angle, int direction); // 旋转坐标
    TypeXY GetRotateXY(int x, int y);

    // 该函数修改于HAL的SPI库函数，专为 LCD_Clear() 清屏函数修改，
    // 目的是为了SPI传输数据不限数据长度的写入
    HAL_StatusTypeDef LCD_SPI_Transmit(SPI_HandleTypeDef* hspi, uint16_t pData, uint32_t Size);
    HAL_StatusTypeDef LCD_SPI_TransmitBuffer(SPI_HandleTypeDef* hspi, uint16_t* pData, uint32_t Size);

    void SPILCD_Printf(int x, int y, const char* format, ...);
#endif

#ifdef __cplusplus
}
#endif

#endif /* INC_SPILCD_H_ */
