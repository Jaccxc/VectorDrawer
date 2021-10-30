# VectorPainter
This script converts .SVG files to actual arithmetic functions that can read by Desmos without using Desmos API for whatever reason you need this. 

## Algorithm
.SVG files consists of only degree 3 Bezier Curves and straight lines. So what I do is first parse the .SVG file. Getting all the coordinates from it. Then for each instruction in the file, we generate different arithmetic functions. 

## Usage
There's no third party library used here. The script is written in C++, just compile and run draw.exe.
```linux
./draw.exe
```


## Example
![ok](https://github.com/Jaccxc/jacc_css/blob/master/docs/video/ezgif-4-dc9ce2b43aaf.gif)
