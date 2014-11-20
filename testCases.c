#include <stdlib.h>
#include <CUnit/Basic.h>
#include "starsim.h"



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


void testAddForce(void){

  struct Body* a = makeTestStar();
  Star*  b = makeTestStar2();

  addForce(a,b);


  CU_ASSERT(fabs(a->force_x - 4.9920000) < 0.0001);
  CU_ASSERT(fabs(a->force_y - 3.9920000) < 0.0001);
  CU_ASSERT(fabs(b->force_x - 2.008000) < 0.0001);
  CU_ASSERT(fabs(b->force_y - 3.008000) < 0.0001);

  /*
  if (fabs(a->force_x + 0.008000) < 0.0001){
    printf("A force_x correct\n");
  }

  if (fabs(a->force_y + 0.008000) < 0.0001){
    printf("A force_y correct\n");
  }


  if (fabs(b->force_x - 0.008000) < 0.0001){
    printf("B force_x correct\n");
  }

  if (fabs(b->force_y e 0.008000) < 0.0001){
    printf("B force_y correct\n");
  }
  */
  /*
    printf("ax test force: %f \n", a->force_x);
    printf("ay test force: %f \n", a->force_y);
    printf("bx test force: %f \n", b->force_x);
    printf("by test force: %f \n", b->force_y);
  */
  free(a);
  free(b);

}


void testSetAcceleration(void) {

  Star*  testStar = makeTestStar();

  setAcceleration(testStar);

  CU_ASSERT(fabs(testStar->acceleration_x - 2.500000) < 0.0001);
  //  CU_ASSERT(fabs(testStar->acceleration_x - 0.000000) < 0.0001);
  /*
  if (fabs(testStar->acceleration_x + 0.004000) < 0.0001){
    printf("acceleration_x correct\n");
  }

  if (fabs(testStar->acceleration_y + 0.004000) < 0.0001){
    printf("acceleration_y correct\n");
  }
  */
  /*
    printf("test Acceleration: %f \n", testStar->acceleration_x);
    printf("test Acceleration: %f \n", testStar->acceleration_y);
  */
  free(testStar);
}

void testSetVelocity(void){
  Star*  testStar = makeTestStar();
  setVelocity(testStar);
  CU_ASSERT(fabs(testStar->velocity_x - 1.005000) < 0.0001);
  CU_ASSERT(fabs(testStar->velocity_y - 2.000000) < 0.0001);
  /*
  if (fabs(testStar->velocity_x - 0.999992) < 0.0001){
    printf("velocity_x correct\n");
  }

  if (fabs(testStar->velocity_y + 1.000008) < 0.0001){
    printf("velocity_y correct\n");
  }
  */
  /*
    printf("test Velocity:nclude <CUnit/Basic.h> %f \n", testStar->velocity_x);
    printf("test Velocty: %f \n", testStar->velocity_y);
  */
  free (testStar);
}

void testSetPosition(void){
  Star*  testStar = makeTestStar();
  setPosition(testStar);
  CU_ASSERT(fabs(testStar->position_x - 400.002014) < 0.0001);
  CU_ASSERT(fabs(testStar->position_y - 400.003998) < 0.0001);
  /*
  if (fabs(testStar->position_x - 400.002014) < 0.0001){
    printf("position_x correct\n");
  }

  if (fabs(testStar->position_y - 399.997986) < 0.0001){
    printf("position_y correct\n");
  }

  printf("test position_X: %f \n", testStar->position_x);
  printf("test position_Y: %f \n", testStar->position_y);
  */  
  free(testStar);
}

void testUpdateForces(void){

  Star*  test_a = makeTestStar();
  Star*  test_b = makeTestStar2();


	// Star* stars[2];
  Star*  stars = malloc (4 * sizeof(struct Body*));
  stars[0] = *test_a;
  stars[1] = *test_b;

  updateForces(3, stars);

  CU_ASSERT(fabs(stars[0].position_x - 400.002014) < 0.0001);
  CU_ASSERT(fabs(stars[0].position_y - 400.003998) < 0.0001);
  CU_ASSERT(fabs(stars[1].position_x - 200.001999) < 0.0001);
  CU_ASSERT(fabs(stars[1].position_y - 200.005997) < 0.0001);

  /*
  printf("\n\ntest position_0X UpdateForces: %f \n", stars[0].position_x);
  printf("test position_0Y UpdateForces: %f \n", stars[0].position_y);
  printf("test position_1X UpdateForces: %f \n", stars[1].position_x);
  printf("test position_1Y UpdateForces: %f \n", stars[1].position_y);
  */

  free(test_a);
  free(test_b);

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
  /*
  pSuite2 = CU_add_suite("Advanced Functions Suite", init_suite_2, clean_suite_2);
  if (NULL == pSuite2)
    {
      CU_cleanup_registry();
      return CU_get_error();
    }
  */

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
