#include <bits/stdc++.h>

using namespace std;

vector<string>lines;
vector<bool>always_taken;
vector<bool>not_taken;
vector<bool>one_bit;
vector<bool>two_bit;
int ob_predictor=0;
string state = "00";

vector<pair<string,string>>buffer_a;
vector<pair<string,string>>buffer_n;
vector<pair<string,string>>buffer_o;
vector<pair<string,string>>buffer_t;
vector<string>history;



int hex2dec(string hexVal)                   //function for converting hexadecimal string to integer
{ 
    int len = hexVal.size(); 
    int base = 1;   
    int dec_val = 0;    
    for (int i = len - 1; i >= 0; i--) { 
        if (hexVal[i] >= '0' && hexVal[i] <= '9') { 
            dec_val += ((int)(hexVal[i]) - 48) * base;
            base = base * 16; 
        } 
        else if (hexVal[i] >= 'a' && hexVal[i] <= 'f') { 
            dec_val += (int)((hexVal[i]) - (int)('a')+10) * base; 
            base = base * 16; 
        } 
    } 
    return dec_val; 
}

string intToHexString(int value) {              //function for converting decimal integer to hexadecimal string
    stringstream ss;
    ss << hex << value;
    return ss.str();
}

void splitString(string str)                //function for slicing the string into substrings in order to access the instruction address and offset 
{                                           //in case of branch instruction
    string s="";                            
    for(int i=0;i<str.size();)
    {
        if(str[i]!=' ')
        {    
            s+=str[i];
            i++;
        }
        else if(str[i]==' ')
        {
            lines.push_back(s);
            s="";
            while(i<str.size() && str[i]==' ')
                i++;
        }
    }
    if(s!="")
        lines.push_back(s);
    //for(int i=0;i<lines.size();i++)
        //cout<<lines[i]<<endl;
}






void sp_always(string str,int i,int address,string l,int j,string sign)           //function for branch prediction using always taken method
{   
    //cout<<"__"<<endl;
    
   int add=hex2dec(lines[i+2]);
   int offset=stoi(lines[j]); 
   if(sign=="+")
        add+=offset;
    else    add-=offset;
   string add_hex="0x";
   add_hex+=intToHexString(add); 
   //cout<<add_hex<<endl;
   buffer_a.push_back({lines[i+2],add_hex});
   i=lines.size();
   splitString(l);
   add=hex2dec(lines[i+2]);
   bool token;
   //cout<<add<<" "<<address<<endl;
   if(add==address)
    {    
        token=true;
        history.push_back("taken");
    }
    else    
    {
        token=false;
        history.push_back("not_taken");
    }
   
   if(token==true)
        always_taken.push_back(true);

   else 
        always_taken.push_back(false); 

}

void sp_not(string str,int i,int address,string l,int j,string sign)              //function for branch prediction using always not taken method
{   int add=hex2dec(lines[i+2]);
    add+=4;
    string add_hex="0x";
    add_hex+=intToHexString(add); 
    buffer_n.push_back({lines[i+2],add_hex});
    i=lines.size();
    splitString(l);
    add=hex2dec(lines[i+2]);
    bool token;
    if(address==add)
        token=true;
    else    token=false;
    if(token==false)
        not_taken.push_back(true);

    else   
        not_taken.push_back(false);

}



void one_bit_branch_predictor( string s ,int i,int address,string l,int j,string sign)       //function for branch prediction using one bit predictor 
{   
    int add=hex2dec(lines[i+2]);
    //cout<<lines[j]<<endl;
    if(ob_predictor==1)
    {
        int offset=stoi(lines[j]); 
        if(sign=="+")
            add+=offset;
        else    add-=offset;
        string add_hex="0x";
        add_hex+=intToHexString(add); 
        buffer_o.push_back({lines[i+2],add_hex});
    }
    else if(ob_predictor==0)
    {
        add+=4;
        string add_hex="0x";
        add_hex+=intToHexString(add); 
        buffer_o.push_back({lines[i+2],add_hex});
    }
    //cout<<"hi"<<endl;
    i=lines.size();
    splitString(l);
    add=hex2dec(lines[i+2]);
    bool token;
    if(address==add)
        token=true;
    else    token=false;

    if( ob_predictor==1 && token==false ) // previous branch is taken & current branch is not-taken 
    {
        one_bit.push_back(false);
        ob_predictor = 0;
    }

    else if( ob_predictor==1 && token==true )// previous branch is taken & current branch is taken
    {
        one_bit.push_back(true);
        ob_predictor = 1;
    }

    else if( ob_predictor==0 && token==false )// previous branch is not-taken & current branch is not-taken
    {
        one_bit.push_back(true);
        ob_predictor = 0;
    }

    else if( ob_predictor==0 && token==true )// previous branch is not-taken & current branch is taken
    {
        one_bit.push_back(false);
        ob_predictor = 1;
    }
}



void bit2_branch_predictor( string s ,int i,int address,string l,int j,string sign)            //function for branch prediction using two bit predictor method
{
    int add=hex2dec(lines[i+2]);
    if( state=="11" || state=="10")
    {
        int offset=stoi(lines[j]); 
        if(sign=="+")
            add+=offset;
        else    add-=offset;
        string add_hex="0x";
        add_hex+=intToHexString(add); 
        buffer_t.push_back({lines[i+2],add_hex});
    }
    else if(state=="00" || state=="01")
    {
        add+=4;
        string add_hex="0x";
        add_hex+=intToHexString(add); 
        buffer_t.push_back({lines[i+2],add_hex});
    }
    i=lines.size();
    splitString(l);
    add=hex2dec(lines[i+2]);
    bool token;
    if(address==add)
        token=true;
    else    token=false;

   if( state== "11" && token==false)        // state : strongly taken ; branch: not-taken
   {
      state = "10";
      two_bit.push_back(false);
   }
   else if( state== "11" && token==true)    // state : strongly taken ; branch: taken
   {
      state = "11";
      two_bit.push_back(true);
   } 
   else if( state== "10" && token==false)    // state : weakly taken ; branch : not-taken
   {
      state = "00";
      two_bit.push_back(false);
   } 
   else if( state== "10" && token==true)     //  state : weakly taken ; branch : taken
   {
      state = "11";
      two_bit.push_back(true);
   } 

   else if( state== "01" && token==false)     //  state : weakly not-taken ; branch : not-taken
   {
      state = "00";
      two_bit.push_back(true);
   } 
   else if( state== "01" && token==true)     //  state : weakly not-taken ; branch : taken
   {
      state = "11";
      two_bit.push_back(false);
   }  
   else if( state== "00" && token==false)     //  state : not-taken ; branch : not-taken
   {
      state = "00";
      two_bit.push_back(true);
   } 
   else if( state== "00" && token==true)     //  state : not-taken ; branch : taken
   {
      state = "01";
      two_bit.push_back(false);
   } 

}

void read_input()                       //function for reading the input file
{
    string filename="input.txt";
    ifstream inFile(filename);
    ifstream inFile2(filename);
    if (inFile.is_open() && inFile2.is_open())
    {
      cout << "file opened successfully: " << endl;
     //return 1; // Exit with an error code
    }
    
    string prev;
    string l;
    getline(inFile,l);

    while(getline(inFile,l))
    {   
        getline(inFile2,prev);
        int i=lines.size();
        //cout<<prev<<endl<<l<<endl;
        
        //splitString(l);      //splitting the string
        splitString(prev);
       
        if(lines[i+4]=="beq" || lines[i+4]=="bne" || lines[i+4]=="bge" || lines[i+4]=="blt" || lines[i+4]=="beqz" || lines[i+4]=="bnez" || lines[i+4]=="bgt" || lines[i+4]=="ble" || lines[i+4]=="bgeu" || lines[i+4]=="bltu")
        {   //checking whether the instruction is a branch instruction or not
           
            int j=lines.size()-1;
            //cout<<prev<<endl;
            int offset=stoi(lines[j]);

            //cout<<offset<<endl;
            int address=hex2dec(lines[i+2]);
            if(lines[j-1]=="+")
                address+=offset;
            else    address-=offset;
            //cout<<"__"<<endl;
            sp_always(lines[j],i,address,l,j,lines[j-1]);
            
            sp_not(lines[j],i,address,l,j,lines[j-1]);
            
            one_bit_branch_predictor(lines[j],i,address,l,j,lines[j-1]);
            
            bit2_branch_predictor(lines[j],i,address,l,j,lines[j-1]);
            

        }
    }
    inFile.close();

}

void accuracy()                   //function for printing the accuracy of each method
{
    int num1=0;
    for(int i=0;i<always_taken.size();i++)
    {
        if(always_taken[i]==true)
            num1++;
    }
    cout<< "always-taken branch predictor's accuracy : " <<  (float(num1)/(float)always_taken.size())*100<<endl;
    
    num1=0;
    for(int i=0;i<not_taken.size();i++)
    {
        if(not_taken[i]==true)
            num1++;
    }
    cout<< "always-not_taken branch predictor's accuracy : " <<  (float(num1)/(float)not_taken.size())*100<<endl;

    num1=0;
    for(int i=0;i<one_bit.size();i++)
    {
        if(one_bit[i]==true)
            num1++;
    }
    cout<< "one-bit branch predictor's accuracy : " <<  (float(num1)/(float)one_bit.size())*100<<endl;

    num1=0;
    for(int i=0;i<two_bit.size();i++)
    {
        if(two_bit[i]==true)
            num1++;
    }
    cout<< "two-bit branch predictor's accuracy : " <<  (float(num1)/(float)two_bit.size())*100<<endl;
}

int main()
{
    read_input();     
    accuracy();
    cout<<endl;
    int a;
    cout<<"To print the target buffer table for always_taken predictor enter 1"<<endl;      //printing the target buffer table for each method
    cin>>a;

    if(a==1)
    {
        cout<<"branch target buffer table for always_taken predictor and history table"<<endl;
        for(int i=0;i<buffer_a.size();i++)
            cout<<buffer_a[i].first<<" "<<buffer_a[i].second<<" "<<history[i]<<endl;
    }

    cout<<"To print the target buffer table for always_not_taken predictor enter 2"<<endl;
    cin>>a;

    cout<<endl;
    if(a==2)
    {
        cout<<"branch target buffer table for always_not_taken predictor and history table"<<endl;
        for(int i=0;i<buffer_a.size();i++)
            cout<<buffer_n[i].first<<" "<<buffer_n[i].second<<" "<<history[i]<<endl;
    }

    cout<<"To print the target buffer table for one_bit predictor enter 3"<<endl;
    cin>>a;

    cout<<endl;
    if(a==3)
    {
        cout<<"branch target buffer table for one_bit predictor and history table"<<endl;
       for(int i=0;i<buffer_a.size();i++)
            cout<<buffer_o[i].first<<" "<<buffer_o[i].second<<" "<<history[i]<<endl;
    }

    cout<<"To print the target buffer table for two_bit predictor enter 4"<<endl;
    cin>>a;

    cout<<endl;
    if(a==4)
    {
        cout<<"branch target buffer table for two_bit predictor and history table"<<endl;
       for(int i=0;i<buffer_a.size();i++)
            cout<<buffer_t[i].first<<" "<<buffer_t[i].second<<" "<<history[i]<<endl;
    }
}