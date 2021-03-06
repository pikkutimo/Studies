/* Program extracts from Chapter 13 of
   "Data Structures and Program Design in C++"
   by Robert L. Kruse and Alexander J. Ryba
   Copyright (C) 1999 by Prentice-Hall, Inc.  All rights reserved.
   Extracts from this file may be used in the construction of other programs,
   but this code will not compile or execute as given here. */


// Section 13.3:

Error_code Expression::evaluate_prefix(Value &result)
/*  Outline of a method to perform prefix evaluation of an Expression.
    The details depend on further decisions about the implementation of
    expressions and values.*/
{
   if (the Expression is empty) return fail;
   else {
      remove the first symbol from the Expression, and
         store the value of the symbol as t;
      if (t is a unary operation) {
        Value the_argument;
        if (evaluate_prefix(the_argument) == fail) return fail;
        else result = the value of operation t applied to the_argument;
      }
      else if (t is a binary operation) {
        Value first_argument, second_argument;
        if (evaluate_prefix(first_argument) == fail) return fail;
        if (evaluate_prefix(second_argument) == fail) return fail;
        result  = the value of operation t
                      applied to first_argument and second_argument;
      }
      else              //  t is a numerical operand.
        result = the value of t;
   }
   return success;
}


class Expression {
public:
   Error_code evaluate_prefix(Value &result);
   Error_code get_token(Token &result);
   //  Add other methods.
private:
   //  Add data members to store an expression.
};


enum Token_type {
   operand, unaryop, binaryop    //  Add any other legitimate token types.
};


Value do_unary(const Token &operation, const Value &the_argument);
Value do_binary(const Token &operation,
                const Value &first_argument, const Value &second_argument);
Value get_value(const Token &operand);


Error_code Expression::evaluate_prefix(Value &result)
/*
Post: If the Expression does not begin with a legal prefix expression, a code
      of fail is returned.  Otherwise a code of success is returned, and
      the Expression is evaluated, giving the Value result.  The initial
      tokens that are evaluated are removed from the Expression.
*/
{
   Token t;
   Value the_argument, first_argument, second_argument;
   if (get_token(t) == fail) return fail;
   switch (t.kind()) {
   case unaryop:
      if (evaluate_prefix(the_argument) == fail) return fail;
      else result = do_unary(t, the_argument);
      break;
   case binaryop:
      if (evaluate_prefix(first_argument) == fail) return fail;
      if (evaluate_prefix(second_argument) == fail) return fail;
      else result = do_binary(t, first_argument, second_argument);
      break;
   case operand:
      result = get_value(t);
      break;
   }
   return success;
}


typedef Value Stack_entry;   //  Set the type of entry to use in stacks.

Error_code Expression::evaluate_postfix(Value &result)
/*
Post: The tokens in Expression up to the first end_expression symbol are
      removed.  If these tokens do not represent a legal postfix expression, a
      code of fail is returned.   Otherwise a code of success is returned,
      and the removed sequence of tokens is evaluated to give Value result.
*/
{
   Token t;             //  Current operator or operand
   Stack operands;      //  Holds values until operators are seen
   Value the_argument, first_argument, second_argument;
   do {
      if (get_token(t) == fail) return fail;   //  No end_expression token
      switch (t.kind()) {
      case unaryop:
         if (operands.empty()) return fail;
         operands.top(the_argument);
         operands.pop();
         operands.push(do_unary(t, the_argument));
         break;
      case binaryop:
         if (operands.empty()) return fail;
         operands.top(second_argument);
         operands.pop();
         if (operands.empty()) return fail;
         operands.top(first_argument);
         operands.pop();
         operands.push(do_binary(t, first_argument, second_argument));
         break;
      case operand:
         operands.push(get_value(t));
         break;
      case end_expression:
         break;
      }
   } while (t.kind() != end_expression);
   if (operands.empty()) return fail;
   operands.top(result);
   operands.pop();
   if (!operands.empty()) return fail;  //  surplus operands detected
   return success;
}


Error_code Expression::evaluate_postfix(Value &result)
/*
Post: The tokens in Expression up to the first end_expression symbol are
      removed.  If these tokens do not represent a legal postfix expression, a
      code of fail is returned.   Otherwise a code of success is returned,
      and the removed sequence of tokens is evaluated to give Value result.
*/
{
   Token first_token, final_token;
   Error_code outcome;
   if (get_token(first_token) == fail || first_token.kind() != operand)
      outcome = fail;
   else {
      outcome = recursive_evaluate(first_token, result, final_token);
      if (outcome == success && final_token.kind() != end_expression)
         outcome = fail;
   }
   return outcome;
}


Error_code Expression::recursive_evaluate(const Token &first_token,
                                          Value &result, Token &final_token)
/*
Pre:  Token first_token is an operand.
Post: If the first_token can be combined with initial tokens of
      the Expression to yield a legal postfix expression followed
      by either an end_expression symbol or a binary operator,
      a code of success is returned, the legal postfix subexpression
      is evaluated, recorded in result, and the terminating Token is
      recorded as final_token.  Otherwise a code of fail is returned.
      The initial tokens of Expression are removed.
Uses: Methods of classes Token and Expression, including
      recursive_evaluate and functions do_unary, do_binary,
      and get_value.
*/
{
   Value first_segment = get_value(first_token),
         next_segment;
   Error_code outcome;
   Token current_token;
   Token_type current_type;
   do {
      outcome = get_token(current_token);
      if (outcome != fail) {
         switch (current_type = current_token.kind()) {
         case binaryop:          //  Binary operations terminate subexpressions.
         case end_expression:    //  Treat subexpression terminators together.
            result = first_segment;
            final_token = current_token;
            break;
         case unaryop:
            first_segment = do_unary(current_token, first_segment);
            break;
         case operand:
            outcome = recursive_evaluate(current_token,
                                         next_segment, final_token);
            if (outcome == success && final_token.kind() != binaryop)
               outcome = fail;
            else

               first_segment = do_binary(final_token, first_segment,
                                         next_segment);
            break;
         }
      }
   } while (outcome == success && current_type != end_expression &&
                                  current_type != binaryop);
   return outcome;
}




// Section 13.4:

Expression Expression::infix_to_postfix()
/*
Pre:  The Expression stores a valid infix expression.
Post: A postfix expression that translates the infix expression is returned.
*/
{
   Expression answer;
   Token current, prior;
   Stack delayed_operations;
   while (get_token(current) != fail) {
      switch (current.kind()) {
      case operand:
         answer.put_token(current);
         break;
      case leftparen:
         delayed_operations.push(current);
         break;
      case rightparen:
         delayed_operations.top(prior);
         while (prior.kind() != leftparen) {
            answer.put_token(prior);
            delayed_operations.pop();
            delayed_operations.top(prior);
         }
         delayed_operations.pop();
         break;
      case unaryop:
      case binaryop:               //  Treat all operators together.
         bool end_right = false;   //  End of right operand reached?

         do {
            if (delayed_operations.empty()) end_right = true;
            else {
               delayed_operations.top(prior);
               if (prior.kind() == leftparen) end_right = true;
               else if (prior.priority() < current.priority()) end_right = true;
               else if (current.priority() == 6) end_right = true;
               else answer.put_token(prior);
               if (!end_right) delayed_operations.pop();
            }
         } while (!end_right);

         delayed_operations.push(current);
         break;
      }
   }
   while (!delayed_operations.empty()) {
      delayed_operations.top(prior);
      answer.put_token(prior);
      delayed_operations.pop();
   }
   answer.put_token(";");
   return answer;
}




// Section 13.5:

int main()
/*
Pre:  None
Post: Acts as a menu-driven graphing program.
Uses: Classes Expression and Plot,
      and functions introduction, get_command,
      and do_command.
*/
{
   introduction();
   Expression infix;      //  Infix expression from user
   Expression postfix;    //  Postfix translation
   Plot graph;
   char ch;
   while ((ch = get_command()) != 'q')
      do_command(ch, infix, postfix, graph);
}


void do_command(char c, Expression &infix, Expression &postfix, Plot &graph)
/*
Pre:  None
Post: Performs the user command represented by char c on the
      Expression infix, the Expression postfix, and the Plot graph.
Uses: Classes Token, Expression and Plot.
*/
{
   switch (c) {
   case 'r':      //  Read an infix expression from the user.
      infix.clear();
      infix.read();
      if (infix.valid_infix() == success) postfix = infix.infix_to_postfix();
      else cout << "Warning: Bad expression ignored. " << endl;
      break;
   case 'w':      //  Write the current expression.
      infix.write();
      postfix.write();
      break;
   case 'g':      //  Graph the current postfix expression.
      if (postfix.size() <= 0)
         cout << "Enter a valid expression before graphing!" << endl;
      else {
         graph.clear();
         graph.find_points(postfix);
         graph.draw();
      }
      break;
   case 'l':    //  Set the graph limits.
      if (graph.set_limits() != success)
         cout << "Warning: Invalid limits" << endl;
      break;
   case 'p':    //  Print the graph parameters.
      Token::print_parameters();
      break;
   case 'n':    //  Set new graph parameters.
      Token::set_parameters();
      break;
   case 'h':    //  Give help to user.
      help();
      break;
   }
}


struct Token_record {
   String name;
   double value;
   int priority;
   Token_type kind;
};


struct Lexicon {
   Lexicon();
   int hash(const String &x) const;
   void set_standard_tokens();  //  Set up the predefined tokens.
   int count;                   //  Number of records in the Lexicon
   int index_code[hash_size];   //  Declare the hash table.
   Token_record token_data[hash_size];
};


class Token {
public:
//  Add methods here.
private:
   int code;
   static Lexicon symbol_table;
   static List<int> parameters;
};

List<int> Token::parameters;   //  Allocate storage for static Token members.
Lexicon Token::symbol_table;


class Expression {
public:
//  Add method prototypes.
private:
   List<Token> terms;
   int current_term;
//  Add auxiliary function prototypes.
};


class Token {
public:
   Token() {}
   Token (const String &x);
   Token_type kind() const;
   int priority() const;
   double value() const;
   String name() const;
   int code_number() const;
   static void set_parameters();
   static void print_parameters();
   static void set_x(double x_val);

private:
   int code;
   static Lexicon symbol_table;
   static List<int> parameters;
};


Token_type Token::kind() const
{
   return symbol_table.token_data[code].kind;
}


Token::Token(const String &identifier)
/*
Post: A Token corresponding to String identifier
      is constructed.  It shares its code with any other Token object
      with this identifier.
Uses: The class Lexicon.
*/
{
   int location = symbol_table.hash(identifier);
   if (symbol_table.index_code[location] == -1) {   //  Create a new record.
      code = symbol_table.count++;
      symbol_table.index_code[location] = code;
      symbol_table.token_data[code] = attributes(identifier);
      if (is_parameter(symbol_table.token_data[code]))
         parameters.insert(0, code);
   }
   else code = symbol_table.index_code[location];  //   Code of an old record
}


void Token::set_parameters()
/*
Post: All parameter values are printed for the user, and any changes
      specified by the user are made to these values.
Uses: Classes List, Token_record, and String, and function read_num.
*/
{
   int n = parameters.size();
   int index_code;
   double x;
   for (int i = 0; i < n; i++) {
      parameters.retrieve(i, index_code);
      Token_record &r = symbol_table.token_data[index_code];
      cout << "Give a new value for parameter " << (r.name).c_str()
           << " with value " << r.value << endl;
      cout << "Enter a value or a new line to keep the old value: " << flush;
      if (read_num(x) == success) r.value = x;
   }
}


Lexicon::Lexicon()
/*
Post: The Lexicon is initialized with the standard tokens.
Uses: set_standard_tokens
*/
{
   count = 0;
   for (int i = 0; i < hash_size; i++)
      index_code[i] = -1;     //  code for an empty hash slot
   set_standard_tokens();
}


get_word(const String &s, int n, String &t);


void Lexicon::set_standard_tokens()
{
   int i = 0;
   String symbols = ( String )
      "; ( ) ~ abs sqr sqrt exp ln lg sin cos arctan round trunc ! % + - * / ^ x pi e";
   String word;
   while (get_word(symbols, i++, word) != fail) {
      Token  t= word;
   }
   token_data[23].value = 3.14159;
   token_data[24].value = 2.71828;
}


int Lexicon::hash(const String &identifier) const
/*
Post: Returns the location in table Lexicon::index_code that
      corresponds to the String identifier.
      If the hash table is full and does not contain a record
      for identifier, the exit function is called to terminate the program.
Uses: The class String, the function exit.
*/
{
   int location;
   const char *convert = identifier.c_str();
   char first = convert[0], second;     //  First two characters of identifier
   if (strlen(convert) >= 2) second = convert[1];
   else second = first;
   location = first % hash_size;
   int probes = 0;
   while (index_code[location] >= 0 &&
          identifier != token_data[index_code[location]].name) {
      if (++probes >= hash_size) {
         cout << "Fatal Error: Hash Table overflow. Increase table size\n";
         exit(1);
      }
      location += second;
      location %= hash_size;
   }
   return location;
}


class Expression {
public:
   Expression();
   Expression(const Expression &original);
   Error_code get_token(Token &next);
   void put_token(const Token &next);
   Expression infix_to_postfix();
   Error_code evaluate_postfix(Value &result);
   void read();
   void clear();
   void write();
   Error_code valid_infix();
   int size();
   void rewind();

private:
   List<Token> terms;
   int current_term;
    Error_code recursive_evaluate(const Token &first_token,
                                  Value &result, Token &final_token);
};


Error_code Expression::get_token(Token &next)
/*
Post: The Token next records the current_term of the Expression,
      current_term is incremented,
      and an error code of success is returned, or if there is no
      such term a code of fail is returned.
Uses: Class List.
*/
{
   if (terms.retrieve(current_term, next) != success) return fail;
   current_term++;
   return success;
}


void Expression::read()
/*
Post: A line of text, entered by the user, is split up into
      tokens and stored in the Expression.
Uses: Classes String, Token, and List.
*/
{
   String input, word;
   int term_count = 0;
   int x;
   input = read_in(cin, x);
   add_spaces(input);                 //  Tokens are now words of input.
   bool leading = true;
   for (int i = 0; get_word(input, i, word) != fail; i++) {  //  Process next token
      if (leading)
         if (word == "+") continue;                   //  unary +
         else if (word == "-") word = "~";            //  unary -
      Token current = word;                      //  Cast word to Token.
      terms.insert(term_count++, current);
      Token_type type = current.kind();
      if (type == leftparen || type == unaryop || type == binaryop)
         leading = true;
      else
         leading = false;
   }
}


Error_code Expression::valid_infix()
/*
Post: A code of success or fail is returned according
      to whether the Expression is a valid or invalid infix sequence.
Uses: Class Token.
*/
{
   Token current;
   bool leading = true;
   int paren_count = 0;
   while (get_token(current) != fail) {
      Token_type type = current.kind();
      if (type == rightparen || type == binaryop || type == rightunaryop) {
         if (leading) return fail;
      }
      else if (!leading) return fail;
      if (type == leftparen) paren_count++;
      else if (type == rightparen) {
         paren_count--;
         if (paren_count < 0) return fail;
      }
      if (type == binaryop || type == unaryop || type == leftparen)
         leading = true;
      else leading = false;
   }
   if (leading)  return fail;  //  An expected final operand is missing.
   if (paren_count > 0)  return fail;  //  Right parentheses are missing.
   rewind();
   return success;
}


Value get_value(const Token &current)
/*
Pre:  Token current is an operand.
Post: The Value of current is returned.
Uses: Methods of class Token.
*/
{
   return current.value();
}


Value do_binary(const Token &operation,
                const Value &first_argument, const Value &second_argument)
/*
Pre:  Token operation is a binary operator.
Post: The Value of operation applied to the pair of Value parameters is returned.
Uses: Methods of class Token.
*/
{
   switch (operation.code_number()) {
   case 17:
      return first_argument + second_argument;
   case 18:
      return first_argument - second_argument;
   case 19:
      return first_argument * second_argument;
   case 20:
      return first_argument / second_argument;
   case 21:
      return exp(first_argument, second_argument);
   }
}


class Plot {
public:
   Plot();
   Error_code set_limits();
   void find_points(Expression &postfix);
   void draw();
   void clear();
   int get_print_row(double y_value);
   int get_print_col(double x_value);
private:
   Sortable_list<Point> points;    //  records of points to be plotted
   double x_low, x_high;            //  x limits
   double y_low, y_high;            //  y limits
   double x_increment;              //  increment for plotting
   int max_row, max_col;           //  screen size
};


int Plot::get_print_row(double y_value)
/*
Post: Returns the row of the screen at which a point with
      y-coordinate y_value should be plotted, or
      returns -1 if the point would fall off the edge of the screen.
*/
{
   double interp_y =
      ((double) max_row) * (y_high - y_value) / (y_high - y_low) + 0.5;
   int answer = (int) interp_y;
   if (answer < 0 || answer > max_row) answer = -1;
   return answer;
}


struct Point {
   int row;
   int col;
   Point();
   Point(int a, int b);
   bool operator == (const Point &p);
   bool operator != (const Point &p);
   bool operator >= (const Point &p);
   bool operator <= (const Point &p);
   bool operator >  (const Point &p);
   bool operator <  (const Point &p);
};


bool Point::operator < (const Point &p)
{
   return (row < p.row) || (col < p.col && row == p.row);
}


void Plot::find_points(Expression &postfix)
/*
Post: The Expression postfix is evaluated for values of
      x that range from x_low to x_high in steps of
      x_increment.  For each evaluation we add a Point
      to the Sortable_list points.
Uses: Classes Token, Expression, Point, and List.
*/
{
   double x_val = x_low;
   double y_val;
   while (x_val <= x_high) {
      Token::set_x(x_val);
      postfix.evaluate_postfix(y_val);
      postfix.rewind();
      Point p(get_print_row(y_val), get_print_col(x_val));
      points.insert(0, p);
      x_val += x_increment;
   }
}


void Plot::draw()
/*
Post: All screen locations represented in points have been marked with
      the character '#' to produce a picture of the stored graph.
Uses: Classes Point and Sortable_list and its method merge_sort.
*/
{
   points.merge_sort();
   int at_row = 0, at_col = 0;         //  cursor coordinates on screen
   for (int i = 0; i < points.size(); i++) {
      Point q;
      points.retrieve(i, q);
      if (q.row < 0 || q.col < 0) continue;  //  off the scale of the graph
      if (q.row < at_row || (q.row == at_row && q.col < at_col)) continue;

      if (q.row > at_row) {                  //  Move cursor down the screen.
         at_col = 0;
         while (q.row > at_row) {
            cout << endl;
            at_row++;
         }
      }
      if (q.col > at_col)                    //  Advance cursor horizontally.
         while (q.col > at_col) {
            cout << " ";
            at_col++;
         }
      cout << "#";
      at_col++;
   }
   while (at_row++ <= max_row) cout << endl;
}


void Plot::find_points(Expression &postfix)
/*
Post: The Expression postfix is evaluated for values of
      x that range from x_low to x_high in steps of
      x_increment.  For each evaluation we add a Point
      of the corresponding data point to the Sortable_list points.
Uses: Classes Token, Expression, Point, and List and the library <graphics.h>.
*/
{
   int graphicdriver = DETECT, graphicmode;
   initgraph(&graphicdriver, &graphicmode,"");   //  screen detection and
   graphresult();                                //  initialization
   max_col = getmaxx();                          //  with graphics.h library
   max_row = getmaxy();

   double x_val = x_low;
   double y_val;
   while (x_val <= x_high) {
      Token::set_x(x_val);
      postfix.evaluate_postfix(y_val);
      postfix.rewind();
      Point p(get_print_row(y_val), get_print_col(x_val));
      points.insert(0, p);
      x_val += x_increment;
   }
}


void Plot::draw()
/*
Post: All pixels represented in points have
      been marked to produce a picture of the stored graph.
Uses: Classes Point and Sortable_list and the library <graphics.h>
*/
{
   for (int i = 0; i < points.size(); i++) {
      Point q;
      points.retrieve(i, q);
      if (q.row < 0 || q.col < 0) continue;  //  off the scale of the graph
      if (q.row > max_row || q.col > max_col) continue;
      putpixel(q.col,q.row,3);               // graphics.h library function
   }
   cout "Enter a character to clear screen and continue: " << flush;
   char wait_for;
   cin >> wait_for;
   restorecrtmode();                         // graphics.h library function
}

/*************************************************************************/

