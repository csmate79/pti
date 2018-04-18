#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <map>
#include <algorithm>
#include <ctime>
#include <set>
#include <boost/algorithm/string.hpp>

using namespace std;
using namespace boost;

bool isInteger(const string &s)
{
   if(s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+')))
    return false;

   char * p ;
   strtol(s.c_str(), &p, 10) ;

   return (*p == 0) ;
}

bool isExist(const string fileName){
    ifstream infile(fileName);
    return infile.good();
  }

vector<vector<string>> readFile(const string datab){
  ifstream data(datab);
  string temp, temp2;
  vector<vector<string>> database;
  vector<string> vTemp;

  char ch;
  while(data.get(ch)){
    if(ch == '\n'){
      vector<string> vTemp ,vTemp2;

      char ch;
      while(data.get(ch)){
        if(ch == '\n'){
          split(vTemp2, temp, is_any_of(","));
          database.push_back(vTemp2);
          temp = "";
        } else {
          if(ch != '\"')
            temp += ch;
        }
      }
    } else {
      if(ch != '\"')
        temp += ch;
    }
  }

  return database;
}

  string getPropsFile(const string path){
    string props, temp;
    stringstream ss(path);
    vector<string> v;
    while(getline(ss, temp, '/')){
      v.push_back(temp);
    }
    props = path + "/" + v[v.size() - 1] + ".props";

    return props;
  }


  int getPoints(const string path) {
    if(!(path.find("Esport") != string::npos)){
    int pont = 0;
    char ch;
    string fileName = getPropsFile(path), temp, temp2;

    if(isExist(fileName)){
      ifstream data(fileName);
      while(data.get(ch)){
        if(ch == '\n'){
          stringstream ss(temp);
          while(getline(ss, temp2, ' ')){
            if(isInteger(temp2))
              pont += stoi(temp2);
          }
          temp = "";
        } else {
        if(ch != '\"')
          temp += ch;
          }
        }
      }
      return pont;
    }
    return 0;
  }


 string getJegy(string s){
   stringstream ss(s);
   string sTemp, vedes = "error";
   vector<string> vTemp;
   while(getline(ss, sTemp, '/')){
     vTemp.push_back(sTemp);
   }
  if(vTemp[0] == "I")
    vedes = "1";
  else if(vTemp[0] == "II")
    vedes = "2";
  else if(vTemp[0] == "III")
    vedes = "3";

  if(vTemp[1] == "elégséges")
    return vedes + " 2";
  else if(vTemp[1] == "közepes")
    return vedes + " 3";
  else if(vTemp[1] == "jó")
    return vedes + " 4";
  else if(vTemp[1] == "jeles")
    return vedes + " 5";
 }

 multimap<string, string> getVedes(const vector<vector<string>> database)
 {
   multimap<string, string> vedesek;
   string sTemp;
   vector<string> vTemp;

   for(int i = 0; i < database.size(); i++){
     stringstream ss(database[i][1]);
     while(getline(ss, sTemp, '/')){
       vTemp.push_back(sTemp);
     }
     if(vTemp[vTemp.size() - 3] == "Védés"){
       vedesek.insert(pair<string, string>(database[i][0], getJegy(database[i][1].substr(database[i][1].find("Védés") + 8))));
     }
   }
   return vedesek;
 }

 multimap<string, int> getJegyek(multimap<string, string> vedesek){
   multimap<string, int> jegyek;
   map<string, int> legnagyobb;
   string temp;
   vector<string> vTemp;
   for(int i = 1; i < 4; i++){
       for(auto const& vedes: vedesek){
           stringstream ss(vedes.second);
           while(getline(ss, temp, ' ')){
             vTemp.push_back(temp);
           }
           if((stoi(vTemp[0]) == i) && (legnagyobb.find(vedes.first) == legnagyobb.end())){
             jegyek.insert(pair<string, int>(vedes.first, stoi(vTemp[1])));
             legnagyobb[vedes.first] = stoi(vTemp[1]);
           } else if((stoi(vTemp[0]) == i) && !((legnagyobb.find(vedes.first)) == legnagyobb.end())){
             if(legnagyobb[vedes.first] <= stoi(vTemp[1])) {
               for(auto const& jegy: jegyek){
                 if((jegy.first == vedes.first) && (jegy.second == legnagyobb[vedes.first])){
                   jegyek.erase(jegy.first);
               }
             }
               legnagyobb.erase(vedes.first);
               legnagyobb[vedes.first] = stoi(vTemp[0]);
               jegyek.insert(pair<string, int>(vedes.first, stoi(vTemp[1])));
             }
           }
           vTemp.clear();
       }

       legnagyobb.erase(legnagyobb.begin(), legnagyobb.end());
   }
   return jegyek;
 }

int main(int argc, char** argv)
{
  srand((unsigned)time(0));

  set<string> osszesFeladat;

  vector<string> osszesV(osszesFeladat.size());
  vector<vector<string>> database =  readFile(argv[1]);
  vector<string> vTemp;



  string kapcsolo = argv[2];
  string temp;

  map<string, int> pontok, legnagyobb, vegsoJegyek;
  multimap<int, string> forditva;
  multimap<string, string> vedesek = getVedes(database);
  multimap<string, int> jegyek = getJegyek(vedesek);

  int i = 0;

  for(i = 0; i < database.size(); i++){
    pontok[database[i][0]] = 0;
    osszesFeladat.insert(database[i][1]);
  }

  copy(osszesFeladat.begin(), osszesFeladat.end(), back_inserter(osszesV));

  for(i = 0; i < database.size(); i++){
    pontok[database[i][0]] += getPoints(database[i][1]);
  }


  for(auto const& value: pontok){
    forditva.insert(pair<int, string>(value.second, value.first));
  }

  i = 0;
  int top = 20;

  if(kapcsolo == "--pont"){
    if(argv[3]){
      top = stoi(argv[3]);
    }

  for(auto value = forditva.rbegin(); value != forditva.rend(); ++value){
    cout << i + 1 << ": " << value->second << ": " << value->first << endl;
    if(i == top - 1)
      break;
    i++;
    }
  }

  else if(kapcsolo == "--trad-lab-mark"){
    for(auto const& vedes: jegyek){
      if(vegsoJegyek.find(vedes.first) != vegsoJegyek.end()){
      	 if(round(double(vedes.second)/double(jegyek.count(vedes.first))) / 10 > 0.5)
			vegsoJegyek[vedes.first] += vedes.second;
		else{
			vegsoJegyek[vedes.first] += vedes.second - 1;

		}
      } else {
        	vegsoJegyek[vedes.first] = vedes.second;
      }
    }

      for(int j = 5; j > 0; j--){
        for(auto const& vedes: vegsoJegyek){
          if(round(double(vedes.second)/double(jegyek.count(vedes.first))) == j)

            	cout << vedes.first << " " << round(double(vedes.second)/double(jegyek.count(vedes.first))) << endl;
          	}

        }
      }
    }
