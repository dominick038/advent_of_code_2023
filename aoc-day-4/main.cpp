#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

string trim(const string& s) { // removes whitespace characters from beginnig and end of string s
    const int l = (int)s.length();
    int a=0, b=l-1;
    char c;
    while(a<l && ((c=s[a])==' '||c=='\t'||c=='\n'||c=='\v'||c=='\f'||c=='\r'||c=='\0')) a++;
    while(b>a && ((c=s[b])==' '||c=='\t'||c=='\n'||c=='\v'||c=='\f'||c=='\r'||c=='\0')) b--;
    return s.substr(a, 1+b-a);
}


int main(){
    ifstream file("./input.txt");
    if(file.is_open()) {

        unordered_map<int, int> scratch_card_index;
        string line;
        int result = 0;
        
        int index = 0;
        while (getline(file, line))
        {
            index++;
            
            int my_values[10];
            int winning_values[25];
            line = line.substr(9);
            
            
            int split_pos = line.find('|');
            string my_values_string = line.substr(1, split_pos - 1);
            string winning_values_string = line.substr(split_pos + 1, line.size() + 1);

            string num;
            for(size_t i = 0; i <= 24; i++) {
                if(i <= 9){
                    num = trim(my_values_string.substr(0,3));
                    my_values_string = my_values_string.substr(3);
                    my_values[i] = stoi(num);
                }
                num = trim(winning_values_string.substr(0,3));
                winning_values_string = winning_values_string.substr(3);
                winning_values[i] = stoi(num);
            }
            
            int match_value = 0;
            int amount_of_matches = 0;
            for (size_t i = 0; i <= 24; i++){
                for(size_t j = 0; j <= 9; j++) {
                    if(winning_values[i] == my_values[j]){
                        if(!match_value) match_value = 1;
                        else match_value += match_value;

                        amount_of_matches++;
                    }
                }
            }
            
            int amount_of_scratchcards = scratch_card_index[index] + 1;
            for (size_t i = 1; i <= amount_of_matches; i++)
            { 
                scratch_card_index[index + i] += amount_of_scratchcards;
            }
            result += match_value;
        }


        for(pair<int, int> copies: scratch_card_index){
            index += copies.second;
        }
        cout << "Your scratch card score: " << result << endl;
        cout << "Your total amount of copies is: " << index;
    }
}