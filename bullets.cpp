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
#include <queue>
#include "BearLibTerminal.h"
#include "helpers.h"
#include "basic_objects.h"
#include "bullets.h"
#include "basic_ent.h"
#include "queue.h"
#include "list.h"
#include "bfMapper.h"
#include "colors.h"
#include "engine.h"

int main()
{
 int k;
 terminal_set("window; title='MaxCodes shooting Demo', size=85x42;");
 terminal_open();
 engine eng;
 eng.game_loop();
 terminal_close();
 return 0;
}
