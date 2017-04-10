#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>
#include <cassert>
/*5: C:/Program Files/mingw-w64/x86_64-6.3.0-posix-seh-rt_v5-rev1/mingw64/lib/gcc/x86_64-w64-mingw32/6.3.0/include/c++/bits/stl_vector.h:1147:7: note: candidate: std::vector<_Tp, _Alloc>::iterator std::vector<_Tp, _Alloc>::erase(std::vector<_Tp, _Alloc>::const_iterator) [with _Tp = int; _Alloc = std::allocator<int>; std::vector<_Tp, _Alloc>::iterator = __gnu_cxx::__normal_iterator<int*, std::vector<int> >; typename std::_Vector_base<_Tp, _Alloc>::pointer = int*; std::vector<_Tp, _Alloc>::const_iterator = __gnu_cxx::__normal_iterator<const int*, std::vector<int> >; typename __gnu_cxx::__alloc_traits<typename std::_Vector_base<_Tp, _Alloc>::_Tp_alloc_type>::const_pointer = const int*] erase(const_iterator __position) ^~~~~ C:/Program Files/mingw-w64/x86_64-6.3.0-posix-seh-rt_v5-rev1/mingw64/lib/gcc/x86_64-w64-mingw32/6.3.0/include/c++/bits/stl_vector.h:1147:7: note: candidate expects 1 argument, 2 provided C:/Program Files/mingw-w64/x86_64-6.3.0-posix-seh-rt_v5-rev1/mingw64/lib/gcc/x86_64-w64-mingw32/6.3.0/include/c++/bits/stl_vector.h:1174:7: note: candidate: std::vector<_Tp, _Alloc>::iterator std::vector<_Tp, _Alloc>::erase(std::vector<_Tp, _Alloc>::const_iterator, std::vector<_Tp, _Alloc>::const_iterator) [with _Tp = int; _Alloc = std::allocator<int>; std::vector<_Tp, _Alloc>::iterator = __gnu_cxx::__normal_iterator<int*, std::vector<int> >; typename std::_Vector_base<_Tp, _Alloc>::pointer = int*; std::vector<_Tp, _Alloc>::const_iterator = __gnu_cxx::__normal_iterator<const int*, std::vector<int> >; typename __gnu_cxx::__alloc_traits<typename std::_Vector_base<_Tp, _Alloc>::_Tp_alloc_type>::const_pointer = const int*] erase(const_iterator __first, const_iterator __last) ^~~~~ C:/Program Files/mingw-w64/x86_64-6.3.0-posix-seh-rt_v5-rev1/mingw64/lib/gcc/x86_64-w64-mingw32/6.3.0/include/c++/bits/stl_vector.h:1174:7: note: no known conversion for argument 1 from '__gnu_cxx::__normal_iterator<std::vector<int>*, std::vector<std::vector<int> > >' to 'std::vector<int>::const_iterator {aka __gnu_cxx::__normal_iterator<const int*, std::vector<int> >}' In file included from C:/Program Files/mingw-w64/x86_64-6.3.0-posix-seh-rt_v5-rev1/mingw64/lib/gcc/x86_64-w64-mingw32/6.3.0/include/c++/bits/stl_algobase.h:71:0, from C:/Program Files/mingw-w64/x86_64-6.3.0-posix-seh-rt_v5-rev1/mingw64/lib/gcc/x86_64-w64-mingw32/6.3.0/include/c++/bits/char_traits.h:39, from C:/Program Files/mingw-w64/x86_64-6.3.0-posix-seh-rt_v5-rev1/mingw64/lib/gcc/x86_64-w64-mingw32/6.3.0/include/c++/ios:40, from C:/Program Files/mingw-w64/x86_64-6.3.0-posix-seh-rt_v5-rev1/mingw64/lib/gcc/x86_64-w64-mingw32/6.3.0/include/c++/ostream:38, from C:/Program Files/mingw-w64/x86_64-6.3.0-posix-seh-rt_v5-rev1/mingw64/lib/gcc/x86_64-w64-mingw32/6.3.0/include/c++/iostream:39, from*/
//#include <algorithm>
/*5: C:/Program Files/mingw-w64/x86_64-6.3.0-posix-seh-rt_v5-rev1/mingw64/lib/gcc/x86_64-w64-mingw32/6.3.0/include/c++/bits/stl_vector.h:1509:5: note: candidate: template<class _Tp, class _Alloc> bool std::operator==(const std::vector<_Tp, _Alloc>&, const std::vector<_Tp, _Alloc>&) operator==(const vector<_Tp, _Alloc>& __x, const vector<_Tp, _Alloc>& __y) ^~~~~~~~ C:/Program Files/mingw-w64/x86_64-6.3.0-posix-seh-rt_v5-rev1/mingw64/lib/gcc/x86_64-w64-mingw32/6.3.0/include/c++/bits/stl_vector.h:1509:5: note: template argument deduction/substitution failed: In file included from C:/Program Files/mingw-w64/x86_64-6.3.0-posix-seh-rt_v5-rev1/mingw64/lib/gcc/x86_64-w64-mingw32/6.3.0/include/c++/bits/stl_algobase.h:71:0, from C:/Program Files/mingw-w64/x86_64-6.3.0-posix-seh-rt_v5-rev1/mingw64/lib/gcc/x86_64-w64-mingw32/6.3.0/include/c++/bits/char_traits.h:39, from C:/Program Files/mingw-w64/x86_64-6.3.0-posix-seh-rt_v5-rev1/mingw64/lib/gcc/x86_64-w64-mingw32/6.3.0/include/c++/ios:40, from C:/Program Files/mingw-w64/x86_64-6.3.0-posix-seh-rt_v5-rev1/mingw64/lib/gcc/x86_64-w64-mingw32/6.3.0/include/c++/ostream:38, from C:/Program Files/mingw-w64/x86_64-6.3.0-posix-seh-rt_v5-rev1/mingw64/lib/gcc/x86_64-w64-mingw32/6.3.0/include/c++/iostream:39, from*/

struct ImageCarver{

  std::vector<std::vector<int>> Image;
  std::vector<std::vector<int>> EnergyMatrix;
  std::vector<std::vector<int>> CEnergyMatrix; //cumulative energy matrix
  int Width;
  int Height;
  int MaxGray;

  ImageCarver(std::string Filename){
    GetImageFromFile(Filename);
  }

  ImageCarver() = default;

  int GetEnergy(int x, int y){
    int Current = Image[x][y];
    int Above, Below, Right, Left;

    if(x == 0){
      Left = Image[x][y];
    }else{
      Left = Image[x-1][y];
    }

    if(y == 0){
      Above = Image[x][y];
    }else{
      Above = Image[x][y-1];
    }

    if(y == Width - 1){
      Right = Image[x][y];
    }else{
      Right = Image[x+1][y];
    }

    if(x == Height - 1){
      Below = Image[x][y];
    }
    else{
      Below = Image[x][y+1];
    }

    int result = abs(Current - Above) + abs(Current - Below) +
                  abs(Current - Right) + abs(Current - Left);

    return result;
  }

void UpdateEnergyMatrix(){
    std::vector<std::vector<int>> ThisEnergyMatrix;
    for(int x = 0; x < Width; x++){
      std::vector<int> TempVec;
      for(int y = 0; y < Height; y++){
        
        TempVec.push_back(GetEnergy(x,y));

      }
      ThisEnergyMatrix.push_back(TempVec);
    }
    EnergyMatrix = ThisEnergyMatrix;
  }

  void GetImageFromFile(std::string Filename){
    //Image = new std::vector<std::vector<int>>;
    std::string TempString;
    std::ifstream Stream;
    int Counter = 1;
    std::vector<std::string> Temp;

    //Open the file
    Stream.open(Filename.c_str());
    if(!Stream) {
      std::cout << "cannot be opened" << std::endl;
      return;
    };

    while(getline(Stream, TempString))
    {
      if(TempString[0] == '#'){
        continue;
        //do nothing, it's a comment
      }

      else if(Counter == 1){
        Counter++; //ignore the first line
      }

      else if(Counter == 2){
        int Space = TempString.find(" ");
        std::string x = TempString.substr(0, Space);
        std::string y = TempString.substr(Space + 1);

        Width = atoi(x.c_str());
        Height = atoi(y.c_str());
        Counter++;
      }
      else if(Counter == 3){
          MaxGray = std::stoi(TempString);
          Counter++;
      }
      else{
        std::string Num = "";
        for(int i = 0; i < (int)TempString.size(); i++){
          if(TempString[i] == ' ' || TempString[i] == '\t' || TempString[i] == '\n'){
            Temp.push_back(Num);
            Num = "";
          }
          else Num += TempString[i];
        }
        if(Num != "") {
          Temp.push_back(Num);
        };
      }
    }

    Stream.close();

    if (Height * Width != (int)Temp.size()){
      std::cout << "Invalid file!"<< std::endl;
      return;
    }

    int TempPos = 0;
    for(int y = 0; y < Height; y++){
      std::vector<int> TempVec;
      for(int x = 0; x < Width; x++){
        TempVec.push_back(atoi(Temp[TempPos].c_str()));
        TempPos++;
      }
      Image.push_back(TempVec);
    }
  }

  int ThreeMin(int A, int B, int C){
    return std::min(std::min(A,B),C);
  }

  void PopulateCumulativeEnergy(){
    CEnergyMatrix = std::vector<std::vector<int>>(EnergyMatrix); //to get proper sized martix
    for(int y = 0; y < Height; y++){
      for(int x = 0; x < Width; x++){
        if(y == 0){
          CEnergyMatrix[x][y] = EnergyMatrix[x][y];
        }
        else{
          int MinPrevNeigh;
          if(x == 0){
            MinPrevNeigh = std::min(CEnergyMatrix[x+1][y-1],
              CEnergyMatrix[x][y-1]);
          }
          else if(x == (Width - 1))
          {
            MinPrevNeigh = std::min(CEnergyMatrix[x-1][y-1],
              CEnergyMatrix[x][y-1]);
          }
          else
          {
            MinPrevNeigh = ThreeMin(CEnergyMatrix[x-1][y-1],CEnergyMatrix[x+1][y-1],CEnergyMatrix[x][y-1]);
          }
          CEnergyMatrix[x][y] = EnergyMatrix[x][y] + MinPrevNeigh;
        }
      }
    }
  }

  void MarkVerticalSeam(){
    int Pos = 0;
    CEnergyMatrix = EnergyMatrix; //steal size
    for(int f = 0; f < Width; f++){
      if(CEnergyMatrix[f][Height-1] < CEnergyMatrix[Pos][Height-1]){
        Pos = f;
      }
    }
    Image[Pos][Height-1] = -1;

    for(int Current = Height -1; Current >= 0; Current--){
      int Right = Pos + 1;
      int Center = Pos;
      int Left = Pos - 1;
      if(Right < 0 || Right >= Width){
        Right = Center;
      }
      if(Left < 0 || Left >= Width){
        Left = Center;
      }

      int Min = ThreeMin(CEnergyMatrix[Right][Current],
          CEnergyMatrix[Left][Current],
          CEnergyMatrix[Center][Current]);
      
      if (Min == CEnergyMatrix[Left][Current]){
        Pos = Left;
      }else if (Min == CEnergyMatrix[Center][Current]){
        Pos = Center;
      }else if (Min == CEnergyMatrix[Right][Current]){
        Pos = Right;
      }
      std::cout << "pos: " << Pos << " Current: " << Current << std::endl;
      Image[Pos][Current] = -1;
    }
  }

  void RemoveVerticalSeam(){
    //int OldHeigt = Height;
    
    std::vector<std::vector<int>> NewImage;

    for(int x = 0; x < Height; x++){
      std::vector<int> TempVec;
      for(int y = 0; y < Width; y++){
        if(Image[x][y] != -1){
           TempVec.push_back(Image[x][y]);
        }else {
          //TempVec.push_back(-69);
        }
      }
      NewImage.push_back(TempVec);
/*229:7: error: 'NewImage' was not declared in this scope NewImage.push_back(TempVec); ^~~~~~~~*/
      //Image[x].erase(std::remove(Image.begin(), Image.end(), -1), Image.end());
/*228:78: error: no matching function for call to 'std::vector<int>::erase(__gnu_cxx::__normal_iterator<std::vector<int>*, std::vector<std::vector<int> > >, std::vector<std::vector<int> >::iterator)' Image[x].erase(std::remove(Image.begin(), Image.end(), -1), Image.end()); ^ In file included from C:/Program Files/mingw-w64/x86_64-6.3.0-posix-seh-rt_v5-rev1/mingw64/lib/gcc/x86_64-w64-mingw32/6.3.0/include/c++/vector:64:0, from*/
/*228:64: required from here C:/Program Files/mingw-w64/x86_64-6.3.0-posix-seh-rt_v5-rev1/mingw64/lib/gcc/x86_64-w64-mingw32/6.3.0/include/c++/bits/predefined_ops.h:194:17: error: no match for 'operator==' (operand types are 'std::vector<int>' and 'const int') { return *__it == _M_value; } ~~~~~~^~~~~~~~~~~ In file included from C:/Program Files/mingw-w64/x86_64-6.3.0-posix-seh-rt_v5-rev1/mingw64/lib/gcc/x86_64-w64-mingw32/6.3.0/include/c++/bits/stl_algobase.h:67:0, from C:/Program Files/mingw-w64/x86_64-6.3.0-posix-seh-rt_v5-rev1/mingw64/lib/gcc/x86_64-w64-mingw32/6.3.0/include/c++/bits/char_traits.h:39, from C:/Program Files/mingw-w64/x86_64-6.3.0-posix-seh-rt_v5-rev1/mingw64/lib/gcc/x86_64-w64-mingw32/6.3.0/include/c++/ios:40, from C:/Program Files/mingw-w64/x86_64-6.3.0-posix-seh-rt_v5-rev1/mingw64/lib/gcc/x86_64-w64-mingw32/6.3.0/include/c++/ostream:38, from C:/Program Files/mingw-w64/x86_64-6.3.0-posix-seh-rt_v5-rev1/mingw64/lib/gcc/x86_64-w64-mingw32/6.3.0/include/c++/iostream:39, from*/
    }
    Width--;
    //Image = NewImage;
  }

  void CarveVerticalSeam(){
    UpdateEnergyMatrix();
    PopulateCumulativeEnergy();
    MarkVerticalSeam();
    //RemoveVerticalSeam();
  }


  void RotateImageRight(){
    std::vector<std::vector<int>> Temp;
    for (int InverseX = Width -1; InverseX >= 0; InverseX--){
      std::vector<int> Temp2;
      for (int InverseY = Height -1; InverseY >= 0; InverseY--) {
        Temp2.push_back(Image[InverseY][InverseX]);
      }
      Temp.push_back(Temp2);
    }

    std::swap(Height, Width);

    Image = Temp;
  }

  void RotateImageLeft(){
    //TODO: do this correctly
    RotateImageRight();
    RotateImageRight();
    RotateImageRight();
  }

  void Carve(int VerticalSeams, int HorizontalSeams){
    for (int Counter = 0; Counter < VerticalSeams; Counter++){
      CarveVerticalSeam();
    }

    RotateImageRight();
    for (int Counter = 0; Counter < HorizontalSeams; Counter++){    
      CarveVerticalSeam();
    }
    RotateImageLeft();
  }

  void PrintImage(std::string filename){
    std::ofstream OutputFile(filename.substr(0,filename.size()-4) + "_processed.pgm"); //create output file

    OutputFile << "P2" << std::endl
                << Width << " " << Height << std::endl
                << MaxGray << std::endl;

    for(int x = 0; x < Height; x++)
    {
      for(int y = 0; y < Width; y++){
        OutputFile << Image[x][y] << " ";// << std::endl;
      }
      OutputFile << std::endl;
    }

    OutputFile.close();
  }
};



int main(int argc, char *argv[])
{
   assert(argc == 4);

  std::string filename = argv[1];
  int VerticalSeams = atoi(argv[2]);
  int HorizontalSeams = atoi(argv[3]);

  ImageCarver Image(filename);

  Image.Carve(VerticalSeams, HorizontalSeams);
  Image.PrintImage(filename);

  return 0;
}
