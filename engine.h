
class engine {
    public:
    World* Map;
    bfMapper* bf;
    ent* me;
    ent* g;
    std::vector<ent*> gobs;
    std::vector<bullet*> caps;
    void checkDead(Point impact);
    void bulletStatus();
    void render();
    void game_loop();
    engine();
};
void achieveGlory(std::vector<int> kp);

engine::engine()
{
 Map = new World(80, 40);
 me = new ent(10,10,666,'@');
 Map->sampleMap();
 bf = new bfMapper(Map);
 g = new ent(57,9,21,'g');
 gobs.push_back(g);
 g = new ent(68,6, 11, 'g');
 gobs.push_back(g);
}

void engine::game_loop()
{
 bool state;
 int keypress;
 std::vector<int> kp;
 while(true)
 {
  terminal_clear();
  if (terminal_has_input())
  {
   if (state)
   {
   keypress=terminal_read();
   kp.push_back(keypress);
   std::cout<<"KP: "<<keypress<<"\n";
   switch (keypress)
   {
    case TK_UP: me->move(Map,0,-1); break;
    case TK_DOWN: me->move(Map,0,1); break;
    case TK_LEFT: me->move(Map,-1,0); break;
    case TK_RIGHT: me->move(Map,1,0); break;
    case TK_SPACE: me->jump(Map); break;
    case TK_S: caps.push_back(me->shoot('r')); break;
    case TK_TAB: caps.push_back(me->shoot('M')); break;
    case TK_1: caps.push_back(me->shoot('G')); break;
    case TK_Q: terminal_close(); exit(0); break;
    default: break;
   }
   bf->setMapValue(me->pos, 200);
    if (kp.size() > 8)
     achieveGlory(kp);
    state = false;
   }
  }
  if (!state)
  {
      for (auto g : gobs)
          g->dijk_step(bf->map);
      state = true;
  }
  render();
  bulletStatus();
  terminal_refresh();
 }
}


void engine::bulletStatus()
{
   int count = 0, cnt2 = 0;
   for (auto p: caps)
   {
    p->render(bf->map);
    if (!p->go)
    {
      if (p->killshot)
        checkDead(p->impact);
        caps.erase(caps.begin()+count);
    }
    count++;
   }
}




void engine::checkDead(Point impact)
{
     int count = 0;
     for (auto g : gobs)
     {
        if (impact == g->pos) //marked for death kid.
        {
            g->die(bf->map);
            gobs.erase(gobs.begin()+count);
        }
        count++;
     }
}

void engine::render()
{
 int x, y;
 float mix;
 int level;
 std::string dist="-1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
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
   terminal_color(fadeColors(blue, yellow, mix/10));
   if (level < dist.length())
   {
     terminal_printf(x,y,"%c", dist.at(level));
   } else {
     terminal_print(x,y,".");
   }
  }
 }
}
  for (auto g : gobs)
    g->render();

  me->render();
}

                    