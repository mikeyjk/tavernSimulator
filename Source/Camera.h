#pragma once
#include "Vec3.h"

/**
	*@class Camera
	*@brief contain the Camera position, lookat point , Up vector and Side Vector
	*@author:  Liu Yi
	*@inherits:  null
	*@Used By:      
	*@date 3/12/2014
	*
*/
class Camera
{
public:
	

	static Camera * Instance();

	/**
	 *@brief This function will Get the position of Camera
	 *
	 * 
	 * 
	 *@param void
	 *@post Return a Vec3 of Position
	*/
	Vec3 GetPosition();
	/**
	 *@brief This function will Get the Up vector of Camera
	 *
	 * 
	 * 
	 *@param void
	 *@post Return a Vec3 of Up
	*/
	Vec3 GetUp();
	/**
	 *@brief This function will Get the Direction of Camera
	 *
	 * 
	 * 
	 *@param void
	 *@post Return a Vec3 of Up
	*/
	Vec3 GetDirection();

	/**
	 *@brief This function will Get the side vector of Camera
	 *
	 * 
	 * 
	 *@param void
	 *@post Return a Vec3 of Side
	*/
	Vec3 GetSide();

	/**
	 *@brief This function will Get the Target of Camera
	 *
	 * 
	 * 
	 *@param void
	 *@post Return a Vec3 of Target
	*/
	Vec3 GetTarget();


	/**
	 *@brief This function will Set the Position of Camera
	 *
	 * 
	 * 
	 *@param void
	 *@post Pass a Vec3 of Position
	*/
	void SetPosition(Vec3 v);


    /**
	 *@brief This function will Set the Position of Camera
	 *
	 * 
	 * 
	 *@param void
	 *@post Pass a Vec3 of Position
	*/
	void SetUp(Vec3 v);


	 /**
	 *@brief This function will Set the Target of Camera
	 *
	 * 
	 * 
	 *@param void
	 *@post Pass a Vec3 of Target
	*/
	void SetTarget(Vec3 v);


	
	 /**
	 *@brief This function will Set the Direction of Camera
	 *
	 * 
	 * 
	 *@param void
	 *@post Pass a Vec3 of Direction
	*/
	void SetDirection(Vec3 v);

	
	/**
	 *@brief This function will get the Speed of Camera
	 *
	 * 
	 * 
	 *@param void
	 *@post return a float value of Speed
	*/
	float GetSpeed();

		
	/**
	 *@brief This function will get the Speed of Camera
	 *
	 * 
	 * 
	 *@param void
	 *@post Set the value of Speed
	*/
	void SetSpeed(float num);

	/**
	 *@brief This function will rotate the Camera by Pitch
	 *
	 * 
	 * 
	 *@param void
	 *@post Rate the camera
	*/
	void RotatePitch(float num);


	/**
	 *@brief This function will rotate the Camera by Yaw
	 *
	 * 
	 * 
	 *@param void
	 *@post Rate the camera
	*/
	void RotateYaw(float num);


	void RotatePitch3rd(float num);
	void RotateYaw3rd(float num);



	float GetRotateX();
	float GetRotateY();

	

private:


	Vec3 Position;
	Vec3 Up;
	Vec3 Target;
	Vec3 Direction;
	float Speed;

	float X_degree_difference;
	float Y_degree_difference;

	void UpdateRotation();
	Camera(void);
	~Camera(void);

};

