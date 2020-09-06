

class bullet {
  public:
    std::unordered_map<char, Point> facing;
    std::vector<Point> heatSeeking;
    char d;
    const char ch = '*';
    const char ch_M = '%';
    Point pos;
    Point impact;
    char bullet_kind;
    bool killshot;
    bool go;
    bool running;
    void grenade(World* map);
    void updatePosMagic(World* Map);
    void updatePos(World* Map);
    void render(World* Map);
    inline bool inBounds(Point);
    bullet(char dir, Point spos, char kind);
    ~bullet();
};

bullet::bullet(char dir, Point spos, char kind) {
  this->facing['N'] = {0,-1};
  this->facing['S'] = {0, 1};
  this->facing['E'] = {1,0};
  this->facing['W'] = {-1,0}; 
  
  this->facing['L'] = {1,-1};
  this->facing['M'] = {1, 1};
  this->facing['N'] = {-1,-1};
  this->facing['O'] = {-1,1}; 
  this->d = dir;
  this->go = true;
  this->killshot = false;
  this->pos = spos;
  this->bullet_kind = kind;
  this->running = false;
}

bullet::~bullet()
{
    std::cout<<"Job well done\n";
    delete this;
}

void bullet::updatePos(World* map)
{
    Point Next;
    Next = {pos.x + facing[d].x, pos.y + facing[d].y};
    pos = Next;
    if (inBounds(Next)) {
      if (map->layout[Next.x][Next.y].blocks)
      {
        if (map->layout[Next.x][Next.y].populated)
        {
            killshot = true;
            impact = Next;
        } 
        go = false;
      } 
    } else if (!inBounds(Next)) {
          go = false; 
    } else {
        go = true;
    }
}


void bullet::updatePosMagic(World* map)
{
  if (heatSeeking.empty())
  {
    mctk::breadthFirst seek(map);
    heatSeeking = seek.pathFind(pos);
    go = true;
  }
  if (!heatSeeking.empty())
  {
    pos = heatSeeking.back();
    std::cout<<"Heat Seaking: "<<pos.x<<"/"<<pos.y<<std::endl;
    heatSeeking.pop_back();
    terminal_print(pos.x,pos.y,"X");
    terminal_refresh();
    if (map->layout[pos.x][pos.y].populated)
    {
        terminal_print(pos.x,pos.y, "D");
        std::cout<<"bingo\n";
        killshot = true;
        go = false;
        impact = pos;
    }
  }
  if (heatSeeking.empty()&&go==true)
  {
    go = false;
  }
}


inline bool bullet::inBounds(Point p)
{
  return p.x > 0 && p.x < 80 && p.y > 0 && p.y < 40;
}

void bullet::grenade(World* map)
{
  if (running == false) 
  {
  running = true;
  Point p,t;
  std::unordered_map<Point, bool, mctk::hashkeyBF> seen;
  std::unordered_map<Point, int, mctk::hashkeyBF> dist;
  mctk::Queue<Point> horseshoes;
  //horseshoes.push({pos.x + facing[d].x, pos.y+facing[d].y});
  horseshoes.push(pos);
  dist[pos] = 0;
  seen[pos] = true;
  while (!horseshoes.empty())
  {
    t = horseshoes.pop();
    for (auto d : facing)
    {
      p = {t.x + d.second.x, t.x + d.second.y};
      if (map->layout[p.x][p.x].populated)
      {
       // killshot=true;
       // impact = p;
       // go = false;
       // break;
      } else if (!map->layout[p.x][p.y].blocks && !seen[p]) {
        std::cout<<p.x<<"/"<<p.y<<"\n";
        terminal_color("yellow");
        terminal_print(p.x,p.y,"\"");
        terminal_refresh();
        horseshoes.push(p);
        seen[p] = true; dist[p] = dist[t] + 1;
        if (dist[p] > 4)
        { 
        //  go = false; break;
        }
      }
    }
  }
  std::cout<<"Queue ran dry..\n";
  running = false;
  }
}

void bullet::render(World* Map)
{
    if (go == true)
    {
      switch (bullet_kind)
      {
        case 'r':
          updatePos(Map);
          terminal_layer(4);
          terminal_color("cyan");
          terminal_put(pos.x,pos.y, ch);
          break;
        case 'M':
          updatePosMagic(Map);
          terminal_layer(4);
          terminal_color("flame");
          terminal_put(pos.x,pos.y, ch_M);
          break;
        case 'G':
          grenade(Map); break;
      }
    }
}