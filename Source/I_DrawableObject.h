#pragma once

/**
	*@class Interface DrawableObject
	*@brief Every object which need to be draw must implement this interface
	*@author:  Liu Yi
	*@inherits:  null
	*@Used By:      
	*@date 3/12/2014
	*
*/

class I_DrawableObject
{
public:

	virtual void Draw() = 0;
	virtual void SetBufferRef() = 0;
	virtual void Destory() = 0;
};