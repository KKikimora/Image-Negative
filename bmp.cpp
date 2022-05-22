#include <iostream>
#include <stdio.h>

struct FileHeader {
    short type;
    int sizeOfFile;
    short reserved1;
    short reserved2;
    int offset;
};

struct PictureHeader {
    int biSize;
    int biWidth;
    int biHeight;
    short biPlanes;
    short biBitCount;
    int biCompression;
    int biSizeImage;
    int biXPelsPerMeter;
    int biYPelsPerMeter;
    int biClrUsed;
    int biClrImportant;
};

void readAndPrintHeaders (FileHeader& fileHeader, PictureHeader& pictureHeader, FILE* input)
{
    std::cout << std::endl << "File Header:" << std::endl;

    fread(&fileHeader.type, sizeof(fileHeader.type), 1,  input);
    std::cout << "type: " << std::hex << fileHeader.type << std::endl;

    fread(&fileHeader.sizeOfFile, sizeof(fileHeader.sizeOfFile), 1,  input);
    std::cout << "sizeOfFile: " << std::dec << fileHeader.sizeOfFile << " bajtow" << std::endl;

    fread(&fileHeader.reserved1, sizeof(fileHeader.reserved1), 1,  input);
    std::cout << "reserved1: " << fileHeader.reserved1 << std::endl;

    fread(&fileHeader.reserved2, sizeof(fileHeader.reserved2), 1,  input);
    std::cout << "reserved2: " << fileHeader.reserved2 << std::endl;

    fread(&fileHeader.offset, sizeof(fileHeader.offset), 1,  input);
    std::cout << "offset: " << fileHeader.offset << std::endl;

    fseek(input, 14, SEEK_SET);

    std::cout << std::endl << "Picture Header:" << std::endl;

    fread(&pictureHeader.biSize, sizeof(pictureHeader.biSize), 1,  input);
    std::cout << "sizeOfHeader: " << pictureHeader.biSize << std::endl;
   
    fread(&pictureHeader.biWidth, sizeof(pictureHeader.biWidth), 1,  input);
    std::cout << "width: " << pictureHeader.biWidth << " pks" << std::endl;

    fread(&pictureHeader.biHeight, sizeof(pictureHeader.biHeight), 1,  input);
    std::cout << "height: " << pictureHeader.biHeight << " pks" << std::endl;

    fread(&pictureHeader.biPlanes, sizeof(pictureHeader.biPlanes), 1,  input);
    std::cout << "planes: " << pictureHeader.biPlanes << std::endl;
    
    fread(&pictureHeader.biBitCount, sizeof(pictureHeader.biBitCount), 1,  input);
    std::cout << "bitCount: " << pictureHeader.biBitCount << std::endl;    

    fread(&pictureHeader.biCompression, sizeof(pictureHeader.biCompression), 1,  input);
    std::cout << "compression: " << pictureHeader.biCompression << std::endl;

    fread(&pictureHeader.biSizeImage, sizeof(pictureHeader.biSizeImage), 1,  input);
    std::cout << "sizeImage: " << pictureHeader.biSizeImage << std::endl;

    fread(&pictureHeader.biXPelsPerMeter, sizeof(pictureHeader.biXPelsPerMeter), 1,  input);
    std::cout << "XPelsPerMeter: " << pictureHeader.biXPelsPerMeter << std::endl;

    fread(&pictureHeader.biYPelsPerMeter, sizeof(pictureHeader.biYPelsPerMeter), 1,  input);
    std::cout << "YPelsPerMeter: " << pictureHeader.biYPelsPerMeter << std::endl;

    fread(&pictureHeader.biClrUsed, sizeof(pictureHeader.biClrUsed), 1,  input);
    std::cout << "clrUsed: " << pictureHeader.biClrUsed << std::endl;

    fread(&pictureHeader.biClrImportant, sizeof(pictureHeader.biClrImportant), 1,  input);
    std::cout << "clrImportant: " << pictureHeader.biClrImportant << std::endl;
}

void writeHeadersInFile (FileHeader& fileHeader, PictureHeader& pictureHeader, FILE* output)
{
    fseek(output, 0, SEEK_SET);

    fwrite(&fileHeader.type, sizeof(fileHeader.type), 1,  output);
    fwrite(&fileHeader.sizeOfFile, sizeof(fileHeader.sizeOfFile), 1,  output);
    fwrite(&fileHeader.reserved1, sizeof(fileHeader.reserved1), 1,  output);
    fwrite(&fileHeader.reserved2, sizeof(fileHeader.reserved2), 1,  output);
    fwrite(&fileHeader.offset, sizeof(fileHeader.offset), 1,  output);

    fseek(output, 14, SEEK_SET);

    fwrite(&pictureHeader.biSize, sizeof(pictureHeader.biSize), 1,  output); 
    fwrite(&pictureHeader.biWidth, sizeof(pictureHeader.biWidth), 1,  output);
    fwrite(&pictureHeader.biHeight, sizeof(pictureHeader.biHeight), 1,  output);
    fwrite(&pictureHeader.biPlanes, sizeof(pictureHeader.biPlanes), 1,  output);  
    fwrite(&pictureHeader.biBitCount, sizeof(pictureHeader.biBitCount), 1,  output);
    fwrite(&pictureHeader.biCompression, sizeof(pictureHeader.biCompression), 1,  output);
    fwrite(&pictureHeader.biSizeImage, sizeof(pictureHeader.biSizeImage), 1,  output);
    fwrite(&pictureHeader.biXPelsPerMeter, sizeof(pictureHeader.biXPelsPerMeter), 1,  output);
    fwrite(&pictureHeader.biYPelsPerMeter, sizeof(pictureHeader.biYPelsPerMeter), 1,  output);
    fwrite(&pictureHeader.biClrUsed, sizeof(pictureHeader.biClrUsed), 1,  output);
    fwrite(&pictureHeader.biClrImportant, sizeof(pictureHeader.biClrImportant), 1,  output);
}

void createNegativeImage (FILE* input, FILE* output, const FileHeader& fileHeader)
{
    int bitColor;

    for (int i = fileHeader.offset; i < fileHeader.sizeOfFile; ++i)
    {
        fseek(input, i, SEEK_SET);
        fseek(output, i, SEEK_SET);

        fread(&bitColor, 3, 1, input);
        bitColor = INT_MAX - bitColor;
        fwrite(&bitColor, 3, 1, output);
    }

    std::cout << std::endl << "Negative Image was created" << std::endl;
}

int main (int arc, char * argv[])
{
    const char* fileInputName = argv[1];

    FILE *input = fopen(fileInputName, "r");

    if(input == nullptr)
    {
        std::cout << "Error of read " << fileInputName << " file" << std::endl;
        return 1;
    }
    else
    {
         std::cout << "File " << fileInputName << " was open" << std::endl;
    }

    FileHeader fileHeader{};
    PictureHeader pictureHeader{};

    readAndPrintHeaders(fileHeader, pictureHeader, input);

    FILE *output = fopen("image_nagative.bmp", "wb");
    
    if(output == nullptr)
    {
        std::cout << std::endl << "Error of write image_nagative.bmp file" << std::endl;
        return 1;
    }
    else
    {
         std::cout << std::endl << "File image_nagative.bmp was open" << std::endl;
    }

    writeHeadersInFile(fileHeader, pictureHeader, output);
   
    createNegativeImage(input, output, fileHeader);

    fclose(output);
    fclose(input);

    return 0;
}
