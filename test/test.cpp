#include <iostream>
#include <fstream>

//using namespace std;

int main()
{
    std::string dh_file_path = "../dh_params/test.json";
    std::ifstream ifs(dh_file_path.c_str(), std::ios_base::binary);
    std::string content((std::istreambuf_iterator<char>(ifs)),
                        (std::istreambuf_iterator<char>()));
    std::cout << "content: " << content << std::endl;

    return 0;
}