#include <stdlib.h>
#include <CUnit/Basic.h>
#include "starsim.h"

#define UNITTEST

Star*  makeTestStar(){
  Star* testStar = malloc(sizeof(struct Body));

  testStar->force_y = 4.0;
  testStar->force_x = 5.0;
  testStar->position_x = 400.0;
  testStar->position_y = 400.0;
  testStar->mass = 2.0;
  testStar->velocity_x = 1.0;
  testStar->velocity_y = 2.0;
  return testStar;
}


Star* makeTestStar2(){
  Star* testStar = malloc (sizeof(struct Body));

  testStar->force_x = 2.0;
  testStar->force_y = 3.0;
  testStar->position_x = 200.0;
  testStar->position_y = 200.0;
  testStar->mass = 2.0;
  testStar->velocity_x = 1.0;
  testStar->velocity_y = 3.0;
  return testStar;
}



Star* createBodiesTest (int numberOfStars)
{

  //time_t t;
  //srand((unsigned) time(&t));

  int i;
  Star* stars = malloc (numberOfStars * sizeof(struct Body ));
  if (stars == NULL)
    {
      printf("   Malloc fail. \n   Not enough memory for Star allocation \n");
      exit(0);
    }

  memset(stars, 0, numberOfStars*sizeof(struct Body));
  for (i = 0; i < numberOfStars-1; i++)
    {
      float ang = 300 + i*10;
      stars[i].position_x = (cos(ang) * 300) + 400;
      stars[i].position_y = (sin(ang) * 300) + 400;
      stars[i].mass = i*2 + 1;
      stars[i].velocity_x = (400 - stars[i].position_y) * 0.05;
      stars[i].velocity_y = -(400 - stars[i].position_x) * 0.05;
      
    }


  return stars; 

}


void testAddForce(void){

  struct Body* a = makeTestStar();
  Star*  b = makeTestStar2();

  addForce(a,b);


  CU_ASSERT(fabs(a->force_x - 4.9920000) < 0.0001);
  CU_ASSERT(fabs(a->force_y - 3.9920000) < 0.0001);
  CU_ASSERT(fabs(b->force_x - 2.008000) < 0.0001);
  CU_ASSERT(fabs(b->force_y - 3.008000) < 0.0001);

  free(a);
  free(b);

}


void testSetAcceleration(void) {

  Star*  testStar = makeTestStar();

  setAcceleration(testStar);

  CU_ASSERT(fabs(testStar->acceleration_x - 2.500000) < 0.0001);
  
  free(testStar);
}

void testSetVelocity(void){
  Star*  testStar = makeTestStar();
  setVelocity(testStar);
  CU_ASSERT(fabs(testStar->velocity_x - 1.005000) < 0.0001);
  CU_ASSERT(fabs(testStar->velocity_y - 2.004000) < 0.0001);
  
  free (testStar);
}

void testSetPosition(void){
  Star*  testStar = makeTestStar();
  setPosition(testStar);
  CU_ASSERT(fabs(testStar->position_x - 400.002014) < 0.0001);
  CU_ASSERT(fabs(testStar->position_y - 400.003998) < 0.0001);
  free(testStar);
}

void testUpdateForces(void){


  Star* stars = malloc (3 * sizeof(struct Body*));
  stars = createBodiesTest(3);

  
  updateForces(3, stars);
  
  CU_ASSERT(fabs(stars[0].position_x - 393.401001) < 0.0001);
  CU_ASSERT(fabs(stars[0].position_y - 100.072586) < 0.0001);
  CU_ASSERT(fabs(stars[1].position_x - 242.370178) < 0.0001);
  CU_ASSERT(fabs(stars[1].position_y - 655.250549) < 0.0001);
  
  free(stars);

}






int init_suite_1(void)
{
 
  return 0;
 

}

int clean_suite_1(void)
{
  return 0;
}


int main()
{
  


  CU_pSuite pSuite1 = NULL;

  /* initialize the CUnit test registry */
  if (CUE_SUCCESS != CU_initialize_registry())
    return CU_get_error();

  /* add a suites to the registry */
  pSuite1 = CU_add_suite("Basic Functions Suite", init_suite_1, clean_suite_1);
  if (NULL == pSuite1)
    {
      CU_cleanup_registry();
      return CU_get_error();
    }

  /* add the tests to the suites */
  if (
      (NULL == CU_add_test(pSuite1, "test of addForce()", testAddForce)) ||
      (NULL == CU_add_test(pSuite1, "test of setAcceleration()", testSetAcceleration)) ||
      (NULL == CU_add_test(pSuite1, "test of setVelocity()", testSetVelocity))  ||
      (NULL == CU_add_test(pSuite1, "test of setPosition()", testSetPosition)) ||
      (NULL == CU_add_test(pSuite1, "test of updateForces()", testUpdateForces))
									      
  )
    {
      CU_cleanup_registry();
      return CU_get_error();
    }


  /* Run all tests using the CUnit Basic interface */
  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_cleanup_registry();
  return CU_get_error();
}
