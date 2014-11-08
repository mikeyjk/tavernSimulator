#ifndef VEC3_H
#define VEC3_H

//-------------------------------------------------------------------------------

/**
	*@class Vec3
	*@brief this class is the basic vector/point class.
	*		It can handle vector type operations like dot and cross product.
	*		It can also be used purely as a 3d point.
	*
	*@author Karl Tysoe
	*@version 01
	*@date 8/09/2013
	*
*/

//-------------------------------------------------------------------------------

#include <math.h>

//-------------------------------------------------------------------------------

class Vec3 {
public:
	/**
		*@brief Vec3 constructor
		*
		* the basic constructor for the Vec3 Class
		*@param nil
		*@post calls the clear function to set everything to 0
	*/
	Vec3();

	//-------------------------------------------------------------------------------

	/**
		*@brief Vec3 param constructor
		*
		* The param constructor for the Vec3 Class, initializes x, y, z, to the given coord.
		*@param x - float, y - float, z - float
		*@post initializes everything to the given data
	*/
	Vec3(float x, float y, float z);

	//-------------------------------------------------------------------------------

	/**
		*@brief clear function
		*
		* This function resets x, y, z to 0
		*@param nil
		*@post re-initialises everything to 0
	*/
	void clear();

	//-------------------------------------------------------------------------------

	/**
		*@brief setX function
		*
		* basic setter for the X float
		*@param x - float
		*@post sets X to given x
	*/
	void setX(float x);

	//-------------------------------------------------------------------------------

	/**
		*@brief setY function
		*
		* basic setter for the Y float
		*@param y - float
		*@post sets Y to given y
	*/
	void setY(float y);

	//-------------------------------------------------------------------------------

	/**
		*@brief setZ function
		*
		* basic setter for the Z float
		*@param z - float
		*@post sets Z to given z
	*/
	void setZ(float z);

	//-------------------------------------------------------------------------------

	/**
		*@brief getX function
		*
		* basic getter for the X float
		*@param nil
		*@return float
		*@post returns X
	*/
	float getX();

	//-------------------------------------------------------------------------------

	/**
		*@brief getY function
		*
		* basic getter for the Y float
		*@param nil
		*@return float
		*@post returns Y
	*/
	float getY();

	//-------------------------------------------------------------------------------

	/**
		*@brief getZ function
		*
		* basic getter for the Z float
		*@param nil
		*@return float
		*@post returns Z
	*/
	float getZ();

	//-------------------------------------------------------------------------------

	/**
		*@brief dot Product function
		*
		* Calculates the dot product, with the supplied Vec3, and the one its called from.
		* Example: 2 Vec3s , Vec1 and Vec2, call by Vec1.dotProd(Vec2)
		*
		*@param v - Vec3
		*@return float
		*@post returns the dot product as a float
	*/
	float dotProd(Vec3 v);

	//-------------------------------------------------------------------------------

	/**
		*@brief cross product function
		*
		* Calculates the cross product, with the supplied Vec3, and the one its called from.
		* Example: 2 Vec3s , Vec1 and Vec2, call by Vec1.dotProd(Vec2)
		*
		*@param v - Vec3
		*@return Vec3
		*@post returns the cross product as a Vec3
	*/
	Vec3 xProd(Vec3 v);

	//-------------------------------------------------------------------------------

	/**
		*@brief Length function
		*
		* Calculates the length of the vector
		* Example: Vec1.length()
		*
		*@param nil
		*@return float
		*@post returns the length as a float
	*/
	float length();

	//-------------------------------------------------------------------------------

	/**
		*@brief Normalize function
		*
		* Calculates the Unit Normal Vector of the defined vector
		* Example: Vec1 = Vec1.normalize()
		*
		*@param nil
		*@return Vec3
		*@post returns the unit normal of the vector called
	*/
	Vec3 normalize();

	//-------------------------------------------------------------------------------

	/**
		*@brief degrees to radians function
		*
		* Not specifically oriented with Vec3, but a handy function.
		* calculates the radian value for a given degree.
		*
		*@param deg - float
		*@return float
		*@post returns the radian value of a degree
	*/
	float degreesToRadians(float deg);

	//-------------------------------------------------------------------------------

	/**
		*@brief rotate function
		*
		* rotates the vector to the given angle
		* actually changes the vec3 used
		*
		*@param angle - float
		*@return nil
		*@post changes the vector to point to the angle provided
	*/
	void rotate(float angle);

	//-------------------------------------------------------------------------------

	/**
		*@brief operator+ override
		*
		* Allows the user to add 2 vectors together
		* Example: 2 Vec3s , Vec1 and Vec2, call by Vec1 + Vec2
		*
		*@param v - Vec3
		*@return Vec3
		*@post returns the added Vec3s
	*/
	Vec3 operator+ (Vec3 v);

	//-------------------------------------------------------------------------------

	/**
		*@brief operator- override
		*
		* Allows the user to subtract 2 vectors together
		* Example: 2 Vec3s , Vec1 and Vec2, call by Vec1 - Vec2
		*
		*@param v - Vec3
		*@return Vec3
		*@post returns the subtracted Vec3
	*/
	Vec3 operator- (Vec3 v);

	//-------------------------------------------------------------------------------

	/**
		*@brief operator* override
		*
		* Allows the user to multiply a vector with a scalar
		*
		*@param value - float
		*@return Vec3
		*@post returns the multiplied Vec3
	*/
	Vec3 operator* (float value);

	//-------------------------------------------------------------------------------

	/**
		*@brief operator+= override
		*
		* Allows the user to add 2 vectors together
		* Example: 2 Vec3s , Vec1 and Vec2, call by Vec1 += Vec2
		*
		*@param v - Vec3
		*@return *this Vec3
		*@post returns the Vec3 to itself.
	*/
	Vec3 operator+= (Vec3 v);

	//-------------------------------------------------------------------------------

	/**
		*@brief operator-= override
		*
		* Allows the user to subtract 2 vectors together
		* Example: 2 Vec3s , Vec1 and Vec2, call by Vec1 -= Vec2
		*
		*@param v - Vec3
		*@return *this Vec3
		*@post returns the Vec3 to itself.
	*/
	Vec3 operator-= (Vec3 v);

	//-------------------------------------------------------------------------------

	/**
		*@brief operator== override
		*
		* Allows the user to test if the vector is equal to another vector
		*
		*@param v - Vec3
		*@return bool
		*@post returns true if the same, or false if not the same
	*/
	bool operator== (Vec3 v);

	//-------------------------------------------------------------------------------

	/**
		*@brief operator= override
		*
		* Allows the user to copy another Vec3 to this one
		*
		*@param v - Vec3
		*@return nil
		*@post copies the Vec3 to this
	*/
	void operator= (Vec3 v);

    /**
     * @brief new operator**
     *        Allows the user to dot product this Vec3 with another one
     * @param v - another Vec3
     * @return float - the result of this dot product
     */
    float operator* (Vec3 v);

	void rotateByPoint(Vec3 Center, float angle);
public:
	/// X variable - float
	float X;

	/// Y variable - float
	float Y;

	/// Z variable - float
	float Z;
};

#endif
