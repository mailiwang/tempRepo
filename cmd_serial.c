
//接收到的串口数据存放的物理地址
#define SERIAL_DATA_PA  (0x12312312)

typedef struct {
	FlagStatus is_valid;  //是否有效
    u8 *base;             //基地址
    u32 index;            //索引
} Serial_Data_Buffer_t;

//串口数据buffer
static Serial_Data_Buffer_t serial_data_buffer = {SERIAL_DATA_PA, 0};



irq:
	if () { //串口有数据
		//清串口标志位
		
		serial_data_buffer[serial_data_buffer.index++] = ; //串口数据
	}

static u32 crc32_compute(u8 *p_data, u32 size)
{
    u32 crc;
    crc = 0xFFFFFFFF;
    for (u32 i = 0; i < size; i++)
    {
        crc = crc ^ p_data[i];
        for (u32 j = 8; j > 0; j--)
        {
            crc = (crc >> 1) ^ (0xEDB88320U & ((crc & 1) ? 0xFFFFFFFF : 0));
        }
    }
    return ~crc;
}

//从串口获取数据
static void serial_get_data(void)
{
	FlagStatus flag == RESET;
    u32 temp_cnt;

    //如果index != 0 则SDRAM里可能有数据, 提示一个警告
    if (serial_data_buffer.index || serial_data_buffer.is_valid == SET) {
        printf("warning: there was data in sdram before, clear it\r\n");
    }
	//清空buffer
	serial_data_buffer.base = SERIAL_DATA_PA;
	serial_data_buffer.index = 0;
	serial_data_buffer.is_valid = RESET;
    while(1)
    {
        if(serial_data_buffer.index != 0) //检测是否有数据包到来
        {
            //检测数据包是否接收完毕
			if(flag == RESET)
			{
				temp_cnt = serial_data_buffer.index;
				flag = SET;
			}
			Delay_Xms(20); //每隔20ms检测一次index
			if (temp_cnt == serial_data_buffer.index) {
				break; //20ms内index未改变, 说明数据已经接收完了
			}

			temp_cnt = serial_data_buffer.index; //获取最新index
        }
    }

    //下面校验数据
    //1, 先校验头部
    
    
    //2, 再校验数据部分




	//校验
	if (校验成功) {
		serial_data_buffer.is_valid = SET;
	} else {
        //清空buffer
        serial_data_buffer.base = SERIAL_DATA_PA;
        serial_data_buffer.index = 0;
        serial_data_buffer.is_valid = RESET;
        printf("serial got bad data, clearing buffer...\r\n");
    }
}
//烧写接收到的数据至nand flash上的kernel分区
static void serial_program(void)
{
    u32 i;

    if (serial_data_buffer.is_valid == RESET) { //确保数据传输过程中没有问题
        printf("no valid data in SDRAM\r\n");
        return;
    }

    //烧写nand flash
    nand_write();

    //检验是否烧写成功
    for (i = 0; i < ) {
        if () { //只要有一个字节不一致, 则烧写失败
            printf("data on nand flash error\r\n");
            break;
        }
    }
}

/*
串口命令, 从uart1接收uImage数据, 先存放至内存
然后烧写进nand/nor flash的kernel分区
*/
void do_serial(s32 argc, _char *argv[])
{
    if (argc != 2) return;

    //获取串口数据
    if (strcmp(argv[1], "get") == 0) {
        serial_get_data();
    } else if (strcmp(argv[1], "nand") {
        serial_program();
    } else {
        printf("unknown param: %s\r\n", argv[1]);
        return;
    }
}

SHELL_EXPORT_CMD_EX(serial, do_serial, get data from uart1 & program data into MTD kernel, \r\n\
serial [get]\r\n\
serial [nand]\
);

http://www.ip33.com/crc.html





