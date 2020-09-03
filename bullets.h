
class bullet {
  public:
    std::unordered_map<char, Point> ing;
    char d;
    const char ch = '*';
    Point pos;
    Point impact;
    bool killshot;
    bool go;
    void updatePos(World* Map);
    void render(World* Map);
    inline bool inBounds(Point);
    bullet(char dir, Point spos);
    ~bullet();
};

bullet::bullet(char dir, Point spos) {
  this->ing['N'] = {0,-1};
  this->ing['S'] = {0, 1};
  this->ing['E'] = {1,0};
  this->ing['W'] = {-1,0}; 
  this->d = dir;
  this->go = true;
  this->killshot = false;
  this->pos = spos;
}

bullet::~bullet()
{
    std::cout<<"Job well done\n";
    delete this;
}

void bullet::updatePos(World* map)
{
    Point Next;
    Next = {pos.x + ing[d].x, pos.y + ing[d].y};
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


inline bool bullet::inBounds(Point p)
{
  return p.x > 0 && p.x < 80 && p.y > 0 && p.y < 40;
}

void bullet::render(World* Map)
{
    if (go == true)
    {
        updatePos(Map);
        terminal_layer(4);
        terminal_color("flame");
        terminal_put(pos.x,pos.y, ch);
    }
}