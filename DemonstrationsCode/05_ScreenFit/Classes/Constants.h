//
//  Constants.h
//
//  Created by Mr_lee on 14-11-7.
//
//

#ifndef _Constants_h
#define _Constants_h
//宏替换
#define Visible_Origin  Director::getInstance()->getVisibleOrigin()

#define   Visible_Size    Director::getInstance()->getVisibleSize()

#define   Visible_Center  Vec2(Visible_Origin.x + Visible_Size.width/2, Visible_Origin.y + Visible_Size.height/2)

#define Visible_Top_Center Vec2(Visible_Center.x,Visible_Origin.y+Visible_Size.height)

#define Visible_Top_Left   Vec2(Visible_Origin.x,Visible_Origin.y+Visible_Size.height)
#define Visible_Top_Right  Vec2(Visible_Origin.x + Visible_Size.width , Visible_Origin.y + Visible_Size.height )
#define Visible_Bottom_Right Vec2(Visible_Origin.x + Visible_Size.width,Visible_Origin.y)

#define b2Factorial 32
#endif
