#include <stdio.h>
#include <stdlib.h>

//I've provided "min" and "max" functions in
//case they are useful to you
int min (int a, int b) {
  if (a < b) {
    return a;
  }
  return b;
}
int max (int a, int b) {
  if (a > b) {
    return a;
  }
  return b;
}

//Declare your rectangle structure here!
typedef struct rect {
  int x, y, width, height;
} rectangle;


rectangle canonicalize(rectangle r) {
  //WRITE THIS FUNCTION  
  if(r.width < 0) {
    r.x = r.x + r.width;
    r.width = -r.width;
  }
  if(r.height < 0) {
    r.y = r.height + r.y;
    r.height = -r.height;
  }
  
  return r;
}

rectangle intersectionOld(rectangle r1, rectangle r2) {
  // WRITE THIS FUNCTION
  rectangle r1c = canonicalize(r1);
  rectangle r2c = canonicalize(r2);
  rectangle r;
  r.x = max(r1c.x, r2c.x);
  r.y = max(r1c.y, r2c.y);
  //   r.width = (r1c.width, r2c.width);
  //   r.height = (r1c.height, r2c.height);
  return r;
}

rectangle intersection(rectangle r1, rectangle r2) {
  rectangle ans;
  rectangle r1c = canonicalize(r1);
  rectangle r2c = canonicalize(r2);

  // left: maximum of r1's left and r2's left
  ans.x = max(r1c.x, r2c.x);
  // bottom: maximum or r1's bottom and r2's bottom
  ans.y = max(r1c.y, r2c.y);
  // right: minimum of r1's right and r2's right
  int right = min((r1c.x + r1c.width), (r2c.x + r2c.width));
  ans.width = right - ans.x;
  // top: minimum of r1's top and r2's top
  int top = min((r1c.y + r1c.height), (r2c.y + r2c.height));
  ans.height = top - ans.y;
  if(ans.width < 0 || ans.height < 0) {
    ans.width = 0;
    ans.height = 0;
  }
  return ans;
}

//You should not need to modify any code below this line
void printRectangle(rectangle r) {
  r = canonicalize(r);
  if (r.width == 0 && r.height == 0) {
    printf("<empty>\n");
  }
  else {
    printf("(%d,%d) to (%d,%d)\n", r.x, r.y, 
	                           r.x + r.width, r.y + r.height);
  }
}

int main (void) {
  rectangle r1;
  rectangle r2;
  rectangle r3;
  rectangle r4;

  r1.x = 2;
  r1.y = 3;
  r1.width = 5;
  r1.height = 6;
  printf("r1 is ");
  printRectangle(r1);

  r2.x = 4;
  r2.y = 5;
  r2.width = -5;
  r2.height = -7;
  printf("r2 is ");
  printRectangle(r2);
  
  r3.x = -2;
  r3.y = 7;
  r3.width = 7;
  r3.height = -10;
  printf("r3 is ");
  printRectangle(r3);

  r4.x = 0;
  r4.y = 7;
  r4.width = -4;
  r4.height = 2;
  printf("r4 is ");
  printRectangle(r4);

  //test everything with r1
  rectangle i = intersection(r1,r1);
  printf("intersection(r1,r1): ");
  printRectangle(i);

  i = intersection(r1,r2);
  printf("intersection(r1,r2): ");
  printRectangle(i);
  
  i = intersection(r1,r3);
  printf("intersection(r1,r3): ");
  printRectangle(i);

  i = intersection(r1,r4);
  printf("intersection(r1,r4): ");
  printRectangle(i);

  //test everything with r2
  i = intersection(r2,r1);
  printf("intersection(r2,r1): ");
  printRectangle(i);

  i = intersection(r2,r2);
  printf("intersection(r2,r2): ");
  printRectangle(i);
  
  i = intersection(r2,r3);
  printf("intersection(r2,r3): ");
  printRectangle(i);

  i = intersection(r2,r4);
  printf("intersection(r2,r4): ");
  printRectangle(i);

  //test everything with r3
  i = intersection(r3,r1);
  printf("intersection(r3,r1): ");
  printRectangle(i);

  i = intersection(r3,r2);
  printf("intersection(r3,r2): ");
  printRectangle(i);
  
  i = intersection(r3,r3);
  printf("intersection(r3,r3): ");
  printRectangle(i);

  i = intersection(r3,r4);
  printf("intersection(r3,r4): ");
  printRectangle(i);

  //test everything with r4
  i = intersection(r4,r1);
  printf("intersection(r4,r1): ");
  printRectangle(i);

  i = intersection(r4,r2);
  printf("intersection(r4,r2): ");
  printRectangle(i);
  
  i = intersection(r4,r3);
  printf("intersection(r4,r3): ");
  printRectangle(i);

  i = intersection(r4,r4);
  printf("intersection(r4,r4): ");
  printRectangle(i);


  return EXIT_SUCCESS;

}
