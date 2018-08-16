/*
 24-783 Advanced Engineerong Computation
 Project: English Subtitle Auto-Generator
 Phoneme class
 Author: Ziang Lu
 */

#ifndef phoneme_h
#define phoneme_h


#include <string>
#include <vector>

using namespace std;

class Phoneme {
private:
  class GMM {
  private:
    int k_;
    int mfcc_dimension_;
    vector<double> weight_vec_;

  public:
    /**
       Default constructor.
     */
    GMM() {
      k_ = 0;
      mfcc_dimension_ = 0;
      weight_vec_.clear();
    }

    /**
       Constructor with parameter.
       @param k vsnvs
       @param mfcc_dimension dimension of MFCC
     */
    GMM(const int k, const int mfcc_dimension,
        const vector<double>& weight_vec) {
      k_ = k;
      mfcc_dimension_ = mfcc_dimension;
      weight_vec_ = weight_vec;
    }
  };

  string my_phoneme_;
  int k_gauss_;
  GMM* my_gmm_;

public:
  Phoneme();
  Phoneme(const int k_gauss, const char phone_file_name[],
          const int mfcc_dimension_);

private:
  /**
     Private helper method to remove the trailing line feed of the given line.
     @param line line to remove trailing line feed
   */
  void RemoveTrailingLineFeed(char line[]) const;
  /**
     Private helper method to parse the given line to a vector of numbers.
     @param line line to parse
     @param nums parsed number containers
   */
  void ParseLine(const char line[], vector<double>& nums) const;

public:
  /**
     Accessor of my_phoneme.
     @return phoneme
   */
  string GetPhoneme() const;
};


#endif /* phoneme_h */
