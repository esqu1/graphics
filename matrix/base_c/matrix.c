#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "matrix.h"

/*-------------- struct matrix *new_matrix() --------------
Inputs:  int rows
         int cols 
Returns: 

Once allocated, access the matrix as follows:
m->m[r][c]=something;
if (m->lastcol)... 
*/
struct matrix *new_matrix(int rows, int cols) {
  double **tmp;
  int i;
  struct matrix *m;

  tmp = (double **)malloc(rows * sizeof(double *)); // Points to double pointers
  for (i=0;i<rows;i++) {
    tmp[i]=(double *)malloc(cols * sizeof(double)); // Each of those pointers points to a new array
    }

  m=(struct matrix *)malloc(sizeof(struct matrix));
  m->m=tmp; // This is the pointer that points to the beginning
  m->rows = rows; // like saying (*m).rows, where *m is the actual matrix
  m->cols = cols;
  m->lastcol = 0;

  return m;
}


/*-------------- void free_matrix() --------------
Inputs:  struct matrix *m 
Returns: 

1. free individual rows
2. free array holding row pointers
3. free actual matrix
*/
void free_matrix(struct matrix *m) {

  int i;
  for (i=0;i<m->rows;i++) {
    free(m->m[i]); // frees the rows
  }
  free(m->m);
  free(m);
}


/*======== void grow_matrix() ==========
Inputs:  struct matrix *m
         int newcols 
Returns: 

Reallocates the memory for m->m such that it now has
newcols number of collumns
====================*/
void grow_matrix(struct matrix *m, int newcols) {
  
  int i;
  for (i=0;i<m->rows;i++) {
      m->m[i] = realloc(m->m[i],newcols*sizeof(double));
  }
  m->cols = newcols;
}


/*-------------- void print_matrix() --------------
Inputs:  struct matrix *m 
Returns: 

print the matrix
*/
void print_matrix(struct matrix *m) {
  int i,j=0;
  for (i = 0; i < m->rows; i++){
    for (j = 0; j < m->cols; j++){
      printf("%fl ",m->m[i][j]);
    }
    printf("\n");
  }
}

/*-------------- void ident() --------------
Inputs:  struct matrix *m <-- assumes m is a square matrix
Returns: 

turns m in to an identity matrix
*/
void ident(struct matrix *m) {
  int i=0,j=0;
  for (i = 0; i < m->rows; i++){
    for (j = 0; j < m->cols; j++){
      if(i != j){
	m->m[i][j] = 0;
      }else{
	m->m[i][j] = 1;
      }
    }
  }
}


/*-------------- void scalar_mult() --------------
Inputs:  double x
         struct matrix *m 
Returns: 

multiply each element of m by x
*/
void scalar_mult(double x, struct matrix *m) {
  int i=0, j=0;
  for (i = 0; i < m->rows; i++){
    for (j = 0; j < m->cols; j++){
      m->m[i][j] = x * m->m[i][j];
    }
  }

}


/*-------------- void matrix_mult() --------------
Inputs:  struct matrix *a
         struct matrix *b 
Returns: 

a*b -> b
Note: b.rows == a.cols
*/
void matrix_mult(struct matrix *a, struct matrix *b) {
  if (a->cols != b->rows){
    printf("Invalid input.\n");
  }else{
    struct matrix * c = new_matrix(a->rows,b->cols);
    int i,j;
    for (i = 0; i < c->rows; i++){
      for (j = 0; j < c->cols; j++){
	int sum = 0;
	int k;
	for (k = 0; k < c->rows; k++){
	  sum += a->m[i][k] * b->m[k][j];
	} 
	c->m[i][j] = sum;
      }
    }
    copy_matrix(c,b);
  }

}



/*-------------- void copy_matrix() --------------
Inputs:  struct matrix *a
         struct matrix *b 
Returns: 

copy matrix a to matrix b
*/
void copy_matrix(struct matrix *a, struct matrix *b) {

  int r, c;

  for (r=0; r < a->rows; r++) 
    for (c=0; c < a->cols; c++)  
      b->m[r][c] = a->m[r][c];  
}

/*======== struct matrix * make_translate() ==========
Inputs:  int x
         int y
         int z 
Returns: The translation matrix created using x, y and z 
as the translation offsets.
====================*/
struct matrix * make_translate(double x, double y, double z) {
  struct matrix * c = new_matrix(4,4);
  ident(c);
  
  c->m[0][3] = x;
  c->m[1][3] = y;
  c->m[2][3] = z;
  return c;
  
}

/*======== struct matrix * make_scale() ==========
Inputs:  int x
         int y
         int z 
Returns: The translation matrix creates using x, y and z
as the scale factors
====================*/
struct matrix * make_scale(double x, double y, double z) {
  struct matrix * c = new_matrix(4,4);
  ident(c);

  c->m[0][0] = x;
  c->m[1][1] = y;
  c->m[2][2] = z;

  return c;

}

/*======== struct matrix * make_rotX() ==========
Inputs:  double theta

Returns: The rotation matrix created using theta as the 
angle of rotation and X as the axis of rotation.
====================*/
struct matrix * make_rotX(double theta) {
  struct matrix * c = new_matrix(4,4);
  ident(c);
  
  c->m[1][1] = cos(theta);
  c->m[1][2] = -sin(theta);
  c->m[2][1] = sin(theta);
  c->m[2][2] = cos(theta);

  return c;

}

/*======== struct matrix * make_rotY() ==========
Inputs:  double theta

Returns: The rotation matrix created using theta as the 
angle of rotation and Y as the axis of rotation.
====================*/
struct matrix * make_rotY(double theta) {
  struct matrix * c = new_matrix(4,4);
  ident(c);
  
  c->m[0][0] = cos(theta);
  c->m[0][2] = -sin(theta);
  c->m[2][0] = sin(theta);
  c->m[2][2] = cos(theta);

  return c;
}

/*======== struct matrix * make_rotZ() ==========
Inputs:  double theta

Returns: The rotation matrix created using theta as the 
angle of rotation and Z as the axis of rotation.
====================*/
struct matrix * make_rotZ(double theta) {
  struct matrix * c = new_matrix(4,4);
  ident(c);
  
  c->m[0][0] = cos(theta);
  c->m[0][1] = -sin(theta);
  c->m[1][0] = sin(theta);
  c->m[1][1] = cos(theta);

  return c;
}
