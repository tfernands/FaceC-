#include <iostream>
#include <fstream> // std::ifstream
// #include <iomanip> // std::setw
#include <map>
#include "include/json.hpp" // download here (https://github.com/nlohmann/json/releases) the (most recent file) "json.hpp"

using json = nlohmann::json;
using std::cout;
using std::endl;
using std::map;

// map<key, value> predict(vname, model, anchors, size, outname='out.avi'){

// }

int main(int argc, char* argv[]){
	const char* json_file_name = argv[1];
	std::ifstream my_file(json_file_name);
	// my_file.open(json_file_name, std::ios::in); // json args; // args << my_file;
	if (!(my_file.is_open())){
		std::cerr<<"Arquivo json nao encontrado"<<endl;
    return 1;
	}

	json args = json::parse(my_file); // cout<<std::setw(4) <<args<<endl;
	// cout<<args["input_shape"]<<endl; // args["input_shape"] returns [56,56]
	// h, w = args["input_shape"];

  /*#######################################################
	  FALTA DESALOCAR MEMÓRIA DOS PONTEIROS E VARIÁVEIS DINÂMICAS
  	####################################################### */

	my_file.close();
	return 0;
}