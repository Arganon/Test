#include <string>
#include <fstream>
#include <io.h>
#include <regex>
#include <iostream>

class MoveFile {
    private:
        std::string filename;
        std::string source;
        std::string destination;
        int count;

    public:
        MoveFile(std::string filename, std::string source, std::string destination) {
            this->filename = filename;
            this->source = source;
            this->destination = destination;
            this->count = 0;
        }

        ~MoveFile() {}

        void change_source() {
            if (this->source[this->source.size()-1] != '\\' || this->source[this->source.size()-1] != '/') {
                this->source.append("/");
            }
            this->source.append(this->filename);
        }

        void change_destination() {
            if (this->destination[this->destination.size()-1] != '\\' || this->destination[this->destination.size()-1] != '/') {
                this->destination.append("/");
            }
            this->destination.append(filename);
        }

        bool is_source_folder_empty() {
            if (access(source.c_str(), 0)) {
                return true;
            }
            return false;
        }

        bool is_dest_has_same_file() {
            if(!access(destination.c_str(), 0)) {
                return true;
            }
            return false;
        }

        void start_copy() {
            std::ifstream out(this->source, std::fstream::binary);
            std::ofstream in(this->destination, std::fstream::binary);
            in << out.rdbuf();
            out.close();
            in.close();
        }

        void delete_source_file() {
            try {
                remove(this->source.c_str());
            }
            catch(...) {
                exit(1);
            }
        }

        void change_dest_path() {
            // this expression find a number between brackets
            std::regex ex1("(\\d+(?=\\)\\.\\w+))");
            
            std::smatch search;
            
            // if destination path contain brackets with num we will increase this num
            if (std::regex_search(this->destination, search, ex1)) {
                this->count++;
                std::string num_in_brakets = std::to_string(this->count);
                this->destination.assign(std::regex_replace(this->destination, ex1, num_in_brakets));
             } 
            
            // if not - we will add num with brackets
            else {
                std::regex ex2("(^[\\s\\S]+)+(?=\\.)");
                std::string result = std::regex_replace(this->destination, ex2, "");
                std::string temp = "(1)";
                temp.append(result);
                std::regex ex3("(\\.)+(\\w)+$");
                this->destination.assign(std::regex_replace(this->destination, ex3, temp));
            }
        }

        void build_process() {
            change_source();
            change_destination();
            if (is_source_folder_empty()) {
                exit(1);
            }
            while (is_dest_has_same_file()) {
                change_dest_path();
            }
            start_copy();
            delete_source_file();
        }
};

int main(int argc, char* argv[]) {
    std::string file_name;
    std::string source;
    std::string destination;
    const bool areFewParams = (argc < 3);
    if (areFewParams) {
        std::cout << "Please, add file name, sorce path and destination path.\n";
        std::cin >> file_name;
        std::cin >> source;
        std::cin >> destination;
    } else {
        file_name = argv[1];
        source = argv[2];
        destination = argv[3];
    }

    MoveFile f(file_name, source, destination);
    f.build_process();

    return 0;
}
