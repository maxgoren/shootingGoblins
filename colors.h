struct colors {
  int a = 255;
  int r = 0;
  int g = 0;
  int b = 0;
  color_t final = color_from_argb(a, r, g, b);
  colors(int q, int c, int d, int l) : a(q), r(c), g(d), b(l) { }
  colors(int c, int d, int l) : r(c), g(d), b(l) { }
  colors() { }
};


const colors black = {0,0,0};
const colors white = {255,255,255};
const colors yellow = {255, 160, 0};
const colors blue = {0,0,255};
const colors green = {0,255,0};
const colors red = {255,0,0};

color_t fadeColors(colors c1, colors c2, float mix)
{
  //mix:  color 1 0.0 <--> 1.0 color 2
  colors result;
  result.r = c1.r*(1-mix) + c2.r*(mix);
  result.g = c1.g*(1-mix) + c2.g*(mix);
  result.b = c1.b*(1-mix) + c2.b*(mix);
  return color_from_argb(255,result.r,result.b,result.b);
}
