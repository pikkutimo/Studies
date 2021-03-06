/* Program extracts from Chapter 10 of
   "Data Structures and Program Design in C++"
   by Robert L. Kruse and Alexander J. Ryba
   Copyright (C) 1999 by Prentice-Hall, Inc.  All rights reserved.
   Extracts from this file may be used in the construction of other programs,
   but this code will not compile or execute as given here. */


// Section 10.1:

template <class Entry>
class Binary_tree {
public:
   //  Add methods here.
protected:
   //  Add auxiliary function prototypes here.
   Binary_node<Entry> *root;
};


template <class Entry>
struct Binary_node {
//    data members:
   Entry data;
   Binary_node<Entry> *left;
   Binary_node<Entry> *right;
//    constructors:
   Binary_node();
   Binary_node(const Entry &x);
};


template <class Entry>
Binary_tree<Entry>::Binary_tree()
/*
Post: An empty binary tree has been created.
*/
{
   root = NULL;
}


template <class Entry>
bool Binary_tree<Entry>::empty() const
/*
Post: A result of true is returned if the binary tree is empty.
      Otherwise, false is returned.
*/
{
   return root == NULL;
}


template <class Entry>
void Binary_tree<Entry>::inorder(void (*visit)(Entry &))
/*
Post: The tree has been traversed in inorder sequence.
Uses: The function recursive_inorder
*/
{
   recursive_inorder(root, visit);
}


template <class Entry>
void Binary_tree<Entry>::recursive_inorder(Binary_node<Entry> *sub_root,
                                           void (*visit)(Entry &))
/*
Pre:  sub_root is either NULL or points to a subtree of the Binary_tree.
Post: The subtree has been traversed in inorder sequence.
Uses: The function recursive_inorder recursively
*/
{
   if (sub_root != NULL) {
      recursive_inorder(sub_root->left, visit);
      (*visit)(sub_root->data);
      recursive_inorder(sub_root->right, visit);
   }
}


template <class Entry>
void Binary_tree<Entry>::recursive_preorder(Binary_node<Entry> *sub_root,
                                            void (*visit)(Entry &))
/*
Pre:  sub_root is either NULL or points to a subtree of the Binary_tree.
Post: The subtree has been traversed in preorder sequence.
Uses: The function recursive_preorder recursively
*/
{
   if (sub_root != NULL) {
      (*visit)(sub_root->data);
      recursive_preorder(sub_root->left, visit);
      recursive_preorder(sub_root->right, visit);
   }
}


template <class Entry>
void Binary_tree<Entry>::recursive_postorder(Binary_node<Entry> *sub_root,
                                             void (*visit)(Entry &))
/*
Pre:  sub_root is either NULL or points to a subtree of the Binary_tree.
Post: The subtree has been traversed in postorder sequence.
Uses: The function recursive_postorder recursively
*/
{
   if (sub_root != NULL) {
      recursive_postorder(sub_root->left, visit);
      recursive_postorder(sub_root->right, visit);
      (*visit)(sub_root->data);
   }
}


template <class Entry>
class Binary_tree {
public:
   Binary_tree();
   bool empty() const;
   void preorder(void (*visit)(Entry &));
   void inorder(void (*visit)(Entry &));
   void postorder(void (*visit)(Entry &));

   int size() const;
   void clear();
   int height() const;
   void insert(const Entry &);

   Binary_tree (const Binary_tree<Entry> &original);
   Binary_tree & operator =(const Binary_tree<Entry> &original);
   ~Binary_tree();

protected:
   //  Add auxiliary function prototypes here.
   Binary_node<Entry> *root;
};


void Binary_tree<Entry>::A(void (*visit)(Entry &))
{
  if (root != NULL) {
    (*visit)(root->data);
    root->left.B(visit);
    root->right.B(visit);
  }
}

void Binary_tree<Entry>::B(void (*visit)(Entry &))
{
  if (root != NULL) {
    root->left.A(visit);
    (*visit)(root->data);
    root->right.A(visit);
  }
}




// Section 10.2:

template <class Record>
class Search_tree: public Binary_tree<Record> {
public:
   Error_code insert(const Record &new_data);
   Error_code remove(const Record &old_data);
   Error_code tree_search(Record &target) const;
 private: //  Add auxiliary function prototypes here.
};


template <class Record>
Binary_node<Record> *Search_tree<Record>::search_for_node(
            Binary_node<Record>* sub_root, const Record &target) const
{
   if (sub_root == NULL || sub_root->data == target) return sub_root;
   else if (sub_root->data < target)
      return search_for_node(sub_root->right, target);
   else return search_for_node(sub_root->left, target);
}


template <class Record>
Binary_node<Record> *Search_tree<Record>::search_for_node(
            Binary_node<Record> *sub_root, const Record &target) const
{
   while (sub_root != NULL && sub_root->data != target)
      if (sub_root->data < target) sub_root = sub_root->right;
      else sub_root = sub_root->left;
   return sub_root;
}


template <class Record>
Error_code Search_tree<Record>::tree_search(Record &target) const
/*
Post: If there is an entry in the tree whose key matches that in target,
      the parameter target is replaced by the corresponding record from
      the tree and a code of success is returned.  Otherwise
      a code of not_present is returned.
Uses: function search_for_node
*/
{
   Error_code result = success;
   Binary_node<Record> *found = search_for_node(root, target);
   if (found == NULL)
      result = not_present;
   else
      target = found->data;
   return result;
}


template <class Record>
Error_code Search_tree<Record>::insert(const Record &new_data)
{
   return search_and_insert(root, new_data);
}


template <class Record>
Error_code Search_tree<Record>::search_and_insert(
           Binary_node<Record> *&sub_root, const Record &new_data)
{
   if (sub_root == NULL) {
      sub_root = new Binary_node<Record>(new_data);
      return success;
   }
   else if (new_data < sub_root->data)
      return search_and_insert(sub_root->left, new_data);
   else if (new_data > sub_root->data)
      return search_and_insert(sub_root->right, new_data);
   else return duplicate_error;
}


template <class Record>
Error_code Search_tree<Record>::remove_root(Binary_node<Record>
                                            *&sub_root)
/*
Pre:  sub_root is either NULL or points to a subtree of the Search_tree.
Post: If sub_root is NULL, a code of not_present is returned.
      Otherwise, the root of the subtree is removed in such a way
      that the properties of a binary search tree are preserved.
      The parameter sub_root is reset as the root of the modified subtree,
      and success is returned.
*/
{
   if (sub_root == NULL) return not_present;
   Binary_node<Record> *to_delete = sub_root;  //  Remember node to delete at end.
   if (sub_root->right == NULL) sub_root = sub_root->left;
   else if (sub_root->left == NULL) sub_root = sub_root->right;
   else {                           //  Neither subtree is empty.
      to_delete = sub_root->left;   //  Move left to find predecessor.
      Binary_node<Record> *parent = sub_root; //  parent of to_delete
      while (to_delete->right != NULL) { //  to_delete is not the predecessor.
         parent = to_delete;
         to_delete = to_delete->right;
      }
      sub_root->data = to_delete->data;  //  Move from to_delete to root.
      if (parent == sub_root) sub_root->left = to_delete->left;
      else parent->right = to_delete->left;
   }
   delete to_delete;   //  Remove to_delete from tree.
   return success;
}


template <class Record>
Error_code Search_tree<Record>::remove(const Record &target)
/*
Post: If a Record with a key matching that of target belongs to the
      Search_tree, a code of success is returned, and the corresponding node
      is removed from the tree.  Otherwise, a code of not_present is returned.
Uses: Function search_and_destroy
*/
{
   return search_and_destroy(root, target);
}


template <class Record>
Error_code Search_tree<Record>::search_and_destroy(
           Binary_node<Record>* &sub_root, const Record &target)
/*
Pre:  sub_root is either NULL or points to a subtree of the Search_tree.
Post: If the key of target is not in the subtree, a code of not_present
      is returned.  Otherwise, a code of success is returned and the subtree
      node containing target has been removed in such a way that
      the properties of a binary search tree have been preserved.
Uses: Functions search_and_destroy recursively and remove_root
*/
{
   if (sub_root == NULL || sub_root->data == target)
      return remove_root(sub_root);
   else if (target < sub_root->data)
      return search_and_destroy(sub_root->left, target);
   else
      return search_and_destroy(sub_root->right, target);
}




// Section 10.3:

template <class Record>
class Buildable_tree: public Search_tree<Record> {
public:
   Error_code build_tree(const List<Record> &supply);
 private: //  Add auxiliary function prototypes here.
};


template <class Record>
Error_code Buildable_tree<Record>::build_tree(const List<Record> &supply)
/*
Post:  If the entries of supply are in increasing order, a code of
       success is returned and the Search_tree is built
       out of these entries as a balanced tree.  Otherwise,
       a code of fail is returned and a balanced tree is
       constructed from the longest increasing sequence
       of entries at the start of supply.
Uses:  The methods of class List and the functions
       build_insert, connect_subtrees, and find_root
*/
{
   Error_code ordered_data = success; //  Set this to fail if keys do not increase.
   int count = 0;                     //  number of entries inserted so far
   Record x, last_x;
   List<Binary_node<Record> *> last_node; //  pointers to last nodes on each level
   Binary_node<Record> *none = NULL;
   last_node.insert(0, none);    //  permanently NULL (for children of leaves)
   while (supply.retrieve(count, x) == success) {
      if (count > 0 && x <= last_x) {
         ordered_data = fail;
         break;
      }
      build_insert(++count, x, last_node);
      last_x = x;
   }
   root = find_root(last_node);
   connect_trees(last_node);
   return ordered_data;  //  Report any data-ordering problems back to client.
}


template <class Record>
void Buildable_tree<Record>::build_insert(int count,
                             const Record &new_data,
                             List<Binary_node<Record>*> &last_node)
/*
Post: A new node, containing the Record new_data, has been inserted as
      the rightmost node of a partially completed
      binary search tree.  The level of this new node is one more than the
      highest power of 2 that divides count.
Uses: Methods of class List
*/
{
   int level;  //  level of new node above the leaves, counting inclusively
   for (level = 1; count % 2 == 0; level++)
      count /= 2;   //  Use count to calculate level of next_node.
   Binary_node<Record> *next_node = new Binary_node<Record>(new_data),
                       *parent;  //  one level higher in last_node
   last_node.retrieve(level - 1, next_node->left);
   if (last_node.size() <= level)
      last_node.insert(level, next_node);
   else
      last_node.replace(level, next_node);
   if (last_node.retrieve(level + 1, parent) == success && parent->right == NULL)
      parent->right = next_node;
}


template <class Record>
Binary_node<Record> *Buildable_tree<Record>::find_root(
                     List<Binary_node<Record>*> &last_node)
/*
Pre:  The list last_node contains pointers to the last node on each occupied
      level of the binary search tree.
Post: A pointer to the root of the newly created binary search tree is returned.
Uses: Methods of class List
*/
{
   Binary_node<Record> *high_node;
   last_node.retrieve(last_node.size() - 1, high_node);
      //  Find root in the highest occupied level in last_node.
   return high_node;
}


template <class Record>
void Buildable_tree<Record>::connect_trees(
                             const List<Binary_node<Record>*> &last_node)
/*
Pre:  The nearly-completed binary search tree has been initialized.  The List
      last_node has been initialized and contains links to the last node
      on each level of the tree.
Post: The final links have been added to complete the binary search tree.
Uses: Methods of class List
*/
{
   Binary_node<Record> *high_node, //  from last_node with NULL right child
                       *low_node;  //  candidate for right child of high_node
   int high_level = last_node.size() - 1,
       low_level;
   while (high_level > 2) {       //  Nodes on levels 1 and 2 are already OK.
      last_node.retrieve(high_level, high_node);
      if (high_node->right != NULL)
         high_level--;            //  Search down for highest dangling node.
      else {                      //  Case: undefined right tree
         low_level = high_level;
         do {               //  Find the highest entry not in the left subtree.
            last_node.retrieve(--low_level, low_node);
         } while (low_node != NULL && low_node->data < high_node->data);
         high_node->right = low_node;
         high_level = low_level;
      }
   }
}




// Section 10.4:

enum Balance_factor { left_higher, equal_height, right_higher };


template <class Record>
struct AVL_node: public Binary_node<Record> {
//    additional data member:
   Balance_factor balance;
//    constructors:
   AVL_node();
   AVL_node(const Record &x);
//    overridden virtual functions:
   void set_balance(Balance_factor b);
   Balance_factor get_balance() const;
};


template <class Record>
void AVL_node<Record>::set_balance(Balance_factor b)
{
   balance = b;
}

template <class Record>
Balance_factor AVL_node<Record>::get_balance() const
{
   return balance;
}


template <class Entry>
struct Binary_node {
//    data members:
   Entry data;
   Binary_node<Entry> *left;
   Binary_node<Entry> *right;
//    constructors:
   Binary_node();
   Binary_node(const Entry &x);

//    virtual methods:
   virtual void set_balance(Balance_factor b);
   virtual Balance_factor get_balance() const;

};


template <class Entry>
void Binary_node<Entry>::set_balance(Balance_factor b)
{
}

template <class Entry>
Balance_factor Binary_node<Entry>::get_balance() const
{
   return equal_height;
}


template <class Record>
class AVL_tree: public Search_tree<Record> {
public:
   Error_code insert(const Record &new_data);
   Error_code remove(const Record &old_data);
 private: //  Add auxiliary function prototypes here.
};


template <class Record>
Error_code AVL_tree<Record>::insert(const Record &new_data)
/*
Post: If the key of new_data is already in the AVL_tree, a code
      of duplicate_error is returned.
      Otherwise, a code of success is returned and the Record new_data
      is inserted into the tree in such a way that the properties of
      an AVL tree are preserved.
Uses: avl_insert.
*/
{
   bool taller;
   return avl_insert(root, new_data, taller);
}


template <class Record>
Error_code AVL_tree<Record>::avl_insert(Binary_node<Record> *&sub_root,
           const Record &new_data, bool &taller)
/*
Pre:  sub_root is either NULL or points to a subtree of the AVL_tree
Post: If the key of new_data is already in the subtree, a
      code of duplicate_error is returned.
      Otherwise, a code of success is returned and the Record new_data
      is inserted into the subtree in such a way that the
      properties of an AVL tree have been preserved.
      If the subtree is increased in height, the parameter taller is set to
      true; otherwise it is set to false.
Uses: Methods of struct AVL_node; functions avl_insert
      recursively, left_balance, and right_balance.
*/
{
   Error_code result = success;
   if (sub_root == NULL) {
      sub_root = new AVL_node<Record>(new_data);
      taller = true;
   }
   else if (new_data == sub_root->data) {
      result = duplicate_error;
      taller = false;
   }
   else if (new_data < sub_root->data) {         //  Insert in left subtree.
      result = avl_insert(sub_root->left, new_data, taller);
      if (taller == true)
         switch (sub_root->get_balance()) {//  Change balance factors.
         case left_higher:
            left_balance(sub_root);
            taller = false;        //  Rebalancing always shortens the tree.
            break;
         case equal_height:
            sub_root->set_balance(left_higher);
            break;
         case right_higher:
            sub_root->set_balance(equal_height);
            taller = false;
            break;
         }
   }
   else {                                       //  Insert in right subtree.
      result = avl_insert(sub_root->right, new_data, taller);
      if (taller == true)
         switch (sub_root->get_balance()) {
         case left_higher:
            sub_root->set_balance(equal_height);
            taller = false;
            break;
         case equal_height:
            sub_root->set_balance(right_higher);
            break;
         case right_higher:
            right_balance(sub_root);
            taller = false;        //  Rebalancing always shortens the tree.
            break;
         }
   }
   return result;
}


template <class Record>
void AVL_tree<Record>::rotate_left(Binary_node<Record> *&sub_root)
/*
Pre:  sub_root points to a subtree of the AVL_tree.
      This subtree has a nonempty right subtree.
Post: sub_root is reset to point to its former right child, and the former
      sub_root node is the left child of the new sub_root node.
*/
{
   if (sub_root == NULL || sub_root->right == NULL)     //  impossible cases
      cout << "WARNING: program error detected in rotate_left" << endl;
   else {
      Binary_node<Record> *right_tree = sub_root->right;
      sub_root->right = right_tree->left;
      right_tree->left = sub_root;
      sub_root = right_tree;
   }
}


template <class Record>
void AVL_tree<Record>::right_balance(Binary_node<Record> *&sub_root)
/*
Pre:  sub_root points to a subtree of an AVL_tree that
      is doubly unbalanced on the right.
Post: The AVL properties have been restored to the subtree.
Uses: Methods of struct AVL_node;
      functions  rotate_right and rotate_left.
*/
{
   Binary_node<Record> *&right_tree = sub_root->right;
   switch (right_tree->get_balance()) {
   case right_higher:                            //  single rotation left
      sub_root->set_balance(equal_height);
      right_tree->set_balance(equal_height);
      rotate_left(sub_root);
      break;
   case equal_height:  //  impossible case
      cout << "WARNING: program error detected in right_balance" << endl;
   case left_higher:                            //  double rotation left
      Binary_node<Record> *sub_tree = right_tree->left;
      switch (sub_tree->get_balance()) {
      case equal_height:
         sub_root->set_balance(equal_height);
         right_tree->set_balance(equal_height);
         break;
      case left_higher:
         sub_root->set_balance(equal_height);
         right_tree->set_balance(right_higher);
         break;
      case right_higher:
         sub_root->set_balance(left_higher);
         right_tree->set_balance(equal_height);
         break;
      }
      sub_tree->set_balance(equal_height);
      rotate_right(right_tree);
      rotate_left(sub_root);
      break;
   }
}




// Section 10.5:

template <class Record>
class Splay_tree:public Search_tree<Record> {
public:
   Error_code splay(const Record &target);
 private: //  Add auxiliary function prototypes here.
};


template <class Record>
void Splay_tree<Record>::link_right(Binary_node<Record> *&current,
                                    Binary_node<Record> *&first_large)
/*
Pre:  The pointer first_large points to an actual Binary_node
      (in particular, it is not NULL).  The three-way invariant holds.
Post: The node referenced by current (with its right subtree) is linked
      to the left of the node referenced by first_large.
      The pointer first_large is reset to current.
      The three-way invariant continues to hold.
*/
{
   first_large->left = current;
   first_large = current;
   current = current->left;
}


template <class Record>
void Splay_tree<Record>::link_left(Binary_node<Record> *&current,
                                   Binary_node<Record> *&last_small)
/*
Pre:  The pointer last_small points to an actual Binary_node
      (in particular, it is not NULL).  The three-way invariant holds.
Post: The node referenced by current (with its left subtree) is linked
      to the right of the node referenced by last_small.
      The pointer last_small is reset to current.
      The three-way invariant continues to hold.
*/
{
   last_small->right = current;
   last_small = current;
   current = current->right;
}


template <class Record>
void Splay_tree<Record>::rotate_right(Binary_node<Record> *&current)
/*
Pre:  current points to the root node of a subtree of a Binary_tree.
      This subtree has a nonempty left subtree.
Post: current is reset to point to its former left child, and the former
      current node is the right child of the new current node.
*/
{
   Binary_node<Record> *left_tree = current->left;
   current->left = left_tree->right;
   left_tree->right = current;
   current = left_tree;
}


template <class Record>
void Splay_tree<Record>::rotate_left(Binary_node<Record> *&current)
/*
Pre:  current points to the root node of a subtree of a Binary_tree.
      This subtree has a nonempty right subtree.
Post: current is reset to point to its former right child, and the former
      current node is the left child of the new current node.
*/
{
   Binary_node<Record> *right_tree = current->right;
   current->right = right_tree->left;
   right_tree->left = current;
   current = right_tree;
}


template <class Record>
Error_code Splay_tree<Record>::splay(const Record &target)
/*
Post: If a node of the splay tree has a key matching that of target,
      it has been moved by splay operations to be the root of the
      tree, and a code of entry_found is returned.  Otherwise,
      a new node containing a copy of target is inserted as the root
      of the tree, and a code of entry_inserted is returned.
*/
{
   Binary_node<Record> *dummy = new Binary_node<Record>;
   Binary_node<Record> *current = root,
                       *child,
                       *last_small = dummy,
                       *first_large = dummy;

 //  Search for target while splaying the tree.
   while (current != NULL && current->data != target)
      if (target < current->data) {
         child = current->left;
         if (child == NULL || target == child->data)    //  zig move
            link_right(current, first_large);
         else if (target < child->data) {           //  zig-zig move
            rotate_right(current);
            link_right(current, first_large);
         }
         else {                                     //  zig-zag move
            link_right(current, first_large);
            link_left(current, last_small);
         }
      }

      else {                              //  case: target > current->data
         child = current->right;
         if (child == NULL || target == child->data)
            link_left(current, last_small);             //  zag move
         else if (target > child->data) {           //  zag-zag move
            rotate_left(current);
            link_left(current, last_small);
         }
         else {                                     //  zag-zig move
            link_left(current, last_small);
            link_right(current, first_large);
         }
      }

 //  Move root to the current node, which is created if necessary.
   Error_code result;
   if (current == NULL) {        //  Search unsuccessful: make a new root.
      current = new Binary_node<Record>(target);
      result = entry_inserted;
      last_small->right = first_large->left = NULL;
   }

   else {                        //  successful search
      result = entry_found;
      last_small->right = current->left;  //   Move remaining central nodes.
      first_large->left = current->right;
   }

   root = current;               //  Define the new root.
   root->right = dummy->left;    //  root of larger-key subtree
   root->left = dummy->right;    //  root of smaller-key subtree
   delete dummy;
   return result;
}

/*************************************************************************/

