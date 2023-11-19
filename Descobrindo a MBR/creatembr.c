#include <stdio.h>
#include <stdint.h>
#include <string.h>

// Estrutura da MBR (Master Boot Record)
struct MBR {
    uint8_t boot_code[446];
    uint16_t partition_entries[4][2];
    uint8_t signature[2];
};

int main() {
    const char *file_path = "mbr_new.bin";

    // Inicializar a estrutura MBR com zeros
    struct MBR mbr;
    memset(&mbr, 0, sizeof(struct MBR));

    // Assinar a MBR com o valor padrão 0xAA55
    mbr.signature[0] = 0x55;
    mbr.signature[1] = 0xAA;

    FILE *file = fopen(file_path, "wb");
    if (file == NULL) {
        perror("Erro ao criar o arquivo");
        return 1;
    }

    // Escrever a estrutura MBR no arquivo
    fwrite(&mbr, sizeof(struct MBR), 1, file);

    fclose(file);

    printf("Arquivo MBR criado com sucesso: %s\n", file_path);

    return 0;
}

