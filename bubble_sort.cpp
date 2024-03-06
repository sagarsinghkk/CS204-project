#include <bits/stdc++.h>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;
vector<string>hold;
void splitString(string str){
              string inputString = str;
    for (int i = 0; i < inputString.size(); i++) {
        if(inputString[i]==','){
          inputString.replace(i, 1," ");
        }
    }
  std::istringstream iss(inputString);
  //std::vector<std::string> tokens;
  std::string token;

  while (iss >> token) {
      hold.push_back(token);
  }
  //return tokens;
}
void write(string str){
  
    // File name
    std::string fileName = "output.mc";

    // Open the file for writing
    ofstream outputFile;
     outputFile.open("output.mc", std::ios::app); 

    // Check if the file is opened successfully
    if (!outputFile.is_open()) {
        std::cerr << "Error opening file: " << fileName << std::endl;
        cout<<"error"; // Exit with an error code
    }

    // Data to write to the file
    std::string dataToWrite = str;

    // Write the data to the file
    outputFile << dataToWrite << std::endl;

    // Close the file
    outputFile.close();



}
string opcode(string a){
    if(a=="addi" || a=="andi" || a=="ori"){
            return "0010011";
    }
    else if(a=="lb" || a=="ld" || a=="lw" || a=="lh"){
            return "0000011";
    }
    else if(a=="jalr"){
            return "1100111";
    }
    return "error";
}

string funct3(string a){
    if(a=="lb" || a=="jalr" || a=="addi"){
        return "000";
    }
    else if(a=="lh"){
        return "001";
    }
    else if(a=="lw"){
        return "010";
    }
    else if(a=="ld"){
        return "011";
    }
    else if(a=="ori"){
        return "110";
    }
    else if(a=="andi"){
        return "111";
    }
    return "error";
}

string register_num(string a){
    string reg_string;
    for(int i=1;i<a.size();i++){
        reg_string+= a[i];
    }
    int reg_no= stoi(reg_string);
    if(reg_no>=0 && reg_no<32){
        string ans;
        for(int i=0;i<5;i++){
            ans+= ('0'+reg_no%2);
            reg_no/=2;
        }
        reverse(ans.begin(),ans.end());
        return ans;
    }
    return "error";
}

string immediate(string a){
    int imm= stoi(a);
    if(imm<0){
        imm = 4096 +imm;
    }
    if(imm>=0 && imm<4096){
        string ans;
        for(int i=0;i<12;i++){
            ans+=('0' + imm%2);
            imm/=2;
        }
        reverse(ans.begin(),ans.end());
        return ans;
    }
    return "error";
}

string I_format(string operation,string rd,string rs1, string imm){
    string ans="0x";
    ans+=immediate(imm);
    ans+=register_num(rs1);
    ans+=funct3(operation);
    ans+=register_num(rd);
    ans+=opcode(operation);
    return ans;
}
int main() {
   std::string fileName = "example.asm";

   // Open the file
   std::ifstream inputFile(fileName);

   // Check if the file is opened successfully
   if (!inputFile.is_open()) {
       std::cerr << "Error opening file: " << fileName << std::endl;
       return 1; // Exit with an error code
   }

   // Read and print the contents of the file
  int i=0;
   std::string line;
   while (std::getline(inputFile, line)) {
       splitString(line);
       
       string I1=I_format(hold[4*i],hold[4*i+1],hold[4*i+2],hold[4*i+3]);
   write(I1);
 i++;
       
   }
   inputFile.close();
    return 0;
}
