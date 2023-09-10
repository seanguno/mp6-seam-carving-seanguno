#include "seam_carver.hpp"

// implement the rest of SeamCarver's functions here

// given functions below, DO NOT MODIFY

SeamCarver::SeamCarver(const ImagePPM& image): image_(image) {
  height_ = image.GetHeight();
  width_ = image.GetWidth();
}

void SeamCarver::SetImage(const ImagePPM& image) {
  image_ = image;
  width_ = image.GetWidth();
  height_ = image.GetHeight();
}




// returns the instance's image_
  const ImagePPM& SeamCarver::GetImage() const {
    return image_;
  }

  // returns the image's height
  int SeamCarver::GetHeight() const {
    return height_;
  }

  // returns the image's width
  int SeamCarver::GetWidth() const {
    return width_;
  }
   // returns the energy of the pixel at row col in image_
  int SeamCarver::GetEnergy(int row, int col) const {
    return SeamCarver::DeltaRow(row, col) + SeamCarver::DeltaCol(row, col);
  }

  int SeamCarver::DeltaRow (int row, int col) const {
    int red_squared = SeamCarver::RedRow(row, col) * SeamCarver::RedRow(row, col);
    int green_squared = SeamCarver::GreenRow(row, col) * SeamCarver::GreenRow(row, col);
    int blue_squared = SeamCarver::BlueRow(row, col) * SeamCarver::BlueRow(row, col);
    return red_squared + green_squared + blue_squared;
  }
  int SeamCarver::RedRow(int row, int col) const {
     if (SeamCarver::CheckTop(row)) {
      if (CheckBottom(row)) {
        return image_.ImagePPM::GetPixel(height_ - 1, col).Pixel::GetRed() - image_.ImagePPM::GetPixel(0, col).Pixel::GetRed();
      }
      return image_.ImagePPM::GetPixel(height_ - 1, col).Pixel::GetRed() - image_.ImagePPM::GetPixel(row + 1, col).Pixel::GetRed();
    }
    if (SeamCarver::CheckBottom(row)) {
      return image_.ImagePPM::GetPixel(row - 1, col).Pixel::GetRed() - image_.ImagePPM::GetPixel(0, col).Pixel::GetRed();
    }
    return image_.ImagePPM::GetPixel(row - 1, col).Pixel::GetRed() - image_.ImagePPM::GetPixel(row + 1, col).Pixel::GetRed();
  }
  int SeamCarver::BlueRow(int row, int col) const {
    if (SeamCarver::CheckTop(row)) {
      if (CheckBottom(row)) {
        return image_.ImagePPM::GetPixel(height_ - 1, col).Pixel::GetBlue() - image_.ImagePPM::GetPixel(0, col).Pixel::GetBlue();
      }
      return image_.ImagePPM::GetPixel(height_ - 1, col).Pixel::GetBlue() - image_.ImagePPM::GetPixel(row + 1, col).Pixel::GetBlue();
    }
    if (SeamCarver::CheckBottom(row)) {
      return image_.ImagePPM::GetPixel(row - 1, col).Pixel::GetBlue() - image_.ImagePPM::GetPixel(0, col).Pixel::GetBlue();
    }
    return image_.ImagePPM::GetPixel(row - 1, col).Pixel::GetBlue() - image_.ImagePPM::GetPixel(row + 1, col).Pixel::GetBlue();
  }
  int SeamCarver::GreenRow(int row, int col) const {
    if (SeamCarver::CheckTop(row)) {
      if (CheckBottom(row)) {
        return image_.ImagePPM::GetPixel(height_ - 1, col).Pixel::GetGreen() - image_.ImagePPM::GetPixel(0, col).Pixel::GetGreen();
      }
      return image_.ImagePPM::GetPixel(height_ - 1, col).Pixel::GetGreen() - image_.ImagePPM::GetPixel(row + 1, col).Pixel::GetGreen();
    }
    if (SeamCarver::CheckBottom(row)) {
      return image_.ImagePPM::GetPixel(row - 1, col).Pixel::GetGreen() - image_.ImagePPM::GetPixel(0, col).Pixel::GetGreen();
    }
    return image_.ImagePPM::GetPixel(row - 1, col).Pixel::GetGreen() - image_.ImagePPM::GetPixel(row + 1, col).Pixel::GetGreen();
  }
  int SeamCarver::DeltaCol(int row, int col) const {
     int red_squared = SeamCarver::RedCol(row, col) * SeamCarver::RedCol(row, col);
    int green_squared = SeamCarver::GreenCol(row, col) * SeamCarver::GreenCol(row, col);
    int blue_squared = SeamCarver::BlueCol(row, col) * SeamCarver::BlueCol(row, col);
    return red_squared + green_squared + blue_squared;
  }
  int SeamCarver::RedCol(int row, int col) const {
    if (SeamCarver::CheckLeft(col)) {
      if (CheckRight(col)) {
        return image_.ImagePPM::GetPixel(row, width_ - 1).Pixel::GetRed() - image_.ImagePPM::GetPixel(row, 0).Pixel::GetRed();
      }
      return image_.ImagePPM::GetPixel(row, width_ - 1).Pixel::GetRed() - image_.ImagePPM::GetPixel(row, col + 1).Pixel::GetRed();
    }
    if (SeamCarver::CheckRight(col)) {
      return image_.ImagePPM::GetPixel(row, col - 1).Pixel::GetRed() - image_.ImagePPM::GetPixel(row, 0).Pixel::GetRed();
    }
    return image_.ImagePPM::GetPixel(row, col - 1).Pixel::GetRed() - image_.ImagePPM::GetPixel(row, col + 1).Pixel::GetRed();
  }
  int SeamCarver::BlueCol(int row, int col) const {
    if (SeamCarver::CheckLeft(col)) {
      if (CheckRight(col)) {
        return image_.ImagePPM::GetPixel(row, width_ - 1).Pixel::GetBlue() - image_.ImagePPM::GetPixel(row, 0).Pixel::GetBlue();
      }
      return image_.ImagePPM::GetPixel(row, width_ - 1).Pixel::GetBlue() - image_.ImagePPM::GetPixel(row, col + 1).Pixel::GetBlue();
    }
    if (SeamCarver::CheckRight(col)) {
      return image_.ImagePPM::GetPixel(row, col - 1).Pixel::GetBlue() - image_.ImagePPM::GetPixel(row, 0).Pixel::GetBlue();
    }
    return image_.ImagePPM::GetPixel(row, col - 1).Pixel::GetBlue() - image_.ImagePPM::GetPixel(row, col + 1).Pixel::GetBlue();
  }
  int SeamCarver::GreenCol(int row, int col) const {
    if (SeamCarver::CheckLeft(col)) {
      if (CheckRight(col)) {
        return image_.ImagePPM::GetPixel(row, width_ - 1).Pixel::GetGreen() - image_.ImagePPM::GetPixel(row, 0).Pixel::GetGreen();
      }
      return image_.ImagePPM::GetPixel(row, width_ - 1).Pixel::GetGreen() - image_.ImagePPM::GetPixel(row, col + 1).Pixel::GetGreen();
    }
    if (SeamCarver::CheckRight(col)) {
      return image_.ImagePPM::GetPixel(row, col - 1).Pixel::GetGreen() - image_.ImagePPM::GetPixel(row, 0).Pixel::GetGreen();
    }
    return image_.ImagePPM::GetPixel(row, col - 1).Pixel::GetGreen() - image_.ImagePPM::GetPixel(row, col + 1).Pixel::GetGreen();
  }

  bool SeamCarver::CheckLeft(int col) const {
    return col == 0;
  }
  bool SeamCarver::CheckRight(int col) const {
    return col == width_ - 1;
  }
  bool SeamCarver::CheckTop(int row) const {
    return row == 0;
  }
  bool SeamCarver::CheckBottom(int row) const {
    return row == height_ - 1;
  }

  int SeamCarver::Minimum(int first, int second, int third) const {
    if (third <= second && third <= first) return third;
    if (second <= third && second <= first) return second;
    return first;
  }
  int SeamCarver::Minimum(int first, int second) const {
    if (second <= first) return second;
    return first;
  }

  int SeamCarver::MinIdx(int first, int second) const {
    if (first <= second) return 0;
    return 1;
  }

  int SeamCarver::MinIdx(int first, int second, int third) const {
    if (second <= first && second <= third) return 1;
    if (first <= third && first <= second) return 0;
    return 2;
  }

//need to account for images of one row/col
  void SeamCarver::FillHorSeamArray(int** seam_arr) const {
    // seam_arr = new int*[height_];
    // for (int row = 0; row < height_; row++) {
    //   seam_arr[row] = new int[width_];
    // }
    for (int row = 0; row < height_; row++) {
      seam_arr[row][width_ - 1] = GetEnergy(row, width_ - 1);
    }
    for (int col = width_ - 2; col > -1; col--) {
      for (int row = 0; row < height_; row++) {
        if (row == 0) {
          seam_arr[row][col] = GetEnergy(row, col) + Minimum(seam_arr[row][col + 1], seam_arr[row + 1][col + 1]);
        } else if (row == height_ - 1) {
           seam_arr[row][col] = GetEnergy(row, col) + Minimum(seam_arr[row][col + 1], seam_arr[row - 1][col + 1]);
        } else {
          seam_arr[row][col] = GetEnergy(row, col) + Minimum(seam_arr[row + 1][col + 1], seam_arr[row][col + 1], seam_arr[row - 1][col + 1]);
        }
      }
    }
  }
  void SeamCarver::ClearSeamArray(int** seam_arr) const {
    for (int i = 0; i < height_; i++) {
      delete[] seam_arr[i];
    }
    delete[] seam_arr;
    seam_arr = nullptr;
  }


  void SeamCarver::GetHorizSeamHelper(int** seam_arr, int* seam_arr_single) const {
    int min_val = kMaxInt;
    int min_idx = 0;
    for (int row = 0; row < height_; row++) { 
      if (seam_arr[row][0] < min_val) {
        min_val = seam_arr[row][0];
        min_idx = row;
      }
    }
    seam_arr_single[0] = min_idx;
    for (int col = 1; col < width_; col++) {
      min_val = kMaxInt;
      int row = seam_arr_single[col - 1];
      if (row == 0) {
        if (MinIdx(seam_arr[row][col], seam_arr[row + 1][col]) == 0) min_idx = row;
        else min_idx = row + 1;
      } else if (row == height_ - 1) {
        if (MinIdx(seam_arr[row - 1][col], seam_arr[row][col]) == 0) min_idx = row - 1;
        else min_idx = row;
      } else { 
        if (MinIdx(seam_arr[row - 1][col], seam_arr[row][col], seam_arr[row + 1][col]) == 1) min_idx = row;
        else if (MinIdx(seam_arr[row - 1][col], seam_arr[row][col], seam_arr[row + 1][col]) == 0) min_idx = row - 1;
        else min_idx = row + 1;
      }
      seam_arr_single[col] = min_idx;
    }
  }

  // returns the horizontal seam of image_ with the least amount of
  // energy
  //
  // the ith int in the returned array corresponds to which row at
  // col i is in the seam. example:
  //
  //    | x |   |
  // ---+---+---+---
  //  x |   | x |
  // ---+---+---+---
  //    |   |   | x
  // returns {1, 0, 1, 2}
  int* SeamCarver::GetHorizontalSeam() const {
    int** seam_arr = new int*[height_];
    for (int row = 0; row < height_; row++) {
      seam_arr[row] = new int[width_];
    }
    int* seam_arr_single = new int[width_];
    FillHorSeamArray(seam_arr);
    GetHorizSeamHelper(seam_arr, seam_arr_single);
    ClearSeamArray(seam_arr);
    return seam_arr_single;
  }

  void SeamCarver::FillVertSeamArray(int** seam_arr) const {
    for (int col = 0; col < width_; col++) {
      seam_arr[height_ - 1][col] = GetEnergy(height_ -1 , col);
    }
    for (int row = height_ - 2; row > -1; row--) {
      for (int col = 0; col < width_; col++) {
        if (col == 0) {
          seam_arr[row][col] = GetEnergy(row, col) + Minimum(seam_arr[row + 1][col], seam_arr[row + 1][col + 1]);
        } else if (col == width_ - 1) {
           seam_arr[row][col] = GetEnergy(row, col) + Minimum(seam_arr[row + 1][col], seam_arr[row + 1][col - 1]);
        } else {
          seam_arr[row][col] = GetEnergy(row, col) + Minimum(seam_arr[row + 1][col], seam_arr[row + 1][col + 1], seam_arr[row + 1][col - 1]);
        }
      }
    }
  }

  void SeamCarver::GetVertSeamHelper(int** seam_arr, int* seam_arr_single) const {
    int min_val = kMaxInt;
    int min_idx = 0;
    for (int col = 0; col < width_; col++) { 
      if (seam_arr[0][col] < min_val) {
        min_val = seam_arr[0][col];
        min_idx = col;
      }
    }
    seam_arr_single[0] = min_idx;
    for (int row = 1; row < height_; row++) {
      min_val = kMaxInt;
      int col = seam_arr_single[row - 1];
      if (col == 0) {
        if (MinIdx(seam_arr[row][col], seam_arr[row][col + 1]) == 0) min_idx = col;
        else min_idx = col + 1;
      } else if (col == width_ - 1) {
        if (MinIdx(seam_arr[row][col - 1], seam_arr[row][col]) == 0) min_idx = col - 1;
        else min_idx = col;
      } else { 
        if (MinIdx(seam_arr[row][col - 1], seam_arr[row][col], seam_arr[row][col + 1]) == 1) min_idx = col;
        else if (MinIdx(seam_arr[row][col - 1], seam_arr[row][col], seam_arr[row][col + 1]) == 0) min_idx = col - 1;
        else min_idx = col + 1;
      }
      seam_arr_single[row] = min_idx;
    }
  }

  // returns the vertical seam of image_ with the least amount of
  // energy
  //
  // the ith int in the returned array corresponds to which col at
  // row i is in the seam. example:
  //
  //    | x |   |
  // ---+---+---+---
  //    |   | x |
  // ---+---+---+---
  //    |   | x |
  // returns {1, 2, 2}
  int* SeamCarver::GetVerticalSeam() const {
    int** seam_arr = new int*[height_];
    for (int row = 0; row < height_; row++) {
      seam_arr[row] = new int[width_];
    }
    int* seam_arr_single = new int[height_];
    FillVertSeamArray(seam_arr);
    GetVertSeamHelper(seam_arr, seam_arr_single);
    ClearSeamArray(seam_arr);
    return seam_arr_single;
  }

  // removes one horizontal seam in image_. example:
  //
  // image_ before:
  //  0 | 1 | 2 | 3
  // ---+---+---+---
  //  4 | 5 | 6 | 7
  // ---+---+---+---
  //  8 | 9 | 10| 11
  //
  // seam to remove:
  //    | x |   |
  // ---+---+---+---
  //  x |   | x |
  // ---+---+---+---
  //    |   |   | x
  //
  // image_ after:
  //  0 | 5 | 2 | 3
  // ---+---+---+---
  //  8 | 9 | 10| 7
  void SeamCarver::RemoveHorizontalSeam() {
    int* horiz_seam = GetHorizontalSeam();
    image_.RemoveHoriz(horiz_seam);
    delete[] horiz_seam;
    //have a pointer to result of GetHorizSeam then delete
  }

  // removes one vertical seam in image_. example:
  //
  // image_ before:
  //  0 | 1 | 2 | 3
  // ---+---+---+---
  //  4 | 5 | 6 | 7
  // ---+---+---+---
  //  8 | 9 | 10| 11
  //
  // seam to remove:
  //    | x |   |
  // ---+---+---+---
  //    |   | x |
  // ---+---+---+---
  //    |   | x |
  //
  // image_ after:
  //  0 | 2 | 3
  // ---+---+---
  //  4 | 5 | 7
  // ---+---+---
  //  8 | 9 | 11
  void SeamCarver::RemoveVerticalSeam() {

  }

  /**
   * Add any helper methods you may need
   */

  /**
   * Add any helper methods you may need
   */
