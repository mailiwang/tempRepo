
//接收到的串口数据存放的物理地址
#define SERIAL_DATA_PA  (0x12312312)

typedef struct {
    u8 *base;             //基地址
    u32 index;            //索引
} Serial_Data_Buffer_t;

//串口数据buffer
static Serial_Data_Buffer_t serial_data_buffer = {SERIAL_DATA_PA, 0};




//从串口获取数据
static void serial_get_data(void)
{
    u32 i;

    while(1)//检测是否有数据包到来
    {
        if () { //串口有数据
            //清串口标志位
            
            serial_data_buffer[serial_data_buffer.index++] = ; //串口数据
        }

        if(serial_data_buffer.index != 0)
        {
            while(1)//检测数据包是否接收完毕
            {
                if(flag==0)
                {
                    temp = APP_DATA_COUNTER;
                    flag = 1;
                }
                delay_ms(200);
                if(temp==APP_DATA_COUNTER)break;
                temp=APP_DATA_COUNTER;
            }
            break;
        }
    }
}


/*
串口命令, 从uart1接收数据, 先存放至内存
然后烧写进nand/nor flash里
*/
void do_serial(s32 argc, _char *argv[])
{
    u8 mode;
    if (argc != 3) return;

    //获取串口数据
    if (strcmp(argv[1], "get") == 0) {
        mode = 0;
    } else if (strcmp(argv[1], "nor") == 0) {
        mode = 1;
    } else if (strcmp(argv[1], "nand") {
        mode = 2;
    } else {
        printf("unknown param: %s\r\n", argv[1]);
        return;
    }
}

SHELL_EXPORT_CMD(serial, do_serial, get data from uart1 & program data into nor/nand flash, \r\n/
serial [get] [addr]\
serial [nor/nand] [addr]\


);







