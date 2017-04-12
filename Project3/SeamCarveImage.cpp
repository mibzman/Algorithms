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
    BuildEnergyMatrix();
  }

  //Utality Functions

  bool IsEmpty(char val) const {
    return val == ' ' || val == '\t' || val == '\n';
  }

  void ReadImage(std::string const& Filename){
    std::ifstream InputFile;    
    std::vector<std::string> Temp;

    InputFile.open(Filename.c_str());
    if(!InputFile){
      std::cout << "File Parsing Failed" << std::endl;
    }
    ParseImage(Temp, InputFile);
    
    int Counter = 0;
    for(int y = 0; y < Height; y++){
      for(int x = 0; x < Width; x++){
        Image[x][y] = atoi(Temp.at(Counter++).c_str());
      }
    }
  }

  void WriteImage(std::string Filename) {
    std::ofstream OutputFile(Filename.substr(0,Filename.size()-4) + "_processed.pgm"); //create output file

    OutputFile << "P2\n" << Width << " " << Height << std::endl << Max << std::endl;
    for(int y = 0; y < Height; y++)
      for(int x = 0; x < Width; x++)
        OutputFile << Image[x][y] << " " << std::endl;

    OutputFile.close();
  }

  void RebuildImage() {
    std::vector<int> Temp;

    for(int y = 0; y < Height; y++){
      for(int x =0; x < Width; x++){
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

  void DumpMatrix(std::vector<std::vector<int>>& img) {
    img.clear();
    int a = 0;
    img.reserve(Width);   
    while(a++ != Width)
      img.push_back(std::vector<int>(Height));
  }

  void ParseImage(std::vector<std::string>& Temp, std::ifstream& input_file) {
    int steps = 1;
    std::string TempString;
    while(getline(input_file, TempString)){
      if(TempString[0] == '#') {
        continue;
      }
      switch(steps){
        case 1:
          ++steps;
          break;
        case 2: {
          int Space = TempString.find(" ");
          std::string WidthString = TempString.substr(0, Space);
          std::string HeightString = TempString.substr(Space + 1);
          Width = atoi(WidthString.c_str());
          Height = atoi(HeightString.c_str());
          DumpMatrix(Image);
          ++steps;
          break;
        }
        case 3:
          Max = TempString;
          ++steps;
          break;
        default: {
          std::string Val = "";
          int len = TempString.length();
          for(int i=0; i<len; ++i){
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

  void RotateImage() {
    EnergyMatrix.clear();

    int w = Width, h = Height;
    Width = h, Height = w; 

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
    int curPixel = Image[x][y];
    int u, d, r, l;

    l = (x == 0? curPixel: Image[x-1][y]);
    u = (y == 0?  curPixel: Image[x][y-1]);
    r = (x == Width-1? curPixel: Image[x+1][y]);
    d = (y == Height-1? curPixel: Image[x][y+1]);

    return abs(curPixel-u) + abs(curPixel-d) + abs(curPixel-r) + abs(curPixel-l);
  }

  void BuildEnergyMatrix() {
    DumpMatrix(EnergyMatrix);
    for(int y = 0; y < Height; y++){
      for(int x = 0; x < Width; x++){
        EnergyMatrix[x][y] = GetEnergy(x,y);
      }
    }
  }

  int MarkSeam(){    
    int seam = 0;
    for(int i = 0; i < Width; ++i)
      if(CEnergy[i][Height-1] < CEnergy[seam][Height-1])
        seam = i;   
    Image[seam][Height-1] = -1;
    return seam;
  }

  void BuildCumulative(){    
    for(int y = 0; y < Height; y++){
      for(int x = 0; x < Width; x++){
        if(y == 0)
          CEnergy[x][y] = EnergyMatrix[x][y];
        else {
          
          int minimum_neighbor, one, two;
          if(x == 0){
            one = CEnergy[x+1][y-1];
            two = CEnergy[x][y-1];           
          } else if(x == Width - 1){
            one = CEnergy[x-1][y-1];
            two = CEnergy[x][y-1];           
          } else {
            one = std::min(CEnergy[x-1][y-1],CEnergy[x+1][y-1]);
            two = CEnergy[x][y-1];           
          }
          minimum_neighbor = std::min(one, two);
          CEnergy[x][y] = EnergyMatrix[x][y] + minimum_neighbor;
        }
      }
    }
  }

  void RemoveSeam() {
    DumpMatrix(CEnergy);  //builds the matrix to the correct size
    BuildCumulative();
    int seam = MarkSeam();

    for(int i=1; i<Height; ++i){
      int current_height = Height - 1 - i;
      int right = seam + 1, center = seam, left = seam - 1;

      if(right < 0 || right >= Width)
        right = center;
      if(left < 0 || left >= Width)
        left = center;

      int minimum = std::min(std::min(CEnergy[right][current_height],CEnergy[left][current_height]),
        CEnergy[center][current_height]);
       int f = CEnergy[left][current_height], s = CEnergy[center][current_height],
        t = CEnergy[right][current_height];
      seam = (minimum == f? left: minimum == s? center: minimum == t? right: seam);
      Image[seam][current_height] = -1;
    }

    RebuildImage();
  }

  void Carve(int VerticalSeams, int HorizontalSeams) {
    int c = 0;
    while(c++ != VerticalSeams){
      RemoveSeam();
      BuildEnergyMatrix();
    }
    c = 0;
    
    RotateImage();
    while(c++ != HorizontalSeams){
      RemoveSeam();
      BuildEnergyMatrix();
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
