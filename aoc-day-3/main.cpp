#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main() {

    ifstream file("./input.txt");


    if(file.is_open()) {
        vector<pair<int, int>> coords;
        vector<string> storage;
        string line;
        int result = 0;

        while (getline(file, line))
        {
            storage.push_back(line);
            for(size_t i = 0; i < line.length() + 1; ++i) {
                pair<int, int> input_coords;
                char c = line[i];

                if(c == '.' || !c) continue;
                if(!isdigit(c)){

                    input_coords.first = i;
                    input_coords.second = storage.size() - 1;

                    coords.push_back(input_coords);
                }
            }
        }


        
        for(pair<int, int> coord : coords){
            //cout << storage[coord.second][coord.first];
            cout << "Char: " << storage[coord.second][coord.first] << endl;
            for (int y = -1; y < 2; ++y){
                bool was_last_num_digit = false;
                for (int x = -1; x < 2; ++x){
                    if (x == 0 && y == 0) continue;
                    char c = storage[coord.second + y] [ coord.first + x];
                    
                    if(!c || !isdigit(c) || was_last_num_digit){
                        was_last_num_digit = false;
                        continue;
                    }  
                    was_last_num_digit = true;

                    bool find_num = true;
                    int l_point = -1;
                    int r_point = 1;
                    string res;
                    res = c;
                    while(find_num) {
                        if(isdigit(storage[coord.second + y] [ coord.first + x + l_point])){
                            res = storage[coord.second + y] [ coord.first + x + l_point] + res;
                            l_point--;
                        } 
                        else if (isdigit(storage[coord.second + y] [ coord.first + x + r_point])) {
                            res = res + storage[coord.second + y] [ coord.first + x + r_point] ;
                            r_point++;
                        } else {
                            find_num = false;
                        }
                    }
                    
                   
                    cout << stoi(res) << endl;
                    result += stoi(res);
                
                }
            }
            cout << endl;
        }

        cout << result;
    
    }

    file.close();
}