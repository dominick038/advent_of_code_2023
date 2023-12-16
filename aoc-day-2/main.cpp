#include <iostream>
#include <fstream>    
#include <string>
#include <unordered_map>
#include <vector>
#include <sstream>



std::vector<std::string> split(const std::string& s, char delimiter) {
    std::vector<std::string> tokens;
    std::istringstream tokenStream(s);
    std::string token;
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

int main(){
    std::unordered_map<std::string, int> max_values {
        {"red", 12},
        {"green", 13},
        {"blue", 14}
    };
    int result = 0;
    std::ifstream file("./input.txt");
    
    if (file.is_open()) {
        std::string line;
        while(std::getline(file, line)){
            // Find the game id of each line
            size_t gamePos = line.find("Game");
            size_t colonPos = line.find(":", gamePos);
            std::string gameID = line.substr(gamePos + 5, colonPos - gamePos - 5);
            line = line.substr(colonPos + 1);
            
            // Get all of the  game values into a vector
            char delimiter = ';';
            std::vector<std::string> tokens = split(line, delimiter);
            std::vector<std::string> game_values;
            
            for(std::string &str: tokens){
                std::vector<std::string> tem_val = split(str, ',');
                game_values.insert(game_values.end(), tem_val.begin(), tem_val.end());
            }

            bool isvalid = true;
            for(std::string &str : game_values) {
                if(!isvalid) break;
                std::istringstream iss(str);
                while (std::getline(iss, line)) {
                    std::istringstream line_stream(line);
                    int number;
                    std::string color;
                    if (line_stream >> number >> color) {
                        if(number <= 12) continue;
                        if(number > max_values[color]) {
                            isvalid = false;
                            break;
                        }
                    }
                }
            }
            if(isvalid) 
                result += stoi(gameID);
            
        }   
    }
    std::cout << result;
    
    file.close();
}
