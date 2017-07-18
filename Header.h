#include<iostream>
using namespace std;
#include<fstream>
#include<sstream>
string readFile(string filename){
	ifstream kyfile;
	stringstream file;
	kyfile.open(filename);
	file<<kyfile.rdbuf();
	kyfile.close();
	string str = file.str();
	return str;

}
void writeFile(string data){
	ofstream kyfile;
	kyfile.open("");
	kyfile << data << endl;
	kyfile.close();
}