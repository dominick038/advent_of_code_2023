#include <iostream>
#include <fstream>
#include <string>
#include <vector>

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

        string line;
        int result = 0;
        
        while (getline(file, line))
        {
            int my_values[10];
            int winning_values[25];
            line = line.substr(9);
            
            
            int split_pos = line.find('|');
            string my_values_string = line.substr(1, split_pos - 1);
            string winning_values_string = line.substr(split_pos + 1, line.size() + 1);

            string num;
            for(int i = 0; i <= 24; i++) {
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
            for (int i = 0; i <= 24; i++){
                for(int j = 0; j <= 9; j++) {
                    if(winning_values[i] == my_values[j]){
                        if(!match_value) match_value = 1;
                        else match_value += match_value;
                    }
                }
            }
            result += match_value;
        }
        cout << "Your scratch card score: " << result;
    }
}