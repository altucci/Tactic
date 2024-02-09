#include "ccc_win.cpp"
#include "ccc_time.cpp"

   class Vectors
   {
   public:
      vector<int> comp;
   private:
   };

   void randseed();

   void draw_grid();

   void draw_X(Point A);

   void draw_O(Point A);

   void computer(vector<int>& A,vector<int>& B,vector<Vectors>& C,int E);

   bool all_else_are_losers(vector<int>& A,vector<int>& B,vector<Vectors> & C);

   bool winner(vector<int>& A);

   bool contains(vector<int>& A,int a,int b,int c);

   bool is_not_taken(vector<int>& A,vector<int>& B,int c);

   bool is_losing_combination(vector<int>& A,vector<Vectors>& B);

   bool vectors_equal(vector<int>& A,vector<int>& B);

   int get_int(Point A);

   int randint(int a, int b);

   vector<int> append(vector<int>& A,vector<int>& B);

   Point get_point(int a);

   int main()
   {
      randseed();
      vector<Vectors> losers1;
      vector<Vectors> losers2;
      Vectors com;
      vector<int> O;
      vector<int> X;
      vector<int> empty;
      int i;
      string winner_is;
      bool more = true;
      while (more)
      {
         cwin << Message(Point(-6,8),"X:")
            << Message(Point(4,8),"O:");
         cwin << Message(Point(-5,8),losers1.size())
            << Message(Point(5,8),losers2.size());
         if (winner(X)||winner(O))
            cwin << Message(Point(-2, 8),winner_is);
         else
            cwin << Message(Point(-2, 8),"Draw!");
         X = empty;
         O = empty;
         draw_grid();
         int count = 0;
         for (i = 1;i <= 9;i=i+2)
         {
            if (losers1.size() < 1800 || count != 0)
            {
               computer(O,X,losers2,2);
               count++;
            }
            else
            {
               bool cont = true;
               Point a;
               while (cont)
               {
                  a = cwin.get_mouse("Player 1's turn");
                  if (is_not_taken(X,O,get_int(a)))
                  {
                     draw_X(a);
                     X.push_back(get_int(a));					
                     cont = false;
                  }
               }
            }
            if (winner(X))
            {
               i = 10;
               winner_is = "Player 1 wins!";
               int last = X[X.size()-1];
               X.pop_back();
               com.comp = append(X,O);
               if (!is_losing_combination(com.comp,losers1))
                  losers1.push_back(com);
               X.push_back(last);
            }
            if (i != 9 && !(winner(X)))
            {            
               computer(X,O,losers1,1);
               if (winner(O))
               {
                  i = 10;
                  winner_is = "Player 2 wins!";
                  int last = O[O.size()-1];
                  O.pop_back();
                  com.comp = append(O,X);
                  if (!is_losing_combination(com.comp,losers2))
                     losers2.push_back(com);
                  O.push_back(last);
               }
            }
         }
         if (losers1.size() >= 1800)
         {
            for (int i = 0;i < 50000000;i++){}
         }
         cwin.clear();
      }
   }

   void randseed()
   {
      Time now;
      int seed = now.seconds_from(Time(0,0,0));
      srand(seed);
   }

   int randint(int a, int b)
   {
      return a + rand() % (b - a + 1);
   }

   vector<int> append(vector<int>& A,vector<int>& B)
   {
      vector<int> C;
      for (int i = 0;i < A.size();i++)
         C.push_back(A[i]);
      for (int j = 0;j < B.size();j++)
         C.push_back(B[j]);
      return C;
   }

   void draw_grid()
   {	
      Line A(Point(-6, 2), Point(6, 2));
      Line B(Point(-2, 6), Point(-2, -6));
      cwin << A << B;
      A.move(0, -4);
      B.move(4, 0);
      cwin << A << B;
   }

   void draw_X(Point A)
   {
      double a = 5.2;
      double b = 2.8;
      double c = 1.2;
      double x = A.get_x();
      double y = A.get_y();
      if (x < -2)
      {
         if (y > 2)
            cwin << Line(Point(-a, a),Point(-b, b))
               << Line(Point(-a, b),Point(-b, a));
         else if (y < -2)
            cwin << Line(Point(-a, -b),Point(-b, -a))
               << Line(Point(-a, -a),Point(-b, -b));
         else
            cwin << Line(Point(-a, c),Point(-b, -c))
               << Line(Point(-a, -c),Point(-b, c));
      }
      else if (x > 2)
      {
         if (y > 2)
            cwin << Line(Point(b, a),Point(a, b))
               << Line(Point(b, b),Point(a, a));
         else if (y < -2)
            cwin << Line(Point(b, -b),Point(a, -a))
               << Line(Point(b, -a),Point(a, -b));
         else
            cwin << Line(Point(b, c),Point(a, -c))
               << Line(Point(b, -c),Point(a, c));
      }
      else
      {
         if (y > 2)
            cwin << Line(Point(-c, a),Point(c, b))
               << Line(Point(-c, b),Point(c, a));
         else if (y < -2)
            cwin << Line(Point(-c, -b),Point(c, -a))
               << Line(Point(-c, -a),Point(c, -b));
         else
            cwin << Line(Point(-c, c),Point(c, -c))
               << Line(Point(-c, -c),Point(c, c));
      }
   }

   void draw_O(Point A)
   {
      double a = 1.2;		
      double x = A.get_x();
      double y = A.get_y();
      if (x < -2)
      {
         if (y > 2)
            cwin << Circle(Point(-4, 4), a);
         else if (y < -2)
            cwin << Circle(Point(-4, -4), a);
         else
            cwin << Circle(Point(-4, 0), a);
      }
      else if (x > 2)
      {
         if (y > 2)
            cwin << Circle(Point(4, 4), a);
         else if (y < -2)
            cwin << Circle(Point(4, -4), a);
         else
            cwin << Circle(Point(4, 0), a);
      }
      else
      {
         if (y > 2)
            cwin << Circle(Point(0, 4), a);
         else if (y < -2)
            cwin << Circle(Point(0, -4), a);
         else
            cwin << Circle(Point(0, 0), a);
      }
   }

   bool winner(vector<int>& A)
   {
      if (contains(A,1,5,9)||contains(A,1,2,3)||contains(A,4,5,6)||contains(A,7,8,9)||
         contains(A,7,5,3)||contains(A,7,4,1)||contains(A,8,5,2)||contains(A,9,6,3)) 
         return true;
      else
         return false;
   }

   bool contains(vector<int>& A, int a, int b, int c)
   {
      for (int i = 0;i <= A.size();i++)
      {
         if (i == A.size())
            return false;
         else if (A[i] == a)
            i = A.size()+1;
         else {}
      }
      for (int i = 0;i <= A.size();i++)
      {
         if (i == A.size())
            return false;
         else if (A[i] == b)
            i = A.size()+1;
         else {}
      }
      for (int i = 0;i <= A.size();i++)
      {
         if (i == A.size())
            return false;
         else if (A[i] == c)
            i = A.size()+1;
         else {}
      }
      return true;
   }

   bool is_not_taken(vector<int>& A,vector<int>& B,int c)
   {
      for (int i = 0;i < A.size();i++)
      {
         if (A[i] == c)
            return false;
      }
      for (int i = 0;i < B.size();i++)
      {
         if (B[i] == c)
            return false;
      }
      return true;
   }

   int get_int(Point A)
   {
      double x = A.get_x();
      double y = A.get_y();
      if (x < -2)
      {
         if (y > 2)
            return 1;
         else if (y < -2)
            return 7;
         else
            return 4;
      }
      else if (x > 2)
      {
         if (y > 2)
            return 3;
         else if (y < -2)
            return 9;
         else
            return 6;
      }
      else
      {
         if (y > 2)
            return 2;
         else if (y < -2)
            return 8;
         else
            return 5;
      }
   }

   Point get_point(int a)
   {
      if (a == 1) 
         return Point(-3,3);
      else if (a == 2) 
         return Point(0,3);
      else if (a == 3) 
         return Point(3,3);
      else if (a == 4) 
         return Point(-3,0);
      else if (a == 5) 
         return Point(0,0);
      else if (a == 6) 
         return Point(3,0);
      else if (a == 7) 
         return Point(-3,-3);
      else if (a == 8) 
         return Point(0,-3);
      else 
         return Point(3,-3);
   }

   void computer(vector<int>& A,vector<int>& B,vector<Vectors>& C,int E)
   {
      if (all_else_are_losers(A,B,C))
      {
         int copy_i;
         for (int i = 1;i <= 9;i++)
         {
            copy_i = i;
            if (is_not_taken(A,B,i))
            {
               if (E == 1) draw_O(get_point(i));
               else draw_X(get_point(i));
               i = 10;
            }
         }
         Vectors com;
         int last = A[A.size()-1];
         A.pop_back();
         com.comp = append(A,B);
         C.push_back(com);
         A.push_back(last);
         B.push_back(copy_i);			
      }
      else
      {
         bool more = true;
         while (more)
         {
            int i = randint(1,9);
            if (is_not_taken(A,B,i))
            {
               B.push_back(i);
               vector<int> D = append(A,B);
               if (is_losing_combination(D,C))
                  B.pop_back();
               else
               {
                  if (E == 1) draw_O(get_point(i));
                  else draw_X(get_point(i));
                  more = false;
               }
            }
         }
      }
   }

   bool vectors_equal(vector<int>& A,vector<int>& B)
   {
      for (int i = 0;i < A.size()/2;i++)
      {
         for (int j = 0;j < B.size()/2;j++)
         {
            if (A[i] != B[j])
            {
               if (j == (B.size()/2)-1)
                  return false;
            }
            else
               j = B.size()/2;
         }
      }
      for (int i = A.size()/2;i < A.size();i++)
      {
         for (int j = B.size()/2;j < B.size();j++)
         {
            if (A[i] != B[j])
            {
               if (j == B.size()-1)
                  return false;
            }
            else
               j = B.size();
         }
      }
      return true;
   }

   bool is_losing_combination(vector<int>& A,vector<Vectors>& B)
   {
      for (int i = 0;i < B.size();i++)
      {
         if (A.size() == B[i].comp.size())
         {				
            if (vectors_equal(A,B[i].comp))
               return true;
         }
      }
      return false;
   }

   bool all_else_are_losers(vector<int>& A,vector<int>& B,vector<Vectors>& C)
   {
      for(int i = 1;i <= 9;i++)
      {
         if (is_not_taken(A,B,i))
         {
            B.push_back(i);
            vector<int> temp = append(A,B);
            if (!is_losing_combination(temp,C))
            {
               B.pop_back();
               return false;
            }
            B.pop_back();				
         }
      }
      return true;
   }