#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cassert>

struct ImageCarver {
  std::vector<std::vector<int>> Image; 
  std::vector<std::vector<int>> EnergyMatrix;
  std::vector<std::vector<int>> CEnergy;
  int Width;
  int Height;
  
  std::string Max;  //this is a string because we never use it

  ImageCarver() = default;

  ImageCarver(std::string Filename){
    ReadImage(Filename);
    //BuildEnergyMatrix();
  }

  //Utality Functions

  bool IsEmpty(char val) const {
    return val == ' ' || val == '\t' || val == '\n';
  }

  int ThreeMin(int A, int B, int C){
    return std::min(std::min(A,B),C);
  }

  void ReadImage(std::string const& Filename){
    std::ifstream InputFile;
    InputFile.open(Filename.c_str());

    if(!InputFile){
      std::cout << "File Parsing Failed" << std::endl;
    }
    std::vector<std::string> RawData = ParseImage(InputFile);
    
    int Counter = 0;
    for(int y = 0; y < Height; y++){
      for(int x = 0; x < Width; x++){
        Image[x][y] = atoi(RawData.at(Counter++).c_str());
      }
    }
  }

  void WriteImage(std::string Filename) {
    std::ofstream OutputFile(Filename.substr(0,Filename.size()-4) + "_processed.pgm"); //create output file
    OutputFile << "P2\n" << Width << " " << Height << std::endl << Max << std::endl;

    for(int y = 0; y < Height; y++){
      for(int x = 0; x < Width; x++){
        OutputFile << Image[x][y] << " " << std::endl;
      }
    }

    OutputFile.close();
  }

  void DumpMatrix(std::vector<std::vector<int>>& Matrix) {
    Matrix.clear();
    Matrix.reserve(Width);

    for (int x = 0; x < Width; x++){
      Matrix.push_back(std::vector<int>(Height));
    }
  }

  std::vector<std::string> ParseImage(std::ifstream& InputFile){
    std::vector<std::string> Temp;
    int Counter = 1;
    std::string TempString;
    while(getline(InputFile, TempString)){
      if(TempString[0] == '#') {
        // it's a comment, do nothing
      }else {
        switch(Counter){
          case 1:{
            //we don't care about the first line
            Counter++;
            break;
          }
          case 2: {
            int Space = TempString.find(" ");
            Width = atoi(TempString.substr(0, Space).c_str());
            Height = atoi(TempString.substr(Space + 1).c_str());
            DumpMatrix(Image);
            Counter++;
            break;
          }
          case 3:
            Max = TempString;
            Counter++;
            break;
          default: {
            std::string Val = "";
            for(int i = 0; i < (int)TempString.length(); i++){
              if(IsEmpty(TempString[i])){
                Temp.push_back(Val);
                Val = "";
              } else {
                Val += TempString[i];
              }
            }
            if(Val != "")
              Temp.push_back(Val);
            break;
          }
        }
      }
    }
    return Temp;
  }

  void RotateImage(){
    EnergyMatrix.clear();

    std::swap(Height, Width);

    std::vector<std::vector<int>> Temp = Image;
    DumpMatrix(Image);
    
    for(int y = 0; y < Height; y++){
      for(int x = 0; x < Width; x++){
        Image[x][y] = Temp[y][x];
      }
    }    
    BuildEnergyMatrix();
  }

  //Actual Seam Carving

  int GetEnergy(int x, int y){
    int Current = Image[x][y];
    int Above, Below, Right, Left;

    if(x == 0){
      Left = Current;
    }else{
      Left = Image[x-1][y];
    }

    if(y == 0){
      Above = Current;
    }else{
      Above = Image[x][y-1];
    }

    if(x == Width - 1){
      Right = Current;
    }else{
      Right = Image[x+1][y];
    }

    if(y == Height - 1){
      Below = Current;
    }
    else{
      Below = Image[x][y+1];
    }

    return abs(Current - Above) + abs(Current - Below) +
              abs(Current - Right) + abs(Current - Left);
  }

  void BuildEnergyMatrix() {
    DumpMatrix(EnergyMatrix);
    for(int y = 0; y < Height; y++){
      for(int x = 0; x < Width; x++){
        EnergyMatrix[x][y] = GetEnergy(x,y);
      }
    }
  }

   void BuildCumulative(){
    DumpMatrix(CEnergy); //to get proper sized martix
    for(int y = 0; y < Height; y++){
      for(int x = 0; x < Width; x++){
        if(y == 0){
          CEnergy[x][y] = EnergyMatrix[x][y];
        }
        else{
          int MinPrevNeigh;
          if(x == 0){
            MinPrevNeigh = std::min(CEnergy[x+1][y-1],
              CEnergy[x][y-1]);
          }
          else if(x == (Width - 1))
          {
            MinPrevNeigh = std::min(CEnergy[x-1][y-1],
              CEnergy[x][y-1]);
          }
          else
          {
            MinPrevNeigh = ThreeMin(CEnergy[x-1][y-1],CEnergy[x+1][y-1],CEnergy[x][y-1]);
          }
          CEnergy[x][y] = EnergyMatrix[x][y] + MinPrevNeigh;
        }
      }
    }
  } 

  void MarkSeam(){
    int Pos = 0;
    for(int x = 0; x < Width; x++){
      if(CEnergy[x][Height-1] < CEnergy[Pos][Height-1]){
        Pos = x;   
      }
    }
    Image[Pos][Height-1] = -1;

    for(int Current = Height-1; Current >= 0; Current--){
      int Right = Pos + 1;
      int Center = Pos;
      int Left = Pos - 1;

      if(Right < 0 || Right >= Width){
        Right = Center;
      }

      if(Left < 0 || Left >= Width){
        Left = Center;
      }

      int Min = ThreeMin(CEnergy[Right][Current], CEnergy[Left][Current], CEnergy[Center][Current]);

      if (Min == CEnergy[Left][Current]){
        Pos = Left;
      } 
      else if (Min == CEnergy[Center][Current]){
        Pos = Center;
      }
      else if (Min == CEnergy[Right][Current]){
        Pos = Right;
      }

      Image[Pos][Current] = -1;
    }
  }

  void RemoveSeam() {
    std::vector<int> Temp;

    for(int y = 0; y < Height; y++){
      for(int x = 0; x < Width; x++){
        if(Image[x][y] != -1)
          Temp.push_back(Image[x][y]);
      }
    }

    Width--;
    DumpMatrix(Image);
    
    int Counter = 0;
    for(int y = 0; y < Height; y++){
      for(int x = 0; x < Width; x++){
        Image[x][y] = Temp[Counter++];
      }
    }
  }

  void CarveVerticalSeam() {
    BuildEnergyMatrix();    
    DumpMatrix(CEnergy);  //builds the matrix to the correct size
    BuildCumulative();
    MarkSeam();
    RemoveSeam();
  }

  void Carve(int VerticalSeams, int HorizontalSeams) {
    for (int Counter = 0; Counter < VerticalSeams; Counter++){
      CarveVerticalSeam();      
    }
    
    RotateImage();
    for (int Counter = 0; Counter < HorizontalSeams; Counter++){
      CarveVerticalSeam();      
    }    
    RotateImage(); 
  }

};

int main(int argc, char *argv[]) {
  std::string Filename = argv[1];
  int VerticalSeams = atoi(argv[2]);
  int HorizontalSeams = atoi(argv[3]);
  
  ImageCarver Image(Filename);
  Image.Carve(VerticalSeams, HorizontalSeams);
  Image.WriteImage(Filename);
}
