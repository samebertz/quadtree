#ifndef __STRUCTURES_H_INCLUDED__ // include guard
#define __STRUCTURES_H_INCLUDED__

#include <stdlib.h>
#include <math.h>
#include <vector>

class XY 
{
  public:

  float x;
  float y;

  //public:

  XY ();
  XY (float, float);
} ;

class AABB 
{
  public:

  XY center;
  XY halfDimension;

  //public:

  AABB ();
  AABB (XY, XY);

  bool containsPoint (XY);
  bool intersectsAABB (AABB);
} ;

class QuadTree 
{
  public:

  static const int QT_NODE_CAPACITY = 4;
  
  AABB boundary;
  std::vector<XY> points;
  
  QuadTree * northWest;
  QuadTree * northEast;
  QuadTree * southWest;
  QuadTree * southEast;
  
  //public:

  QuadTree ();
  QuadTree (AABB _boundary);

  bool insert (XY);
  void subdivide ();
  std::vector<XY> queryRange (AABB);
} ;

#endif
