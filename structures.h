// TODO : update naming for consistency

#ifndef __STRUCTURES_H_INCLUDED__ // include guard
#define __STRUCTURES_H_INCLUDED__

//#include <stdlib.h>
//#include <math.h>
//#include <vector>

class XY 
{
	private:
	// member variables
  float x;
  float y;

	public:
	// constructors
  XY ();
  XY (float, float);
	// getters
	float get_x ();
	float get_y ();
} ;

class AABB 
{
	private:
	// member variables
  XY center;
  XY halfDimension;

  public:
	// constructors
  AABB ();
  AABB (XY, XY);
	// getters
	XY get_center ();
	XY get_halfDimension ();
	// functional methods
  bool contains_XY (XY);
  bool intersects_AABB (AABB);
} ;

class QuadTree 
{
	private:
	// member variables
  static const int QT_NODE_CAPACITY = 4;
  AABB boundary;
  std::vector<XY> points;
  QuadTree * northWest;
  QuadTree * northEast;
  QuadTree * southWest;
  QuadTree * southEast;
  
  public:
	// constructors
  QuadTree ();
  QuadTree (AABB);
	// getters
	AABB get_AABB ();
	std::vector<XY> get_points ();
	QuadTree * get_northWest ();
	QuadTree * get_northEast ();
	QuadTree * get_southWest ();
	QuadTree * get_southEast ();
	// functional methods
  bool insert (XY);
  void subdivide ();
  std::vector<XY> query_AABB (AABB);
} ;

#endif
