# game-class-debugger
A simple game class debugger

# Navigate
* Plus: current address + 0x4
* Minus: current address - 0x4
* Multiply: go to the reference
* Divide: back to the pointer
* Numpad: switch between classes

# Example
```Javascript
// add entries
debugger.AddClass("ClassNameA", (DWORD)0x1337A);
debugger.AddClass("ClassNameB", (DWORD)0x1337B);
debugger.AddClass("ClassNameC", (DWORD)0x1337C);

// update info
debugger.Update();

// show info
draw.Text(x, y, debugger.Text(), GreenColor);
```


