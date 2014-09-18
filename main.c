#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#ifdef ANIMATE
#include <X11/Xlib.h>
#include <X11/Xutil.h>

#define X_SIZE 800
#define Y_SIZE 800
#endif

#define prec float
#define PI 3.14159265359


//G expressed in tons of kilos
static float G = 0.0000000667384;

static prec gdt = 0.0001;

typedef struct body {
  int position_x;
  int position_y;
  float  mass;
  float velocity_x;
  float velocity_y;
  float acceleration_x;
  float acceleration_y;
  float force_x;
  float force_y;
} body;



static void setVelocity (struct body *star)
{
  star->velocity_x = (star->velocity_x) + (star->acceleration_x) * gdt;
  star->velocity_y = (star->velocity_y) + (star->acceleration_y) * gdt;

}

static void setAcceleration (struct body *star)
{
  star->acceleration_x += (star->force_x) / (star->mass);
  star->acceleration_y += (star->force_y) / (star->mass);
}

static void setPosition (struct body *star)
{
  star->position_x = (star->position_x) + ((star->velocity_x) * gdt) + (((star->acceleration_x) * gdt * gdt) / 2);
  star->position_y = (star->position_y) + ((star->velocity_y) * gdt) + (((star->acceleration_y) * gdt * gdt) / 2);

} 

static struct body *createBodies (int N)
{
  time_t t;
  srand((unsigned) time(&t));

  int i;
  // kolla ifall NULL!!
  struct  body *stars = malloc (N* sizeof(struct body ));
  memset(stars, 0, N*sizeof(struct body));
  for (i = 0; i < N; i++)
    {
      stars[i].position_x = rand() % 100 + 350;
      stars[i].position_y = rand() % 100 + 350;
      stars[i].mass = rand() % 1000 + 1000;
    }

  return stars; 

}

static void update(body* a, prec dt)
{
  
}


static void resetForce(body* star, int N)
{
  for (int i = 0; i <= N; i++)
    {
      star[i].force_y = 0;
      star[i].force_x = 0;
    }
}

 

static float distance(body a, body b) {
  int x = (a.position_x - b.position_x) * (a.position_x - b.position_x);
  int y = (a.position_y - b.position_y) * (a.position_y - b.position_y);

  float distance = sqrt (x+y);

  return distance;
}

static void addForce(body *a, body *b)
{

  // DIV 0!
  float force_x;
  float force_y;
  float distance_x = (a->position_x - b->position_x);
  if (distance_x != 0)
    {
      force_x = ((a->mass * b->mass) / (fabsf (distance_x))) * G;
    }
  float distance_y = (a->position_y - b->position_y);
  if (distance_y != 0)
    {
      force_y = ((a->mass * b->mass) / (fabsf (distance_y))) * G;
    }



  if (distance_x < 0)
    {
      a->force_x += force_x;
      b->force_x += 0 - force_x;
    }
  else if (distance_x > 0)
    {
      a->force_x += 0 - force_x;

      b->force_x += force_x;
    }

  if (distance_y < 0)
    {
      a->force_y += force_y;
      b->force_y += 0 - force_y;
    }
  else if (distance_y > 0)
    {
      a->force_y += 0 - force_y;
      b->force_y += force_y;
    }
 
}

static prec newRand() 
{
  prec r = (prec)((double)rand()/(double)RAND_MAX);
  return r;
}


void init(int N, body* star)
{
  //kopiera createBodies hit 
}


static void updateForces(int N, body* star)
{
  for (int i = 0; i < N; i++)
    {
      for (int j = i+1; j <= N; j++)
	{ 
	  addForce(&star[i], &star[j]);
	}   
      setAcceleration(&star[i]);
      setVelocity(&star[i]);
      setPosition(&star[i]);
    }
  setAcceleration(&star[N]);
  setVelocity(&star[N]);
  setPosition(&star[N]);
}

// Manually copy coordinates from stars into points (to be drawn).
// Look at the manual file for XPoint to see which 
// format XPoint accepts its coordinates in.
#ifdef ANIMATE
static void copyToXBuffer(body* star, XPoint* points, int N)
{
  // points->x = star->position_x
  for (int i = 0; i <= N; i++)
    {
      points[i].x = star[i].position_x;
      points[i].y = star[i].position_y;
    }
}
#endif

int main(int argc, char* argv[]) {



  int N = 200;
  int iter = 1000;

  
  if(argc == 3)
    {
      N = atoi(argv[1]);
      iter = atoi(argv[2]);
    }


  struct body *stars = createBodies(N);


  //  copyToXBuffer(&stars, &points, N);
  /*
  printf("random: %f\n", newRand());

  printf("position_x [0] test: %d\n", stars[0].position_x);
  printf("position_x [52] test: %d\n", stars[52].position_x);


  printf("Test y acceleration: %f\n", stars[0].acceleration_y);
  printf("Test y acceleration no. 199: %f\n", stars[199].acceleration_y);
  printf("Test y velocity: %f\n", stars[0].velocity_y);
  printf("Test y velocity: %d\n", stars[0].position_y);
  printf("Test force old %f\n", stars[8].force_x);

  printf("Test force new %f\n", stars[8].force_x);
  */
#ifdef ANIMATE
  XPoint* points = malloc(sizeof(XPoint)*N);
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

      updateForces(N, &stars[0]);
      resetForce(&stars[0], N);
      //printf("position_x [0] test: %d\n", stars[0].position_x);
      //printf("Test y acceleration: %f\n", stars[0].acceleration_y);
      //printf("Test y acceleration no. 199: %f\n", stars[199].acceleration_y);
      //printf("Test y velocity: %f\n", stars[0].velocity_y);

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
#endif

  return 0;
}
