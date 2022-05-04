#include "image.h"

#include <fstream>

namespace {

const size_t BYTES_BEFORE_IMG_SHAPE = 18;
const size_t BYTES_BEFORE_PIXEL_ARRAY = 28;
const size_t MAX_VALUE = 255;
const size_t FILE_HEADER_SIZE = 14;
const size_t INFO_HEADER_SIZE = 40;

void WriteByte(std::ofstream& output, uint8_t byte) {
    output.write(reinterpret_cast<char*>(&byte), 1);
}

void WriteNBytes(std::ofstream& output, uint8_t* bytes, size_t n) {
    output.write(reinterpret_cast<char*>(bytes), n);
}

uint8_t ReadByte(std::ifstream& input_file) {
    uint8_t byte;
    input_file.read(reinterpret_cast<char*>(&byte), 1);

    return byte;
}

uint32_t ReadInt(std::ifstream& input_file) {
    auto a = ReadByte(input_file);
    auto b = ReadByte(input_file);
    auto c = ReadByte(input_file);
    auto d = ReadByte(input_file);

    return a + (b << 8) + (c << 16) + (d << 24);
}

void WriteInt(uint8_t* array, size_t from, int n) {
    array[from++] = n;
    array[from++] = n >> 8;
    array[from++] = n >> 16;
    array[from] = n >> 24;
}

Color ReadColor(std::ifstream& input_file) {
    Color c;
    c.blue = ReadByte(input_file) * 1.0 / MAX_VALUE;
    c.green = ReadByte(input_file) * 1.0 / MAX_VALUE;
    c.red = ReadByte(input_file) * 1.0 / MAX_VALUE;

    return c;
}

void SkipNBytes(std::ifstream& input_file, size_t n) {
    for (size_t i = 0; i < n; ++i) {
        ReadByte(input_file);
    }
}

size_t CalcPadding(size_t width) {
    size_t padd = 0;

    for (size_t i = 0; i < 4; ++i) {
        if ((width * 3 + i) % 4 == 0) {
            padd = i;
            break;
        }
    }

    return padd;
}

void WriteNZeroBytes(std::ofstream& output, size_t n) {
    for (size_t i = 0; i < n; ++i) {
        WriteByte(output, 0);
    }
}

void WriteColor(std::ofstream& output, const Color& c) {
    WriteByte(output, static_cast<uint8_t>(c.blue * 255));
    WriteByte(output, static_cast<uint8_t>(c.green * 255));
    WriteByte(output, static_cast<uint8_t>(c.red * 255));
}

void MakeFileHeader(uint8_t* file_header, int filesize) {
    file_header[0] = 'B';
    file_header[1] = 'M';

    WriteInt(file_header, 2, filesize);

    for (int i = 6; i < 14; ++i) {
        file_header[i] = 0;
    }

    file_header[10] = FILE_HEADER_SIZE + INFO_HEADER_SIZE;
}

void MakeInfoHeader(uint8_t* information_header, size_t width, size_t height) {
    for (int i = 0; i < 40; ++i) {
        information_header[i] = 0;
    }

    information_header[0] = INFO_HEADER_SIZE;

    WriteInt(information_header, 4, width);

    WriteInt(information_header, 8, height);

    information_header[12] = 1;

    information_header[14] = 24;
}

}  // namespace

Image::Image(size_t width, size_t height) : width_(width), height_(height), img_(std::vector<Color>(width * height)) {
}

Image::Image(const std::string& img_path) {
    std::ifstream input_file(img_path, std::ios::binary);

    SkipNBytes(input_file, BYTES_BEFORE_IMG_SHAPE);

    width_ = ReadInt(input_file);
    height_ = ReadInt(input_file);

    SkipNBytes(input_file, BYTES_BEFORE_PIXEL_ARRAY);

    img_ = std::vector<Color>(width_ * height_);
    size_t padding = CalcPadding(width_);

    for (size_t y = 0; y < height_; ++y) {
        for (size_t x = 0; x < width_; ++x) {
            img_[(height_ - y - 1) * width_ + x] = ReadColor(input_file);
        }

        SkipNBytes(input_file, padding);
    }
}

Image::Image(const Image& img, size_t width, size_t height) : width_(width), height_(height) {
    img_ = std::vector<Color>(width_ * height_);

    for (size_t y = 0; y < height_; ++y) {
        for (size_t x = 0; x < width_; ++x) {
            img_[y * width_ + x] = img.GetColor(x, y);
        }
    }
}

void Image::Save(const std::string& saving_path) {
    std::ofstream output_file(saving_path, std::ios::binary);

    size_t padding = CalcPadding(width_);

    int filesize = FILE_HEADER_SIZE + INFO_HEADER_SIZE + width_ * height_ * 3 + padding * height_;

    uint8_t file_header[FILE_HEADER_SIZE];
    MakeFileHeader(file_header, filesize);

    uint8_t information_header[INFO_HEADER_SIZE];
    MakeInfoHeader(information_header, width_, height_);

    WriteNBytes(output_file, file_header, FILE_HEADER_SIZE);
    WriteNBytes(output_file, information_header, INFO_HEADER_SIZE);

    for (size_t y = 0; y < height_; ++y) {
        for (size_t x = 0; x < width_; ++x) {
            auto c = this->GetColor(x, height_ - y - 1);
            WriteColor(output_file, c);
        }

        WriteNZeroBytes(output_file, padding);
    }
}

Color Image::GetColor(size_t x, size_t y) const {
    return img_[y * width_ + x];
}

void Image::SetColor(const Color& color, size_t x, size_t y) {
    img_[y * width_ + x] = color;
}

size_t Image::GetWidth() const {
    return width_;
}

size_t Image::GetHeight() const {
    return height_;
}
