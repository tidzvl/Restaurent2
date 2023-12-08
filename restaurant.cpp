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
	vector<char> ch;
	vector<string> code;
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
		            if (charCount[j].count > charCount[j+1].count || (charCount[j].count == charCount[j+1].count && ((isupper(charCount[j].c) && islower(charCount[j+1].c)) || (islower(charCount[j].c) && islower(charCount[j+1].c) && charCount[j].c > charCount[j+1].c) || (isupper(charCount[j].c) && isupper(charCount[j+1].c) && charCount[j].c > charCount[j+1].c)))) {
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
	string convert2Bin(){
		string result = "";
		for (int i = 0; i < k; i++)
		{
			for(int j = 0; j < k; j++){
				if(khach[i][0][0] == ch[j]){
					for(int l = 0; l < stoi(khach[i][1]); l++){
						result = result + code[j];
					}
				}
			}
		}
		return result.substr(result.length()-10);
	}

	int convert210(){
		string binaryString = convert2Bin();
		int decimal = 0;
		int size = binaryString.size();
		for(int i = 0; i < size; i++) {
		        if(binaryString[i] == '1') {
		            decimal += pow(2, size - 1 - i);
		        }
		}
		return decimal;
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
			if (charCount[j].count > charCount[j+1].count || (charCount[j].count == charCount[j+1].count && ((isupper(charCount[j].c) && islower(charCount[j+1].c)) || (islower(charCount[j].c) && islower(charCount[j+1].c) && charCount[j].c > charCount[j+1].c) || (isupper(charCount[j].c) && isupper(charCount[j+1].c) && charCount[j].c > charCount[j+1].c)))) {
				Name temp = charCount[j];
				charCount[j] = charCount[j+1];
				charCount[j+1] = temp;
			}
		}
	}
	string result;
	for (int i = 0; i < 128; i++) {
		if (charCount[i].count > 0) {
			for (int j = 0; j < charCount[i].count; j++)
			{
				result += charCount[i].c;
			}
		}
	}
	return result;	    
}

struct HuffmanNode
{
	char data;
	int frequency;
	HuffmanNode* left;
	HuffmanNode* right;
	HuffmanNode(char data, int frequency) : data(data), frequency(frequency), left(nullptr), right(nullptr){}
};

struct CompareNodes
{
	bool operator()(HuffmanNode* left, HuffmanNode* right){
		return left->frequency > right->frequency;
	}
};

HuffmanNode* buildHuffmanTree(KhachHang khach[], int n){
	const size_t arraySize = 256;
	HuffmanNode* nodes[arraySize];

	for (size_t i = 0; i < arraySize; ++i)
	{
		nodes[i] = nullptr;
	}
	for (int i = 0; i < khach[n].k; ++i)
	{
		nodes[i] = new HuffmanNode(khach[n].khach[i][0][0], stoi(khach[n].khach[i][1]));
	}
	while(true){
		int min1 = -1, min2 = -1;
		for(size_t i = 0; i < arraySize; ++i){
			if(nodes[i] != nullptr && nodes[i]->frequency > 0){
				if(min1 == -1 || nodes[i]->frequency < nodes[min1]->frequency){
					min2 = min1;
					min1 = i;
				}else if (min2 == -1 || nodes[i]->frequency < nodes[min2]->frequency){
					min2 = i;
				}
			}
		}
		if(min2 == -1){
			break;
		}

		HuffmanNode* internalNode = new HuffmanNode('$', nodes[min1]->frequency + nodes[min2]->frequency);
		internalNode->left = nodes[min1];
		internalNode->right = nodes[min2];
		nodes[min1]->frequency = nodes[min2]->frequency = 0;
		nodes[min1] = internalNode;
		nodes[min2] = nullptr;
	}
	for(size_t i = 0; i < arraySize; ++i){
		if(nodes[i] != nullptr){
			return nodes[i];
		}
	}

	return nullptr;
}

void printHuffmanTree(HuffmanNode* root, string code){
	if(root){
		if(root->data != '$'){
			cout << root->data << ": " << code << endl;
		}
		printHuffmanTree(root->left, code + "0");
		printHuffmanTree(root->right, code + "1");
	}
}

KhachHang khach[1000];
vector<HuffmanNode*> HuffKhach;
// vector<string> Result;

void addBin(HuffmanNode* root, string code, int i, vector<char> &ch, vector<string> &codes){
	if(root){
		if(root->data != '$'){
			// cout << root->data << ": " << code << endl;
			ch.push_back(root->data);
			codes.push_back(code);
		}
		addBin(root->left, code + "0", i, ch, codes);
		addBin(root->right, code + "1", i, ch, codes);
	}
}

vector<int> G;
vector<int> S;

bool Lapse(const string& name, int n){
	string result = sortStr(name);
	khach[n].name = anCeasar(result);
	// khach[n].name = sortStr(result);
	khach[n].cropName();
	if(khach[n].k <= 3) return false;
	khach[n].Print();
	// cout << sortStr(khach[n].name);
	HuffmanNode* root = buildHuffmanTree(khach, n);
	HuffKhach.push_back(root);
	addBin(root, "", n, khach[n].ch, khach[n].code);
	// cout << khach[n].convert210() << endl;
	// cout << "-----------------------------------------"<<endl;
	if(khach[n].convert210()%2 != 0){
		G.push_back(n);
	}else{
		S.push_back(n);
	}
	return true;
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
	    		if(Lapse(name, n));
		    		n++;
	    	}else if(line == "HAND"){
	    	}
	}
	cout << "-----------------------------------------"<<endl;
	cout << "Nha` G: ";
	for(int i = 0; i < G.size(); i++){
		cout << G[i];
	}
	cout << endl;
	cout << "Nha` S: ";
	for(int i = 0; i < S.size(); i++){
		cout << S[i];
	}
}