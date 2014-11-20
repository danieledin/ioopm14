/**
 * @file starsim.c
 * @author Alexander Lind & Daniel Edin
 * @date 19 nov 2014
 * @brief A program for simulating a system of stars. 
 * @details Running the program starts the simulation with the standard values which is 200 stars and 1000 iterations. If running the program with arguments, the first argument is the number of stars for the simulations and the second argument is for how many iterations you want to simulate the system.
 */

#include "starsim.h"



#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

#ifdef ANIMATE
#include <X11/Xlib.h> 
#include <X11/Xutil.h>

#define X_SIZE 800
#define Y_SIZE 800
#endif

#define prec float
#define PI 3.14159265359

static float G = 0.8;

static prec gdt = 0.002;

typedef struct body {
  float position_x;
  float position_y;
  float mass;
  float velocity_x;
  float velocity_y;
  float acceleration_x;
  float acceleration_y;
  float force_x;
  float force_y;
} body;

static prec newRand() 
{
  prec r = (prec)((double)rand()/(double)RAND_MAX);
  return r;
}

static void setAcceleration (struct body *star)
{
  star->acceleration_x = (star->force_x) / (star->mass);
  star[0].acceleration_y = (star[0].force_y) / (star[0].mass);
}

static void setVelocity (struct body *star)
{
  star->velocity_x = (star->velocity_x) + ((star->acceleration_x) * gdt);
  star->velocity_y = (star->velocity_y) + ((star->acceleration_y) * gdt);

}

static void setPosition (struct body *star)
{
  star->position_x = (star->position_x) + ((star->velocity_x) * gdt) + (0.5*((star->acceleration_x) * gdt * gdt));
  star->position_y = (star->position_y) + ((star->velocity_y) * gdt) + (0.5*((star->acceleration_y) * gdt * gdt));

} 

static struct body *createBodies (int numberOfStars)
{

  time_t t;
  srand((unsigned) time(&t));

  int i;
  struct  body *stars = malloc (numberOfStars * sizeof(struct body ));
  if (stars == NULL)
    {
      printf("   Malloc fail. \n   Not enough memory for struct body allocation \n");
      exit(0);
    }

  memset(stars, 0, numberOfStars*sizeof(struct body));
  for (i = 0; i < numberOfStars-1; i++)
    {
      float ang = 360 * newRand ();
      stars[i].position_x = (cos(ang) * newRand() * 300) + 400;
      stars[i].position_y = (sin(ang) * newRand() * 300) + 400;
      stars[i].mass = (newRand()*2) + 1;
      stars[i].velocity_x = (400 - stars[i].position_y) * 0.05;
      stars[i].velocity_y = -(400 - stars[i].position_x) * 0.05;
      
    }


  return stars; 

}


static void resetForce(body* starList, int numberOfStars)
{
  for (int i = 0; i <= numberOfStars-1; i++)
    {
      starList[i].force_y = 0;
      starList[i].force_x = 0;
    }
}


static float distance(struct body *a, struct body *b) {
  float x = (a->position_x - b->position_x) * (a->position_x - b->position_x);
  float y = (a->position_y - b->position_y) * (a->position_y - b->position_y);

  float distance = sqrt (x+y);  // float sqrt!

  return distance;
}
 

static void addForce(body *a, body *b)
{
  float force_x;
  float force_y;
  float distance_x = (b->position_x - a->position_x);
  float distance_y = (b->position_y - a->position_y);
  float distance_r = (distance(a, b));
  if (distance_y != 0)
    {
      force_y = ((a->mass * b->mass) / (distance_r * distance_r)) * G * distance_y;
      a->force_y += force_y;
      b->force_y -= force_y;
    }

  if ( distance_x != 0)
    {
      force_x = ((a->mass * b->mass) / (distance_r * distance_r)) * G * distance_x;
     
      a->force_x += force_x;
      b->force_x -= force_x;
    }
}


static void updateForces(int numberOfStars, body* star)
{
  for (int i = 0; i < numberOfStars-1; i++)
    {
      for (int j = i+1; j <= numberOfStars-1; j++)
	{ 
	  addForce(&star[i], &star[j]);
	}   
      setAcceleration(&star[i]);
      setVelocity(&star[i]);
      setPosition(&star[i]);
    }
}



#ifdef ANIMATE
static void copyToXBuffer(body* star, XPoint* points, int N)
{
  for (int i = 0; i <= N-1; i++)
    {
      points[i].x = star[i].position_x;
      points[i].y = star[i].position_y;
    }
}
#endif





#ifndef UNITTEST
int main(int argc, char* argv[]) {
  


  int N = 200;
  int iter = 1000;
  int i = 0;

  while (i<100) {
    int rand = newRand();  
    printf("%d\n", rand);
    i++;
  }

  if(argc == 3)
    {
      while (atoi(argv[1]) < 0 )
	{
	  printf("Please enter a valid amount of stars\n");
	  scanf("%s", argv[1]);
	}
      while (atoi(argv[2]) < 0)
	{
	  printf("Please enter a valid amount of iterations:\n");
	  scanf("%s", argv[2]);
	}
	
      N = atoi(argv[1]);
      iter = atoi(argv[2]);
	
    }




  struct body *stars = createBodies(N);


#ifdef ANIMATE
  XPoint* points = malloc(sizeof(XPoint)*N);
  if (points == NULL)
    {
      printf("   Malloc fail. \n   Not enough memory for XPoint allocation \n");
      exit(0);
    }
  
  Display* disp;
  Window window, rootwin;
  int screen;

  disp = XOpenDisplay(NULL);
  screen = DefaultScreen(disp);
  rootwin = RootWindow(disp,screen);
  window = XCreateSimpleWindow(disp,rootwin,
                               0,0,X_SIZE,Y_SIZE,1,0,0);
  GC gc = XCreateGC(disp, window, 0, 0);
  XSetForeground(disp, gc, WhitePixel(disp, screen));
  XSetBackground(disp, gc, BlackPixel(disp, screen));
  XMapWindow(disp,window);

  XClearWindow(disp,window);	
	
  copyToXBuffer(stars, points, N);
  XDrawPoints(disp, window, gc, points, N, 0);

  XFlush(disp);

#endif

  clock_t start = clock();
  for(int i = 0; i < iter; i++)
    {
      resetForce(stars, N);
      updateForces(N, &stars[0]);

#ifdef ANIMATE
      copyToXBuffer(&stars[0], points, N);
      
      XDrawPoints(disp, window, gc, points, N, CoordModeOrigin);
      
      XClearWindow(disp,window);	
      
      
#endif
    }
  clock_t stop = clock();
  float diff = (float)(stop - start)/CLOCKS_PER_SEC;
  printf("Total: %lf seconds\n",diff);
  printf("Bodies: %d\n",N);
  printf("Iterations: %d\n", iter);

#ifdef ANIMATE
  XCloseDisplay(disp);
  free(gc);
  free(points);  
#endif

  free(stars);



  return 0;
}
#endif


