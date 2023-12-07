#include "main.h"

class Name
{
public:
	char c;
	int count;
	string exName;
};

struct KhachHang
{
	string name;
	string khach[128][2];
	int k = 0;
	void cropName(){
		Name charCount[128];
		    for (int i = 0; i < 128; i++) {
		        charCount[i].c = i;
		        charCount[i].count = 0;
		    }

		    for (char c : name) {
		        charCount[c].count++;
		    }
		    int n = 128;
		    for (int i = 0; i < n-1; i++) {
		        for (int j = 0; j < n-i-1; j++) {
		            if (charCount[j].count > charCount[j+1].count || (charCount[j].count == charCount[j+1].count && (isupper(charCount[j].c) && islower(charCount[j+1].c)) || (islower(charCount[j].c) && islower(charCount[j+1].c) && charCount[j].c > charCount[j+1].c) || (isupper(charCount[j].c) && isupper(charCount[j+1].c) && charCount[j].c > charCount[j+1].c))) {
		                Name temp = charCount[j];
		                charCount[j] = charCount[j+1];
		                charCount[j+1] = temp;
		            }
		        }
		    }
		    string result;
		    for (int i = 0; i < 128; i++) {
		        if (charCount[i].count > 0) {
		        	khach[k][0] = charCount[i].c;
		        	khach[k][1] = to_string(charCount[i].count);
		        	this->k++;
		        }
		    }
	}
	void Print(){
		for (int l = 0; l < k; l++)
		{
			cout << khach[l][0] << ":" << khach[l][1] << "->";
		}
		cout << endl;
	}
};

string anCeasar(const string &name){
	int freq[256] = {0};
	for(char c : name){
		freq[(int)c]++;
	}
	string result;
	for(char c : name){
		char encoded = c;
		if(c >= 'a' && c <= 'z'){
			encoded = 'a' + (c - 'a' - freq[(int)c] + 26) % 26;
		}else if(c >= 'A' && c <= 'Z'){
			encoded = 'A' + (c - 'A' - freq[(int)c] + 26) % 26;
		}
		result.push_back(encoded);
	}
	return result;
}

string sortStr(string name){
	Name charCount[128];

	    for (int i = 0; i < 128; i++) {
	        charCount[i].c = i;
	        charCount[i].count = 0;
	    }

	    for (char c : name) {
	        charCount[c].count++;
	    }
	    int n = 128;
	    for (int i = 0; i < n-1; i++) {
	        for (int j = 0; j < n-i-1; j++) {
	            if (charCount[j].count > charCount[j+1].count || (charCount[j].count == charCount[j+1].count && (isupper(charCount[j].c) && islower(charCount[j+1].c)) || (islower(charCount[j].c) && islower(charCount[j+1].c) && charCount[j].c > charCount[j+1].c) || (isupper(charCount[j].c) && isupper(charCount[j+1].c) && charCount[j].c > charCount[j+1].c))) {
	                Name temp = charCount[j];
	                charCount[j] = charCount[j+1];
	                charCount[j+1] = temp;
	            }
	        }
	    }
	    string result;
	    for (int i = 0; i < 128; i++) {
	        if (charCount[i].count > 0) {
	            // result << charCount[i].c << " : " << charCount[i].count << " -> ";
	        	for (int j = 0; j < charCount[i].count; j++)
	        	{
	        		result += charCount[i].c;
	        	}
	        }
	    }
	return result;	    
}

KhachHang khach[1000];

void Lapse(const string& name, int n){
	string result = sortStr(name);
	result = anCeasar(result);
	khach[n].name = sortStr(result);
	khach[n].cropName();
	khach[n].Print();
	// cout << khach[n].name;
	cout << endl;
}

void simulate(string filename)
{
	int MAXSIZE, n = 0;
	ifstream ss(filename);
	string line, maxsize,name;
	while(ss >> line)
	{ 
		if(line == "MAXSIZE")
		{
			ss >> maxsize;
			MAXSIZE = stoi(maxsize); 
	    	}else if(line == "LAPSE") {
	    		ss>>name;
	    		Lapse(name, n);
	    		n++;
	    	}else if(line == "HAND"){
	    	}
	}
	cout << "-----------------------------------------" << endl;
}