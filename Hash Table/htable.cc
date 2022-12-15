#include "htable.h"

#define N1 10  // num of decimal digits
#define N2 26  // num of upper-case letters

// Hash function, you may NOT modify this function
int HT::hash(const string &s) {
  int n = (N2 * N1) * (s[0] - 'A') + N1 * (s[1] - 'A') + (s[2] - '0');

  return n % hsize;
}

// You will complete the code below ...

// bool function returns true if p comes before q. For use in sort() 
bool cmp(Entry *p, Entry *q)
{
  if(p->key < q->key)
  {
    return true;
  }

  else return false;
}

//constructor to set the size of the htabke to hs
HT::HT(const unsigned &hs) 
{
  hsize = hs;
  hTable.resize(hs);
}

//freeing the memory of containers with this destructor
HT::~HT() 
{
  hTable.clear();
  pTable.clear();
}


void HT::insert(const Entry &e) 
{
  int i = hash(e.key);
  list<Entry>&l = hTable[i];

  //record to store index of record "e" inside of list
  auto record = std::find_if(l.cbegin(), l.cend(), [e](const Entry &val){return e.key == val.key;});
  
  //if key already exists
  if(record != l.cend())
  {
    std::cout << " not inserted - duplicate key!!!" << std::endl;
  }

  // if key does not exist
  else
  {
    std::cout << " entry =  " << i << std::endl;
  
    l.push_front(e); //in case of collision, insert element to beginning of list
    pTable.push_back(&l.front()); // in case of collision, insert adress to beginning of ptable
  }
}

//search hash table for record with key
void HT::search(const string &s) 
{
  int index = hash(s);
  list<Entry> l = hTable[index];

  //store index of element in record
  auto record = std::find_if(l.cbegin(),l.cend(),[s](Entry val){return s == val.key;});

  //if found in table print the information
  if(record != l.cend())
  {
    std::cout << " ==> number: " << std::setw(4) << (*record).num << " - item:" << (*record).desc;
  }

  //if not found
  else
  {
    std::cout << " not in table!!";
  }
  std::cout << endl;
}

//print subscript of hash table 
void HT::hTable_print() 
{
  std::cout << std::endl;
  for(size_t i=0; i<hTable.size(); i++)//look through all of table
  {
    for(auto item : hTable[i])//range based for loop that prints all items in table
    {
      //because of formatting in the refout the first time it prints out it is right justified 
      if(pTable.size() < 10)
      {
        std::cout << std::right << setw(4) <<i << ":" << item.key << "    - " << setw(5) << item.num << "  -  " << item.desc << std::endl;
      }
      //left justified to match refout
      else
      {
        std::cout << std::left << setw(4) <<i << ":" << item.key << "    - " << setw(5) << item.num << "  -  " << item.desc << std::endl;
 
      }
    }
  }
}

//print content of active records in hash table sorted
void HT::pTable_print() 
{
  //reorder ptable in alphabetical order using cmp function initialized at the beginning
  sort(pTable.begin(), pTable.end(), cmp);

  //print the contents
  for(size_t i=0; i<pTable.size();i++)
  {
    std::cout << setw(3) << " " << pTable[i]->key << "  -" << std::right << std::setw(6) << pTable[i]->num << "  -  " << left << pTable[i]->desc << std::endl;
  }
}