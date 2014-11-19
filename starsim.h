/**
 * @file starsim.h
 * @author Alexander Lind & Daniel Edin
 * @date 19 nov 2014
 * @brief A program for simulating a system of stars. 
 * @details Running the program starts the simulation with the standard values which is 200 stars and 1000 iterations. If running the program with arguments, the first argument is the number of stars for the simulations and the second argument is for how many iterations you want to simulate the system.
 */

/**
 * @brief A body Star represents a star in the system. A star has mass, position, acceleration, velocity and force. 
 * 
 * 
 */
typedef struct body *Star;


/**
 * @brief Sets the new acceleration for body using body's force and mass.
 * 
 * 
 * @param body the star that the function will set the acceleration for.  
 */
static void setAcceleration (Star);
/**
 * @brief Sets the new velocity for body using the global variable gdt, body's old velocity and body's acceleration.
 * 
 * @param body the star that the function will set the velocity for. 
 */
static void setVelocity (Star);
/**
 * @brief Sets the new position for body using the global variable gdt along with body's velocity, old position and acceleration.
 * 
 * 
 * @param body  the star that the function will set the position for. 
 */
static void setPosition (Star);
/**
 * @brief Creates the bodies used in the simulation. If possible (if the system has enough memory), creates N bodies and places them at most 300 points from the middle of the simulation window. It randomizes the mass, and sets the velocity in a way so that the stars will move in a circular pattern. 
 * 
 * 
 * @param numberOfStars The number of bodies that will be created for the simulation.
 * @return An array of bodies of size numberOfStars
 */
static struct body *createBodies (int numberOfStars);
/**
 * @brief Resets the force of numberOfStars bodies in Star
 *
 * 
 * @param star the first body in the array of bodies.
 * @param numberOfStars the number of bodies that the function will reset the force for.
 */
static void resetForce(Star star, int numberOfStars);
/**
 * @brief Calculates the distance between star1 and star2 using the stars' positions. 
 * 
 * 
 * @param star1 the first star.
 * @param star2 the second star. 
 * 
 * @return the distance between star1 and star2. 
 */
static float distance(Star star1, Star star2);
/**
 * @brief Adds the force to star1 and star2 using the stars' masses and position. 
 * 
 * 
 * @param star1 the first star that will have its force updated.
 * @param star2 the second star that will have its force updated.
 */
static void addForce(Star star1, Star star2);
/**
 * @brief Updates the force, velocity, acceleration and position for the first numberOfStars stars in starList. The function calls the functions addForce, setVelocity, setAcceleration and setPostition.
 * 
 * 
 * @param numberOfStars The number of Stars that will be updated.
 * @param starList The array of stars that will be updated.
 */
static void updateForces(int numberOfStars, Star starList);


