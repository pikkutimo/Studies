/* Program extracts from Chapter 4 of
   "Data Structures and Program Design in C++"
   by Robert L. Kruse and Alexander J. Ryba
   Copyright (C) 1999 by Prentice-Hall, Inc.  All rights reserved.
   Extracts from this file may be used in the construction of other programs,
   but this code will not compile or execute as given here. */


// Section 4.1:

int size, *dynamic_array, i;
cout << "Enter an array size: " << flush;
cin >> size;
dynamic_array = new int[size];
for (i = 0; i < size; i++) dynamic_array[i] = i;


class Fraction{
public:
   int numerator;
   int denominator;
};
Fraction *p;


struct Node {
//  data members
   Node_entry entry;
   Node *next;
//  constructors
   Node();
   Node(Node_entry item, Node *add_on = NULL);
};


Node::Node()
{
   next = NULL;
}


Node::Node(Node_entry item, Node *add_on)
{
   entry = item;
   next = add_on;
}


Node first_node('a'); //  Node first_node stores data 'a'.
Node *p0 = &first_node;  //  p0 points to first_Node.
Node *p1 = new Node('b'); //  A second node storing 'b' is created.
p0->next = p1;  //  The second Node is linked after first_node.
Node *p2 = new Node('c', p0);  //  A third Node storing 'c' is created.
    //  The third Node links back to the first node, *p0.
p1->next = p2;  //  The third Node is linked after the second Node.


Node *p0 = new Node('0');
Node *p1 = p0->next = new Node('1');
Node *p2 = p1->next = new Node('2', p1);



// Section 4.2:

class Stack {
public:
   Stack();
   bool empty() const;
   Error_code push(const Stack_entry &item);
   Error_code pop();
   Error_code top(Stack_entry &item) const;
protected:
   Node *top_node;
};


Error_code Stack::push(const Stack_entry &item)
/*
Post: Stack_entry item is added to the top of
      the Stack; returns success or returns a code
      of overflow if dynamic memory is exhausted.
*/
{
   Node *new_top = new Node(item, top_node);
   if (new_top == NULL) return overflow;
   top_node = new_top;
   return success;
}


Error_code Stack::pop()
/*
Post: The top of the Stack is removed.  If the Stack
      is empty the method returns underflow; otherwise it returns success.
*/
{
   Node *old_top = top_node;
   if (top_node == NULL) return underflow;
   top_node = old_top->next;
   delete old_top;
   return success;
}


Error_code Stack::push(Stack_entry item)
{
   Node new_top(item, top_node);
   top_node = new_top;
   return success;
}



// Section 4.3:

for (int i=0; i < 1000000; i++) {
   Stack small;
   small.push(some_data);
}


Stack::~Stack() //  Destructor
/*
Post: The Stack is cleared.
*/
{
   while (!empty())
      pop();
}


Stack outer_stack;
for (int i=0; i < 1000000; i++) {
   Stack inner_stack;
   inner_stack.push(some_data);
   inner_stack = outer_stack;
}


void Stack::operator = (const Stack &original) //  Overload assignment
/*
Post: The Stack is reset as a copy of Stack original.
*/
{
   Node *new_top, *new_copy, *original_node = original.top_node;
   if (original_node == NULL) new_top = NULL;
   else {                         //  Duplicate the linked nodes
      new_copy = new_top = new Node(original_node->entry);
      while (original_node->next != NULL) {
         original_node = original_node->next;
         new_copy->next = new Node(original_node->entry);
         new_copy = new_copy->next;
      }
   }
   while (!empty())               //  Clean out old Stack entries
      pop();
   top_node = new_top;            //  and replace them with new entries.
}


void destroy_the_stack (Stack copy)
{
}

int main()
{
   Stack vital_data;
   destroy_the_stack(vital_data);
}


Stack::Stack(const Stack &original) //  copy constructor
/*
Post: The Stack is initialized as a copy of Stack original.
*/
{
   Node *new_copy, *original_node = original.top_node;
   if (original_node == NULL) top_node = NULL;
   else {                         //  Duplicate the linked nodes.
      top_node = new_copy = new Node(original_node->entry);
      while (original_node->next != NULL) {
         original_node = original_node->next;
         new_copy->next = new Node(original_node->entry);
         new_copy = new_copy->next;
      }
   }
}


class Stack {
public:
//  Standard Stack methods
   Stack();
   bool empty() const;
   Error_code push(const Stack_entry &item);
   Error_code pop();
   Error_code top(Stack_entry &item) const;
//  Safety features for linked structures
   ~Stack();
   Stack(const Stack &original);
   void operator =(const Stack &original);
protected:
   Node *top_node;
};


void Stack::operator = (const Stack &original)
{
   Stack new_copy(original);
   top_node = new_copy.top_node;
}



// Section 4.4:

class Queue {
public:
//  standard Queue methods
   Queue();
   bool empty() const;
   Error_code append(const Queue_entry &item);
   Error_code serve();
   Error_code retrieve(Queue_entry &item) const;
//  safety features for linked structures
   ~Queue();
   Queue(const Queue &original);
   void operator =(const Queue &original);
protected:
   Node *front, *rear;
};


Queue::Queue()
/*
Post: The Queue is initialized to be empty.
*/
{
   front = rear = NULL;
}


Error_code Queue::append(const Queue_entry &item)
/*
Post: Add item to the rear of the Queue and return a code of success
      or return a code of overflow if dynamic memory is exhausted.
*/
{
   Node *new_rear = new Node(item);
   if (new_rear == NULL) return overflow;
   if (rear == NULL) front = rear = new_rear;
   else {
      rear->next = new_rear;
      rear = new_rear;
   }
   return success;
}


Error_code Queue::serve()
/*
Post: The front of the Queue is removed.  If the Queue
      is empty, return an Error_code of underflow.
*/
{
   if (front == NULL) return underflow;
   Node *old_front = front;
   front = old_front->next;
   if (front == NULL) rear = NULL;
   delete old_front;
   return success;
}


class Extended_queue: public Queue {
public:
   bool full() const;
   int size() const;
   void clear();
   Error_code serve_and_retrieve(Queue_entry &item);
};


int Extended_queue::size() const
/*
Post: Return the number of entries in the Extended_queue.
*/
{
   Node *window = front;
   int count = 0;
   while (window != NULL) {
      window = window->next;
      count++;
   }
   return count;
}



// Section 4.5:

int main()
/*
Post: The program has executed simple polynomial arithmetic
      commands entered by the user.
Uses: The classes Stack and Polynomial and the functions
      introduction, instructions, do_command, and get_command.
*/
{
   Stack stored_polynomials;
   introduction();
   instructions();
   while (do_command(get_command(), stored_polynomials));
}


bool do_command(char command, Stack &stored_polynomials)
/*
Pre:  The first parameter specifies a valid calculator command.
Post: The command specified by the first parameter
      has been applied to the Stack of Polynomial
      objects given by the second parameter.
      A result of true is returned unless command == 'q'.
Uses: The classes Stack and Polynomial.
*/
{
   Polynomial p, q, r;
   switch (command) {
   case '?':
      p.read();
      if (stored_polynomials.push(p) == overflow)
         cout << "Warning: Stack full, lost polynomial" << endl;
      break;

   case '=':
      if (stored_polynomials.empty())
         cout << "Stack empty" << endl;
      else {
         stored_polynomials.top(p);
         p.print();
      }
      break;

   case '+':
      if (stored_polynomials.empty())
         cout << "Stack empty" << endl;
      else {
         stored_polynomials.top(p);
         stored_polynomials.pop();
         if (stored_polynomials.empty()) {
            cout << "Stack has just one polynomial" << endl;
            stored_polynomials.push(p);
         }

         else {
            stored_polynomials.top(q);
            stored_polynomials.pop();
            r.equals_sum(q, p);
            if (stored_polynomials.push(r) == overflow)
               cout << "Warning: Stack full, lost polynomial" << endl;
         }
      }
      break;

   //   Add options for further user commands.
    case 'q':
      cout << "Calculation finished." << endl;
      return false;
   }
   return true;
}


class Polynomial {
public:
   void read();
   void print();
   void equals_sum(Polynomial p, Polynomial q);
   void equals_difference(Polynomial p, Polynomial q);
   void equals_product(Polynomial p, Polynomial q);
   Error_code equals_quotient(Polynomial p, Polynomial q);
private:
   double value;
};


void Polynomial::equals_sum(Polynomial p, Polynomial q)
{
   value = p.value + q.value;
}


struct Term {
   int degree;
   double coefficient;
   Term (int exponent = 0, double scalar = 0);
};


Term::Term(int exponent, double scalar)
/*
Post: The Term is initialized with the given coefficient and exponent,
      or with default parameter values of 0.
*/
{
   degree = exponent;
   coefficient = scalar;
}


class Polynomial: private Extended_queue {  //  Use private inheritance.
public:
   void read();
   void print() const;
   void equals_sum(Polynomial p, Polynomial q);
   void equals_difference(Polynomial p, Polynomial q);
   void equals_product(Polynomial p, Polynomial q);
   Error_code equals_quotient(Polynomial p, Polynomial q);
   int degree() const;
private:
   void mult_term(Polynomial p, Term t);
};


void Polynomial::print() const
/*
Post: The Polynomial is printed to cout.
*/
{
   Node *print_node = front;
   bool first_term = true;

   while (print_node != NULL) {
      Term &print_term = print_node->entry;
      if (first_term) {  //  In this case, suppress printing an initial '+'.
         first_term = false;
         if (print_term.coefficient < 0) cout << "- ";
      }
      else if (print_term.coefficient < 0) cout << " - ";
      else cout << " + ";
      double r = (print_term.coefficient >= 0)
                 ? print_term.coefficient : -(print_term.coefficient);
      if (r != 1) cout << r;
      if (print_term.degree > 1) cout << " X^" << print_term.degree;
      if (print_term.degree == 1) cout << " X";
      if (r == 1 && print_term.degree == 0) cout << " 1";
      print_node = print_node->next;
   }
   if (first_term)
      cout << "0";  //  Print 0 for an empty Polynomial.
   cout << endl;
}


void Polynomial::read()
/*
Post: The Polynomial is read from cin.
*/
{
   clear();
   double coefficient;
   int last_exponent, exponent;
   bool first_term = true;

   cout << "Enter the coefficients and exponents for the polynomial, "
        << "one pair per line.  Exponents must be in descending order." << endl
        << "Enter a coefficient of 0 or an exponent of 0 to terminate." << endl;

   do {
      cout << "coefficient? " << flush;
      cin  >> coefficient;
      if (coefficient != 0.0) {
         cout << "exponent? " << flush;
         cin  >> exponent;
         if ((!first_term && exponent >= last_exponent) || exponent < 0) {
            exponent = 0;

            cout << "Bad exponent: Polynomial terminates without its last term."
                 << endl;
         }
         else {
            Term new_term(exponent, coefficient);
            append(new_term);
            first_term = false;
         }
         last_exponent = exponent;
      }
   } while (coefficient != 0.0 && exponent != 0);
}


void Polynomial::equals_sum(Polynomial p, Polynomial q)
/*
Post: The Polynomial object is reset as the sum of the two parameters.
*/
{
   clear();
   while (!p.empty() || !q.empty()) {
      Term p_term, q_term;
      if (p.degree() > q.degree()) {
         p.serve_and_retrieve(p_term);
         append(p_term);
      }
      else if (q.degree() > p.degree()) {
         q.serve_and_retrieve(q_term);
         append(q_term);
      }
      else {
         p.serve_and_retrieve(p_term);
         q.serve_and_retrieve(q_term);
         if (p_term.coefficient + q_term.coefficient != 0) {
            Term answer_term(p_term.degree,
                             p_term.coefficient + q_term.coefficient);
            append(answer_term);
         }
      }
   }
}


int Polynomial::degree() const
/*
Post: If the Polynomial is identically 0, a result of -1 is returned.
      Otherwise the degree of the Polynomial is returned.
*/
{
   if (empty()) return -1;
   Term lead;
   retrieve(lead);
   return lead.degree;
}

/*************************************************************************/

