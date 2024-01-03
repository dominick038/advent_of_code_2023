#include <iostream>
#include <fstream>
#include <string>
#include <vector>


#include <chrono>
using namespace std::chrono;
 

using namespace std;

int main() {

    ifstream file("./input.txt");
    auto start = high_resolution_clock::now();

    if(file.is_open()) {
        vector<pair<int, int>> coords;
        vector<string> storage;
        string line;
        int result = 0;
        int result_part_2 = 0;

        while (getline(file, line))
        {
            storage.push_back(line);
            for(size_t i = 0; i < line.length(); ++i) {
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
            int numbers_found = 0;
            int first_found_num = 0;
            for (int y = -1; y < 2; ++y){
                bool was_last_num_digit = false;
                for (int x = -1; x < 2; ++x){
                    if (x == 0 && y == 0) continue;
                    char c = storage[coord.second + y] [ coord.first + x];
                    
                    if(!c || !isdigit(c)){
                        was_last_num_digit = false;
                        continue;
                    }  
                    if(was_last_num_digit && y) continue;
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
                    
                    numbers_found += 1;
                    
                    if(storage[coord.second] [ coord.first] == '*' && numbers_found == 2){
                        result_part_2 += stoi(res) * first_found_num;
                    }
                    
                    first_found_num = stoi(res);
                    result += stoi(res);
                
                }
            }
        }

        cout << "part 1 result: " << result << endl;
        cout << "part 2 result: " << result_part_2 << endl;

    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "total time taken in microseconds: " << duration.count() << endl;
    
    file.close();
}