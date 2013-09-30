// TODO : update naming for consistency

#include "structures.h"

// XY constructor : creates a cartesian coordinate pair object to represent vectors
//	parameters :
//		float x, the x coordinate of a cartesian coordinate pair
//		float y, the y coordinate of a cartesian coordinate pair
//	function :
//		?
XY::XY (float x, float y) : x(x), y(y) {} ;

// AABB constructor : creates an axis-aligned bounding box with center coordinate and relative half dimension
//	parameters :
//		XY center, the cartesian coordinate pair representing the center of the AABB
//		XY halfDimension, the cartesian coordinate pair representing the size of a quadrant of the AABB relative to the center
//	function :
//		?
AABB::AABB (XY center, XY halfDimension) : center(center), halfDimension(halfDimension) {} ;

// AABB method : checks whether a point lies within the AABB
//	parameters :
//		XY p, the XY to check against
//	function :
//		checks the position of the point relative to the center against the half dimension
bool AABB::contains_XY (XY p) {
	// TODO : check this math, should it be > or >= ?
	// TODO : use getters instead of accessing members directly
	return fabs(p.x - center.x) < halfDimension.x && fabs(.y - center.y) < halfDimension.y ;
}

// AABB method : checks whether another AABB intersects the AABB
//	parameters :
//		AABB other, the AABB to check collision against
//	function :
//		checks the position of each corner of the other AABB relative to the 
bool AABB::intersects_AABB (AABB other) {
	// TODO : check this math, can it just use contains_XY ?
	// TODO : use getters instead of accessing members directly
	// TODO : just return the boolean evaluation of the expression, remove if statement
  if ((fabs(other.center.x - center.x) <= halfDimension.x && fabs (other.center.y - center.y) <= halfDimension.y)
   || (fabs(other.center.x - center.x) <= halfDimension.x && fabs(other.halfDimension.y - center.y) <= halfDimension.y)
   || (fabs(other.halfDimension.x - center.x) <= halfDimension.x && fabs(other.center.y - center.y) <= halfDimension.y)
   || (fabs(other.halfDimension.x - center.x) <= halfDimension.x && fabs(other.halfDimension.y - center.y) <= halfDimension.y))
    return true ;
  return false ;
}

// QT constructor : creates a quadtree from an AABB representing the boundary of the tree in the cartesian plane
//	parameters :
//		AABB boundary, the AABB representing the boundary of the QT in the cartesian plane
//	function :
//		?
QT::QT (AABB boundary) : boundary(boundary) {
	// TODO : figure out what this is, maybe can do it better ?
	// TODO : (cont.) maybe give each QT a boolean member indicating the presence of subdivisions ?
  northWest = 0;
}

// QT method : adds an XY to the QT
//	paramters :
//		XY p, the XY to add to the QT
//	function :
//		attempts to put the XY into the QT (if it belongs), but if it won't fit, it puts it in a sub-QT, creating all 4 sub-QTs if they don't exist
bool QT::insert (XY p) {
		// TODO : this should probably do something more useful than just return false
		// TODO : decide if one line if statements should be bracketed, or condensed to one line, or what
    // ignore objects which do not belong in this quadtree
    if (!boundary.containsPoint(p))
      return false;
		
    // if there is space in this quad tree, add the object here
    if ((int)points.size() < QT_NODE_CAPACITY) {
			// TODO : find out if push_back is actually a std::vector method
      points.push_back(p);
      return true;
    } ;

		// TODO : this links to the TODO in the QT constructor, should northWest be 0 or NULL or what ?
    // otherwise, we need to subdivide then add the point to whichever node will accept it
    if (northWest == NULL)
      subdivide();
		
		// TODO : comment the following, but how ?
    if (northWest->insert(p)) return true;
    if (northEast->insert(p)) return true;
    if (southWest->insert(p)) return true;
    if (southEast->insert(p)) return true;

    // otherwise, the point could not be inserted for some unknown reason ( which should never happen )
    return false;
}

// create four children which fully divide this quad into four quads of equal area
void QT::subdivide () {
  XY halfDimension = XY(boundary.halfDimension.x / 2, boundary.halfDimension.y / 2);

  XY northWestCenter = XY(boundary.center.x - (boundary.halfDimension.x / 2), boundary.center.y + (boundary.halfDimension.y / 2));
  XY northEastCenter = XY(boundary.center.x + (boundary.halfDimension.x / 2), boundary.center.y + (boundary.halfDimension.y / 2));
  XY southWestCenter = XY(boundary.center.x - (boundary.halfDimension.x / 2), boundary.center.y - (boundary.halfDimension.y / 2));
  XY southEastCenter = XY(boundary.center.x + (boundary.halfDimension.x / 2), boundary.center.y - (boundary.halfDimension.y / 2));

  AABB northWestAABB = AABB(northWestCenter, halfDimension);
  AABB northEastAABB = AABB(northEastCenter, halfDimension);
  AABB southWestAABB = AABB(southWestCenter, halfDimension);
  AABB southEastAABB = AABB(southEastCenter, halfDimension);

  northWest = new QT(northWestAABB);
  northEast = new QT(northEastAABB);
  southWest = new QT(southWestAABB);
  southEast = new QT(southEastAABB);
}

// find all points which appear within a range
std::vector<XY> QT::queryRange (AABB range) {
  // prepare an array of results
  std::vector<XY> pointsInRange;

  // automatically abort if the range does not collide with this quad
  if (!boundary.intersectsAABB(range))
    return pointsInRange; // Empty list

  // check objects at this quad level
  for (int p = 0; p < (int)points.size(); p++) {
    if (range.containsPoint(points.at(p)))
      pointsInRange.push_back(points.at(p));
  }

  // terminate here, if there are no children
  if (!northWest)
    return pointsInRange;

  // otherwise, add the points from the children
  std::vector<XY> pointsInRangeNorthWest = northWest->queryRange(range);
  pointsInRange.insert(pointsInRange.end(), pointsInRangeNorthWest.begin(), pointsInRangeNorthWest.end());
  std::vector<XY> pointsInRangeNorthEast = northEast->queryRange(range);
  pointsInRange.insert(pointsInRange.end(), pointsInRangeNorthEast.begin(), pointsInRangeNorthEast.end());
  std::vector<XY> pointsInRangeSouthWest = southWest->queryRange(range);
  pointsInRange.insert(pointsInRange.end(), pointsInRangeSouthWest.begin(), pointsInRangeSouthWest.end());
  std::vector<XY> pointsInRangeSouthEast = southEast->queryRange(range);
  pointsInRange.insert(pointsInRange.end(), pointsInRangeSouthEast.begin(), pointsInRangeSouthEast.end());

  return pointsInRange;
}

// TODO FIXME 

// TODO : find out if this is necessary
// arbitrary constant to indicate how many elements can be stored in this quad tree node
// QT::QT_NODE_CAPACITY = 4;

