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

class ent {
public:
  std::unordered_map<char, Point>facing;
  Point pos;
  char face;
  char ch;
  int id;
  bool canMove(World* Map, int x, int y);
  void move(World*, int x, int y);
  void render();
  void turn(bool dir);
  bullet* shoot();
  ent(int x, int y, int id, char ch);
  ent();
};

ent::ent(int x, int y, int id, char ch)
{
 
  facing['N'] = {0,-1};
  facing['S'] = {0, 1};
  facing['E'] = {1,0};
  facing['W'] = {-1,0}; 
 this->pos.x = x;
 this->pos.y = y;
 this->ch = ch;
 this->id = id;
 this->face = 'N';
}

bool ent::canMove(World* Map, int x, int y)
{
 if (Map->layout[x][y].blocks == false && Map->layout[x][y].populated == false) {
    return true;
 } else {
   return false;
 }
}

void ent::move(World* Map, int dx, int dy)
{
  for (auto i : facing)
  {
    if (i.second.x == dx && i.second.y == dy)
    {
      face = i.first;
    }
  } 
 if (canMove(Map, this->pos.x + dx,this->pos.y + dy))
 {
  Map->layout[pos.x][pos.y].blocks = false;
  Map->layout[pos.x][pos.y].populated = false;
  this->pos.x += dx;
  this->pos.y += dy;
  Map->layout[pos.x][pos.y].blocks = true;
  Map->layout[pos.x][pos.y].populated = true;
 }
}

void ent::render()
{
 Point lead;
 terminal_layer(4);
 terminal_color("green");
 terminal_put(pos.x, pos.y, ch);
 lead = {pos.x + facing[face].x, pos.y + facing[face].y};
 if (face == 'N')
   terminal_print(lead.x, lead.y, "^");
 if (face == 'E')
   terminal_print(lead.x,lead.y, ">");
 if (face == 'W')
   terminal_print(lead.x, lead.y, "<");
 if (face == 'S')
   terminal_print(lead.x, lead.y, "v");
}



bullet* ent::shoot()
{
    return new bullet(face, pos);
}

void ent::turn(bool cw)
{
    char cur = this->face;
    if (cw)
    {
        if (cur == 'N')
          this->face = 'E'; 
        if (cur == 'E')
          this->face = 'S'; 
        if (cur == 'S') 
          this->face = 'W'; 
        if (cur == 'W') 
          this->face = 'N'; 
    }
    if (!cw)
    {
        if (cur == 'N')
          this->face = 'W'; 
        if (cur == 'W')
          this->face = 'S'; 
        if (cur == 'S')
          this->face = 'E'; 
        if (cur == 'E')
          this->face = 'N'; 
    }
}
