#include "UART_Connect.h"

uart_t*uart_1=NULL;

void UART_Init_setup()
{
    uart_1=uartBegin(1, 9600, SERIAL_8N1,RX_Pin,TX_Pin,256,256,false, 112);
}


/*
发送指令
"Pump:ON"
"Pump:OFF"
"Heater:ON"
"Heater:OFF"
"Light:ON"
"Light:OFF"
"Feed"

"Get_Temperature"
"Get_Light"

"Pump:status"
"Heater:status"
"Light:status"
"Feed:status"
*/
void UART_SendString(const char *data)
{
    uartWriteBuf(uart_1, (const uint8_t *)data, strlen(data));
}

/*
获取信息数据
"TEMP:26.5"
"LIGHT:650"

"Pump:ON"
"Pump:OFF"
"Heater:ON"
"Heater:OFF"
"Light:ON"
"Light:OFF"
"Feed"

*/
String UART_ReceiveString()
{
    String RX_Data="";
     while (uartAvailable(uart_1) > 0)
    {
        char c = uartRead(uart_1);
        if (c == '\n')
        {
            //Serial.println(RX_Data);
           return RX_Data;
        }
         RX_Data += c;
    }
    return RX_Data;
}

