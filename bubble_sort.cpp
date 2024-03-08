#include <bits/stdc++.h>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;
vector<string> hold;
bool error = false;
int pc = 0;

void splitString(string str)
{
  string inputString = str;
  for (int i = 0; i < inputString.size(); i++)
  {
    if (inputString[i] == ',')
    {
      inputString.replace(i, 1, " ");
    }
  }
  std::istringstream iss(inputString);
  // std::vector<std::string> tokens;
  std::string token;

  while (iss >> token)
  {
    hold.push_back(token);
  }
  // return tokens;
}
void write(string str)
{

  // File name
  std::string fileName = "output.mc";

  // Open the file for writing
  ofstream outputFile;
  outputFile.open("output.mc", std::ios::app);

  // Check if the file is opened successfully
  if (!outputFile.is_open())
  {
    std::cerr << "Error opening file: " << fileName << std::endl;
    cout << "error"; // Exit with an error code
  }

  // Data to write to the file
  std::string dataToWrite = str;

  // Write the data to the file
  outputFile << dataToWrite << std::endl;

  // Close the file
  outputFile.close();
}
string opcode(string a)
{
  if (a == "R")
  {
    return "0110011";
  }
  else if (a == "S")
  {
    return "0100011";
  }
  else if (a == "addi" || a == "andi" || a == "ori")
  {
    return "0010011";
  }
  else if (a == "lb" || a == "ld" || a == "lw" || a == "lh")
  {
    return "0000011";
  }
  else if (a == "jalr")
  {
    return "1100111";
  }
  else if (a == "auipc")
  {
    return "0010111";
  }
  else if (a == "lui")
  {
    return "0110111";
  }
  else if (a == "beq" || a == "bne" || a == "bge" || a == "blt")
  {
    return "1100011";
  }
  else if (a == "jal")
  {
    return "1101111";
  }
  error = true;
  return "";
}

string funct3(string a)
{
  if (a == "lb" || a == "jalr" || a == "addi")
  {
    return "000";
  }
  else if (a == "lh")
  {
    return "001";
  }
  else if (a == "lw")
  {
    return "010";
  }
  else if (a == "ld")
  {
    return "011";
  }
  else if (a == "ori")
  {
    return "110";
  }
  else if (a == "andi")
  {
    return "111";
  }
  return "error";
}

string register_num(string a)
{
  string reg_string;
  for (int i = 1; i < a.size(); i++)
  {
    reg_string += a[i];
  }
  int reg_no = stoi(reg_string);
  if (reg_no >= 0 && reg_no < 32)
  {
    string ans;
    for (int i = 0; i < 5; i++)
    {
      ans += ('0' + reg_no % 2);
      reg_no /= 2;
    }
    reverse(ans.begin(), ans.end());
    return ans;
  }
  return "error";
}

string immediate(string a)
{
  int imm = stoi(a);
  if (imm < 0)
  {
    imm = 4096 + imm;
  }
  if (imm >= 0 && imm < 4096)
  {
    string ans;
    for (int i = 0; i < 12; i++)
    {
      ans += ('0' + imm % 2);
      imm /= 2;
    }
    reverse(ans.begin(), ans.end());
    return ans;
  }
  return "error";
}
string immediate_U(string a)
{
  int imm = stoi(a);
  if (imm >= 0 && imm < 1048576)
  {
    string ans;
    for (int i = 0; i < 20; i++)
    {
      ans += ('0' + imm % 2);
      imm /= 2;
    }
    reverse(ans.begin(), ans.end());
    return ans;
  }
  error = true;
  return "";
}

string I_format(string hold[4 * i], string rd, string rs1, string imm)
{
  string ans = "0x";
  ans += immediate(imm);
  ans += register_num(rs1);
  ans += funct3(hold[4 * i]);
  ans += register_num(rd);
  ans += opcode(hold[4 * i]);
  return ans;
}
string convert_to_hex(string a)
{
  bitset<32> b(a);
  unsigned long int x = b.to_ulong();
  stringstream ss;
  ss << hex << x;
  string hexString = ss.str();
  return hexString;
}
string func3(string a)
{
  if (a == "add" || a == "sub" || a == "mul" || a == "sb")
  {
    return "000";
  }
  else if (a == "xor" || a == "div")
  {
    return "100";
  }
  else if (a == "srl")
  {
    return "101";
  }
  else if (a == "sra")
  {
    return "101";
  }
  else if (a == "sll" || a == "sh")
  {
    return "001";
  }
  else if (a == "slt" || a == "sw")
  {
    return "010";
  }
  else if (a == "or" || a == "rem")
  {
    return "110";
  }
  else if (a == "and")
  {
    return "111";
  }
  else if (a == "sd")
  {
    return "011";
  }
  else if (a == "lb" || a == "jalr" || a == "addi")
  {
    return "000";
  }
  else if (a == "lh")
  {
    return "001";
  }
  else if (a == "lw")
  {
    return "010";
  }
  else if (a == "ld")
  {
    return "011";
  }
  else if (a == "ori")
  {
    return "110";
  }
  else if (a == "andi")
  {
    return "111";
  }
  else if (a == "beq")
  {
    return "000";
  }
  else if (a == "bne")
  {
    return "001";
  }
  else if (a == "blt")
  {
    return "100";
  }
  else if (a == "bge")
  {
    return "101";
  }
  error = true;
  return "";
}
string func7(string a)
{
  if (a == "add" || a == "sll" || a == "slt" || a == "xor" || a == "srl" || a == "or" || a == "and")
  {
    return "0000000";
  }
  else if (a == "mul" || a == "div" || a == "rem")
  {
    return "0000001";
  }
  else if (a == "sub" || a == "sra")
  {
    return "0100000";
  }
  error = true;
  return "";
}
string S_format(string operation, string rs2, string rs1, string imm)
{

  string ans = "";
  imm = immediate(imm);
  string imm1 = imm.substr(5), imm2 = imm.substr(0, 5);
  reverse(imm1.begin(), imm1.end());
  reverse(imm2.begin(), imm2.end());
  ans += imm1;
  ans += register_num(rs2);
  ans += register_num(rs1);
  ans += func3(operation);
  ans += imm2;
  ans += opcode("S");
  if (error)
  {
    return "";
  }
  ans = convert_to_hex(ans);
  ans = "0x" + ans;
  return ans;
}
int main()
{
  std::string fileName = "example.asm";

  // Open the file
  std::ifstream inputFile(fileName);

  // Check if the file is opened successfully
  if (!inputFile.is_open())
  {
    std::cerr << "Error opening file: " << fileName << std::endl;
    return 1; // Exit with an error code
  }

  // Read and print the contents of the file
  int i = 0;
  std::string line;
  string ans;
  while (std::getline(inputFile, line))
  {
    splitString(line);

    if (hold[4 * i] == "addi" || hold[4 * i] == "andi" || hold[4 * i] == "ori" || hold[4 * i] == "lb" || hold[4 * i] == "ld" || hold[4 * i] == "lh" || hold[4 * i] == "lw" || hold[4 * i] == "jalr")
    {
      ans = I_format(hold[4 * i], hold[4 * i + 1], hold[4 * i + 2], hold[4 * i + 3]);
    }
    else if (hold[4 * i] == "sb" || hold[4 * i] == "sw" || hold[4 * i] == "sd" || hold[4 * i] == "sh")
    {

      ans = S_format(hold[4 * i], hold[4 * i + 1], hold[4 * i + 2], hold[4 * i + 3]);
    }
    else if (hold[4 * i] == "bne" || hold[4 * i] == "beq" || hold[4 * i] == "blt" || hold[4 * i] == "bge")
    {

      ans = SB_format(hold[4 * i], hold[4 * i + 1], hold[4 * i + 2], hold[4 * i + 3]);
    }
    else if (hold[4 * i] == "auipc" || hold[4 * i] == "lui")
    {

      ans = U_format(hold[4 * i], hold[4 * i + 1], hold[4 * i + 2]);
    }
    else if (hold[4 * i] == "jal")
    {

      ans = UJ_format(hold[4 * i], hold[4 * i + 1], hold[4 * i + 2]);
    }

    write(ans);
    i++;
  }
  inputFile.close();
  return 0;
}
