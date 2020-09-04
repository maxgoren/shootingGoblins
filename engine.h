
class engine {
    public:
    World* Map;
    bfMapper* bf;
    ent* me;
    ent* g;
    std::vector<ent*> gobs;
    std::vector<bullet*> caps;
    std::vector<bullet*> bulletStatus(std::vector<bullet*> rnds);
    void render();
    void game_loop();
    engine();
};

engine::engine()
{
 Map = new World(80, 40);
 me = new ent(10,10,666,'@');
 Map->sampleMap();
 bf = new bfMapper(Map);
}

void engine::game_loop()
{
 bool state;
 int keypress;
 while(true)
 {
  terminal_clear();
  if (terminal_has_input())
  {
   if (state)
   {
   keypress=terminal_read();
   switch (keypress)
   {
    case TK_UP: me->move(Map,0,-1); break;
    case TK_DOWN: me->move(Map,0,1); break;
    case TK_LEFT: me->move(Map,-1,0); break;
    case TK_RIGHT: me->move(Map,1,0); break;
    case TK_SPACE: caps.push_back(me->shoot()); break;
    case TK_Q: terminal_close(); exit(0); break;
    default: break;
   }
   bf->setMapValue(me->pos, 200);
    state = false;
   }
  }
  if (!state)
  {
      state = true;
  }
  render();
  caps = bulletStatus(caps);
  terminal_refresh();
 }
}


std::vector<bullet*> engine::bulletStatus(std::vector<bullet*> rnds)
{
  if (rnds.size() > 0)
  {
   int count = 0;
   for (auto p: rnds)
   {
    p->render(bf->map);
    if (!p->go)
    {
      if (p->killshot)
      {
        for (auto g : gobs)
        {
          if (p->impact == g->pos) //marked for death kid.
          {
            
          }
        }
      }
      rnds.pop_back();
    }
   }
  }
  return rnds;
}

void engine::render()
{
 int x, y;
 float mix;
 int level;
 for (x = 0; x < 80; x++)
 {
  for (y = 0; y < 40; y++)
  {
  level = bf->map->layout[x][y].level;
  if (bf->map->layout[x][y].blocks == true && bf->map->layout[x][y].populated == false)
  {
   terminal_layer(0);
   terminal_bkcolor("black");
   terminal_color("white");
   terminal_print(x, y, "#");
  } else {
   terminal_layer(0);
   mix = level/2;
   terminal_bkcolor(fadeColors(green, yellow, mix/14));
   terminal_print(x,y," ");
  }
 }
}
  me->render();
}