#include <stdlib.h>
#include <math.h>
#include <vector>

using namespace std;

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
  vector<XY> points;
  
  QuadTree * northWest;
  QuadTree * northEast;
  QuadTree * southWest;
  QuadTree * southEast;
  
  //public:

  QuadTree ();
  QuadTree (AABB _boundary);

  bool insert (XY);
  void subdivide ();
  vector<XY> queryRange (AABB);
} ;
