#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
using namespace std;


struct struct_chunk{
	int chunk_size;
	int chunk_count;
};
struct struct_op{

	string pid;
	int time;
	string exec_name;
	string file_path;
	int read_byte;
	int write_byte;
	int io_time;
	double io_time_per_kb;
	vector<struct_chunk> chunklist;
};

bool comparebyio_time(const struct_op &op1, const struct_op &op2){
	return op1.io_time_per_kb < op2.io_time_per_kb;
}

int main(){

int a,i;
string line;
std::vector<struct_op> oplist;
ifstream input("output.txt");

struct_op struct_op_temp;
for( i = 1; getline( input, line ) && i<=35467; i++ )
{
    //cout<<line<< " " << line.size() << endl;
    int sz= line.size();
    if(sz == 0){
    	struct_op struct_op_temp_2  = struct_op_temp;
    	if(struct_op_temp_2.read_byte != 0 ||  struct_op_temp_2.write_byte != 0 )
    	oplist.push_back(struct_op_temp_2);
    	struct_op_temp = {};
    
    	continue;
    }
    if(line.rfind("Time",0) == 0){
    	string s = line;
    	string delimiter = "  ";
    	size_t pos = 0;
    	string token;
    	while((pos = s.find(delimiter)) != std::string::npos){
    		token = s.substr(0,pos);
    		string tmpp = token;
    		if(tmpp.rfind("Time",0) == 0){
    			tmpp.erase(0,6);
    			int pos = tmpp.find(" ");
    			string tt = tmpp.substr(0,pos);
    			struct_op_temp.time = stoi(tt);
    			tmpp.erase(0,pos);
    			tmpp.erase(0,6);
    			struct_op_temp.pid = tmpp;	

    		}
    		else if(tmpp.rfind("ExecName:",0) == 0){
    			tmpp.erase(0,10);
    			int pos = tmpp.find(" ");
    			string tt = tmpp.substr(0,pos);
    			struct_op_temp.exec_name = tt;	
    			tmpp.erase(0,pos);
    			tmpp.erase(0,7);
    			struct_op_temp.file_path = tmpp;
    		}
    		else if(tmpp.rfind("read",0) == 0){
    			tmpp.erase(0,6);
    			int pos = tmpp.find(" ");
    			string tt = tmpp.substr(0,pos);
    			struct_op_temp.read_byte = stoi(tt);

    		}
     		else if(tmpp.rfind("write",0) == 0){
    			tmpp.erase(0,7);
    			int pos = tmpp.find(" ");
    			string tt = tmpp.substr(0,pos);
    			struct_op_temp.write_byte = stoi(tt);
    		}
    		   		
    	
    		s.erase(0,pos + delimiter.length());
    		if(s.rfind("IOTime:",0) == 0){
    			s.erase(0,8);
    			struct_op_temp.io_time = stoi(s);
    			if(struct_op_temp.io_time > 0){
    				if(struct_op_temp.read_byte > 0)
    					struct_op_temp.io_time_per_kb = ((struct_op_temp.io_time * 1024* 1.0)/ struct_op_temp.read_byte);
    				else if (struct_op_temp.write_byte > 0)
    				    struct_op_temp.io_time_per_kb = ((struct_op_temp.io_time * 1024* 1.0)/ struct_op_temp.write_byte);	
    				
    			}
    			
    		}  
    	}
    }

    if(line.rfind("VFSReadSize",0) == 0){
    	struct_chunk cktmp;

    	line.erase(0,12);
        int pos = line.find(" ");
        string tt = line.substr(0,pos);
    	cktmp.chunk_size = stoi(tt);
    	line.erase(0,pos);
    	line.erase(0,15);
   
    	cktmp.chunk_count = stoi(line);
    	struct_op_temp.chunklist.push_back(cktmp);
    	

    }

}
	for(int i = 0; i< oplist.size(); i++){
	}
	sort(oplist.begin(),oplist.end(),comparebyio_time);
    for(int i = 0; i< oplist.size(); i++){
 /*   	cout<<oplist[i].time<< " " <<oplist[i].pid << " " << 
    	oplist[i].exec_name << " " << oplist[i].file_path<< " " 
    	<<oplist[i].read_byte << " " <<oplist[i].write_byte<< " " 
    	<<oplist[i].io_time_per_kb<<"msperkb"<<endl;
    	for(int j = 0; j < oplist[i].chunklist.size(); j++ )
    		cout<<oplist[i].chunklist[j].chunk_size<< " " << oplist[i].chunklist[j].chunk_count<<endl;
    	cout<<endl;	  
  */
    if(oplist[i].read_byte > 0){
         
     int max  = 0;
     for(int j =0; j < oplist[i].chunklist.size(); j++)
        if( oplist[i].chunklist[j].chunk_size > max )
        max = oplist[i].chunklist[j].chunk_size;
    if(max > 0 ){
        cout<< oplist[i].read_byte <<",";
        cout<<max<<endl;   
    }
    }
       
    }
	return 0;
}