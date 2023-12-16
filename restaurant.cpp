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
	string namenonsort;
	string khach[128][2];
	// string khachnonsort[128][2];
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
		        charCount[static_cast<int>(c)].count++;
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
	// string convert2Bin(){
	// 	string result = "";
	// 	for (int i = 0; i < k; i++)
	// 	{
	// 		for(int j = 0; j < k; j++){
	// 			if(khach[i][0][0] == ch[j]){
	// 				for(int l = 0; l < stoi(khach[i][1]); l++){
	// 					result = result + code[j];
	// 				}
	// 			}
	// 		}
	// 	}
	// 	if(result.length() <= 10) return result;
	// 	return result.substr(result.length()-10);
	// }
	string convert2Bin(){
		string result = "";
		for (int i = 0; i < namenonsort.length(); i++)
		{
			for(int j = 0; j < k; j++){
				if(namenonsort[i] == ch[j]){
					result = result + code[j];
				}
			}
		}
		if(result.length() <= 10) return result;
		return result.substr(result.length()-10);
	}

	int convert210(){
		string binaryString = convert2Bin();
		// cout << binaryString << endl;
		int decimal = 0;
		int size = binaryString.size();
		for(int i = 0; i < size; i++) {
		        if(binaryString[i] == '1') {
		            decimal += pow(2, size - 1 - i);
		        }
		}
		// cout << decimal << endl;
		return decimal;
	}
};

// string anCeasar(const string &name){
// 	int freq[256] = {0};
// 	for(char c : name){
// 		freq[(int)c]++;
// 	}
// 	string result;
// 	for(char c : name){
// 		char encoded = c;
// 		if(c >= 'a' && c <= 'z'){
// 			encoded = 'a' + (c - 'a' - freq[(int)c] + 26) % 26;
// 		}else if(c >= 'A' && c <= 'Z'){
// 			encoded = 'A' + (c - 'A' - freq[(int)c] + 26) % 26;
// 		}
// 		result.push_back(encoded);
// 	}
// 	return result;
// }

string anCeasar(const string &name){
	int freq[256] = {0};
	for(char c : name){
		freq[(int)c]++;
	}
	string result;
	for(char c : name){
		char encoded = c;
		if(c >= 'a' && c <= 'z'){
			encoded = 'a' + (c - 'a' + freq[(int)c]) % 26;
		}else if(c >= 'A' && c <= 'Z'){
			encoded = 'A' + (c - 'A' + freq[(int)c]) % 26;
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
		charCount[static_cast<int>(c)].count++;
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
	// int height;
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

void printInOrder(HuffmanNode* root) {
	if(root ==  nullptr) return;
    	if (root) {
	        printInOrder(root->left);
        if (root->data != '$') {
            	cout << root->data << "\n";
            	// cout << root->data << " ";
        }
        printInOrder(root->right);
    }
}


KhachHang khach[1000];
vector<HuffmanNode*> HuffKhach;
vector<int> Result;

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
//---------- xoay xoay xoay
int rotationCount = 0;

int height(HuffmanNode* N) {
    	if (N == nullptr)
        	return 0;
    	return max(height(N->left), height(N->right)) + 1;
}

HuffmanNode* rightRotate(HuffmanNode* y) {
    	HuffmanNode* x = y->left;
    	HuffmanNode* T2 = x->right;
    	x->right = y;
    	y->left = T2;
    	return x;
}

HuffmanNode* leftRotate(HuffmanNode* x) {
    	HuffmanNode* y = x->right;
    	HuffmanNode* T2 = y->left;
    	y->left = x;
    	x->right = T2;
    	return y;
}

int getBalance(HuffmanNode* N) {
    	if (N == nullptr)
        	return 0;
    	return height(N->left) - height(N->right);
}

void printTreeStructure(HuffmanNode* root, string indent = "", bool isLeft = true) {
    	if (root != nullptr) {
        	cout << indent;
	        if (isLeft)
	           	cout << "L----";
	        else
	            	cout << "R----";
	        cout << root->data << "\n";

	        indent += "     ";
	        printTreeStructure(root->left, indent, true);
	        printTreeStructure(root->right, indent, false);
    	}
}

HuffmanNode* balanceTree(HuffmanNode* node, HuffmanNode* parent = nullptr) {
    	if (node == nullptr || rotationCount >= 3) {
        	return node;
    	}

    	int balance = getBalance(node);
    	if (balance > 1) {
        	if (getBalance(node->left) >= 0) {
	            	node = rightRotate(node);
	            	rotationCount++;
	            	// cout << "After right rotation: \n";
	            	// printTreeStructure(node);
	        } else {
	            	node->left = leftRotate(node->left);
	            	node = rightRotate(node);
	            	rotationCount++;
	            	// cout << "After left-right rotation: \n";
	           	//  printTreeStructure(node);
	        }
   	 } else if (balance < -1) {
	        if (getBalance(node->right) <= 0) {
	            	node = leftRotate(node);
	            	rotationCount++;
	            	// cout << "After left rotation: \n";
	            	// printTreeStructure(node);
	        } else {
	            node->right = rightRotate(node->right);
	            node = leftRotate(node);
	            rotationCount++;
	            // cout << "After right-left rotation: \n";
	            // printTreeStructure(node);
	        }
    	}

    	if (parent != nullptr) {
	        if (parent->left == node) {
	            	parent->left = node;
	        } else if (parent->right == node) {
	            	parent->right = node;
	        }
    	}

    	if (rotationCount < 3) {
	        node->left = balanceTree(node->left, node);
	        node->right = balanceTree(node->right, node);
    	}

    	return node;
}


void printHuffmanTree2(HuffmanNode* root, int space = 0, int height = 10) {
    	if (root == nullptr)
        	return;

    	space += height;

    	printHuffmanTree2(root->right, space);

    	cout << endl;
    	for (int i = height; i < space; i++)
        	cout << " ";
    	cout << root->data << "\n";

    	printHuffmanTree2(root->left, space);
}



//--


vector<int> G;
vector<int> S;

bool Lapse(const string& name, int n){
	khach[n].namenonsort = anCeasar(name);
	string result = sortStr(name);
	khach[n].name = anCeasar(result);
	// khach[n].name = sortStr(result);
	khach[n].cropName();
	if(khach[n].k < 3){
		khach[n].name.clear();
		for(int i = 0; i < 128; i++){
			khach[n].khach[i][0].clear();
			khach[n].khach[i][1].clear();
		}
		khach[n].ch.clear();
		khach[n].code.clear();
		khach[n].k = 0;
		return false;
	}
	// khach[n].Print();
	// // cout << sortStr(khach[n].name);
	HuffmanNode* root = buildHuffmanTree(khach, n);
	// printHuffmanTree2(root);
	// printTreeStructure(root);
	// cout << "---------------------------" << endl;
	//-xoay
	rotationCount = 0;
        root = balanceTree(root);
        // if (getBalance(root) >= -1 && getBalance(root) <= 1) {
        //     cout << "Tree is balanced after " << rotationCount << " rotations\n";
        // } else {
        //     cout << "Tree is not balanced after " << rotationCount << " rotations\n";
        // }
	// printHuffmanTree2(root);
	// cout << "---------------------------" << endl;
	// printTreeStructure(root);
	
	HuffKhach.push_back(root);
	addBin(root, "", n, khach[n].ch, khach[n].code);
	Result.push_back(khach[n].convert210());	
	// cout << "-----------------------------------------"<<endl;
	if(khach[n].convert210()%2 != 0){
		G.push_back(n);
	}else{
		S.push_back(n);
	}
	return true;
}

struct Node{
	int data;
	int time;
	Node *pLeft;
	Node *pRight;
};

void TrongCay(Node* &t){
	t = nullptr;
}

unordered_map<Node*, queue<Node*>> nodeQueues;

void AddNode(Node* &t, int x){
	if(t == nullptr){
		Node* root = new Node;
		root->data = x;
		root->pLeft = nullptr;
		root->pRight = nullptr;
		t = root;
		nodeQueues[t].push(root);
	}else{		
		if(x < t->data){
			AddNode(t->pLeft, x);
		}else{
			AddNode(t->pRight, x);
		}
		nodeQueues[t].push(t);
	}
}

string InOrder(Node* root) {
    	if(root == NULL) return "NULL";
    	string result;
    	string left = InOrder(root->pLeft); 
    	result += to_string(root->data) +  " ";
    	string right = InOrder(root->pRight); 

    	if(root->pLeft == nullptr && root->pRight == nullptr) return result;
    	return result+ "(" +left+ "," +right + ")";
}

void InOrderLML(Node* root) {
    	if (root != NULL) {
        	InOrderLML(root->pLeft);
        	cout << root->data << "\n";
        	InOrderLML(root->pRight);
    	}
}

void postOrder(Node* t, vector<int> &arr){
	if(t == nullptr) return;
	if(t != nullptr){		
		postOrder(t->pLeft, arr);
		postOrder(t->pRight, arr);
		arr.push_back(t->data);
	}
}

void deleteNode(Node* &root){
    	if(root == nullptr) return;

    	if(root->pLeft == nullptr){
	        Node* temp = root;
	        root = root->pRight;
	        delete temp;
    	}else if(root->pRight == nullptr){
        	Node* temp = root;
        	root = root->pLeft;
        	delete temp;
    	}else{
        	Node* temp = root->pRight;
        	while(temp->pLeft != nullptr){
            		temp = temp->pLeft;
        	}
        	root->data = temp->data;
        	deleteNode(root->pRight);
    	}
}

void deleteTree(Node* &root){
    	if(root == nullptr) return;

    	deleteTree(root->pLeft);
    	deleteTree(root->pRight);

    	delete root;
    	root = nullptr;
}

void deleteCustomers(Node* &t, size_t Y){
	if( Y >= nodeQueues[t].size()){
	        deleteTree(t);
	        nodeQueues[t] = queue<Node*>();  // Xóa hàng đợi tương ứng
	}else{
		while(Y-- > 0 && !nodeQueues[t].empty()){
			Node* nodeToDelete = nodeQueues[t].front();
			nodeQueues[t].pop();
			deleteNode(nodeToDelete);
		}
	}
}
void createTempBST(Node* &tempBST, const vector<int> &permutation){
    	for(int i = 0; i < permutation.size(); i++){
        	AddNode(tempBST, permutation[i]);
    	}
}
int isIdentical(Node* root1, Node* root2) {
    	if (root1 == NULL && root2 == NULL)
        	return 1;
    	else if (root1 == NULL || root2 == NULL)
        	return 0;
    	else {
	        if (root1->data == root2->data && isIdentical(root1->pLeft, root2->pLeft) && isIdentical(root1->pRight, root2->pRight))
	            	return 1;
	        else
	            	return 0;
    	}
}

vector<Node*> BST;

// void printInOrder(int n){
// 	string s = InOrder(BST[n]);
// 	cout << s << endl;
// }


class Area {
public:
    	int id;
    	int guests;
    	int timestamp;
    	int result;

    	Area(int id, int guests, int timestamp, int result) : id(id), guests(guests), timestamp(timestamp), result(result) {}

    	bool operator<(const Area& other) const {
        	if (guests == other.guests) {
            		return timestamp < other.timestamp;
        	}
        	return guests > other.guests;
    	}
};

priority_queue<Area> heap;
vector<int> areas;
int MAXHEAP = 6;
int timeheap = 0;

void addGuest(int area, int result) {
    	if (area < 1 || area > MAXHEAP) {
        	return;
    	}
    	areas[area - 1]++;
    	heap.push(Area(area, areas[area - 1], timeheap++, result));
}

// void removeGuest(int area) {
//     	if (area < 1 || area > MAXHEAP) {
//         	return;
//     	}
//     	if (areas[area - 1] == 0) {
//         	return;
//     	}
//     	areas[area - 1]--;
//     	if (areas[area - 1] > 0) {
//         	heap.push(Area(area, areas[area - 1], timeheap++));
//     	}
// }

void printHeap() {
    	priority_queue<Area> temp = heap;
    	vector<bool> printed(MAXHEAP, false);
    	while (!temp.empty()) {
        	Area top = temp.top();
        	temp.pop();
	        if (top.guests == areas[top.id - 1] && !printed[top.id - 1]) {
	            cout << "ID " << top.id << ": " << top.guests << " khach\n";
	            printed[top.id - 1] = true;
        	}
    	}
}

void removeNGuests(int N) {
    	while (N > 0 && !heap.empty()) {
        	Area top = heap.top();
        	heap.pop();
        	if (top.guests == areas[top.id - 1]) {
            		int guestsToRemove = min(N, top.guests);
            		areas[top.id - 1] -= guestsToRemove;
           	 	N -= guestsToRemove;
            		// cout << "Result-" << top.id << "\n";
            		for (int i = 0; i < guestsToRemove; i++) {
		            cout << top.result << "-" << top.id << "\n";
		        }
            		if (areas[top.id - 1] > 0) {
                		heap.push(Area(top.id, areas[top.id - 1], timeheap++, top.result));
            		}else{
            			return;
            		}
        	}
    	}
}

void printNGuests(int N) {
    	priority_queue<Area> temp = heap;
    	vector<bool> printed(MAXHEAP, false);
    	while (N > 0 && !temp.empty()) {
        	Area top = temp.top();
        	temp.pop();
        	if (top.guests == areas[top.id - 1] && !printed[top.id - 1]) {
            		int guestsToPrint = min(N, top.guests);
            		for (int i = 0; i < guestsToPrint; i++) {
                		cout << top.id << "-" << top.result << "\n";
            		}
            		printed[top.id - 1] = true;
            		N -= guestsToPrint;
        	}
    	}
}


void LapseNext(int n, int ID){
	for(size_t i = 0; i < G.size(); i++){
		if(n == G[i]){
			AddNode(BST[ID-1], Result[n]);
		}
	}
	for(size_t l = 0; l < S.size(); l++){
		if(n == S[l])
			addGuest(ID, Result[n]);
	}
}

int MAXSIZE;
int n = 0;

void kokusen(){
	for(int i = 0; i < MAXSIZE; i++){
		if(BST[i] != nullptr){
			int Y;
			vector<int> arr;
			postOrder(BST[i], arr);
			// for(int j = 0; j < arr.size(); j++){
			// 	cout << arr[j] << " ";
			// }
			// cout << endl;
			sort(arr.begin(), arr.end());
			vector<vector<int>> permutations;
			do {
			        permutations.push_back(arr);
			} while(next_permutation(arr.begin(), arr.end()));
		    	// for(const auto& perm : permutations) {
		        // 	if(perm[0] == arr[arr.size() - 1]) {
			//             	// for(int num : perm) {
			//                 // 	cout << num << ' ';
			//             	// }
			//             	Y++;
			//             	// cout << endl;
			//         }
		    	// }
		    	for(const auto& perm : permutations) {
			    	Node* TempTree;
			    	TrongCay(TempTree);
			    	createTempBST(TempTree, perm);
			    	if(isIdentical(TempTree, BST[i])){
			    		Y++;
			    	}
			    	delete TempTree;
		    	}
		    	// cout <<"Y: " << Y << endl;
		    	Y = Y%MAXSIZE;
		    	// cout << "Y%MAXSIZE = " << Y << endl;
		    	deleteCustomers(BST[i], Y);
		}
	}
	// vector<int> arr;
	// postOrder(BST[4], arr);
	// int numPermutations = countPermutations(arr);
	// cout << "4 : " << numPermutations << endl;
	// for(int i = 0; i < MAXSIZE; i++){
	// 	for(int j = 0; j < arr.size(); j++){
	// 		cout << arr[j] << " ";
	// 	}
	// 	cout << endl;
	// }
}

void Keiteiken(int num){
	if(num < 1 || num > MAXSIZE) return;
	removeNGuests(num);
}

void Hand(int n){
	// khach[n-1].Print();
	if(HuffKhach.empty()) {
		return;
	}
	printInOrder(HuffKhach[n-1]);
}

void Limitless(int num){
	// AddNode(BST[num-1], 1707);
	// AddNode(BST[num-1], 2417);
	// AddNode(BST[num-1], 2417);
	// AddNode(BST[num-1], 1565);
	InOrderLML(BST[num-1]);
	// cout << InOrder(BST[num-1]) << endl;
}

void Cleave(int num){
	printNGuests(num);
}

void simulate(string filename)
{
	int ID;
	int keiteiken, num;
	ifstream ss(filename);
	string line, maxsize,name, kei;
	while(ss >> line)
	{ 
		if(line == "MAXSIZE")
		{
			ss >> maxsize;
			MAXSIZE = stoi(maxsize); 
			for(int i = 0; i < MAXSIZE; i++){
				Node* tree;
				TrongCay(tree);
				BST.push_back(tree);
			}
			areas.resize(MAXSIZE, 0);
	    	}else if(line == "LAPSE") {
	    		ss>>name;
	    		if(Lapse(name, n)){
	    			// cout << Result[n] << "%" << MAXSIZE <<"+1" << endl;
	    			ID = Result[n] % MAXSIZE + 1;
		    		LapseNext(n, ID);
		    		n++;
		    	}
	    	}else if(line == "KOKUSEN"){
	    		kokusen();
	    	}else if(line == "KEITEIKEN"){
	    		ss>>keiteiken;
	    		Keiteiken(keiteiken);
	    	}else if(line == "HAND"){
	    		Hand(n);
	    	}else if(line == "LIMITLESS"){
	    		ss>>num;
	    		Limitless(num);
	    	}else if(line == "CLEAVE"){
	    		ss>>num;
	    		Cleave(num);
	    	}
	}
	// cout << "-----------------------------------------"<<endl;
	// cout << "Nha` G: ";
	// for(int i = 0; i < G.size(); i++){
	// 	cout << G[i];
	// }
	// cout << endl;
	// cout << "Nha` S: ";
	// for(int i = 0; i < S.size(); i++){
	// 	cout << S[i];
	// }
	// cout << endl;
	// for(int k = 0; k < n; k++){
		// InOrder(BST[k]);
		// printInOrder(k);
		// cout << Result[k] << endl;
		// khach[k].Print();
	// }
	// printHeap();
}