#include <iostream>
#include <fstream>
#include "../include/traces.h"

int main()
{
    std::string dh_file_path = "../dh_params/kr10.json";
    std::ifstream ifs(dh_file_path.c_str(), std::ios_base::binary);
    std::string content((std::istreambuf_iterator<char>(ifs)),
                        (std::istreambuf_iterator<char>()));
    info_msg("content: ", content);

    return 0;
}