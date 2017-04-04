#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>
#include <cassert>

struct ImageCarver{

  std::vector<std::vector<int>> Image;
  std::vector<std::vector<int>> EnergyMatrix;
  std::vector<std::vector<int>> CEnergyMatrix; //cumulative energy matrix
  int Width;
  int Height;
  int MaxGray;

  ImageCarver(std::string Filename){
    GetImageFromFile(Filename);
    UpdateEnergyMatrix();
  }

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

    if(x == Width - 1){
      Right = Image[x][y];
    }else{
      Right = Image[x+1][y];
    }

    if(y == Height - 1){
      Below = Image[x][y];
    }
    else{
      Below = Image[x][y+1];
    }

    int result = abs(Current - Above) +
                abs(Current - Below) +
                abs(Current - Right) +
                abs(Current - Left);

    return result;
  }

  void UpdateEnergyMatrix(){
    EnergyMatrix = Image; //this gives us a 2-D array of the correct size to use
    for(int y = 0; y < Height; y++){
      for(int x = 0; x < Width; x++){
        EnergyMatrix[x][y] = GetEnergy(x,y);
      }
    }        
  }

  void GetImageFromFile(std::string Filename){
    Image = new std::vector<std::vector<int>>;
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
          MaxGray = TempString;
          Counter++;
      }
      else{
        std::string Num = "";
        for(int i = 0; i < TempString.length(); i++){
          if(TempString[i] == ' ' || TempString[i] == '\t' || TempString[i] == '\n'){
            Temp.push_back(Num);
            Num = "";
          }
          else Num += TempString[i];
        }
        if(Num != "") {
          Temp.push_back(Num)
        };
      }
    }

    Stream.close();

    if (Height * Width != Temp.length()){
      std::cout << "Invalid file!"<< std::endl;
      return;
    }

    int TempPos = 0;
    for(int y = 0; y < Height; y++){
      std::vector<int> TempVec = new std::vector<int>;
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
    CEnergyMatrix = EnergyMatrix; //to get proper sized martix
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
          CEnergyMatrix[x][y] = EnergyMatrix[x][y] +
          MinPrevNeigh;
        }
      }
    }
  }

  void MarkSeamInImage(){
    int Pos = 0;

    for(int i = 0; i < Width; i++){
      if(CEnergyMatrix[i][Height-1] < CEnergyMatrix[Pos][Height-1]){
        Pos = i;
      }
    }

    Image[Pos][Height-1] = -1;

    for(int Current = Height -1; i >= 0; Current--){
      int Right = Pos + 1;
      int Left = Pos - 1;

      if(Right < 0 || Right >= Width){
        Right = Pos;
      }
      if(Left < 0 || Left >= Width){
        Left = Pos;
      }

      int Min = ThreeMin(CEnergyMatrix[Right][Current],
          CEnergyMatrix[Left][Current],
          CEnergyMatrix[Pos][Current]);

      switch (Min){
        case CEnergyMatrix[Left][Current]:
          Pos = Left;
          break;
        case CEnergyMatrix[Pos][Current]:
          Pos = Pos;
          break;
        case CEnergyMatrix[Right][Current]:
          Pos = Right;
          break;
      }

      Image[Pos][Current] = -1;
    }
  }

  void RemoveSeamFromImage(){
    int OldWidth = Width;
    Width--;
    NewImage = new std::vector<std::vector<int>>;

    for(int y = 0; y < Height; y++){
      std::vector<int> TempVec = new std::vector<int>;
      for(int x = 0; x < OldWidth; x++){        
        if(Image[x][y] != -1){
          TempVec.push_back(Image[x][y]);
        }
      }
      NewImage.push_back(TempVec);
    }
  }

  void CarveVerticalSeam()
  {
    PopulateCumulativeEnergy();
    MarkSeamInImage();
    RemoveSeamFromImage();
  }
}

int main(int argc, char *argv[])
{
    assert(argc == 4);

    std::string filename = argv[1];

    int vert = atoi(argv[2]);
    int horz = atoi(argv[3]);

    ImageCarver Image(filename);

    Image.carve(vert, horz);
    Image.outputimage();

    return 0;
}
