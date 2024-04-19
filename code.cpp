#include <bits/stdc++.h>
/*#include <fstream>
#include <sstream>
#include <bitset>
#include <vector>*/
using namespace std;
vector<string> hold;

bool error = false;


map<string,int> labels;
map<int,int> address;
vector<string>memory;
int pc = 0;

string convert_to_hex(const string& bits) {
    // Convert binary string to unsigned long integer
    bitset<32> bitset(bits);
    unsigned long int value = bitset.to_ulong();

    // Convert integer to hexadecimal string
    stringstream ss;
    ss << hex << value;
    string hexString = ss.str();

    // Ensure the output is 8 characters (32 bits in hexadecimal)
    hexString = string(8 - hexString.length(), '0') + hexString;

    return hexString;
}

string getfirst( string str )
{
  string ans = "";
  for(int i=0 ; i<str.size() ; i++)
  {
    if( str[i] == ' ' )
      break;
 
    ans = ans + str[i];
  }
  return ans;
}

void splitmemory(string str, vector<string> &extra)
{
  int start =  0;
  string s = getfirst(str);
  if( s[s.size()-1]  == ':')
  {
    for(int start = s.size() ; start < str.size() ; start++)
    {
      if( str[start] == ' ' )
        continue;
      else
        break;
    }
  }
  string inputString = str;
  for (int i = start; i < inputString.size(); i++)
  {
    if (inputString[i] == ',')
    {
      inputString.replace(i, 1, " ");
    }
  }
  istringstream iss(inputString);
  // vector<string> tokens;
  string token;

  while (iss >> token)
  {
    extra.push_back(token);
  }
  // return tokens;
}

void splitString(string str)
{
  int start =  0;
  string s = getfirst(str);
  if( s[s.size()-1]  == ':')
  {
    for(int start = s.size() ; start < str.size() ; start++)
    {
      if( str[start] == ' ' )
        continue;
      else
        break;
    }
  }
  string inputString = str;
  for (int i = start; i < inputString.size(); i++)
  {
    if (inputString[i] == ',')
    {
      inputString.replace(i, 1, " ");
    }
  }
  istringstream iss(inputString);
  // vector<string> tokens;
  string token;

  while (iss >> token)
  {
    hold.push_back(token);
  }
  // return tokens;
}


void write(string str)
{
  
  int num = address[pc];

  string ans = "";
    for (int i = 0; i < 32; i++)
    {
      ans += ('0' + num % 2);
      num /= 2;
    }
  reverse(ans.begin(), ans.end());
  ans = convert_to_hex(ans);
  str = "0x" +  ans + " " + str;
  
  // File name
  string fileName = "output.mc";
  // Open the file for writing
  ofstream outputFile;
  outputFile.open("output.mc", ios::app);

  // Check if the file is opened successfully
  if (!outputFile.is_open())
  {
    cout << "Error opening file: " << fileName << endl;
    cout << "error"; // Exit with an error code
  }

  // Data to write to the files
  string dataToWrite = str;

  // Write the data to the file
  outputFile << dataToWrite << endl;

  // Close the file
  outputFile.close();
  //cout<<""<<endl;
}

void write_data(string str,int num)
{
  //cout<<str<<" "<<num<<endl;
  int n=stoi(str);
  string ans = "";
    for (int i = 0; i < 32; i++)
    {
      ans += ('0' + num % 2);
      num /= 2;
    }
    string temp="";
    for (int i = 0; i < 32; i++)
    {
      temp += ('0' + n % 2);
      n /= 2;
    }
    //cout<<ans<<endl;
  reverse(ans.begin(), ans.end());
  reverse(temp.begin(), temp.end());
  ans = convert_to_hex(ans);
  temp= convert_to_hex(temp);
  ans="0x"+ans+" "+"0x"+temp;
  memory.push_back(ans);
}
void write_data_byte(string str,int num)
{
  //cout<<str<<" "<<num<<endl;
  int n=(int)str[1];
  
  string ans = "";
    for (int i = 0; i < 32; i++)
    {
      ans += ('0' + num % 2);
      num /= 2;
    }
    string temp="";
    for (int i = 0; i < 32; i++)
    {
      temp += ('0' + n % 2);
      n /= 2;
    }
    //cout<<ans<<endl;
  reverse(ans.begin(), ans.end());
  reverse(temp.begin(), temp.end());
  ans = convert_to_hex(ans);
  temp= convert_to_hex(temp);
  ans="0x"+ans+" "+"0x"+temp;
  memory.push_back(ans);
}
void write_data_string(string str,int num)
{
  //cout<<str<<" "<<num<<endl;
  int n=(int)str[0];
  
  string ans = "";
    for (int i = 0; i < 32; i++)
    {
      ans += ('0' + num % 2);
      num /= 2;
    }
    string temp="";
    for (int i = 0; i < 32; i++)
    {
      temp += ('0' + n % 2);
      n /= 2;
    }
    //cout<<ans<<endl;
  reverse(ans.begin(), ans.end());
  reverse(temp.begin(), temp.end());
  ans = convert_to_hex(ans);
  temp= convert_to_hex(temp);
  ans="0x"+ans+" "+"0x"+temp;
  memory.push_back(ans);
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


string immediate_sb(string a)
{
  int imm = labels[a] - pc*4;
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
  int imm = labels[a] - pc*4;           // calculate the offset
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
string R_format(string operation,string rd,string rs1,string rs2){
    
    string ans="";
    ans+=func7(operation);
    ans+=register_num(rs2);
    ans+=register_num(rs1);
    ans+=func3(operation);
    ans+=register_num(rd);
    ans+=opcode("R");
    if(error){
        return "";
    }
    ans=convert_to_hex(ans);
    ans="0x"+ans;
}
string I_format(string h, string rd, string rs1, string imm)
{
  string ans = "";
  ans += immediate(imm);
  ans += register_num(rs1);
  ans += func3(h);
  ans += register_num(rd);
  ans += opcode(h);
  ans = convert_to_hex(ans);
  ans = "0x" + ans;
  return ans;
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
string SB_format(string operation,string rs1, string rs2, string imm){
    string ans="";
    imm=immediate_sb(imm);
    ans+=imm[0];            //12
    ans+=imm.substr(2,6);   //10:5
    ans+=register_num(rs2);
    ans+=register_num(rs1);
    ans+=func3(operation);
    ans+=imm.substr(8,4);   //4:1
    ans+=imm[1];            //11
    ans+=opcode(operation);
    if(error){
        return "";
    }
    ans=convert_to_hex(ans);
    ans="0x"+ans;
    return ans;
}
string U_format(string operation,string rd,string imm){
    string ans="";
    ans+=immediate(imm);
    ans+=register_num(rd);
    ans+=opcode(operation);
    if(error){
        return "";
    }
    ans=convert_to_hex(ans);
    ans="0x"+ans;
    return ans;
}

string UJ_format(string operation,string rd,string imm){
    string ans="";
    imm=immediate_U(imm);
    ans+=imm[0];            //20
    ans+=imm.substr(10,10); //10:1
    ans+=imm[9];            //11
    ans+=imm.substr(1,8);   //19:12
    ans+=register_num(rd);
    ans+=opcode(operation);
    if(error){
        return "";
    }
    ans=convert_to_hex(ans);
    ans="0x"+ans;
    return ans;
}
int main()
{

  string fileName = "example.asm";

  // Open the file
  ifstream inFile(fileName);

  // Check if the file is opened successfully

  
  if (inFile.is_open())
  {
    cout << "file opened successfully: " << endl;
    //return 1; // Exit with an error code
  }
  int j = 0;
  string l;
  int flag=0;
  int mem_add=0x10000000;
  while (getline(inFile, l))
  {
    string s = getfirst(l);
    //cout<<l<<endl;
    //cout<<flag<<endl;
    if(s==".data")
    {    
        //cout<<""<<endl;
        flag=-1;
    }
    else if(s==".text")
        flag=0;
    else if(flag==-1)
    {   
        //cout<<""<<endl;
        vector<string> extra;
        splitmemory(l,extra);
        if(extra[1]==".word")
        {
          //cout<<1<<endl;
          for(int i=2;i<extra.size();i++,mem_add+=4)
          {
            write_data(extra[i],mem_add);
            //cout<<extra[i]<<endl;
            //cout<<mem_add<<endl;

          }

        }
        else if(extra[1]==".byte")
        {
          for(int i=2;i<extra.size();i++,mem_add+=1)
          { 

            write_data_byte(extra[i],mem_add);
            //cout<<extra[i]<<endl;
            //cout<<mem_add<<endl;

          }
        }
        else if(extra[1]==".half")
        {
          for(int i=2;i<extra.size();i++,mem_add+=2)
          {
            write_data(extra[i],mem_add);
            //cout<<extra[i]<<endl;
            //cout<<mem_add<<endl;

          }
        }
        else if(extra[1]==".dword")
        {
          for(int i=2;i<extra.size();i++,mem_add+=8)
          {
            write_data(extra[i],mem_add);
            //cout<<extra[i]<<endl;
            //cout<<mem_add<<endl;

          }
        }
        else if(extra[1]==".asciiz")
        {
          for(int i=2;i<extra.size();i++)
          { 
            for(int j=1;j<extra[i].size()-1;j++,mem_add+=1)
            { 
              //cout<<extra[i].substr(j,1)<<endl;
              write_data_string(extra[i].substr(j,1),mem_add);
            }
            //cout<<extra[i]<<endl;
            //cout<<mem_add<<endl;

          }
        }
        
    }
    
    else if(flag==0)
    {   
        //cout<<""<<endl;
        //string s = getfirst(l);
        if( s[s.size()-1] == ':' )
        {
            s.pop_back();
            labels[s] = j*4;
        }
        if( s!= "" )   // if line is not empty or blank provide address to the instruction there
        address[j] = j*4;
        j++;
    }
  }
  inFile.close();
 


string fileName2 = "example.asm";

  // Open the file
  ifstream inputFile(fileName2);

  // Check if the file is opened successfully

 if (inputFile.is_open())
  {
    cout << "File opened successfully " << fileName2 << endl;
    //return 1; // Exit with an error code
  }
  // Read and print the contents of the file
  int i = 0;
  
  string line;
  string ans;
  while(getline(inputFile, line))
  { 
    //cout<<line<<endl;
    //cout<<flag<<endl;
    string s = getfirst(line);
    //cout<<line<<endl;
    if(s==".data")
    {
        flag=-1;
    }    
    else if(s==".text")
        flag=0;
    else if(flag==0)    
    {   
        //cout<<""<<endl;
        splitString(line);

        if (hold[4 * i] == "addi" || hold[4 * i] == "andi" || hold[4 * i] == "ori" || hold[4 * i] == "lb" || hold[4 * i] == "ld" || hold[4 * i] == "lh" || hold[4 * i] == "lw" || hold[4 * i] == "jalr")
        {   
            //cout<<""<<endl;
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
        
        pc++;
        i++;
        cout<<"written"<<endl;
    }    
    
  }
  cout<<""<<endl;
  string fileName3 = "output.mc";
  // Open the file for writing
  ofstream outputFile;
  outputFile.open("output.mc", ios::app);

  // Check if the file is opened successfully
  if (!outputFile.is_open())
  {
    cout << "Error opening file: " << fileName << endl;
    cout << "error"; // Exit with an error code
  }
  int num = address[pc-1];
  num+=4;

  string ans1 = "";
    for (int i = 0; i < 32; i++)
    {
      ans1 += ('0' + num % 2);
      num /= 2;
    }
  reverse(ans1.begin(), ans1.end());
  ans1 = convert_to_hex(ans1);
  string data_to_write="0x" +  ans1;
  outputFile<<data_to_write<<endl;
  outputFile<<" "<<endl;
  for(int i=0;i<memory.size();i++)
  {
    outputFile<<memory[i]<<endl;
  }
  outputFile.close();
  inputFile.close();
  return 0;
}
