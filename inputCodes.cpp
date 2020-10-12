int main() {
 int b;
 int c;
 b = 1;
 c = foo(b);
 if(c > 10){
    return 12;
 }else{
   return 13;
 }
}
int foo(int b){
  if(b == 1){
    return 10;
  }else{
    return 0;
  }
}
