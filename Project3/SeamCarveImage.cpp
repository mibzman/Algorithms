#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>
#include <cassert>
//#include <algorithm>

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
    Image[Height-1][Pos] = -1;

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
      Image[Current][Pos] = -1;
    }
  }

  void RemoveVerticalSeam(){
    std::vector<std::vector<int>> NewImage;

    for(int x = 0; x < Height; x++){
      std::vector<int> TempVec;
      for(int y = 0; y < Width; y++){
        if(Image[x][y] != -1){
          //std::cout << x << " " << y << std::endl;
          TempVec.push_back(Image[x][y]);
        }else {
          //TempVec.push_back(-69);
        }
      }
      NewImage.push_back(TempVec);
      // for( auto iter = Image[x].begin(); iter != Image[x].end(); ++iter ){
      //   if( *iter == -1 ){
      //     Image[x].erase(iter);
      //     break;
      //   }
      // }
    }
    Image = NewImage;
    Width--;
  }

  void CarveVerticalSeam(){
    UpdateEnergyMatrix();
    PopulateCumulativeEnergy();
    MarkVerticalSeam();
    RemoveVerticalSeam();
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
      //std::cout << Counter  << std::endl;
    }
    //std::cout << "finished"  << std::endl;

    // RotateImageRight();
    // for (int Counter = 0; Counter < HorizontalSeams; Counter++){    
    //   CarveVerticalSeam();
    // }
    // RotateImageLeft();
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
  std::cout << "printed"  << std::endl;

  return 0;
}
