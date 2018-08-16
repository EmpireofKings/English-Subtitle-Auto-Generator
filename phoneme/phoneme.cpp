#include "phoneme.h"

Phoneme::Phoneme() {
  my_phoneme_ = "";
  k_gauss_ = 0;
  my_gmm_ = new GMM;
}

Phoneme::Phoneme(const int k_gauss, const char phone_filename[],
                 const int mfcc_dimension) {
  k_gauss_ = k_gauss;

  FILE* phone_file_ptr;
  phone_file_ptr = fopen(phone_filename, "r");

  char line[256];
  fgets(line, 255, phone_file_ptr);
  RemoveTrailingLineFeed(line);
  my_phoneme_ = line;

  // Read the weight vector (1 x 12)
  fgets(line, 255, phone_file_ptr);
  vector<double> weight_vec(k_gauss);
  ParseLine(line, weight_vec);

  // Construct the GMM model
  my_gmm_ = new GMM(k_gauss, mfcc_dimension, weight_vec);
}

void Phoneme::RemoveTrailingLineFeed(char line[]) const {
  for (int i = 0; i < strlen(line); ++i) {
    if (line[i] == '\n') {
      line[i] = 0;
      break;
    }
  }
}

void Phoneme::ParseLine(const char line[], vector<double>& nums) const {
  string s = ""; // String used to contain one number
  int num_idx = 0;
  for (int i = 0; i < strlen(line); ++i) {
    if (line[i] != '\t') {
      // Add the current character to the number string
      s += line[i];
    } else {
      // Put the number to the number array
      nums[num_idx] = atof(s.c_str());
      // Clear the number container
      s = "";
      // Increment the number index
      ++num_idx;
    }
  }
  // Put the last number to the number array
  nums[num_idx] = atof(s.c_str());
}

string Phoneme::GetPhoneme() const {
  return my_phoneme_;
}
