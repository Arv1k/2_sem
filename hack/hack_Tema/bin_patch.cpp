#include <cstdio>
#include <cstdlib>

extern "C" void _printui(const char* str, ...);

enum Errors {
    ERROR_NUM_OF_ARGS = 25,
    ERROR_FILE_NAME   = 26,
    ERROR_OUTPUT_FILE = 27,
};


char* Fill_the_Buffer(const char* InputFile, long* num);

void Fill_the_OutputFile(char* Addresses, const char* nameOutput, long num);



int main(int argc, char const* argv[]) {
    if (argc != 4) {
        printf("There isn't any file's name!\n");
        return ERROR_NUM_OF_ARGS;
    }

    long num = 0;
    char* buffer = Fill_the_Buffer(argv[1], &num);

    //buffer[0xb44] = 0x90;
    //buffer[0xb45] = 0x90;
    buffer[0xa72] = 0x75; // stack smashing
    buffer[0xa35] = 0x77; // strlen

    buffer[0xb8d] = 0x75;
    for (int i = 0; i < 20; i++) buffer[0x8a6 + i] = 0x90;
    for (int i = 0; i < 10; i++) buffer[0x972 + i] = 0x90;

    //buffer[0xb2d] = 0x7d;
    //buffer[0x7fd] = 0x7d;
    FILE* text = fopen(argv[3], "wb");
    char str[] = "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%";
    fprintf(text, "%s%c%c%c", str, 0x97, 0x09, 0x40);
    fclose(text);


    Fill_the_OutputFile(buffer, argv[2], num);

    free(buffer);
}



void Fill_the_OutputFile(char* Addresses, const char* nameOutput, long num) {
    FILE* OutputFile = fopen(nameOutput, "wb");
    if (OutputFile == nullptr) {
        printf("OutputFile is not declared in this scope!\n");
        exit(ERROR_OUTPUT_FILE);
    }

    fwrite(Addresses, sizeof(char), num, OutputFile);
}


char* Fill_the_Buffer(const char* InputFile, long* num) {
    FILE* source_file = fopen(InputFile, "rb");
    if (!source_file) {
        printf("Wrong file's name!\n");
        exit(ERROR_FILE_NAME);
    }

    long Position = ftell(source_file);
    fseek(source_file, 0, SEEK_END);

    long NumSymbols = ftell(source_file);

    *num = NumSymbols;

    fseek(source_file, Position, SEEK_SET);

    char* buffer = (char*) calloc(NumSymbols + 1, sizeof(*buffer));

    fread(buffer, sizeof(*buffer), NumSymbols, source_file);

    fclose(source_file);

    return buffer;
}
