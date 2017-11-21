#include <iostream>
#include "h5reader.h"

#define FILE "dset.h5"

#define COLS 3712

#define ROWS 3712

#define DATASET "/U-MARF/MSG/Level1.5/DATA/Channel 04/IMAGE_DATA"

int main(int argc, char *argv[]) {
  if(argc != 2) {
    std::cout << "USAGE: h5reader <path of file>" << std::endl;
    return 0;
  }

  h5Image *image = new h5Image(argv[1], DATASET, ROWS, COLS);
  image->read();
  return 0;
}
