#include <bits/stdc++.h>
using namespace std;
#include "BST.cpp"



vector<string> parse;
void split (string str, char seperator)  
{  
    parse.clear();
    int currIndex = 0, i = 0;  
    int startIndex = 0, endIndex = 0;  
    while (i <= str.length())  
    {  
        if (str[i] == seperator || i == str.length())  
        {  
            endIndex = i;
            parse.push_back(str.substr(startIndex,endIndex-startIndex));
            startIndex = endIndex + 1;  
        }  
        i++;  
        }     
}  

int main(){
	int i,j,k,N,t;
	cout<<"Would you like to test the first part(0)? or the second(1)?"<<endl;
	cin>>t;
	if(t){
		cout<<"Enter the number of Nodes, you'd like to have?";
		cin>>N;
		BST *b1 = new BST();
		set<int> js,ks;
		for(i = 0;i<N;i++){
			do{
				j = rand();
				k = rand() % 100000;
			}while(js.find(j)==js.end() && ks.find(k)==ks.end());
			b1->insert(j,k);
			js.insert(j);
			ks.insert(k);
		}
		b1->customStore("test.ser");
		BST *b2 = new BST();
		b2->customLoad(LOAD_FULL_BST,"test.ser");
		b1->getBST("");
		b2->getBST("");
		if(b1->getResult()==b2->getResult()){
			cout<<"Storing-Loading Works For FULL BST :)"<<endl;
		}else{
			cout<<"Storing-Loading Doesn't Work :("<<endl;
		}
	}else{
		BST *b = new BST();
		string s;
		while(true){
			cout<<">>>";
			getline(cin,s);
			split(s,' ');
			if(parse[0]=="ADD"){
				if(b->insert(stoi(parse[1]),stoi(parse[2]))){
					cout<<"SUCCESSFULLY INSERTED!"<<endl;
				}else{
					cout<<"INSERTION FAILED!"<<endl;
				}
			}else if(parse[0]=="DEL"){
				if(b->remove(stoi(parse[1]),stoi(parse[2]))){
					cout<<"SUCCESSFULLY DELETED!"<<endl;
				}else{
					cout<<"JOURNEY NOT FOUND!"<<endl;
				}
			}else if(parse[0]=="FIND"){
				if(b->find(stoi(parse[1]),stoi(parse[2]))){
					cout<<"JOURNEY FOUND!"<<endl;
				}else{
					cout<<"JOURNEY NOT FOUND!"<<endl;
				}
			}else if(parse[0]=="TRAVERSE"){
				if(parse[1]!="PRE" && parse[1]!="POST" && parse[1]!="IN"){
					cout<<"INVALID REQUEST!"<<endl;
				}
				int x = (parse[1]=="PRE")?0 : ((parse[1]=="POST")?1:2);
				b->traverse(x);
			}else if(parse[0]=="GETMIN"){
				cout<<b->getMinimum()<<endl;
			}else if(parse[0]=="BOUNDS"){
				cout<<b->countJourneysInPriceBound(stoi(parse[1]),stoi(parse[2]))<<endl;
			}else if(parse[0]=="PRINT"){
				b->printBST("");
			}else{
				cout<<"INVALID REQUEST"<<endl;
			}

		}
	}

}
