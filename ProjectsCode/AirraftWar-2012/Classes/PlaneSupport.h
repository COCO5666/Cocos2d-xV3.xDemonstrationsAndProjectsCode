//
//  PlaneSupport.h
//  a4
//
//  Created by student on 15-7-13.
//
//

#ifndef __a4__PlaneSupport__
#define __a4__PlaneSupport__

#include "cocos2d.h"
USING_NS_CC;

class PlaneSupport : public Sprite
{
public:
	PlaneSupport();
	~PlaneSupport();
public:
	virtual bool init();
	CREATE_FUNC(PlaneSupport);
public:
	//
	void init_support(int index);
};
#endif /* defined(__a4__PlaneSupport__) */
