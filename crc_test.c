#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define IH_NMLEN		32	/* Image Name Length		*/
typedef struct image_header {
	uint32_t	ih_magic;	/* Image Header Magic Number	*/
	uint32_t	ih_hcrc;	/* Image Header CRC Checksum	*/
	uint32_t	ih_time;	/* Image Creation Timestamp	*/
	uint32_t	ih_size;	/* Image Data Size		*/
	uint32_t	ih_load;	/* Data	 Load  Address		*/
	uint32_t	ih_ep;		/* Entry Point Address		*/
	uint32_t	ih_dcrc;	/* Image Data CRC Checksum	*/
	uint8_t		ih_os;		/* Operating System		*/
	uint8_t		ih_arch;	/* CPU architecture		*/
	uint8_t		ih_type;	/* Image Type			*/
	uint8_t		ih_comp;	/* Compression Type		*/
	uint8_t		ih_name[IH_NMLEN];	/* Image Name		*/
} image_header_t;



uint32_t crc32_compute(uint8_t const * p_data, uint32_t size)
{
    uint32_t crc;
    crc = 0xFFFFFFFF;
    for (uint32_t i = 0; i < size; i++)
    {
        crc = crc ^ p_data[i];
        for (uint32_t j = 8; j > 0; j--)
        {
            crc = (crc >> 1) ^ (0xEDB88320U & ((crc & 1) ? 0xFFFFFFFF : 0));
        }
    }
    return ~crc;
}

//计算文件大小
int file_size(char* filename)
{
    FILE *fp=fopen(filename,"rb");
    if(!fp) return -1;
    fseek(fp,0L,SEEK_END);
    int size=ftell(fp);
    fclose(fp);

    return size;
}

uint8_t uImage_buffer[1024 * 1024 * 5];
uint8_t header_buffer[60];

int main(void)
{
    int f_Image_size;
    FILE *f_Image;
    image_header_t *p_header;
    uint32_t header_crc_value, cal_crc_value;


    printf("%d\n", sizeof(image_header_t));

    f_Image_size = file_size("uImage"); //获取文件大小
    printf("bin file size: %d Bytes.\n", f_Image_size);

    //打开文件
    f_Image = fopen("uImage", "rb");
    if (f_Image == NULL) {
        printf("Can't open uImage file.\n");
        return -1;
    }

    //读取整个文件到buffer里
    printf("%d read into uImage buffer.\n\n", fread(uImage_buffer, 1, f_Image_size, f_Image));
    fclose(f_Image);//关闭bin文件

    //打印buffer
    for (int i = 0; i < f_Image_size; i++) {
        printf("%02x ", uImage_buffer[i]);
    }

    //提取header中的CRC32值
    p_header = (image_header_t *)uImage_buffer;
    header_crc_value = p_header->ih_hcrc;
    printf("\nuImage data CRC32 in header= %x\n", header_crc_value);

    //计算实际uImage data CRC32
    cal_crc_value = crc32_compute(uImage_buffer + sizeof(image_header_t), f_Image_size - sizeof(image_header_t));
    printf("\nuImage data CRC32 calculated = %x\n", cal_crc_value);


    int j = 0;
    //把头部复制到历史buffer里
    for (int i = 0; i < 64; i++) {
        if (4 <= i && i <= 7) continue;

        header_buffer[j++] = uImage_buffer[i];
    }

    //打印buffer
    for (int i = 0; i < j; i++) {
        printf("%02x ", header_buffer[i]);
    }

    //计算头部CRC
    printf("\nuImage header CRC32 calculated = %x\n", crc32_compute(header_buffer, j));


    return 0;
}
