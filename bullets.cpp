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

#include <vector>
#include <iostream>
#include <random>
#include <string>
#include <unordered_map>
#include "BearLibTerminal.h"
#include "helpers.h"
#include "basic_objects.h"
#include "bullets.h"
#include "basic_ent.h"
#include "queue.h"
#include "list.h"
#include "bfMapper.h"
#include "colors.h"

void drawAll(World* map, ent* me)
{
 int x, y;
 float mix;
 int level;
 for (x = 0; x < 80; x++)
 {
  for (y = 0; y < 40; y++)
  {
  level = map->layout[x][y].level;
  if (map->layout[x][y].blocks == true)
  {
   terminal_layer(1);
   terminal_color("white");
   terminal_print(x, y, "#");
  } else {
   terminal_layer(0);
   mix = level/2;
   terminal_color(fadeColors(blue, yellow, mix/10));
   terminal_print(x, y, ".");
  }
 }
}
  me->render();
}

std::vector<bullet*> bulletStatus(std::vector<bullet*> rnds, World* Map)
{
  if (rnds.size() > 0)
  {
   int count = 0;
   for (auto p: rnds)
   {
    p->render(Map);
    if (!p->go)
      rnds.pop_back();
   }
  }
  return rnds;
}

int main()
{
 int k;
 terminal_set("window; title='dj', size=85x42;");
 terminal_open();
 World* Map;
 ent* me;
 Map = new World(80, 40);
 me = new ent(10,10,666,'@');
 Map->sampleMap();
 bfMapper bf(Map);
 std::vector<bullet*> caps;
 while(true)
 {
  terminal_clear();
  if (terminal_has_input())
  {
   k=terminal_read();
   switch (k)
   {
    case TK_UP: me->move(Map,0,-1); break;
    case TK_DOWN: me->move(Map,0,1); break;
    case TK_LEFT: me->move(Map,-1,0); break;
    case TK_RIGHT: me->move(Map,1,0); break;
    case TK_SPACE: caps.push_back(me->shoot()); break;
    case TK_Q: terminal_close(); exit(0); break;
    default: break;
   }
   bf.setMapValue(me->pos, 200);
  }
  drawAll(bf.map, me);
  caps = bulletStatus(caps, bf.map);
  terminal_refresh();
 }
 terminal_close();
 return 0;
}
