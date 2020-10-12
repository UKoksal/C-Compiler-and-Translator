int main() {
 int b;
 int c;
 c = 5;
 b = fib(69);
 if(c == 5){
   return b;
 }
}
int fib(int n){
  if(n == 1){
    return 1;
  }else{
    if(n == 2){
      return 13;
    }else{
        int a;
        int b;
        a = n - 1;
        b = n - 2;
      return (a-1)/2;//this line
    }
  }
}
