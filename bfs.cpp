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
namespace mctk {

breadthFirst::breadthFirst(World* outline)
{
 this->layout = outline->layout;
 this->mapW = outline->mapW;
 this->mapH = outline->mapH;
  visited.resize(mapW, std::vector<bool>(mapH));
  distance.resize(mapW, std::vector<int>(mapH));
 int x, y;
 for (x = 0; x < this->mapW; x++)
 {
   for (y = 0; y < this->mapH; y++)
   {
     visited[x][y] = false;
     distance[x][y] = 0;
   }
 }
  cdir[0] = {0,-1}; cdir[1] = {0,1};
  cdir[2] ={-1,1}; cdir[3] = {1,-1};
  cdir[4] = {1,0}; cdir[5] = {-1,0};
  cdir[6] = {-1,-1}; cdir[7] = {1,1};
 
}

bool breadthFirst::inbounds(Point p)
{
  return p.x > 0 && p.x < mapW && p.y > 0 && p.y < mapH;
}

bool breadthFirst::bfs(Point start)
{
 int i;
 int level = 0;
 Point current, next, mark={INF, INF};
 struct Edge node;
 node = {start, start};
 visited[start.x][start.y] = true;
 queue.push(start);
 camefrom[start] = start;
 queue.push(mark);
 while (!queue.empty())
 {
  current = queue.pop();
  if (current == mark)
  {
    level++;
    queue.push(mark);
    current = queue.pop();
    if (current == mark) return false; 
  }
  for (auto dir : cdir)
  {
   next = {current.x + dir.x, current.y + dir.y};
   if (visited[next.x][next.y] == false && inbounds(next))
   {
      if (this->layout[next.x][next.y].populated)
      {
        camefrom[next] = current;
        target = next;
        return true;
      } else if (this->layout[next.x][next.y].blocks == false) {
    	  queue.push(next);
        camefrom[next] = current;
        distance[next.x][next.y] = level;
        visited[next.x][next.y] = true;
       
      }
   }
  }
 }
 return false;
}

std::vector<Point> breadthFirst::pathFind(Point start)
{
   std::vector<Point> path;
   reset();
   bfs(start);
   Point current = target;
   while (current != start) {
      path.push_back(current);
      current = camefrom[current];
   }
   //std::reverse(path.begin(),path.end());
   //path.push_back(start);
   return path;
}


void breadthFirst::reset()
{
  int x, y;
  for (x = 0; x < 80; x++)
  {
    for (y = 0; y < 40; y++)
    {
      visited[x][y] = false;
      distance[x][y] = 0;
    }
  }
}

}