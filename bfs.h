/****************************************************************************
 * MIT License

Copyright (c) 2020 Max Goren - maxgoren@icloud.com, https://www.maxcodes.info

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
******************************************************************************/
#define INF -666

namespace mctk {

struct hashkeyBF {
  std::size_t operator()(const Point pt) const {
      std::size_t x = std::hash<int>()(pt.x);
      std::size_t y = std::hash<int>()(pt.y >> 4);
    return x^y;
  }
};

class breadthFirst {
typedef std::vector<std::vector<Point>> field;
 private:
    struct Edge {
      Point at;
      Point from; 
    };
    int mapW, mapH;
    std::array<Point, 8> cdir;
    mctk::Queue<Point> queue;
    std::unordered_map<Point, Point, hashkeyBF> camefrom;    
  public:
    field layout; 
    Point target;
    std::vector<std::vector<int>> distance;
    std::vector<std::vector<bool>> visited;
    bool inbounds(Point p);
    bool bfs(Point start);
    std::vector<Point> pathFind(Point start);
    void reset();
    breadthFirst(World* outline);
};

}