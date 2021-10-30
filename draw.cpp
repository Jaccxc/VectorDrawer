#include <iostream>
#include <vector>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define max_char_size 50000
#define max_coord_size 5000
using namespace std;

int create_bezierX(double PX0,double PX1,double PX2,double PX3, double Z0)
{
  double a,b,c,d;
  fstream fresx;
  cout.setf(ios_base::fixed);
  fresx.open("tmpx.txt", ios::app);
  a = (-3*PX2 - PX0 + PX3 + 3*PX1);
  b = (9*PX2*Z0 + 3*PX0*Z0 + -3*PX3*Z0 - 9*PX1*Z0 + 3*PX2 + 3*PX0 - 6*PX1);
  c = (-9*PX2*Z0*Z0 - 3*PX0*Z0*Z0 + 3*PX3*Z0*Z0 + 9*PX1*Z0*Z0 - 6*PX2*Z0 - 6*PX0*Z0 + 12*PX1*Z0 - 3*PX0 + 3*PX1);
  d = (3*PX2*Z0*Z0*Z0 + PX0*Z0*Z0*Z0 - PX3*Z0*Z0*Z0 - 3*PX1*Z0*Z0*Z0 + 3*PX2*Z0*Z0 + 3*PX0*Z0*Z0 - 6*PX1*Z0*Z0 + 3*PX0*Z0 - 3*PX1*Z0 + PX0);
  cout << "a,b,c,d: " << a << " " << b << " " << c << " " << d << " " << endl;
  fresx << fixed << "(" << a << "*t^{3}+(" << b << ")*t^{2}+(" << c << ")*t+(" << d << "))";
  fresx.close();
}

int create_bezierY(double PX0,double PX1,double PX2,double PX3, double Z0)
{
  double a,b,c,d;
  fstream fresy;
  cout.setf(ios_base::fixed);
  fresy.open("tmpy.txt", ios::app);
  a = (-3*PX2 - PX0 + PX3 + 3*PX1);
  b = (9*PX2*Z0 + 3*PX0*Z0 + -3*PX3*Z0 - 9*PX1*Z0 + 3*PX2 + 3*PX0 - 6*PX1);
  c = (-9*PX2*Z0*Z0 - 3*PX0*Z0*Z0 + 3*PX3*Z0*Z0 + 9*PX1*Z0*Z0 - 6*PX2*Z0 - 6*PX0*Z0 + 12*PX1*Z0 - 3*PX0 + 3*PX1);
  d = (3*PX2*Z0*Z0*Z0 + PX0*Z0*Z0*Z0 - PX3*Z0*Z0*Z0 - 3*PX1*Z0*Z0*Z0 + 3*PX2*Z0*Z0 + 3*PX0*Z0*Z0 - 6*PX1*Z0*Z0 + 3*PX0*Z0 - 3*PX1*Z0 + PX0);
  fresy << fixed << "(" << a << "*t^{3}+(" << b << ")*t^{2}+(" << c << ")*t+(" << d << "))";
  fresy.close();
}

int get_svg_func(vector<char>&step, double *coord)
{
  fstream fsvg;
  char buffer[max_char_size];
  const char *func_pref = "\" d=\"M",*ctx_pref = "<", *func_suf = "\"/>", *delimit = " ,", *func_cont = "\"/>\n<", *func_suf1 = "<", *func_suf2 = ">";
  fsvg.open("obj.svg",ios::in);
  fsvg.read(buffer,sizeof(buffer));
  if(buffer[0]==ctx_pref[0])
  {
    char *procf1 = strstr(buffer, func_pref)+6;
    if(procf1 != NULL)
    {
      int i=0, wordc=0;
      char **ptr;
      char procf3[max_char_size];
      memset(procf3, '\0', max_char_size);
      string procf2(procf1);
      cout << "Proccessed file: " << endl << procf2 << endl << endl;
      while(procf2.find(func_cont)!=procf2.npos)
      {
        wordc = procf2.find(func_cont);
        procf2 = procf2.replace(wordc,25," ");
        cout << "Proccessed file: " << endl << procf2 << endl << endl;
      }
      cout << "procf2 succeeded" << endl ;
      if(procf2.find(func_suf1)!=procf2.npos)
        cout << "wow";
        //procf2 = procf2.replace(procf2.find(func_suf1),max_char_size-procf2.find(func_suf1)-5," ");

      else if(procf2.find(func_suf2)!=procf2.npos)
        cout << "wow1";
        //procf2 = procf2.replace(procf2.find(func_suf2),max_char_size-procf2.find(func_suf2)-5," ");
      else
        procf2 = procf2.replace(wordc,1," ");
      cout << "procf3 succeeded" << endl ;
      string procf4 = procf2;
      while(procf4.find('\n')!=procf4.npos)
        procf4 = procf4.replace(procf4.find('\n'),2," ");
      while(procf4.find('-')!=procf4.npos)
        procf4 = procf4.replace(procf4.find('-'),1," m");
      while(procf4.find('m')!=procf4.npos)
        procf4 = procf4.replace(procf4.find('m'),1,"-");
      while(procf4.find('z')!=procf4.npos)
        procf4 = procf4.replace(procf4.find('z'),1," ");

      while(procf4[i]!='\0')
      {
        if(procf4[i]=='c')
        {
          step.push_back('c');
          procf4[i] = ',';
        }
        if(procf4[i]=='C')
        {
          step.push_back('C');
          procf4[i] = ',';
        }
        if(procf4[i]=='s')
        {
          step.push_back('s');
          procf4[i] = ',';
        }
        if(procf4[i]=='S')
        {
          step.push_back('S');
          procf4[i] = ',';
        }
        if(procf4[i]=='M')
        {
          step.push_back('M');
          procf4[i] = ',';
        }
        i+=1;
      }
      cout << "Final Proccessed file: " << endl << procf4 << endl << endl;
      int n = procf4.length();
      char procf5[n + 1];
      strcpy(procf5, procf4.c_str());

      i=0;
      coord[i] = strtod(strtok(procf5, delimit), ptr);
      i+=1;
      while (i<max_coord_size)
      {
        char *tmp;
        tmp = strtok(NULL, delimit);
        if(tmp == NULL)
          break;
        coord[i]=strtod(tmp, ptr);
        i+=1;
      }

      vector<char>::iterator it;
      cout << "Steps following: ";
      for(it=step.begin(); it!=step.end(); ++it)
        cout << *it  << " ";
      cout << endl << endl;
      return i;
    }
    else
      cout << "Couldn't find any bezier curves." << endl;
    fsvg.close();
  }
  else
  {
    cout << "Couldn't open file obj.svg.\nThe file may not exist or be corrupted" << endl;
  }
}

int output_func(vector<char>&step, double *coord, int num)
{
  int cur_num=2;
  char buffer1[max_char_size], buffer2[max_char_size];
  memset(buffer1, '\0', max_char_size);
  memset(buffer2, '\0', max_char_size);
  double PX0=coord[0], PX1, PX2, PX3, Z0, PY0=coord[1], PY1, PY2, PY3, tmp, resx=1920, resy=1080;
  fstream fres, fresx, fresy;
  fresx.open("tmpx.txt", ios::out);
  fresy.open("tmpy.txt", ios::out);
  fresx << "(((";
  fresy << "((";
  fresx.close();
  fresy.close();
  for(int i=0; i<num; i++)
  {
    cout << "coords: " << coord[i] << endl;
  }
  for(int i=0; i<num; i++)
  {
    if((i%2)==1)
      coord[i] *= 1;
    cout << "fixed coords: " << coord[i] << endl;
  }
  PX0 -= (resx/2);
  PY0 -= (resy/2);
  PY0 *= -1;
  Z0 = 0;
  for(int i=0; i<step.size(); i++)
  {
    cout << endl;
    if(step[i]=='c')
    {
      fresx.open("tmpx.txt", ios::app);
      fresy.open("tmpy.txt", ios::app);
      fresx << "+(\\operatorname{sign}(t-" << Z0 << ")*\\operatorname{sign}(" << Z0+1 << "-t)+1)*0.5*";
      fresy << "+(\\operatorname{sign}(t-" << Z0 << ")*\\operatorname{sign}(" << Z0+1 << "-t)+1)*0.5*";
      fresx.close();
      fresy.close();
      PX1=PX0+coord[cur_num];
      PY1=PY0-coord[cur_num+1];
      PX2=PX0+coord[cur_num+2];
      PY2=PY0-coord[cur_num+3];
      PX3=PX0+coord[cur_num+4];
      PY3=PY0-coord[cur_num+5];
      cout << "Original coords:  " << coord[cur_num] << " " << coord[cur_num+1] << " " <<coord[cur_num+2] << " " << coord[cur_num+3] << " " << coord[cur_num+4] << " " << coord[cur_num+5] <<endl;
      cout << "Step=\'c\'  " << PX0 << " " << PY0 << " " << PX1 << " " << PY1 << " " << PX2 << " " << PY2 << " " << PX3 << " " << PY3 << "  Z0: " << Z0 <<endl << endl;
      create_bezierX(PX0,PX1,PX2,PX3,Z0);
      create_bezierY(PY0,PY1,PY2,PY3,Z0);
      cur_num += 6;
      Z0+=1;
      PX0=PX3;
      PY0=PY3;
    }
    if(step[i]=='C')
    {
      fresx.open("tmpx.txt", ios::app);
      fresy.open("tmpy.txt", ios::app);
      fresx << "+(\\operatorname{sign}(t-" << Z0 << ")*\\operatorname{sign}(" << Z0+1 << "-t)+1)*0.5*";
      fresy << "+(\\operatorname{sign}(t-" << Z0 << ")*\\operatorname{sign}(" << Z0+1 << "-t)+1)*0.5*";
      fresx.close();
      fresy.close();
      PX1=coord[cur_num]-(resx/2);
      PY1=(coord[cur_num+1]-resy/2)*-1;
      PX2=coord[cur_num+2]-(resx/2);
      PY2=(coord[cur_num+3]-resy/2)*-1;
      PX3=coord[cur_num+4]-(resx/2);
      PY3=(coord[cur_num+5]-resy/2)*-1;
      cout << "Original coords:  " << coord[cur_num] << " " << coord[cur_num+1] << " " <<coord[cur_num+2] << " " << coord[cur_num+3] << " " << coord[cur_num+4] << " " << coord[cur_num+5] <<endl;
      cout << "Step=\'C\'  " << PX0 << " " << PY0 << " " << PX1 << " " << PY1 << " " << PX2 << " " << PY2 << " " << PX3 << " " << PY3 << "  Z0: " << Z0 <<endl;
      create_bezierX(PX0,PX1,PX2,PX3,Z0);
      create_bezierY(PY0,PY1,PY2,PY3,Z0);
      cur_num += 6;
      Z0+=1;
      PX0=PX3;
      PY0=PY3;
    }
    if(step[i]=='s')
    {
      fresx.open("tmpx.txt", ios::app);
      fresy.open("tmpy.txt", ios::app);
      fresx << "+(\\operatorname{sign}(t-" << Z0 << ")*\\operatorname{sign}(" << Z0+1 << "-t)+1)*0.5*";
      fresy << "+(\\operatorname{sign}(t-" << Z0 << ")*\\operatorname{sign}(" << Z0+1 << "-t)+1)*0.5*";
      fresx.close();
      fresy.close();
      PX1=PX0+(PX0-PX2);
      PY1=PY0+(PY0-PY2);
      PX2=PX0+coord[cur_num];
      PY2=PY0-coord[cur_num+1];
      PX3=PX0+coord[cur_num+2];
      PY3=PY0-coord[cur_num+3];
      cout << "Original coords:  " << coord[cur_num] << " " << coord[cur_num+1] << " " <<coord[cur_num+2] << " " << coord[cur_num+3] <<endl;
      cout << "Step=\'s\'  " << PX0 << " " << PY0 << " " << PX1 << " " << PY1 << " " << PX2 << " " << PY2 << " " << PX3 << " " << PY3 << "  Z0: " << Z0 <<endl;
      create_bezierX(PX0,PX1,PX2,PX3,Z0);
      create_bezierY(PY0,PY1,PY2,PY3,Z0);
      cur_num += 4;
      Z0+=1;
      PX0=PX3;
      PY0=PY3;
    }
    if(step[i]=='S')
    {
      fresx.open("tmpx.txt", ios::app);
      fresy.open("tmpy.txt", ios::app);
      fresx << "+(\\operatorname{sign}(t-" << Z0 << ")*\\operatorname{sign}(" << Z0+1 << "-t)+1)*0.5*";
      fresy << "+(\\operatorname{sign}(t-" << Z0 << ")*\\operatorname{sign}(" << Z0+1 << "-t)+1)*0.5*";
      fresx.close();
      fresy.close();
      PX1=PX0+(PX0-PX2);
      PY1=PY0+(PY0-PY2);
      PX2=coord[cur_num]-(resx/2);
      PY2=(coord[cur_num+1]-resy/2)*-1;
      PX3=coord[cur_num+2]-(resx/2);
      PY3=(coord[cur_num+3]-resy/2)*-1;
      cout << "Original coords:  " << coord[cur_num] << " " << coord[cur_num+1] << " " <<coord[cur_num+2] << " " << coord[cur_num+3] <<endl;
      cout << "Step=\'S\'  " << PX0 << " " << PY0 << " " << PX1 << " " << PY1 << " " << PX2 << " " << PY2 << " " << PX3 << " " << PY3 << "  Z0: " << Z0 <<endl;
      create_bezierX(PX0,PX1,PX2,PX3,Z0);
      create_bezierY(PY0,PY1,PY2,PY3,Z0);
      cur_num += 4;
      Z0+=1;
      PX0=PX3;
      PY0=PY3;
    }
    if(step[i]=='M')
    {
      PX0=coord[cur_num]-resx/2;
      PY0=coord[cur_num+1]-resy/2;
      PY0*=-1;
      cur_num +=2;
    }
  }
  fresx.open("tmpx.txt", ios::app);
  fresy.open("tmpy.txt", ios::app);
  fresx << "))";
  fresy << ")))";
  fresx.close();
  fresy.close();
  fresx.open("tmpx.txt", ios::in);
  fresy.open("tmpy.txt", ios::in);
  fres.open("Result.txt", ios::out);
  fresx.read(buffer1,sizeof(buffer1));
  fres << buffer1 << ",";
  fresy.read(buffer2,sizeof(buffer2));
  fres << buffer2 << "";
  fresx.close();
  fresy.close();
  fres.close();
  cout  << endl << "Success!" << endl;

}


main()
{
  int num_of_coords;
  double coords[max_coord_size];
  vector<char> steps;
  memset(coords,'0',max_coord_size);
  num_of_coords = get_svg_func(steps, coords);
  output_func(steps, coords, num_of_coords);

  int arr[5];
  for(int i=0; i<5; i++)
  {
    arr[i] = i+1;
    printf("arr[%d]=%d\n",i,arr[i]);
  }

}
