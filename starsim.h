
/*
typedef struct body  {
  int position_x;
  int position_y;
  float  mass;
  float velocity_x;
  float velocity_y;
  float acceleration_x;
  float acceleration_y;
  float force_x;
  float force_y;

}body, *Star;
*/
struct body;
typedef struct body *Star;

static void setAcceleration (Star);
static void setVelocity (Star);
static void setPosition (Star);
static struct body *createBodies (int N);
static void resetForce(Star, int N);
static float distance(Star, Star);
static void addForce(Star, Star);
static void updateForces(int N, Star);
