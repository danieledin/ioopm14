#include "starsim.h"
#include <CUnit/CUnit.h>

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <unistd.h>


typedef struct body {
float position_x;
float position_y;
  float  mass;
  float velocity_x;
  float velocity_y;
  float acceleration_x;
  float acceleration_y;
  float force_x;
  float force_y;
} body;



static struct body * makeTestStar(){
  struct  body *testStar = malloc (sizeof(struct body));

  testStar->force_y = 0.0;
  testStar->force_x = 0.0;
  testStar->position_x = 400.0;
  testStar->position_y = 400.0;
  testStar->mass = 2.0;
  testStar->velocity_x = 1.0;
  testStar->velocity_y = -1.0;
  return testStar;
}


static struct body * makeTestStar2(){
  struct  body *testStar = malloc (sizeof(struct body));

  testStar->force_x = 0.0;
  testStar->force_y = 0.0;
  testStar->position_x = 200.0;
  testStar->position_y = 200.0;
  testStar->mass = 2.0;
  testStar->velocity_x = 1.0;
  testStar->velocity_y = -1.0;
  return testStar;
}

static void testAddForce(body *a, body *b){

  CU_ASSERT(fabs(a->force_x + 0.008000) < 0.0001);
  CU_ASSERT(fabs(a->force_y + 0.008000) < 0.0001);
  CU_ASSERT(fabs(b->force_x - 0.008000) < 0.0001);
  CU_ASSERT(fabs(b->force_y - 0.008000) < 0.0001);

  if (fabs(a->force_x + 0.008000) < 0.0001){
    printf("A force_x correct\n");
  }

  if (fabs(a->force_y + 0.008000) < 0.0001){
    printf("A force_y correct\n");
  }


  if (fabs(b->force_x - 0.008000) < 0.0001){
    printf("B force_x correct\n");
  }

  if (fabs(b->force_y - 0.008000) < 0.0001){
    printf("B force_y correct\n");
  }
  /*
    printf("ax test force: %f \n", a->force_x);
    printf("ay test force: %f \n", a->force_y);
    printf("bx test force: %f \n", b->force_x);
    printf("by test force: %f \n", b->force_y);
  */

}


static void testSetAcceleration(struct body* testStar) {
  setAcceleration(testStar);

  CU_ASSERT(fabs(testStar->acceleration_x + 0.004000) < 0.0001);
  CU_ASSERT(fabs(testStar->acceleration_x + 0.004000) < 0.0001);

  if (fabs(testStar->acceleration_x + 0.004000) < 0.0001){
    printf("acceleration_x correct\n");
  }

  if (fabs(testStar->acceleration_y + 0.004000) < 0.0001){
    printf("acceleration_y correct\n");
  }
  /*
    printf("test Acceleration: %f \n", testStar->acceleration_x);
    printf("test Acceleration: %f \n", testStar->acceleration_y);
  */
}

static void testSetVelocity(struct body* testStar){
  setVelocity(testStar);
  CU_ASSERT(fabs(testStar->velocity_x - 0.999992) < 0.0001);
  CU_ASSERT(fabs(testStar->velocity_y + 1.000008) < 0.0001);

  if (fabs(testStar->velocity_x - 0.999992) < 0.0001){
    printf("velocity_x correct\n");
  }

  if (fabs(testStar->velocity_y + 1.000008) < 0.0001){
    printf("velocity_y correct\n");
  }

  /*
    printf("test Velocity: %f \n", testStar->velocity_x);
    printf("test Velocty: %f \n", testStar->velocity_y);
  */
}

static void testSetPosition(struct body* testStar){
  setPosition(testStar);
  CU_ASSERT(fabs(testStar->position_x - 400.002014) < 0.0001);
  CU_ASSERT(fabs(testStar->position_y - 399.997986) < 0.0001);

  if (fabs(testStar->position_x - 400.002014) < 0.0001){
    printf("position_x correct\n");
  }

  if (fabs(testStar->position_y - 399.997986) < 0.0001){
    printf("position_y correct\n");
  }

  printf("test position_X: %f \n", testStar->position_x);
  printf("test position_Y: %f \n", testStar->position_y);
}

static void testUpdateForces(){

  struct body* test_a = makeTestStar();
  struct body* test_b = makeTestStar2();
  struct body* test_c = makeTestStar2();
  struct body* test_d = makeTestStar2();
  test_c->position_x = 50;
  test_c->position_y = 50;

  test_d->position_x = 700;
  test_d->position_y = 700;

  struct body* stars = malloc (4 * sizeof(struct body*));
  stars[0] = *test_a;
  stars[1] = *test_b;
  stars[2] = *test_c;
  stars[3] = *test_d;
  updateForces(100, stars);

  CU_ASSERT_EQUAL(stars[0].position_x, stars[0].position_x)
  CU_ASSERT_EQUAL(stars[0].position_y, stars[0].position_y)

  printf("test position_X UpdateForces: %f \n", stars[0].position_x);
  printf("test position_Y UpdateForces: %f \n", stars[0].position_y);


}




int main(int argc, char *argv[])
{
  testUpdateForces();  

  struct body* testStar_a = makeTestStar();
  struct body* testStar_b = makeTestStar2();

  testAddForce(testStar_a, testStar_b);
  testSetAcceleration(testStar_a);
  testSetVelocity(testStar_a);
  testSetPosition(testStar_a);






  return 0;
}
