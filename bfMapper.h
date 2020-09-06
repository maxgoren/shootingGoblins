/*
Copyright (c) 2020 Max Goren
maxgoren@icloud.com
http://www.maxcodes.info

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/
#define INF -666

class bfMapper {
  Point cdir[8];
  mctk::Queue<Point> que;
  mctk::list<Point> visited;
public:
  World* map;
  void setMapValue(Point origin, int cut);
  void inverseField(Point origin, int cut);
  bool inBounds(Point p);
  bfMapper(World* map);
};


bfMapper::bfMapper(World* map)
{
   this->map = map;
   int x, y;
   for (x = 0; x < map->mapW;x++)
   {
     for (y = 0; y < map->mapH; y++)
     {
       map->layout[x][y].level = 0;
     }
   }
  cdir[0] = {0,-1}; cdir[1] = {0,1};
  cdir[2] ={-1,1}; cdir[3] = {1,-1};
  cdir[4] = {1,0}; cdir[5] = {-1,0};
  cdir[6] = {-1,-1}; cdir[7] = {1,1};
}

bool bfMapper::inBounds(Point p)
{
     return 0 <= p.x && p.x < map->mapW && 0 <= p.y && p.y < map->mapH;
}


void bfMapper::setMapValue(Point start, int cut)
{
   Point current, next, marker = {INF, INF}; 
   auto visited = mctk::list<Point>(); 
   int level = 1;      
   que.push(start);   
   visited.push(start);
   que.push(marker);   
   while (!que.empty())
   {
     current = que.pop();    
      if (current == marker) 
      { 
        level++; que.push(marker); 
        if (que.front() == marker) 
          break;                   
      } 
      if (level == cut)     
        break;
      for (auto dir : cdir) 
      {
        next = Point{current.x + dir.x, current.y + dir.y, dir.s}; 
        if (inBounds(next) && map->layout[next.x][next.y].blocks == false)
        {
          if (visited.find(next) == false) 
          {
            que.push(next);         
            visited.push(next);   
	          map->layout[next.x][next.y].level = level; 
          }
        }
      }
   }
   visited.clear(); //clean her up and send her home ;-)
   que.clear();
   start.level = 0;
}


void bfMapper::inverseField(Point start, int cut)
{
   Point current, next, marker = {INF, INF};
   auto visited = mctk::list<Point>();
   int level = 100;      
   que.push(start);   
   visited.push(start); 
   que.push(marker);   
   while (!que.empty())
   {
     current = que.pop();    
      if (current == marker)  
      { 
        level--; que.push(marker); 
        if (que.front() == marker) 
          break;                    
      } 
      if (level == cut)     
        break;
      for (auto dir : cdir) 
      {
        next = Point{current.x + dir.x, current.y + dir.y, dir.s}; 
        if (inBounds(next) && map->layout[next.x][next.y].blocks == false) 
        {
          if (visited.find(next) == false) 
          {
            que.push(next);         
            visited.push(next);    
	          map->layout[next.x][next.y].level = level; 
          }
        }
      }
   }
   visited.clear(); 
   que.clear();
   start.level = 0;
}
