#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Point {
    int x, y;
};

bool operator==(const Point& lhs, const Point& rhs)
{
	return lhs.x == rhs.x && lhs.y == rhs.y;
}

int pointLocation(Point A, Point B, Point P) {
    int cp1 = (B.x-A.x)*(P.y-A.y) - (B.y-A.y)*(P.x-A.x);
    return (cp1>0)?1:-1;
}


int distance(Point A, Point B, Point C) {
	int ABx = B.x-A.x;
    int ABy = B.y-A.y;
    int num = ABx*(A.y-C.y)-ABy*(A.x-C.x);
    if (num < 0) num = -num;
 	return num;
}

void hullSet(Point A, Point B, vector<Point> & set, vector<Point> & hull) {

    //int insertPosition = hull.indexOf(B);
    //vector<Point>::iterator it;

    //it = find(hull.begin(),hull.end(),B);
    
    if (set.size() == 0) return;
    
    if (set.size() == 1) {
      Point p = set[0];
      set.erase(std::remove(set.begin(), set.end(), p), set.end());
      //hull.push_back(insertPosition,p);
      //hull.insert(hull.begin()+it, p)
      hull.push_back(p);
      return;
    }

    int dist = INT_MIN;
    int furthestPoint = -1;
    for (int i = 0; i < set.size(); i++) {
      Point p = set[i];

      int distan = distance(A,B,p);
      if (distan > dist) {
        dist = distan;
        furthestPoint = i;
      }
    }

    Point P = set[furthestPoint];
    //set.remove(furthestPoint);
    //RemovePoint(set, P);
    set.erase(std::remove(set.begin(), set.end(), P), set.end());
    //hull.add(insertPosition,P);
    //hull.insert(hull.begin()+it, P);
    hull.push_back(P);

    
    // Determine who's to the left of AP
    vector<Point> leftSetAP;
    for (int i = 0; i < set.size(); i++) {
      Point M = set[i];
      if (pointLocation(A,P,M)==1) {
        leftSetAP.push_back(M);
      }
    }
    
    // Determine who's to the left of PB
    vector<Point> leftSetPB;
    for (int i = 0; i < set.size(); i++) {
      Point M = set[i];
      if (pointLocation(P,B,M)==1) {
        leftSetPB.push_back(M);
      }
    }
    hullSet(A,P,leftSetAP,hull);
    hullSet(P,B,leftSetPB,hull);
    
}

vector<Point> quickHull(vector<Point> points) {
    
    vector<Point> convexHull;
    
    if (points.size() < 3) return points;
    
    int minPoint = -1, maxPoint = -1;
    int minX = INT_MAX;
    int maxX = INT_MIN;
    
    for (int i = 0; i < points.size(); i++) {
      if (points[i].x < minX) {
        minX = points[i].x;
        minPoint = i;
      } 
      if (points[i].x > maxX) {
        maxX = points[i].x;
        maxPoint = i;       
      }
    }

    Point A = points[minPoint];
    Point B = points[maxPoint];

    convexHull.push_back(A);
    convexHull.push_back(B);

    //points.remove(A);
    points.erase(std::remove(points.begin(), points.end(), A), points.end());
    //RemovePoint(points, A);
    //points.remove(B);
    //RemovePoint(points, B);
    points.erase(std::remove(points.begin(), points.end(), B), points.end());
    
   	vector<Point> leftSet;
   	vector<Point> rightSet;
    
    for (int i = 0; i < points.size(); i++) {
      Point p = points[i];
      if (pointLocation(A,B,p) == -1)
        leftSet.push_back(p);
      else
        rightSet.push_back(p);
    }

    hullSet(A,B,rightSet,convexHull);
    hullSet(B,A,leftSet,convexHull);
    
    return convexHull;
}  
 
int main()
{
	Point points[] = {{2, 1}, {3, 0}, {0, 0}, {3, 3}, {0, 3}, {2, 2}, {1, 1}};
    int n = sizeof(points)/sizeof(points[0]);
    vector<Point> point_vec;
    for(int i = 0;i<n;i++)
    {	
    	point_vec.push_back(points[i]);
	}
	vector<Point> hull = quickHull(point_vec);

    for(int i = 0; i < hull.size(); i++)
        cout << "(" << hull[i].x << ", " << hull[i].y << ")" << endl;
    
    return 0;

}
  

