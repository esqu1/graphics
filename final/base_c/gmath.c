#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "matrix.h"
#include "gmath.h"



/*======== double * calculate_normal() ==========
  Inputs:   double ax
            double ay
	    double az
	    double bx
	    double by
	    double bz  
  Returns: A double arry of size 3 representing the 
           cross product of <ax, ay, az> and <bx, by, bz>

  04/17/12 16:46:30
  jonalf
  ====================*/
double * calculate_normal( double ax, double ay, double az,
			   double bx, double by, double bz ) {
  
  double *normal;
  normal = (double *)malloc(3 * sizeof(double));

  normal[0] = ay*bz - az*by;
  normal[1] = az*bx - ax*bz;
  normal[2] = ax*by - ay*bx;

  return normal;
}

/*======== double calculate_dot() ==========
  Inputs:   struct matrix *points
            int i  
  Returns: The dot product of a surface normal and
           a view vector
  
  calculates the dot product of the surface normal to
  triangle points[i], points[i+1], points[i+2] and a 
  view vector (use <0, 0, -1> to start.

  04/17/12 16:38:34
  jonalf
  ====================*/
double calculate_dot( struct matrix *points, int i ) {

  double ax, ay, az, bx, by, bz;
  double *normal;
  double vx, vy, vz;
  double dot;

  //calculate A and B vectors
  ax = points->m[0][i+1] - points->m[0][i];
  ay = points->m[1][i+1] - points->m[1][i];
  az = points->m[2][i+1] - points->m[2][i];

  bx = points->m[0][i+2] - points->m[0][i];
  by = points->m[1][i+2] - points->m[1][i];
  bz = points->m[2][i+2] - points->m[2][i];

  //get the surface normal
  normal = calculate_normal( ax, ay, az, bx, by, bz );

  //set up view vector
  vx = 0;
  vy = 0;
  vz = -1;

  //calculate dot product
  dot = normal[0] * vx + normal[1] * vy + normal[2] * vz;

  free(normal);  
  return dot;
}


/*======== double max3() ==========
  Inputs:  double a,b,c  
  Returns: The maximum value among a,b,c
  ====================*/
double max3(double a, double b, double c){
  if (a >= b && a >= c){
    return a;
  }else if (b >= a && b >= c){
    return b;
  }else if (c >= a && c >= b){
    return c;
  }
  return a;
}

/*======== double mid3() ==========
  Inputs:  double a,b,c  
  Returns: The middle value among a,b,c
  ====================*/
double mid3(double a, double b, double c){
  if ((a >= b && a <= c) || (a <= b && a >= c)){
    return a;
  }else if ((b >= a && b <= c) || (b <= a && b >= c)){
    return b;
  }else if ((c >= a && c <= b) || (c <= a && c >= b)){
    return c;
  }
  return a;
}

/*======== double min3() ==========
  Inputs:  double a,b,c  
  Returns: The minimum value among a,b,c
  ====================*/
double min3(double a, double b, double c){
  if (a <= b && a <= c){
    return a;
  }else if (b <= a && b <= c){
    return b;
  }else if (c <= a && c <= b){
    return c;
  }
  return a;
}


double extract(struct matrix * polygons, int mode, int minmidmax, int i){
  double x;
  if(minmidmax == 1){
    x = min3(polygons->m[0][i],polygons->m[0][i+1],polygons->m[0][i+2]);
    if(mode == 1){
      return x;
    }else if (mode == 2){
      int k;
      for (k = 0; k < 3; k++){
	if(polygons->m[0][i+k] == x){
	  return polygons->m[1][i+k];
	}
      }
    }else{
      int k;
      for (k = 0; k < 3; k++){
	if(polygons->m[0][i+k] == x){
	  return polygons->m[2][i+k];
	}
      }
    }
  }else if(minmidmax == 2){
    x = mid3(polygons->m[0][i],polygons->m[0][i+1],polygons->m[0][i+2]);
    if(mode == 1){
      return x;
    }else if (mode == 2){
      int k;
      for (k = 0; k < 3; k++){
	if(polygons->m[0][i+k] == x){
	  return polygons->m[1][i+k];
	}
      }
    }else{
      int k;
      for (k = 0; k < 3; k++){
	if(polygons->m[0][i+k] == x){
	  return polygons->m[2][i+k];
	}
      }
    }
  }else{
    x = max3(polygons->m[0][i],polygons->m[0][i+1],polygons->m[0][i+2]);
    if(mode == 1){
      return x;
    }else if (mode == 2){
      int k;
      for (k = 0; k < 3; k++){
	if(polygons->m[0][i+k] == x){
	  return polygons->m[1][i+k];
	}
      }
    }else{
      int k;
      for (k = 0; k < 3; k++){
	if(polygons->m[0][i+k] == x){
	  return polygons->m[2][i+k];
	}
      }
    }
  }
}
