#include <iostream>
#include <string>
#include <queue>

#define numSteps 25

using namespace std;


/*run: a.out < names.txt */
int main(){
    srand(time(0));
    vector<string> shoppers = vector<string>();
    string line;
    getline(cin, line);
    while(!cin.bad() && ! cin.eof() && !line.empty()){
        shoppers.emplace_back(line);
        getline(cin, line);
    }

    queue<string> waitlist = queue<string>();
    for(int i=0; i < numSteps; i++){
        if(waitlist.empty() || rand() & 1){
            int index = rand() % shoppers.size();
            string enter = shoppers[index];
            shoppers.erase(shoppers.begin() + index);
            waitlist.emplace(enter);
            cout << enter << " gets in line." << endl;
        }
        else{
            string leave = waitlist.front(); waitlist.pop();
            shoppers.push_back(leave);
            cout << leave << " finishes checking out." << endl;
        }
    }
    return 0;
}