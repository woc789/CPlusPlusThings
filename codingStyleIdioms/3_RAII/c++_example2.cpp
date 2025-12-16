//
// Created by light on 19-12-12.
//
#include <iostream>
#include <vector>
#include <cstring>
#include <fstream>
#include <bits/unique_ptr.h>

using namespace std;
unique_ptr<vector<string>> read_lines_from_file(string &file_name) {
    unique_ptr<vector<string>> lines(new vector<string>);
    string line;

    ifstream file_handle (file_name.c_str());
    while (file_handle.good() && !file_handle.eof()) {
        getline(file_handle, line);
        lines->push_back(line);
    }

    file_handle.close();

    return lines;
}
int main() {
    // get file name from the first argument
    string file_name ("/home/wang/CPlusPlusThings/CMakeLists.txt");
    int count = read_lines_from_file(file_name).get()->size();

    unique_ptr<vector<string>> file_ptr=read_lines_from_file(file_name);
    vector<string> count1=*file_ptr;
    cout << "File " << file_name << " contains " << count << " lines.";
    cout<<endl;

    for(const string & line :count1){
        cout << line << endl;
    }
    return 0;
}