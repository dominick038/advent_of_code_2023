#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

int main() {
    const std::unordered_map<std::string, int> string_lookup = {
        {"one", 1},
        {"two", 2},
        {"three", 3},
        {"four", 4},
        {"five", 5},
        {"six", 6},
        {"seven", 7},
        {"eight", 8},
        {"nine", 9}
    };
    
    std::ifstream file("./input.txt");
    
    

    if (file.is_open()) {
        std::string line;
        int first_num;
        int last_num;
        int result = 0; 
        char c;
        std::pair<int, int> pos_of_entry;
        std::pair<int, int> pos_value;

        while (std::getline(file, line)) {
            first_num = 0;
            last_num = 0;
            pos_of_entry = {-1,-1};
            pos_value = {0,0};

            for (const auto& entry : string_lookup) { 
                const std::string& substring = entry.first;
                int position = line.find(substring);
                int last_pos = line.rfind(substring);
                if (position != std::string::npos) {
                    if (pos_of_entry.first == -1 || position < pos_of_entry.first) {
                        pos_of_entry.first = position;
                        pos_value.first = entry.second;
                    }
                    if (pos_of_entry.second == -1 || last_pos > pos_of_entry.second) {
                        pos_of_entry.second = last_pos;
                        pos_value.second = entry.second;
                    }
                }
            }
            for (size_t i = 0; i < line.length() + 1; ++i) { 
                c = line[i];  
                if(std::isdigit(c)){
                    if(!first_num){
                        if(i < pos_of_entry.first || pos_of_entry.first == -1){
                            first_num = c - '0';
                        } else {
                            first_num = pos_value.first;
                        }
                    } 
        
                    if( i > pos_of_entry.second || pos_of_entry.second == -1){
                        last_num = c - '0';
                    } else {
                        last_num = pos_value.second;
                    }
                }
            }
            if (!last_num && pos_of_entry.second != -1) {
                last_num = pos_value.second;
            }
            if(!last_num){
                result += (first_num*10) + first_num; 
            } else {
                result += (first_num*10) + last_num;   
            }  

            
        }
        std::cout << result;
        file.close();
    }
    
    return 1;
}