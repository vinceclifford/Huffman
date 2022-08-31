
#ifndef GRA_WRITE_INFORMATION_H
#define GRA_WRITE_INFORMATION_H

struct write_information {
    unsigned char current_byte;
    unsigned char* write_buffer;
    unsigned short byte_pos;
    unsigned long write_counter;
    unsigned long total_size;
};

#endif //GRA_WRITE_INFORMATION_H
