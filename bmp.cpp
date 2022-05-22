#include <iostream>
#include <stdio.h>

struct FileHeader {
    short type;
    int sizeOfFile;
    short reserved1;
    short reserved2;
    int dataOffset;
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

struct RGB
{
    char R;
    char G;
    char B;
};

int main (int arc, char * argv[])
{
    const char* fileInputName = argv[1];

    FILE *input = fopen(fileInputName, "r");

    if(input == nullptr)
    {
        std::cout << "Error of read " << fileInputName << " file" << std::endl;
    }
    else
    {
         std::cout << "File " << fileInputName << " was open" << std::endl;
    }

    FileHeader fileHeader{};
    
    std::cout << std::endl << "File Header:" << std::endl;

    fread(&fileHeader.type, sizeof(fileHeader.type), 1,  input);
    std::cout << "type: " << std::hex << fileHeader.type << std::endl;

    fread(&fileHeader.sizeOfFile, sizeof(fileHeader.sizeOfFile), 1,  input);
    std::cout << "sizeOfFile: " << std::dec << fileHeader.sizeOfFile << " bajtow" << std::endl;

    fread(&fileHeader.reserved1, sizeof(fileHeader.reserved1), 1,  input);
    std::cout << "reserved1: " << fileHeader.reserved1 << std::endl;

    fread(&fileHeader.reserved2, sizeof(fileHeader.reserved2), 1,  input);
    std::cout << "reserved2: " << fileHeader.reserved2 << std::endl;

    fread(&fileHeader.dataOffset, sizeof(fileHeader.dataOffset), 1,  input);
    std::cout << "dataOffset: " << fileHeader.dataOffset << std::endl;

    PictureHeader pictureHeader{};

    std::cout << std::endl << "Picture Header:" << std::endl;

    fread(&pictureHeader.biSize, sizeof(pictureHeader.biSize), 1,  input);
    std::cout << "biSize: " << pictureHeader.biSize << std::endl;
   
    fread(&pictureHeader.biWidth, sizeof(pictureHeader.biWidth), 1,  input);
    std::cout << "biWidth: " << pictureHeader.biWidth << " pks" << std::endl;

    fread(&pictureHeader.biHeight, sizeof(pictureHeader.biHeight), 1,  input);
    std::cout << "biHeight: " << pictureHeader.biHeight << " pks" << std::endl;

    fread(&pictureHeader.biPlanes, sizeof(pictureHeader.biPlanes), 1,  input);
    std::cout << "biPlanes: " << pictureHeader.biPlanes << std::endl;
    
    fread(&pictureHeader.biBitCount, sizeof(pictureHeader.biBitCount), 1,  input);
    std::cout << "biBitCount: " << pictureHeader.biBitCount << std::endl;    

    fread(&pictureHeader.biCompression, sizeof(pictureHeader.biCompression), 1,  input);
    std::cout << "biCompression: " << pictureHeader.biCompression << std::endl;

    fread(&pictureHeader.biSizeImage, sizeof(pictureHeader.biSizeImage), 1,  input);
    std::cout << "biSizeImage: " << pictureHeader.biSizeImage << std::endl;

    fread(&pictureHeader.biXPelsPerMeter, sizeof(pictureHeader.biXPelsPerMeter), 1,  input);
    std::cout << "biXPelsPerMeter: " << pictureHeader.biXPelsPerMeter << std::endl;

    fread(&pictureHeader.biYPelsPerMeter, sizeof(pictureHeader.biYPelsPerMeter), 1,  input);
    std::cout << "biYPelsPerMeter: " << pictureHeader.biYPelsPerMeter << std::endl;

    fread(&pictureHeader.biClrUsed, sizeof(pictureHeader.biClrUsed), 1,  input);
    std::cout << "biClrUsed: " << pictureHeader.biClrUsed << std::endl;

    fread(&pictureHeader.biClrImportant, sizeof(pictureHeader.biClrImportant), 1,  input);
    std::cout << "biClrImportant: " << pictureHeader.biClrImportant << std::endl;

    FILE *output = fopen("image_nagative.bmp", "bw");
    
    if(output == nullptr)
    {
        std::cout << "Error of write image_nagative.bmp file" << std::endl;
    }
    else
    {
         std::cout << "File image_nagative.bmp was open" << std::endl;
    }

    fwrite(&fileHeader.type, sizeof(fileHeader.type), 1,  output);
    fwrite(&fileHeader.sizeOfFile, sizeof(fileHeader.sizeOfFile), 1,  output);
    fwrite(&fileHeader.reserved1, sizeof(fileHeader.reserved1), 1,  output);
    fwrite(&fileHeader.reserved2, sizeof(fileHeader.reserved2), 1,  output);
    fwrite(&fileHeader.dataOffset, sizeof(fileHeader.dataOffset), 1,  output);

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
        
    fclose(input);

    return 0;
}
