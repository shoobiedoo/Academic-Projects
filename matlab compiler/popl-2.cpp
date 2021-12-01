//doing it for only structs and basic not arrays arrays will be implemented later
//free the popple
#include <bits/stdc++.h> 
#include <unordered_map> 
#include <map> 
#include <string> 
#include <fstream>
using namespace std;
map < string, string > umap;
map < string, string > struct_map;
map < string, string > array_map;
map < string, int > return_val;
map < string, int > argument_val;
map <string ,string> function_map_ret;
map <string,string> function_map_arg;
vector<pair<string,string> > inte ;
void printout(map < int, string > & mapp) {
  for (auto x: mapp)
    cout << x.first << " " << x.second << endl;
}
void processLine(const string & line1) {
  string line = line1;
  int leftidentifier = 0;
  int rightindentifier = 0;
  int expression;
  int floating = 0;
  string left = "";
  string right = "";
  int other = 0, digit = 0;
  int space_index = 0;
  int firstpart;
  while (line[leftidentifier] != '=') {
    /*if(leftidentifier==' ')
	{
		//space_index=leftidentifier;
		other=1;
	}*/
    left += line[leftidentifier];
    leftidentifier++;
  } //cout<<left<<endl;

  rightindentifier = leftidentifier + 1;
  while (rightindentifier != line.length()) {
    right += line[rightindentifier];
    rightindentifier++;
  }

  if (other == 0) {
    int i = 0;
    int c = 0;
    if (umap.find(left) == umap.end()) {
      while (i != right.length()) {
        if (right[i] == '\'') {
          umap[left] = "char";
          break;
        } else if (isdigit(right[i]) != 0 || right[i] == '.') {
          digit = 1;
          if (right[i] == '.') {
            floating = 1;
            umap[left] = "float";
          }
        } else if (right[0] == 's') {
          struct_map[left] = right;
          umap[left] = "struct";
          break;
        } else if (right[i] == '[') {
          array_map[left] = right;
          umap[left] = "array";
          break;
        } else {
          if (right[0] == '\"') {
            umap[left] = "string";
            break;
          }
        }
        i++;
      }

      if (floating == 0 && digit == 1)
        umap[left] = "int";
    }
  }
  if (other == 1) //this for parsing of a function  
  {

  }
}
//one d array equivalence
string array_structural_equivalence(string s1, string s2) {

  string rights1 = array_map[s1];
  string rights2 = array_map[s2];
  //cout<<rights2<<endl;
  int floating = 0;
  int digit = 0;
  int i1 = 1;
  int c1 = 1;
  string ans1;
  string right = "";
  //cout<<"ok"<<rights1<<endl;
  while (i1 != rights1.length() - 1) {
    if (rights1[i1] == ' ')
      c1++;
    else {
      if (c1 == 1) {
        int i = 0;
        right = right + rights1[i1];
        if (rights1[i1 + 1] == ' ') {
          //cout<<right
          while (i != right.length()) {
            if (right[i] == '\'') {
              ans1 = "char";
              break;
            } else if (isdigit(right[i]) != 0 || right[i] == '.') {
              digit = 1;
              if (right[i] == '.') {
                floating = 1;
                ans1 = "float";
                break;
              }
            } else {
              if (right[0] == '\"') {
                ans1 = "string";
                break;
              }
            }
            i++;
          }
          if (floating == 0 && digit == 1)
            ans1 = "int";
        }
      }
    }
    i1++;
  }
  //cout<<"ans1="<<ans1<<endl;

  floating = 0;
  digit = 0;

  int i2 = 1;
  int c2 = 1;
  string ans2 = "";
  string right2 = "";
  //cout<<"ok"<<rights2<<endl;
  while (i2 != rights2.length() - 2) {
    if (rights2[i2] == ' ')
      c2++;
    else {
      if (c2 == 1) {
        int i = 0;
        right2 = right2 + rights2[i2];
        if (rights2[i2 + 1] == ' ') {
          //cout<<right2<<endl;
          while (i != right2.length()) {
            if (right2[i] == '\'') {
              ans2 = "char";
              break;
            } else if (isdigit(right2[i]) != 0 || right2[i] == '.') {
              digit = 2;
              if (right2[i] == '.') {
                floating = 2;
                ans2 = "float";
                break;
              }
            } else {
              if (right2[0] == '\"') {
                ans2 = "string";
                break;
              }
            }
            i++;
          }
          if (floating == 0 && digit == 2)
            ans2 = "int";
        }
      }
    }
    i2++;
  }
  //cout<<"ans2"<<ans2<<endl;
  //cout<<c1<<" "<<c2<<endl;
  //cout<<"ok"<<" "<<ans1<<" "<<ans2<<"ok"<<endl;
  if (c1 == c2 && ans1 == ans2)
    return "Y";
  else
    return "N";

}
string struct_structural_equivalence(string s1, string s2) {
  //table method for structural equivalence of structs
  //it will only involve one iteration as there are no pointers in our grammar	
  string rights1 = struct_map[s1];
  string rights2 = struct_map[s2];
  map < string, string > maps1;
  map < string, string > maps2;
  int lowers1 = 7, lowers2 = 7;
  int uppers1 = rights1.length() - 2;
  int uppers2 = rights2.length() - 2;
  int digit = 0, floating = 0;

  while (lowers1 <= uppers1) {
    floating = 0;
    digit = 0;
    if (rights1[lowers1] == '\'') {
      lowers1++;
      string temp = "";
      while (rights1[lowers1] != '\'') {
        temp += rights1[lowers1];
        lowers1++;
      }
      lowers1 += 2;
      int d = 0;
      //cout<<endl;
      //cout<<lowers1<<" "<<rights1[lowers1];

      if (rights1[lowers1] == '\'') {
        maps1[temp] = "char";
        //lowers1++;
      } else if (isdigit(rights1[lowers1]) != 0) { //lowers1++;
        digit = 1;
        //	cout<<"okokok";
        while (rights1[lowers1] != ',' && rights1[lowers1] != ')') {
          if (rights1[lowers1] == '.') {
            floating = 1;
            maps1[temp] = "float";
          }

          lowers1++;
        }
      } else {

        if (rights1[lowers1] == '\"') {
          maps1[temp] = "string";

        }
        //lowers1++;
      }

      while ((rights1[lowers1] != ',' && rights1[lowers1] != ')'))
        lowers1++;
      if (floating == 0 && digit == 1)
        maps1[temp] = "int";

      //cout<<endl<<" "<<temp;//testing debugging sorry for shotting in the code
      //cout<<endl<<" "<<rights1[lowers1];
      lowers1 += 1;
      //cout<<endl<<" "<<rights1[lowers1];
    }

  }
  //printout(maps1);
  digit = 0;
  floating = 0;

  while (lowers2 <= uppers2) {
    floating = 0;
    digit = 0;
    if (rights2[lowers2] == '\'') {
      lowers2++;
      string temp = "";
      while (rights2[lowers2] != '\'') {
        temp += rights2[lowers2];
        lowers2++;
      }
      lowers2 += 2;
      int d = 0;

      if (rights2[lowers2] == '\'') {
        maps2[temp] = "char";

      } else if (isdigit(rights2[lowers2]) != 0) {
        digit = 2;
        while (rights2[lowers2] != ',' && rights2[lowers2] != ')') {
          if (rights2[lowers2] == '.') {
            floating = 2;
            maps2[temp] = "float";
          }
          lowers2++;
        }
      } else {
        if (rights2[lowers2] == '\"') {
          maps2[temp] = "string";
        }
      }
      while ((rights2[lowers2] != ',' && rights2[lowers2] != ')'))
        lowers2++;
      if (floating == 0 && digit == 2)
        maps2[temp] = "int";
      lowers2 += 1;

    }

  }
  //cout<<endl;
  int c1 = 0;
  int c2 = 0;
  int c3 = 0;
  int flag = 0;
  //printout(maps2);

  for (auto x: maps1) {
    c1++;
  }
  for (auto y: maps2) {
    c2++;
  }
  if (c1 == c2) {
    for (auto x = maps1.begin(), y = maps2.begin(); x != maps1.end(); ++x, ++y) {
      //do something
      if (x -> second == y -> second)
        c3++;
    }
    if (c3 == c1)
      return "Y";
    else
      return "N";
  } else {
    return "N";
  }
}
string function_equivalence(string s1, string s2)
{
    string rights1 = function_map_arg[s1];
  string rights2 = function_map_arg[s2];
  //cout << rights1 << " " << rights2;
  map < int, string > maps1;
  map < int, string > maps2;
  int lowers1 = 1, lowers2 = 1;
  int uppers1 = rights1.length() - 2;
  int uppers2 = rights2.length() - 2;
  int digit = 0, floating = 0;
  int temp=0;

  while (lowers1 <= uppers1) {
    floating = 0;
    digit = 0;
    
      int d = 0;
      //cout<<endl;
      //cout<<lowers1<<" "<<rights1[lowers1];

      if (rights1[lowers1] == '\'') {
        maps1[temp] = "char";
        //lowers1++;
      } else if (isdigit(rights1[lowers1]) != 0) { //lowers1++;
        digit = 1;
        //	cout<<"okokok";
        while (rights1[lowers1] != ',' && rights1[lowers1] != ')') {
          if (rights1[lowers1] == '.') {
            floating = 1;
            maps1[temp] = "float";
          }

          lowers1++;
        }
      } else {

        if (rights1[lowers1] == '\"') {
          maps1[temp] = "string";

        }
        //lowers1++;
      }

      while ((rights1[lowers1] != ',' && rights1[lowers1] != ')'))
        lowers1++;
      if (floating == 0 && digit == 1)
        maps1[temp] = "int";

      //cout<<endl<<" "<<temp;//testing debugging sorry for shotting in the code
      //cout<<endl<<" "<<rights1[lowers1];
      lowers1 += 1;
      temp++;
      //cout<<endl<<" "<<rights1[lowers1];
    }

  
  //printout(maps1);
  digit = 0;
  floating = 0;
  temp=0;

  while (lowers2 <= uppers2) {
    floating = 0;
    digit = 0;
   
      if (rights2[lowers2] == '\'') {
        maps2[temp] = "char";

      } else if (isdigit(rights2[lowers2]) != 0) {
        digit = 2;
        while (rights2[lowers2] != ',' && rights2[lowers2] != ')') {
          if (rights2[lowers2] == '.') {
            floating = 2;
            maps2[temp] = "float";
          }
          lowers2++;
        }
      } else {
        if (rights2[lowers2] == '\"') {
          maps2[temp] = "string";
        }
      }
      while ((rights2[lowers2] != ',' && rights2[lowers2] != ')'))
        lowers2++;
      if (floating == 0 && digit == 2)
        maps2[temp] = "int";
      lowers2 += 1;
temp++;
    }


  //cout<<endl;
  int c1 = 0;
  int c2 = 0;
  int c3 = 0;
  int flag = 0;
  //printout(maps2);

  for (auto x: maps1) {
    c1++;
  }
  for (auto y: maps2) {
    c2++;
  }
  if (c1 == c2) {
    for (auto x = maps1.begin(), y = maps2.begin(); x != maps1.end(); ++x, ++y) {
      //do something
      if (x -> second == y -> second)
        c3++;
    }
    if (c3 == c1)
      return "Y";
    else
      return "N";
  } else {
    return "N";
  }
}
void equivalencematrix() {
  //store this in a matrix would be neater 
  //and the matrix can be used for later purposes
  // that is the part 2 of the asignment
  cout << endl << "DETERMINING STRUCTURAL EQUIVALENCE:" << endl;
  cout << "  ";
  for (auto x: umap)
    cout << x.first << " ";
  cout << endl;
  for (auto x: umap) {
    cout << x.first << " ";
    for (auto y: umap) {
		if(x == y)
		{
			cout << "Y ";
		}
      else if (umap[x.first] == umap[y.first] && umap[x.first] != "struct" && umap[x.first] != "array" && umap[x.first] != "function")
	  {
        cout << "Y" << " ";
	  }
      else if (umap[x.first] == umap[y.first] && umap[y.first] == "struct") {
        //cout<<x.first;
        cout << struct_structural_equivalence(x.first, y.first) << " ";
      } else if (umap[x.first] == umap[y.first] && umap[y.first] == "array") {
        //cout<<x.first;
        cout << array_structural_equivalence(x.first, y.first) << " ";
      } else if(umap[x.first] == umap[y.first] && umap[x.first] == "function")
	  {
		  if(return_val[x.first] == return_val[y.first] && argument_val[x.first] == argument_val[y.first])
		  {
			  if(function_equivalence(x.first, y.first) == "Y")
			  	cout << "Y ";
				else
				cout << "N ";
		  }
		  else
		  {
			  cout << "N ";
		  }
	  }
	  else
        cout << "N" << " ";

    }
    cout << endl;
  }
}

int processfunc(string s)
{
	int num_ret = 1, num_arg = 0;
	int flag = 0;
	int index;
	string name = "";
    int index_space;
	for(int i = 0; i < s.size(); i++)
	{
		if(flag == 0 && s[i] == ',')
		{
			num_ret++;
		}
		if(s[i] == '=')
		{
			flag = 1;
			index = i;
		}
        if(s[i] == ' ')
        {
            index_space = i;
        }
		if(s[i] == ',' && flag == 1)
		{
			num_arg++;
		}
	}
	for(int i = index + 1; ; i++)
	{
		if(s[i] != '(')
		{
			name += s[i];
		}
		else
		{
			break;
		}
	}
    int index_equal;
    string return_par = "";
    for(int i = index_space + 1;  ; i++)
    {
        return_par += s[i];
        if(s[i] == '=')
        {
            index_equal = i;
            break;
        }
    }
    string argument_par = "";
    int flag1 = 0;
    for(int i = index_equal; ; i++)
    {
        if(s[i] == '(')
        {
            argument_par += s[i];
            flag1 = 1;
        }
        else if(flag1)
        {
            argument_par += s[i];
        }
        if(s[i] == ')')
        {
            
            break;
        }
    }

	if(num_arg == 0)
	{
		num_arg = 1;
	}
	else
	{
		num_arg++;
	}
    function_map_ret[name] = return_par;
    function_map_arg[name] = argument_par;
	cout << name << " " << num_ret << " " << num_arg << endl;
	umap[name] = "function";
	return_val[name] = num_ret;
	argument_val[name] = num_arg;
}
int main() {
  ifstream file("engsent"); //file just has some sentences
  if (!file) {
    cout << "unable to open file";
    return 0;
  }
  string sent;
  while (getline(file, sent)) {
   cout << sent << endl;
	string s = "";
	int i = 0;
	while(sent[i] != ' ' && sent[i] != '=' && i < sent.size())
	{
		s += sent[i++];
	}
    cout << s << endl;
	if(s == "function")
	{
		processfunc(sent);
        continue;
	}
    int num = 0;
    for(i = 0; i < sent.size(); i++)
    {
        if(sent[i] == '=')
        {
            num++;
        }
    }
    //cout << num << endl;
    string a = "",b = "";
    int index;
    if(num > 1)
    {
        for(int j = 0; j < sent.size(); j++)
        {
            if(sent[j] != ','){
            a = a + sent[j];

            }
            else{
                            index = j;
            break;
            }
        }
        for(int j = index + 1; j < sent.size(); j++)
        {
            b += sent[j];
        }
       cout << a  << " " << b <<  endl;
        string name_a = "", name_b = "";
        for(int j = 0 ; j < a.size(); j++)
        {
            if(a[j] != '=')
            {
                            name_a += a[j];
            }
            else
                break;

        }
        for(int j = 0 ; j < b.size(); j++)
        {
            if(b[j] != '=')
            {
                            name_b += b[j];
                            
            }
            else
            break;
        }
        cout << name_a << " " << name_b << endl;
    inte.push_back(make_pair(name_a,name_b));
    inte.push_back(make_pair(name_b,name_a));
    //inte[name_b] = name_a;
    //internal1.push_back(make_pair(name_b, name_a));
    cout << "error" << endl;
        processLine(a);
        processLine(b);
        continue;

    }
    processLine(sent);
  }
  equivalencematrix();

  //printout();
  return 0;
}

/*

1 . Name equivalence is used for basic data types
2 . Structural equivalence is used for structures
3 . Structural equivalence is used for arrays
4 . Structural equivalence is used for functions
5 . Internal name equivalence is used in a special case(when two basic data types are defined on the same line seperated by a comma) for basic data types


*/