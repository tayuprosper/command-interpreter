#include <string>
#include <vector>

using namespace std;
vector<string> get_tokens(string& s){
    vector<string> t;
    string f;
    int i = 0;

   for (const char c : s)
    {
        if (c == ' ' || c == '\0'){
            t.push_back(f);
            f.clear();
            continue;
        };
        f.append(string(1,c));
    }
    t.push_back(f);
    
    return t;
}