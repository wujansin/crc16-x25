#include <stdio.h>
#include <stdint.h>

uint16_t crc16_x25_table[256] = {0};

void generate_crc16_x25_table() {
    uint16_t polynomial = 0x8408;
    for (int i = 0; i < 256; i++) {
        uint16_t crc = i;
        for (int j = 0; j < 8; j++) {
            if (crc & 1) {
                crc = (crc >> 1) ^ polynomial;
            } else {
                crc >>= 1;
            }
        }
        crc16_x25_table[i] = crc;
    }
}

uint16_t crc16_x25(const uint8_t *data, size_t len) {
    uint16_t crc = 0xFFFF;

    for (size_t i = 0; i < len; i++) {
        uint8_t table_index = (crc & 0xFF) ^ data[i];
        crc = (crc >> 8) ^ crc16_x25_table[table_index];
    }

    crc = ~crc;
    return crc;
}

int main() {
    generate_crc16_x25_table();

    uint8_t data[] ="Hello World!";
    size_t data_len = sizeof(data) - 1;

    uint16_t crc = crc16_x25(data, data_len);
    printf("CRC16 X25 checksum: 0x%04X\n", crc);

    return 0;
}
