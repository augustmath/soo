#include <stdio.h>
#include <stdint.h>

// Estrutura da MBR (Master Boot Record)
struct MBR {
    uint8_t boot_code[446];
    uint16_t partition_entries[4][2];
    uint8_t signature[2];
};

int main() {
    const char *file_path = "mbr_new.bin"; // Substitua pelo caminho do seu arquivo MBR

    FILE *file = fopen(file_path, "rb");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    struct MBR mbr;
    fread(&mbr, sizeof(struct MBR), 1, file);

    fclose(file);

    printf("Disk %s: 512 B, 512 bytes, 1 sector\n", file_path);
    printf("Units: sectors of 1 * 512 = 512 bytes\n");

    for (int i = 0; i < 4; ++i) {
        uint8_t start_head = mbr.partition_entries[i][0] >> 8;
        uint8_t start_sector = mbr.partition_entries[i][0] & 0xFF;
        uint8_t start_cylinder = mbr.partition_entries[i][1] >> 8;
        uint8_t type = mbr.partition_entries[i][1] & 0xFF;

        uint32_t start_sector_chs = (start_cylinder << 6) | start_head;
        uint32_t end_sector_chs = start_sector_chs + start_sector;

        printf("  Device Boot  Start     End Sectors Size Id Type\n");
        printf("  %s%d    %c  %8u %8u %7u %6uM %02X Unknown\n",
               file_path, i + 1, (i == 0) ? '*' : ' ', start_sector_chs, end_sector_chs,
               start_sector, start_sector * 512 / (1024 * 1024), type);
    }

    return 0;
}

