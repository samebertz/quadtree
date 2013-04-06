#include "structures.h"

// Simple coordinate object to represent vectors
XY::XY (float _x, float _y) {
  x = _x;
  y = _y;
}

// Axis-aligned bounding box with half dimension and center
AABB::AABB (XY _center, XY _halfDimension) {
  center = _center;
  halfDimension = _halfDimension;
}

bool AABB::containsPoint (XY p) {
  if (fabs(p.x - center.x) < halfDimension.x && fabs(p.y - center.y) < halfDimension.y)
    return true;
  return false;
}

bool AABB::intersectsAABB (AABB other) {
  if ((fabs(other.center.x - center.x) <= halfDimension.x && fabs (other.center.y - center.y) <= halfDimension.y)
   || (fabs(other.center.x - center.x) <= halfDimension.x && fabs(other.halfDimension.y - center.y) <= halfDimension.y)
   || (fabs(other.halfDimension.x - center.x) <= halfDimension.x && fabs(other.center.y - center.y) <= halfDimension.y)
   || (fabs(other.halfDimension.x - center.x) <= halfDimension.x && fabs(other.halfDimension.y - center.y) <= halfDimension.y))
    return true ;
  return false ;
}

QuadTree::QuadTree (AABB _boundary) {
  boundary = _boundary;
  northWest = 0;
}

bool QuadTree::insert (XY p) {
    // Ignore objects which do not belong in this quadtree
    if (!boundary.containsPoint(p))
      return false;

    // If there is space in this quad tree, add the object here
    if ((int)points.size() < QT_NODE_CAPACITY) {
      points.push_back(p);
      return true;
    } ;

    // Otherwise, we need to subdivide then add the point to whichever node will accept it
    if (northWest == NULL)
      subdivide();

    if (northWest->insert(p)) return true;
    if (northEast->insert(p)) return true;
    if (southWest->insert(p)) return true;
    if (southEast->insert(p)) return true;

    // Otherwise, the point could not be inserted for some unknown reason ( which should never happen )
    return false;
}

// Create four children which fully divide this quad into four quads of equal area
void QuadTree::subdivide () {
  XY halfDimension = XY(boundary.halfDimension.x / 2, boundary.halfDimension.y / 2);

  XY northWestCenter = XY(boundary.center.x - (boundary.halfDimension.x / 2), boundary.center.y + (boundary.halfDimension.y / 2));
  XY northEastCenter = XY(boundary.center.x + (boundary.halfDimension.x / 2), boundary.center.y + (boundary.halfDimension.y / 2));
  XY southWestCenter = XY(boundary.center.x - (boundary.halfDimension.x / 2), boundary.center.y - (boundary.halfDimension.y / 2));
  XY southEastCenter = XY(boundary.center.x + (boundary.halfDimension.x / 2), boundary.center.y - (boundary.halfDimension.y / 2));

  AABB northWestAABB = AABB(northWestCenter, halfDimension);
  AABB northEastAABB = AABB(northEastCenter, halfDimension);
  AABB southWestAABB = AABB(southWestCenter, halfDimension);
  AABB southEastAABB = AABB(southEastCenter, halfDimension);

  northWest = new QuadTree(northWestAABB);
  northEast = new QuadTree(northEastAABB);
  southWest = new QuadTree(southWestAABB);
  southEast = new QuadTree(southEastAABB);
}

// Find all points which appear within a range
std::vector<XY> QuadTree::queryRange (AABB range) {
  // Prepare an array of results
  std::vector<XY> pointsInRange;

  // Automatically abort if the range does not collide with this quad
  if (!boundary.intersectsAABB(range))
    return pointsInRange; // Empty list

  // Check objects at this quad level
  for (int p = 0; p < (int)points.size(); p++) {
    if (range.containsPoint(points.at(p)))
      pointsInRange.push_back(points.at(p));
  }

  // Terminate here, if there are no children
  if (!northWest)
    return pointsInRange;

  // Otherwise, add the points from the children
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

// Arbitrary constant to indicate how many elements can be stored in this quad tree node
//QuadTree::QT_NODE_CAPACITY = 4;

