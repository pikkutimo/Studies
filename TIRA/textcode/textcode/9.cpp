/* Program extracts from Chapter 9 of
   "Data Structures and Program Design in C++"
   by Robert L. Kruse and Alexander J. Ryba
   Copyright (C) 1999 by Prentice-Hall, Inc.  All rights reserved.
   Extracts from this file may be used in the construction of other programs,
   but this code will not compile or execute as given here. */


// Section 9.5:

template <class Record>
class Sortable_list: public List<Record> {
public:   //   sorting methods
   void radix_sort();
   //   Specify any other sorting methods here.
private:  //   auxiliary functions
   void rethread(Queue queues[]);
};


class Record {
public:
   char key_letter(int position) const;
   Record();                    //  default constructor
   operator Key() const;        //  cast to Key
//   Add other methods and data members for the class.
};


const int max_chars = 28;
template <class Record>
void Sortable_list<Record>::radix_sort()
/*
Post: The entries of the Sortable_list have been sorted
      so all their keys are in alphabetical order.
Uses: Methods from classes List, Queue, and Record;
      functions position and rethread.
*/
{
   Record data;
   Queue queues[max_chars];
   for (int position = key_size - 1; position >= 0; position--) {
      //   Loop from the least to the most significant position.
      while (remove(0, data) == success) {
         int queue_number = alphabetic_order(data.key_letter(position));
         queues[queue_number].append(data);    //   Queue operation.
      }
      rethread(queues);                        //   Reassemble the list.
   }
}


int alphabetic_order(char c)
/*
Post: The function returns the alphabetic position of character c,
      or it returns 0 if the character is blank.
*/
{
   if (c == ' ') return 0;
   if ('a' <= c && c <= 'z') return c - 'a' + 1;
   if ('A' <= c && c <= 'Z') return c - 'A' + 1;
   return 27;
}


template <class Record>
void Sortable_list<Record>::rethread(Queue queues[])
/*
Post: All the queues are combined back to the Sortable_list, leaving
      all the queues empty.
Uses: Methods of classes List and Queue.
*/
{
   Record data;
   for (int i = 0; i < max_chars; i++)
      while (!queues[i].empty()) {
         queues[i].retrieve(data);
         insert(size(), data);
         queues[i].serve();
      }
}



// Section 9.6:

class Key: public String{
public:
    char key_letter(int position) const;
    void make_blank();
    //  Add constructors and other methods.
};


int hash(const Key &target)
/*
Post: target has been hashed, returning a value between 0 and hash_size-1.
Uses: Methods for the class Key.
*/
{
   int value = 0;
   for (int position = 0; position < 8; position++)
      value = 4 * value + target.key_letter(position);
   return value % hash_size;
}


const int hash_size = 997;   //  a prime number of appropriate size
class Hash_table {
public:
   Hash_table();
   void clear();
   Error_code insert(const Record &new_entry);
   Error_code retrieve(const Key &target, Record &found) const;
private:
   Record table[hash_size];
};


Error_code Hash_table::insert(const Record &new_entry)
/*
Post: If the Hash_table is full, a code of overflow is returned.
      If the table already contains an item with the key of new_entry
      a code of duplicate_error is returned.  Otherwise: The Record new_entry
      is inserted into the Hash_table and success is returned.
Uses: Methods for classes Key and Record, the function hash.
*/
{
   Error_code result = success;
   int probe_count,           //  Counter to be sure that table is not full.
       increment,             //  Increment used for quadratic probing.
       probe;                 //  Position currently probed in the hash table.
   Key null;                   //  Null key for comparison purposes.
   null.make_blank();

   probe = hash(new_entry);
   probe_count = 0;
   increment = 1;

   while (table[probe] != null              //   Is the location empty?
     && table[probe] != new_entry           //   Duplicate key?
     && probe_count < (hash_size + 1) / 2) {//   Has overflow occurred?
      probe_count++;
      probe = (probe + increment) % hash_size;
      increment += 2;                  //     Prepare increment for next iteration.
   }
   if (table[probe] == null) table[probe] = new_entry; //   Insert new entry.
   else if (table[probe] == new_entry) result = duplicate_error;
   else result =  overflow;                                   //   The table is full.
   return result;
}


class Hash_table {
public:
   //  Specify methods here.
private:
   List<Record> table[hash_size];
};



// Section 9.9:

class Life {
public:
   //  methods
private:
   bool map[int][int];
   //  other data and auxiliary functions
};


int main()  //  Program to play Conway's game of Life.
/*
Pre:
The user supplies an initial configuration of living cells.
Post: The program prints a sequence of pictures showing the changes in
      the configuration of living cells according to the rules for
      the game of Life.
Uses: The class Life and its methods initialize(), print() and update().
      The functions  instructions(),  user_says_yes().
*/
{
   Life configuration;
   instructions();
   configuration.initialize();
   configuration.print();
   cout << "Continue viewing new generations? " << endl;
   while (user_says_yes()) {
      configuration.update();
      configuration.print();
      cout << "Continue viewing new generations? " << endl;
   }
}


struct Cell {
   Cell() { row = col = 0; }   //  constructors
   Cell(int x, int y) { row = x;  col = y; }
   int row, col;               //   grid coordinates
};


class Hash_table {
public:
   Error_code insert(Cell *new_entry);
   bool retrieve(int row, int col) const;
private:
   List<Cell *> table[hash_size];
};


class Life {
public:
   Life();
   void initialize();
   void print();
   void update();
   ~Life();

private:
   List<Cell *> *living;
   Hash_table *is_living;
   bool retrieve(int row, int col) const;
   Error_code insert(int row, int col);
   int neighbor_count(int row, int col) const;
};


void Life::update()
/*
Post: The Life object contains the next generation of configuration.
Uses: The class Hash_table and the class Life and its auxiliary functions.
*/
{
   Life new_configuration;
   Cell *old_cell;
   for (int i = 0; i < living->size(); i++) {
      living->retrieve(i, old_cell);      //  Obtain a living cell.
      for (int row_add = -1; row_add < 2; row_add ++)
         for (int col_add = -1; col_add < 2; col_add++) {
            int new_row = old_cell->row + row_add,
                new_col = old_cell->col + col_add;
//  new_row, new_col is now a living cell or a neighbor of a living cell,

            if (!new_configuration.retrieve(new_row, new_col))
               switch (neighbor_count(new_row, new_col)) {
               case 3:  //  With neighbor count 3, the cell becomes alive.
                  new_configuration.insert(new_row, new_col);
                  break;

               case 2:  //  With count 2, cell keeps the same status.
                  if (retrieve(new_row, new_col))
                     new_configuration.insert(new_row, new_col);
                  break;

               default: //  Otherwise, the cell is dead.
                  break;
               }
         }
   }

//  Exchange data of current configuration with data of new_configuration.
   List<Cell *> *temp_list = living;
   living = new_configuration.living;
   new_configuration.living = temp_list;
   Hash_table *temp_hash = is_living;
   is_living = new_configuration.is_living;
   new_configuration.is_living = temp_hash;
}


void Life::print()
/*
Post: A central window onto the Life object is displayed.
Uses: The auxiliary function Life::retrieve.
*/
{
   int row, col;
   cout << endl << "The current Life configuration is:" << endl;
   for (row = 0; row < 20; row++) {
      for (col = 0; col < 80; col++)
         if (retrieve(row, col)) cout << '*';
         else cout << ' ';
      cout << endl;
   }
   cout << endl;
}


Error_code Life::insert(int row, int col)
/*
Pre:  The cell with coordinates row and col does not
      belong to the Life configuration.
Post: The cell has been added to the configuration.  If insertion into
      either the List or the Hash_table fails, an error
      code is returned.
Uses: The class List, the class Hash_table, and the struct Cell
*/
{
   Error_code outcome;
   Cell *new_cell = new Cell(row, col);

   int index = living->size();
   outcome = living->insert(index, new_cell);
   if (outcome == success)
      outcome = is_living->insert(new_cell);
   if (outcome != success)
      cout << " Warning: new Cell insertion failed" << endl;
   return outcome;
}


Life::Life()
/*
Post: The members of a Life object are dynamically allocated and initialized.
Uses: The class Hash_table and the class List.
*/
{
   living = new List<Cell *>;
   is_living = new Hash_table;
}


Life::~Life()
/*
Post: The dynamically allocated members of a Life object
      and all ell objects that they reference are deleted.
Uses: The class Hash_table and the class List.
*/
{
   Cell *old_cell;
   for (int i = 0; i < living->size(); i++) {
      living->retrieve(i, old_cell);
      delete old_cell;
   }
   delete is_living;         //  Calls the Hash_table destructor
   delete living;            //  Calls the List destructor
}


const int factor = 101;

int hash(int row, int col)
/*
Post: The function returns the hashed valued between
      0 and hash_size - 1 that corresponds to the given Cell parameter.
*/
{
   int value;
   value = row + factor * col;
   value %= hash_size;
   if (value < 0) return value + hash_size;
   else return value;
}

/*************************************************************************/

